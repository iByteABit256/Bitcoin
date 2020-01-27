#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bitcoin.h"
#define maxWord 40

HTHash Sender;
HTHash Receiver;
//HTHash BTCTable;
HTHash Users;
HTHash Bitcoins;
int transactions = 0;

void Initialize(void){
	Sender = HTCreate();
	Receiver = HTCreate();
//	BTCTable = HTCreate();
	Users = HTCreate();
	Bitcoins = HTCreate();	
}

void createUser(char *userID){
	User user = malloc(sizeof(struct user));
	user->wallet = ListCreate();
	user->userID = malloc(sizeof(char)*maxWord);
	strcpy(user->userID, userID);
	HTInsert(Users, userID, user);
	Listptr se = ListCreate();
	HTInsert(Sender, userID, se);
	Listptr re = ListCreate();
	HTInsert(Receiver, userID, re);
}

void createBitcoin(char *bitcoinID, char *userID, int amount){
	BitcoinPart btc = malloc(sizeof(struct bitcoinpart));
	btc->bitcoinID = malloc(sizeof(char)*maxWord);	
	btc->userID = malloc(sizeof(char)*maxWord);	
	strcpy(btc->bitcoinID, bitcoinID);
	strcpy(btc->userID, userID);
	btc->amount = amount;
	Bitcoin bitcoin = BTcreateTree(1000); 	
	BTinsertRoot(bitcoin, (BTItem)btc);
	HTInsert(Bitcoins, bitcoinID, bitcoin);
	User u = HTGetItem(Users, userID);
	ListInsertLast(u->wallet, BTgetRoot(bitcoin));
}

int getUserAmount(char *userID){
	User u = HTGetItem(Users, userID);
	Wallet w = u->wallet;
	int amount = 0;
	for(w = w->head->next; w != w->tail; w = w->next){
		amount += ((BitcoinPart)((Bitcoin)w->value)->item)->amount;
	}
	return amount;
}

Wallet getWallet(char *userID){
	User u = HTGetItem(Users, userID);
	Wallet w = u->wallet;
	return w;
}

char *getBitcoinID(Bitcoin b){
	return ((BitcoinPart)b->item)->bitcoinID;
}

int getBitcoinAmount(Bitcoin b){
	return ((BitcoinPart)b->item)->amount;
}

char *getUserID(Bitcoin b){
	return ((BitcoinPart)b->item)->userID;
}

BitcoinPart createBitcoinPart(char *bitcoinID, char *userID, int amount){
	BitcoinPart btc = malloc(sizeof(struct bitcoinpart));
	btc->bitcoinID = malloc(sizeof(char)*maxWord);	
	btc->userID = malloc(sizeof(char)*maxWord);	
	strcpy(btc->bitcoinID, bitcoinID);
	strcpy(btc->userID, userID);
	btc->amount = amount;
	return btc;
}

int transfer(char *fromUserID, char *toUserID, int amount){

	if(getUserAmount(fromUserID) < amount) return 0; 

	Transaction tr = malloc(sizeof(struct transaction));
	tr->ID = ++transactions;
	tr->date = time(NULL);
	tr->members = ListCreate();

	Wallet w1 = getWallet(fromUserID);	
	Wallet w2 = getWallet(toUserID);	

	w1 = w1->head->next;
	while(w1 != w1->tail && amount != 0){
		int am = getBitcoinAmount(w1->value);

		if(amount >= am){
			BitcoinPart a = createBitcoinPart(getBitcoinID(w1->value), toUserID, am);
			BitcoinPart b = createBitcoinPart(getBitcoinID(w1->value), fromUserID, 0);
			BTTree node = BTinsertLeft(w1->value, w1->value, a);  
			ListInsertLast(tr->members, node);
			BTinsertRight(w1->value, w1->value, b);  
			ListInsertLast(w1->head, node->right); 
			ListInsertLast(w2->head, node->left); 
			ListDelete(w1->head, w1);
			amount -= am;
		}else{
			BitcoinPart a = createBitcoinPart(getBitcoinID(w1->value), toUserID, amount);
			BitcoinPart b = createBitcoinPart(getBitcoinID(w1->value), fromUserID, am-amount);
			BTTree node = BTinsertLeft(w1->value, w1->value, a);
			ListInsertLast(tr->members, node);
			BTinsertRight(w1->value, w1->value, b);
			ListInsertLast(w2->head, node->left); 
			ListInsertLast(w1->head, node->right); 
			ListDelete(w1->head, w1);
			amount = 0;
		}
		w1 = w1->next;
	}

	Listptr l = HTGetItem(Sender, fromUserID);
	ListInsertLast(l, tr);
	l = HTGetItem(Receiver, toUserID);
	ListInsertLast(l, tr);

	return 1;
}

void printSent(char *userID){
	Listptr l = HTGetItem(Sender, userID);
	for(l = l->head->next; l != l->tail; l = l->next){
		Transaction tr = l->value;
		printf("Transaction %d: ", tr->ID);
		printf("%s ", ctime(&(tr->date)));	
		printf("\t");
		Bitcoin b = ListGetFirst(tr->members)->value;
		printf("Sender: %s | ", getUserID(b->right));
		printf("Receiver: %s | ", getUserID(b->left));
		int amount = 0;
		for(Listptr list = tr->members->head->next; list != list->tail; list = list->next){
			b = list->value;
			amount += getBitcoinAmount(b->left);	
		}
		printf("Amount: %d\n", amount);
	}
}

void printReceived(char *userID){
	Listptr l = HTGetItem(Receiver, userID);
	for(l = l->head->next; l != l->tail; l = l->next){
		Transaction tr = l->value;
		printf("Transaction %d: ", tr->ID);
		printf("%s ", ctime(&(tr->date)));	
		printf("\t");
		Bitcoin b = ListGetFirst(tr->members)->value;
		printf("Sender: %s | ", getUserID(b->right));
		printf("Receiver: %s | ", getUserID(b->left));
		int amount = 0;
		for(Listptr list = ListGetFirst(tr->members); list != list->tail; list = list->next){
			b = list->value;
			amount += getBitcoinAmount(b->left);
		}
		printf("Amount: %d\n", amount);
	}
}

void getLastRow(BTTree tree, Listptr list){
	if(tree->left == NULL && tree->right == NULL){
		ListInsertLast(list, tree);
		return;
	}
	if(tree->left != NULL) getLastRow(tree->left, list);
	if(tree->right != NULL) getLastRow(tree->right, list);
}

void printAmounts(HTHash ht, char *key, HTItem item){
	printf("%s: %d\n", key, (int)item);
}

void printBitcoinOwners(char *bitcoinID){
	Bitcoin b = HTGetItem(Bitcoins, bitcoinID);
	Listptr lastrow = ListCreate();
	getLastRow(b, lastrow);
	HTHash owners = HTCreate();
	for(lastrow = ListGetFirst(lastrow); lastrow != lastrow->tail; lastrow = lastrow->next){
		int amount = getBitcoinAmount(lastrow->value);	
		if(amount){
			amount += (int)HTGetItem(owners, getUserID(lastrow->value));
			HTInsert(owners, getUserID(lastrow->value), (HTItem)amount); 
		}
	}
	printf("%s owners:\n", bitcoinID);
	HTVisit(owners, printAmounts);
	HTDestroy(owners);
}

void printTransaction(BTTree tree, BTNode node){
	if(node->left != NULL){
		printf("%s -> %s %d\n", getUserID(node), getUserID(node->left), getBitcoinAmount(node->left));
	}
}

void printBitcoinHistory(char *bitcoinID){
	Bitcoin b = HTGetItem(Bitcoins, bitcoinID);
	printf("%s history:\n", bitcoinID);
	BTLevelOrder(b, printTransaction);
}

void freeLists(HTHash hash, char *key, HTItem item){
	for(Listptr list = ListGetFirst(item); list != list->tail; list = list->next){
		free(list->value);
	}
	ListDestroy(item);
}

void freeWallets(HTHash hash, char *key, HTItem item){
	User u = item;
	//free(u->userID);
//	for(Listptr list = ListGetFirst(u->wallet); list != list->tail; list = list->next){
//		free(list->value);
//	}
	ListDestroy(u->wallet);
	free(u);
}

void freeBitcoinParts(BTTree tree, BTNode node){
	free(node->item);
}

void freeTrees(HTHash hash, char *key, HTItem item){
	BTInOrder(BTgetRoot(item), freeBitcoinParts);			
	BTDestroy(item);
}

void Terminate(void){
	printf("Terminating...");
	HTVisit(Sender, freeLists);
	HTDestroy(Sender);
	HTDestroy(Receiver);	
	HTVisit(Users, freeWallets);
	HTDestroy(Users);	
	HTVisit(Bitcoins, freeTrees);
	HTDestroy(Bitcoins);	
	printf(" Done\n");
}
