/*
 * client.h
 */

#include "compte.h"

#ifndef MODELE_HEADERS_CLIENT_H_
#define MODELE_HEADERS_CLIENT_H_

typedef struct
{
	int numero;
	char nom[50];
	char prenom[50];
	Compte comptes[10];
	int nbComptes;
} Client;

void afficherComptes(Client *client);

void afficherClient(Client *client);

void ouvrirCompte(Client *client, char *nom);

void cloturerCompte(Client *client, int numeroCompte);

Compte* getCompteByNumero(Client *client, int numeroCompte);

#endif /* MODELE_HEADERS_CLIENT_H_ */
