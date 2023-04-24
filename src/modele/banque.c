#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/banque.h"
#include "../headers/tools.h"

Client* getClientByIdentifiant(Banque *banque, char *identifiantClient)
{
	Client *client = NULL;
	for (int i = 0; i < banque->nbClients; i++) {
		if (!strcmp(banque->clients[i].identifiant,identifiantClient))
		{
			client = &(banque->clients[i]);
		}
	}
	return client;
}

Compte* getCompteByIdentifiant(Banque *banque, char *identifiantCompte)
{
	Compte *compte = NULL;
	Client *client = NULL;
	for (int i = 0 ; i < banque->nbClients ; i++)
	{
		client = &(banque->clients[i]);
		for (int j = 0; j < client->nbComptes; j++) {
			if (!strcmp(client->comptes[j].identifiant, identifiantCompte))
			{
				compte = &(client->comptes[j]);
			}
		}
	}
	return compte;
}

Client* creerClient(Banque *banque, char *nom, char *prenom)
{
    Client client;
    strcpy(client.nom, nom);
    strcpy(client.prenom, prenom);
    client.nbComptes = 0;
    strcpy(client.identifiantBanque, banque->identifiant);

    // Génération d'un identifiant unique
    genererIdentifiantUnique(client.identifiant);

    banque->clients[banque->nbClients] = client;
    banque->nbClients ++;
    return &(banque->clients[banque->nbClients-1]);
}

void editerClient(Banque *banque, char *identifiantClient, char *nom, char *prenom)
{
	Client *client = getClientByIdentifiant(banque, identifiantClient);
	strcpy(client->nom, nom);
	strcpy(client->prenom, prenom);
}

void supprimerClient(Banque *banque, char *identifiantClient)
{
    int i;
    int supression = 0;
    for (i = 0; i < banque->nbClients; i++) {
        if (banque->clients[i].identifiant == identifiantClient) {
            // Supprimer le client en décalant les éléments suivants dans le tableau
            for (int j = i; j < banque->nbClients - 1; j++) {
                banque->clients[j] = banque->clients[j + 1];
            }
            banque->nbClients--;
            supression = 1;
            printf("Le client n°%s a été supprimé avec succès\n", identifiantClient);
            break;
        }
    }
    if (supression == 0)
    {
    	printf("Le client n°%s n'a pas été trouvé dans la base\n", identifiantClient);
    }
}

void afficherClients(Banque *banque)
{
    printf("Liste des clients : \n");
    for (int i = 0; i < banque->nbClients; i++) {
        afficherClient(&banque->clients[i]);
    }
}
