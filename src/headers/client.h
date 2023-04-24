/*
 * client.h
 */

#include "compte.h"

#ifndef MODELE_HEADERS_CLIENT_H_
#define MODELE_HEADERS_CLIENT_H_

typedef struct
{
	char identifiant[65];
	char nom[50];
	char prenom[50];
	Compte comptes[10];
	int nbComptes;
	char identifiantBanque[65];
} Client;

void afficherComptes(Client *client);

void afficherClient(Client *client);

Compte* ouvrirCompte(Client *client, char *nom);

void cloturerCompte(Client *client, char *numeroCompte);

#endif /* MODELE_HEADERS_CLIENT_H_ */
