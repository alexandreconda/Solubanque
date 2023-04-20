/*
 * compte.h
 */

#include "transaction.h"

#ifndef MODELE_HEADERS_COMPTE_H_
#define MODELE_HEADERS_COMPTE_H_

typedef struct
{
	int numero;
	char nom[50];
	float solde;
//	Transaction transaction[100];
} Compte;

void afficherCompte(Compte *compte);

void crediter(Compte *compte, int montant);

void debiter(Compte *compte, int montant);

void virer(Compte *compteCrediteur, Compte *compteDebiteur, int montant);

#endif /* MODELE_HEADERS_COMPTE_H_ */
