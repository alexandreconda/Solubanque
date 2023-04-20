/*
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modele/headers/banque.h"

Banque maBanque;

void terminal_ouvrirCompte(Client *client)
{
	char nomCompte[50];
	printf("Entrez le nom du compte a créer : ");
	scanf("%s", nomCompte);
	ouvrirCompte(client, nomCompte);
}

void terminal_cloturerCompte(Client *client)
{
	int numeroCompte = 0;
	printf("Entrez le numero du compte a clôturer : ");
	scanf("%d", &numeroCompte);
	cloturerCompte(client, numeroCompte);
}

void terminal_consulterCompte(Client *client)
{
	int numeroCompte = 0;
	printf("Entrez le numero du compte a consulter : ");
	scanf("%d", &numeroCompte);
	Compte *compte = getCompteByNumero(client, numeroCompte);
	if (compte)
	{
		afficherCompte(compte);
		printf("\n\n");
	}
	else
	{
		printf("Le compte n°%d n'a pas été trouvé\n", numeroCompte);
	}
}

void terminal_creerClient()
{
	char nomClient[50];
	char prenomClient[50];
	printf("Entrez le nom du client a créer : ");
	scanf("%s", nomClient);
	printf("Entrez le prénom du client a créer : ");
	scanf("%s", prenomClient);
	creerClient(&maBanque, nomClient, prenomClient);
}

void terminal_editerClient()
{
	int numeroClient = 0;
	char nomClient[50];
	char prenomClient[50];

	printf("Entrez le numéro du client à éditer : ");
	scanf("%d", &numeroClient);
	Client *client = getClientByNumero(&maBanque, numeroClient);
	if (client)
	{
		afficherClient(client);
		printf("Entrez le nouveau nom du client : ");
		scanf("%s", nomClient);
		printf("Entrez le nouveau prénom du client : ");
		scanf("%s", prenomClient);
		editerClient(&maBanque, numeroClient, nomClient, prenomClient);
	}
	else
	{
		printf("Le client n°%d n'a pas été trouvé\n", numeroClient);
	}
}

void terminal_supprimerClient()
{
	int numeroClient = 0;
	printf("Entrez le numero du client a supprimer : ");
	scanf("%d", &numeroClient);
	supprimerClient(&maBanque, numeroClient);
}

void terminal_consulterClient()
{
	int numeroClient = 0;
	printf("Entrez le numero du client a consulter : ");
	scanf("%d", &numeroClient);
	Client *client = getClientByNumero(&maBanque, numeroClient);
	if (client)
	{
		int choix = 0;

		do {
			afficherClient(client);
			afficherComptes(client);
				printf("\n=== Menu ===\n");
				printf("1. Ouvrir un compte\n");
				printf("2. Clotûrer un compte\n");
				printf("3. Consulter un compte\n");
				printf("4. Retour\n");
				printf("Entrez votre choix : ");
				scanf("%d", &choix);

				switch (choix) {
					case 1:
						terminal_ouvrirCompte(client);
						break;

					case 2:
						terminal_cloturerCompte(client);
						break;

					case 3:
						terminal_consulterCompte(client);
						break;

					case 4:
						break;

					default:
						printf("Choix invalide.\n");
						break;
				}
				printf("\n\n");
			} while (choix != 4);
	}
	else
	{
		printf("Le client n°%d n'a pas été trouvé\n", numeroClient);
	}
}

int main(void)
{

	strcpy(maBanque.nom, "Solubanque");
	maBanque.numero = 1;
	maBanque.nbClients = 0;

	creerClient(&maBanque, "Bernard", "Alice");
	creerClient(&maBanque, "Leval", "Bob");
	creerClient(&maBanque, "Durand", "Charlie");

	int choix = 0;

	do {
			printf("%s (Banque n°%d) :\n\n-------------------------\n\n", maBanque.nom, maBanque.numero);
			afficherClients(&maBanque);

	        printf("\n=== Menu ===\n");
	        printf("1. Creer un dossier client\n");
	        printf("2. Editer un dossier client\n");
	        printf("3. Supprimer un dossier client\n");
	        printf("4. Consulter un dossier client\n");
	        printf("5. Quitter\n");
	        printf("Entrez votre choix : ");
	        scanf("%d", &choix);

	        switch (choix) {
	            case 1:
	            	terminal_creerClient();
	                break;

	            case 2:
	            	terminal_editerClient();
	                break;

	            case 3:
	            	terminal_supprimerClient();
	                break;

	            case 4:
	            	terminal_consulterClient();
	                break;

	            case 5:
	                printf("Au revoir !\n");
	                break;

	            default:
	                printf("Choix invalide.\n");
	                break;
	        }
	        printf("\n\n");
	    } while (choix != 5);

	return EXIT_SUCCESS;
}

