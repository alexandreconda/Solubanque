#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "headers/banque.h"

Client* getClientByNumero(Banque *banque, int numeroClient)
{
	Client *client = NULL;
	for (int i = 0; i < banque->nbClients; i++) {
		if (banque->clients[i].numero == numeroClient)
		{
			client = &(banque->clients[i]);
		}
	}
	return client;
}

// Méthode pour créer un client dans la banque
void creerClient(Banque *banque, char *nom, char *prenom)
{
    Client client;
    strcpy(client.nom, nom);
    strcpy(client.prenom, prenom);

    // Génération d'un identifiant unique
    int numero;
    srand( time( NULL ) );

    do
    {
    	numero =  (rand() % 99999) + 1;
		for (int i = 0; i < banque->nbClients; i++) {
			// Si le numéro est déjà présent dans la liste des clients,
			// on lui affecte une valeur erronée pour forcer sa régénération.
			if (banque->clients[i].numero == numero)
			{
				numero = -1;
			}
		}
    }
    while (numero < 0);
    client.numero = numero;

    banque->clients[banque->nbClients++] = client;
}

// Méthode pour créer un client dans la banque
void editerClient(Banque *banque, int numeroClient, char *nom, char *prenom)
{
	Client *client = getClientByNumero(banque, numeroClient);
	strcpy(client->nom, nom);
	strcpy(client->prenom, prenom);
}

// Méthode pour supprimer un client de la banque
void supprimerClient(Banque *banque, int numeroClient)
{
    int i;
    int supression = 0;
    for (i = 0; i < banque->nbClients; i++) {
        if (banque->clients[i].numero == numeroClient) {
            // Supprimer le client en décalant les éléments suivants dans le tableau
            for (int j = i; j < banque->nbClients - 1; j++) {
                banque->clients[j] = banque->clients[j + 1];
            }
            banque->nbClients--;
            supression = 1;
            printf("Le client n°%d a été supprimé avec succès\n", numeroClient);
            break;
        }
    }
    if (supression == 0)
    {
    	printf("Le client n°%d n'a pas été trouvé dans la base\n", numeroClient);
    }
}

// Méthode pour afficher l'ensemble des clients de la banque
void afficherClients(Banque *banque)
{
    printf("Liste des clients : \n");
    for (int i = 0; i < banque->nbClients; i++) {
        afficherClient(&banque->clients[i]);
    }
}
