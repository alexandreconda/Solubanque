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
	printf("%-10s %-10s %10.2f€\n", compte->identifiant, compte->nom, compte->solde);
}

void afficherTransactions(Compte *compte)
{
	printf("Liste des transactions : \n");
	for (int i = 0; i < compte->nbTransactions; i++) {
		afficherTransaction(&compte->transactions[i]);
	}
}

Transaction* creerTransaction(char *libelle, double montant, Compte *debiteur, Compte *crediteur)
{
	toolsLog("Début creerTransaction");
	Transaction transaction;
	strcpy(transaction.libelle, libelle);
	transaction.montant = montant;
	toolsLog("Test");
	strcpy(transaction.identifiantDebiteur, debiteur ? debiteur->identifiant : "0");
	strcpy(transaction.identifiantCrediteur, crediteur ? crediteur->identifiant : "0");
	// Génération d'un identifiant unique
	genererIdentifiantUnique(transaction.identifiant);

	if (debiteur)
	{
		debiteur->transactions[debiteur->nbTransactions] = transaction;
		debiteur->nbTransactions ++;
	}


	if (crediteur)
	{
		crediteur->transactions[crediteur->nbTransactions] = transaction;
		crediteur->nbTransactions ++;
	}

	enregistrerTransaction(&(transaction));
	return debiteur ? &(debiteur->transactions[debiteur->nbTransactions-1]) : &(crediteur->transactions[crediteur->nbTransactions-1]);

}

void crediter(Compte *compte, double montant)
{
	if (montant > 0)
	{
		compte->solde += montant;
		enregistrerCompte(compte);
		creerTransaction("crédit", montant, compte, NULL);
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
			creerTransaction("débit", montant, NULL, compte);
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
			creerTransaction("virement", montant, compteDebiteur, compteCrediteur);
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
