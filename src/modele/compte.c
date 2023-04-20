/*
 * compte.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers/compte.h"

void afficherCompte(Compte *compte)
{
	printf("%-6d %-10s %-10.2f€\n", compte->numero, compte->nom, compte->solde);
}

void crediter(Compte *compte, int montant)
{
	if (montant > 0)
	{
		compte->solde += montant;
	}
	else
	{
		printf("Veuillez entrer un montant strictement positif\n");
	}
}

void debiter(Compte *compte, int montant)
{
	if (montant > 0)
	{
		int nouveauSolde = compte->solde - montant;
		if (nouveauSolde >= 0)
		{
			compte->solde = nouveauSolde;
		}
		else
		{
			printf("Débit impossible. Le montant choisi excède le découvert autorisé\n");
		}
	}
	else
	{
		printf("Veuillez entrer un montant strictement positif\n");
	}
}

void virer(Compte *compteCrediteur, Compte *compteDebiteur, int montant)
{
}
