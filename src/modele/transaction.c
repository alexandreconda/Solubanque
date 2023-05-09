/*
 * transaction.c
 */

#include "../headers/transaction.h"
#include "../headers/tools.h"

void enregistrerTransaction(Transaction *transaction)
{
	char montantToString[50];
	sprintf(montantToString, "%f", transaction->montant);
	char *nomColonnes[] = {"libelle", "montant", "identifiantcrediteur", "identifiantdebiteur"};
	char *valeurColonnes[] = {transaction->libelle, montantToString, transaction->identifiantCrediteur, transaction->identifiantDebiteur};
	enregistrerGenerique("transaction", transaction->identifiant, nomColonnes, valeurColonnes, 4);
}

void afficherTransaction(Transaction *transaction)
{
	printf("%-10s %-10s %10.2f€ %-10s %-10s\n", transaction->identifiant, transaction->libelle, transaction->montant, transaction->identifiantCrediteur, transaction->identifiantDebiteur);
}
