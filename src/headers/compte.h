/*
 * compte.h
 */

#include "transaction.h"

#ifndef MODELE_HEADERS_COMPTE_H_
#define MODELE_HEADERS_COMPTE_H_

typedef struct
{
	char identifiant[65];
	char nom[50];
	double solde;
	char identifiantClient[65];
//	Transaction transaction[100];
} Compte;

void afficherCompte(Compte *compte);

void crediter(Compte *compte, double montant);

void debiter(Compte *compte, double montant);

void virer(Compte *compteCrediteur, Compte *compteDebiteur, double montant);

#endif /* MODELE_HEADERS_COMPTE_H_ */
