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
//	Compte comptes[10];
//	int banque; // Numéro de la banque à laquelle est rattaché le client
} Client;

// Méthode pour afficher les informations d'un client
void afficherClient(Client *client);

#endif /* MODELE_HEADERS_CLIENT_H_ */
