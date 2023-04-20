/*
 * banque.h
 */

#include "client.h"

#ifndef MODELE_HEADERS_BANQUE_H_
#define MODELE_HEADERS_BANQUE_H_

typedef struct
{
	int numero;
	char nom[50];
	Client clients[100];
	int nbClients;
} Banque;

void creerClient(Banque *banque, char *nom, char *prenom);

void editerClient(Banque *banque, int numeroClient, char *nom, char *prenom);

void supprimerClient(Banque *banque, int numeroClient);

void afficherClients(Banque *banque);

Client* getClientByNumero(Banque *banque, int numeroClient);


#endif /* MODELE_HEADERS_BANQUE_H_ */
