#include "bitcoinTypes.h"
void Initialize(void);
void createUser(char *);
void createBitcoin(char *, char *, int);
int getUserAmount(char *);
int transfer(char *, char *, int);
void printSent(char *);
void printReceived(char *);
void printBitcoinOwners(char *);
void printBitcoinHistory(char *);
void Terminate(void);
