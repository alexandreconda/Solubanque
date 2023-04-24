/*
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers/banque.h"

Banque maBanque;

void terminal_crediter(Compte *compte)
{
	double montant = 0;
	printf("Entrez le montant à créditer : ");
	scanf("%lf", &montant);
	crediter(compte, montant);
}

void terminal_debiter(Compte *compte)
{
	double montant = 0;
	printf("Entrez le montant à débiter : ");
	scanf("%lf", &montant);
	debiter(compte, montant);
}

void terminal_virer(Compte *compte)
{
	char identifiantCompteDebiteur = 0;
	printf("Entrez le numéro du compte destinataire : ");
	scanf("%s", &identifiantCompteDebiteur);
	Compte *compteDebiteur = getCompteByIdentifiant(&maBanque, &identifiantCompteDebiteur);
	if (compteDebiteur)
	{
		double montant = 0;
		printf("Entrez le montant à virer : ");
		scanf("%lf", &montant);
		virer(compte, compteDebiteur , montant);
	}
	else
	{
		printf("Le compte n°%s n'a pas été trouvé\n", &identifiantCompteDebiteur);
	}
}

void terminal_ouvrirCompte(Client *client)
{
	char nomCompte[50];
	printf("Entrez le nom du compte à créer : ");
	scanf("%s", nomCompte);
	ouvrirCompte(client, nomCompte);
}

void terminal_cloturerCompte(Client *client)
{
	char identifiantCompte = 0;
	printf("Entrez l'identifiant du compte à clôturer : ");
	scanf("%s", &identifiantCompte);
	cloturerCompte(client, &identifiantCompte);
}

void terminal_consulterCompte(Client *client)
{
	char identifiantCompte = 0;
	printf("Entrez l'identifiant du compte a consulter : ");
	scanf("%s", &identifiantCompte);
	Compte *compte = getCompteByIdentifiant(&maBanque, &identifiantCompte);
	if (compte)
	{
		int choix = 0;

		do {
			afficherClient(client);
			afficherCompte(compte);
			printf("\n\n");

			printf("\n=== Menu ===\n");
			printf("1. Effectuer un dépôt\n");
			printf("2. Effectuer un retrait\n");
			printf("3. Effectuer un virement\n");
			printf("4. Retour\n");
			printf("Entrez votre choix : ");
			scanf("%d", &choix);

			switch (choix) {
				case 1:
					terminal_crediter(compte);
					break;

				case 2:
					terminal_debiter(compte);
					break;

				case 3:
					terminal_virer(compte);
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
		printf("Le compte n°%s n'a pas été trouvé\n", &identifiantCompte);
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
	char identifiantClient = 0;
	char nomClient[50];
	char prenomClient[50];

	printf("Entrez le numéro du client à éditer : ");
	scanf("%s", &identifiantClient);
	Client *client = getClientByIdentifiant(&maBanque, &identifiantClient);
	if (client)
	{
		afficherClient(client);
		printf("Entrez le nouveau nom du client : ");
		scanf("%s", nomClient);
		printf("Entrez le nouveau prénom du client : ");
		scanf("%s", prenomClient);
		editerClient(&maBanque, &identifiantClient, nomClient, prenomClient);
	}
	else
	{
		printf("Le client n°%s n'a pas été trouvé\n", &identifiantClient);
	}
}

void terminal_supprimerClient()
{
	char identifiantClient = 0;
	printf("Entrez l'identifiant du client a supprimer : ");
	scanf("%s", &identifiantClient);
	supprimerClient(&maBanque, &identifiantClient);
}

void terminal_consulterClient()
{
	char identifiantClient = 0;
	printf("Entrez l'identifiant du client a consulter : ");
	scanf("%s", &identifiantClient);
	Client *client = getClientByIdentifiant(&maBanque, &identifiantClient);
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
		printf("Le client n°%s n'a pas été trouvé\n", &identifiantClient);
	}
}

int main(void)
{
	srand( time( NULL ));

	strcpy(maBanque.nom, "Solubanque");
	strcpy(maBanque.identifiant, "1");
	maBanque.nbClients = 0;

	Client *bernard = creerClient(&maBanque, "Nigon", "Bernard");
	Client *leval   = creerClient(&maBanque, "Leval", "Charles");
	Client *durand  = creerClient(&maBanque, "Durand", "Pierre");

	printf("%p\n%p\n", bernard, &(maBanque.clients[0]));
	printf("%p\n%p\n", leval, &(maBanque.clients[1]));
	printf("%p\n%p\n", durand, &(maBanque.clients[2]));
	ouvrirCompte(bernard, "LivretA");

	ouvrirCompte(leval, "CompteCourant");
	ouvrirCompte(leval, "LivretA");
	ouvrirCompte(leval, "AssuranceVie");

	ouvrirCompte(durand, "PEA");
	ouvrirCompte(durand, "PEL");

	int choix = 0;

	do {
			printf("%s (Banque n°%s) :\n\n-------------------------\n\n", maBanque.nom, maBanque.identifiant);
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

