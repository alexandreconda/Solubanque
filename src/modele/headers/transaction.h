/*
 * transaction.h
 */

#ifndef MODELE_HEADERS_TRANSACTION_H_
#define MODELE_HEADERS_TRANSACTION_H_

typedef struct
{
	int numero;
	int montant;
	char libelle[100];
	int crediteur; // Numéro client du créditeur éventuel
	int debiteur; // Numéro client du débiteur éventuel
} Transaction;

#endif /* MODELE_HEADERS_TRANSACTION_H_ */
