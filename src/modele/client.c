/*
 * client.c
 */

#include "../headers/client.h"
#include "../headers/tools.h"

void enregistrerClient(Client *client)
{
	char *nomColonnes[] = {"nom", "prenom", "identifiantbanque"};
	char *valeurColonnes[] = {client->nom,client->prenom,client->identifiantBanque};
	enregistrerGenerique("client", client->identifiant, nomColonnes, valeurColonnes, 3);
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
	printf("%-10s %-10s %-10s\n", client->identifiant, client->nom, client->prenom);
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
	enregistrerCompte(&(client->comptes[client->nbComptes-1]));
	return &(client->comptes[client->nbComptes-1]);
}

void cloturerCompte(Client *client, char *identifiantCompte)
{
    int i;
    int supression = 0;
    for (i = 0; i < client->nbComptes; i++) {
        if (!strcmp(client->comptes[i].identifiant, identifiantCompte)) {
            // Supprimer le compte en décalant les éléments suivants dans le tableau
            for (int j = i; j < client->nbComptes - 1; j++) {
                client->comptes[j] = client->comptes[j + 1];
            }
            client->nbComptes--;
            enregistrerGenerique("compte", identifiantCompte, NULL, NULL, 0);
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
