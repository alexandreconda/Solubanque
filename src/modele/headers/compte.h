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
	int solde;
//	Transaction transaction[100];
	int titulaire; // Numéro client du titulaire du compte
} Compte;


#endif /* MODELE_HEADERS_COMPTE_H_ */
