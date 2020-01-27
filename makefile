OBJ = lists.o hashtable.o main.o bitcoin.o btreestr.o queue.o
LIST_DIR = "../lists/"
HT_DIR = "../hashtable/"
BT_DIR = "../btree/"
BTC_DIR = "../bitcoin/"
Q_DIR = "../queue/"
FL = -I $(LIST_DIR) -I $(HT_DIR) -I $(BT_DIR) -I $(BTC_DIR) 
DBG = -ggdb3

default: $(OBJ)
	gcc -o main $(OBJ) $(DBG)

main.o: main.c
	gcc -c main.c $(FL) $(DBG)

lists.o: ../lists/lists.c
	gcc -c ../lists/lists.c $(DBG)

hashtable.o: ../hashtable/hashtable.c
	gcc -c ../hashtable/hashtable.c -I $(LIST_DIR) $(DBG)

btreestr.o: ../btree/btreestr.c
	gcc -c ../btree/btreestr.c $(DBG) -I $(Q_DIR)

queue.o: ../queue/queue.c
	gcc -c ../queue/queue.c $(DBG)

bitcoin.o: ../bitcoin/bitcoin.c
	gcc -c ../bitcoin/bitcoin.c $(FL) $(DBG)

clean:
	rm *.o main
