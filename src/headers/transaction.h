/*
 * transaction.h
 */

#include <time.h>

#ifndef MODELE_HEADERS_TRANSACTION_H_
#define MODELE_HEADERS_TRANSACTION_H_

typedef struct
{
	char identifiant[65];
	char libelle[10];
	double montant;
	time_t dateOperation; // Exprimé en UTC
	char identifiantCrediteur[65]; // Numéro compte du créditeur éventue
	char identifiantDebiteur[65]; // Numéro compte du débiteur éventuel
} Transaction;

void enregistrerTransaction(Transaction *transaction);

void afficherTransaction(Transaction *transaction);

#endif /* MODELE_HEADERS_TRANSACTION_H_ */
