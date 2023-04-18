/*
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modele/headers/banque.h"

Banque maBanque;

void ouvrirCompte()
{

}

void cloturerCompte()
{

}

void consulterCompte()
{

}

void creerDossier()
{
	char nomClient[50];
	char prenomClient[50];
	printf("Entrez le nom du client a créer : ");
	scanf("%s", nomClient);
	printf("Entrez le prénom du client a créer : ");
	scanf("%s", prenomClient);
	creerClient(&maBanque, nomClient, prenomClient);
}

void editerDossier()
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

void supprimerDossier()
{
	int numeroClient = 0;
	printf("Entrez le numero du client a supprimer : ");
	scanf("%d", &numeroClient);
	supprimerClient(&maBanque, numeroClient);
}

void consulterDossier()
{
	int numeroClient = 0;
	printf("Entrez le numero du client a consulter : ");
	scanf("%d", &numeroClient);
	Client *client = getClientByNumero(&maBanque, numeroClient);
	if (client)
	{
		afficherClient(client);
		int choix = 0;

		do {

				printf("\n=== Menu ===\n");
				printf("1. Ouvrir un compte\n");
				printf("2. Clotûrer un compte\n");
				printf("3. Consulter un compte\n");
				printf("4. Retour\n");
				printf("Entrez votre choix : ");
				scanf("%d", &choix);

				switch (choix) {
					case 1:
						ouvrirCompte();
						break;

					case 2:
						cloturerCompte();
						break;

					case 3:
						consulterCompte();
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
	            	creerDossier();
	                break;

	            case 2:
	            	editerDossier();
	                break;

	            case 3:
	                supprimerDossier();
	                break;

	            case 4:
	                consulterDossier();
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

