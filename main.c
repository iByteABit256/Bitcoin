#include <stdio.h>
#include <stdlib.h>
#include "bitcoin.h"

int main(void){
	Initialize();
	createUser("C3P0");
	createUser("R2D2");
	createBitcoin("Dogecoin", "C3P0", 540);
	createBitcoin("Rupee", "R2D2", 320);
	printf("C3P0 has %d$\n", getUserAmount("C3P0"));
	printf("R2D2 has %d$\n\n", getUserAmount("R2D2"));

	printBitcoinOwners("Dogecoin");
	printBitcoinOwners("Rupee");
	printf("\n");

	transfer("C3P0", "R2D2", 120);
	printf("C3P0 has %d$\n", getUserAmount("C3P0"));
	printf("R2D2 has %d$\n\n", getUserAmount("R2D2"));

	printBitcoinOwners("Dogecoin");
	printBitcoinOwners("Rupee");
	printf("\n");

	transfer("C3P0", "R2D2", 440);
	printf("C3P0 has %d$\n", getUserAmount("C3P0"));
	printf("R2D2 has %d$\n\n", getUserAmount("R2D2"));

	printBitcoinOwners("Dogecoin");
	printBitcoinOwners("Rupee");
	printf("\n");

	transfer("C3P0", "R2D2", 420);
	printf("C3P0 has %d$\n", getUserAmount("C3P0"));
	printf("R2D2 has %d$\n\n", getUserAmount("R2D2"));

	printBitcoinOwners("Dogecoin");
	printBitcoinOwners("Rupee");
	printf("\n");

	transfer("R2D2", "C3P0", 70);
	printf("C3P0 has %d$\n", getUserAmount("C3P0"));
	printf("R2D2 has %d$\n\n", getUserAmount("R2D2"));

	printBitcoinOwners("Dogecoin");
	printBitcoinOwners("Rupee");
	printf("\n");

	transfer("R2D2", "C3P0", 791);
	printf("C3P0 has %d$\n", getUserAmount("C3P0"));
	printf("R2D2 has %d$\n\n", getUserAmount("R2D2"));

	printBitcoinOwners("Dogecoin");
	printBitcoinOwners("Rupee");
	printf("\n");

	transfer("R2D2", "C3P0", 790);
	printf("C3P0 has %d$\n", getUserAmount("C3P0"));
	printf("R2D2 has %d$\n\n", getUserAmount("R2D2"));

	printBitcoinOwners("Dogecoin");
	printBitcoinOwners("Rupee");
	printf("\n");

	printf("\n\n");
	printf("Printing C3P0's sent:\n");
	printSent("C3P0");
	printf("\n");
	printf("Printing R2D2's sent:\n");
	printSent("R2D2");
	printf("\n\n");
	printf("Printing C3P0's received:\n");
	printReceived("C3P0");
	printf("\n");
	printf("Printing R2D2's received:\n");
	printReceived("R2D2");
	printf("\n\n");
	printBitcoinOwners("Dogecoin");
	printf("\n");
	printBitcoinOwners("Rupee");
	printf("\n");
	printBitcoinHistory("Dogecoin");
	printBitcoinHistory("Rupee");
	printf("\n");
	Terminate();
	return 0;
}
