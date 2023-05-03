/*
 * compte.c
 */

#include "../headers/compte.h"
#include "../headers/tools.h"

void enregistrerCompte(Compte *compte)
{
	char soldeToString[50];
	sprintf(soldeToString, "%f", compte->solde);
	char *nomColonnes[] = {"nom", "solde", "identifiantclient"};
	char *valeurColonnes[] = {compte->nom,soldeToString,compte->identifiantClient};
	enregistrerGenerique("compte", compte->identifiant, nomColonnes, valeurColonnes, 3);
}

void afficherCompte(Compte *compte)
{
	printf("%-10s %-10s %-10.2f€\n", compte->identifiant, compte->nom, compte->solde);
}

void crediter(Compte *compte, double montant)
{
	if (montant > 0)
	{
		compte->solde += montant;
		enregistrerCompte(compte);
	}
	else
	{
		printf("Veuillez entrer un montant strictement positif\n");
	}
}

void debiter(Compte *compte, double montant)
{
	if (montant > 0)
	{
		double nouveauSolde = compte->solde - montant;
		if (nouveauSolde >= 0)
		{
			compte->solde = nouveauSolde;
			enregistrerCompte(compte);
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

void virer(Compte *compteCrediteur, Compte *compteDebiteur, double montant)
{
	if (montant > 0)
	{
		if (compteCrediteur->solde >= montant)
		{
			compteCrediteur->solde -= montant;
			compteDebiteur->solde += montant;
			enregistrerCompte(compteCrediteur);
			enregistrerCompte(compteDebiteur);
			printf("Transfert effectué avec succès !\n");
		}
		else
		{
			printf("Le compte débiteur ne possède pas assez de fonds pour effectuer le transfert\n");
		}
	}
	else
	{
		printf("Veuillez entrer un montant strictement positif\n");
	}
}
