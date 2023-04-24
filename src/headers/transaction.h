/*
 * transaction.h
 */

#ifndef MODELE_HEADERS_TRANSACTION_H_
#define MODELE_HEADERS_TRANSACTION_H_

typedef struct
{
	char identifiant[65];
	int montant;
	char libelle[100];
	char crediteur[65]; // Numéro client du créditeur éventuel
	char debiteur[65]; // Numéro client du débiteur éventuel
} Transaction;

#endif /* MODELE_HEADERS_TRANSACTION_H_ */
