/*
 * client.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers/client.h"

Compte* getCompteByNumero(Client *client, int numeroCompte)
{
	Compte *compte = NULL;
	for (int i = 0; i < client->nbComptes; i++) {
		if (client->comptes[i].numero == numeroCompte)
		{
			compte = &(client->comptes[i]);
		}
	}
	return compte;
}

void afficherComptes(Client *client)
{
	printf("Liste des comptes : \n");
	for (int i = 0; i < client->nbComptes; i++) {
		afficherCompte(&client->comptes[i]);
	}
}

void afficherClient(Client *client)
{
	printf("%-6d %-10s %-10s\n", client->numero, client->nom, client->prenom);
}

void ouvrirCompte(Client *client, char *nom)
{
	Compte compte;
	strcpy(compte.nom, nom);
	compte.solde = 0.0;

	// Génération d'un identifiant unique
	int numero;
	srand( time( NULL ) );

	do
	{
		numero =  (rand() % 99999) + 1;
		for (int i = 0; i < client->nbComptes; i++) {
			// Si le numéro est déjà présent dans la liste des comptes,
			// on lui affecte une valeur erronée pour forcer sa régénération.
			if (client->comptes[i].numero == numero)
			{
				numero = -1;
			}
		}
	}
	while (numero < 0);
	compte.numero = numero;

	client->comptes[client->nbComptes++] = compte;
}

void cloturerCompte(Client *client, int numeroCompte)
{
    int i;
    int supression = 0;
    for (i = 0; i < client->nbComptes; i++) {
        if (client->comptes[i].numero == numeroCompte) {
            // Supprimer le compte en décalant les éléments suivants dans le tableau
            for (int j = i; j < client->nbComptes - 1; j++) {
                client->comptes[j] = client->comptes[j + 1];
            }
            client->nbComptes--;
            supression = 1;
            printf("Le compte n°%d a été supprimé avec succès\n", numeroCompte);
            break;
        }
    }
    if (supression == 0)
    {
    	printf("Le compte n°%d n'a pas été trouvé dans la base\n", numeroCompte);
    }
}
