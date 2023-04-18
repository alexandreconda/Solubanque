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

// Méthode pour créer un client dans la banque
void creerClient(Banque *banque, char *nom, char *prenom);

// Méthode pour supprimer un client de la banque
void supprimerClient(Banque *banque, int numeroClient);

// Méthode pour afficher l'ensemble des clients de la banque
void afficherClients(Banque *banque);

Client* getClientByNumero(Banque *banque, int numeroClient);


#endif /* MODELE_HEADERS_BANQUE_H_ */
