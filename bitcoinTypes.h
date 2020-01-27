#include "lists.h"
#include "btreeInterface.h"
#include "htInterface.h"

struct bitcoinpart{
	char *userID;
	char *bitcoinID;
	int amount;
};

typedef struct bitcoinpart *BitcoinPart;

typedef BTTree Bitcoin;

typedef Listptr Wallet;

struct transaction{
	int ID;
	long date;
	Listptr members;
};

typedef struct transaction *Transaction;

struct user{
	char *userID;
	Wallet wallet;
};

typedef struct user *User;
