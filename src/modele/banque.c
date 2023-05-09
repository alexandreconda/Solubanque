#include "../headers/banque.h"
#include "../headers/tools.h"

void enregistrerBanque(Banque *banque)
{
	// Connexion à la base de données
	PGconn *conn = PQconnectdb("user=user password=user dbname=solubanque host=localhost port=5432");
	if (PQstatus(conn) != CONNECTION_OK) {
		fprintf(stderr, "Connexion à la base de données a échoué : %s", PQerrorMessage(conn));
		PQfinish(conn);
		exit(1);
	}

	// Vérifier si l'identifiant de la banque existe déjà dans la base de données
	char query[MAX_QUERY_SIZE];
	snprintf(query, MAX_QUERY_SIZE, "SELECT COUNT(*) FROM banque WHERE identifiant='%s'", banque->identifiant);
	PGresult *res = PQexec(conn, query);
	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		fprintf(stderr, "Échec de la requête : %s", PQerrorMessage(conn));
		PQclear(res);
		PQfinish(conn);
		exit(1);
	}

	// Obtenir le nombre de lignes renvoyées par la requête
	int nbRows = atoi(PQgetvalue(res, 0, 0));
	PQclear(res);

	if (nbRows == 0) {
		// L'identifiant de la banque n'existe pas dans la base de données, donc nous devons insérer une nouvelle ligne
		snprintf(query, MAX_QUERY_SIZE, "INSERT INTO banque (identifiant, nom) VALUES ('%s', '%s')",
				 banque->identifiant, banque->nom);
		res = PQexec(conn, query);
		if (PQresultStatus(res) != PGRES_COMMAND_OK) {
			fprintf(stderr, "Échec de l'insertion : %s", PQerrorMessage(conn));
			PQclear(res);
			PQfinish(conn);
			exit(1);
		}
	} else {
		// L'identifiant de la banque existe déjà dans la base de données, donc nous devons mettre à jour la ligne correspondante
		snprintf(query, MAX_QUERY_SIZE, "UPDATE banque SET nom='%s' WHERE identifiant='%s'",
				 banque->nom, banque->identifiant);
		res = PQexec(conn, query);
		if (PQresultStatus(res) != PGRES_COMMAND_OK) {
			fprintf(stderr, "Échec de la mise à jour : %s", PQerrorMessage(conn));
			PQclear(res);
			PQfinish(conn);
			exit(1);
		}
	}

	// Fermer la connexion à la base de données
	PQclear(res);
	PQfinish(conn);
}

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
    enregistrerClient(&(banque->clients[banque->nbClients-1]));
    return &(banque->clients[banque->nbClients-1]);
}

void editerClient(Banque *banque, char *identifiantClient, char *nom, char *prenom)
{
	Client *client = getClientByIdentifiant(banque, identifiantClient);
	strcpy(client->nom, nom);
	strcpy(client->prenom, prenom);
	enregistrerClient(client);
}

void supprimerClient(Banque *banque, char *identifiantClient)
{
    int i;
    int suppression = 0;
    for (i = 0; i < banque->nbClients; i++) {
        if (!strcmp(banque->clients[i].identifiant, identifiantClient)) {
            // Supprimer le client en décalant les éléments suivants dans le tableau
            for (int j = i; j < banque->nbClients - 1; j++) {
                banque->clients[j] = banque->clients[j + 1];
            }
            banque->nbClients--;
            enregistrerGenerique("client", identifiantClient, NULL, NULL, 0);
            suppression = 1;
            printf("Le client n°%s a été supprimé avec succès\n", identifiantClient);
            break;
        }
    }
    if (suppression == 0)
    {
    	printf("Le client n°%s n'a pas été trouvé dans la base\n", identifiantClient);
    }
}

void afficherClients(Banque *banque)
{
    printf("CLIENTS : \n\n");
    printf("%-10s %-50s %-50s\n", "NUMERO", "NOM", "PRENOM");
    for (int i = 0; i < banque->nbClients; i++) {
        afficherClient(&banque->clients[i]);
    }
}


