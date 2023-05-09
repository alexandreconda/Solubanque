/*
 * transaction.c
 */

#include "../headers/transaction.h"
#include "../headers/tools.h"

void enregistrerTransaction(Transaction *transaction)
{
	char montantToString[50];
	sprintf(montantToString, "%f", transaction->montant);

	char dateOperation[128];
	const struct tm *tmp;
	tmp = gmtime(&(transaction->dateOperation));
	strftime(dateOperation, sizeof(dateOperation), "%a %b %d %T %Y", tmp);

	char *nomColonnes[] = {"libelle", "dateoperation", "montant", "identifiantcrediteur", "identifiantdebiteur"};
	char *valeurColonnes[] = {transaction->libelle, dateOperation, montantToString, transaction->identifiantCrediteur, transaction->identifiantDebiteur};
	enregistrerGenerique("transaction", transaction->identifiant, nomColonnes, valeurColonnes, 5);
}

void afficherTransaction(Transaction *transaction)
{
	char dateOperation[128];
	const struct tm *tmp;
	tmp = localtime(&(transaction->dateOperation));
	strftime(dateOperation, sizeof(dateOperation), "%d %b %Y (%T)", tmp);

	printf("%-10s %-30s %-50s %-22.2f %-10s %-10s\n", transaction->identifiant, dateOperation, transaction->libelle, transaction->montant, transaction->identifiantCrediteur, transaction->identifiantDebiteur);
}
