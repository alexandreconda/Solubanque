/*
 * banque.h
 */

#include "client.h"

#ifndef MODELE_HEADERS_BANQUE_H_
#define MODELE_HEADERS_BANQUE_H_

typedef struct
{
	char identifiant[65];
	char nom[50];
	Client clients[10];
	int nbClients;
} Banque;

Client* creerClient(Banque *banque, char *nom, char *prenom);

void editerClient(Banque *banque, char *identifiantClient, char *nom, char *prenom);

void supprimerClient(Banque *banque, char *identifiantClient);

void afficherClients(Banque *banque);

Client* getClientByIdentifiant(Banque *banque, char *identifiantClient);

Compte* getCompteByIdentifiant(Banque *banque, char *identifiantCompte);

void enregistrerBanque(Banque *banque);


#endif /* MODELE_HEADERS_BANQUE_H_ */
