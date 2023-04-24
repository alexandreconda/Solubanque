/*
 * client.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/client.h"
#include "../headers/tools.h"

void afficherComptes(Client *client)
{
	printf("Liste des comptes : \n");
	for (int i = 0; i < client->nbComptes; i++) {
		afficherCompte(&client->comptes[i]);
	}
}

void afficherClient(Client *client)
{
	printf("%-10s %-10s %-10s\n", client->identifiant, client->nom, client->prenom);
	printf("Nb comptes : %d\n", client->nbComptes);
}

Compte* ouvrirCompte(Client *client, char *nom)
{
	Compte compte;
	strcpy(compte.nom, nom);
	compte.solde = 0.0;
	strcpy(compte.identifiantClient, client->identifiant);

	// Génération d'un identifiant unique
	genererIdentifiantUnique(compte.identifiant);

	client->comptes[client->nbComptes] = compte;
	client->nbComptes ++;
	return &(client->comptes[client->nbComptes-1]);
}

void cloturerCompte(Client *client, char *identifiantCompte)
{
    int i;
    int supression = 0;
    for (i = 0; i < client->nbComptes; i++) {
        if (client->comptes[i].identifiant == identifiantCompte) {
            // Supprimer le compte en décalant les éléments suivants dans le tableau
            for (int j = i; j < client->nbComptes - 1; j++) {
                client->comptes[j] = client->comptes[j + 1];
            }
            client->nbComptes--;
            supression = 1;
            printf("Le compte n°%s a été supprimé avec succès\n", identifiantCompte);
            break;
        }
    }
    if (supression == 0)
    {
    	printf("Le compte n°%s n'a pas été trouvé dans la base\n", identifiantCompte);
    }
}
