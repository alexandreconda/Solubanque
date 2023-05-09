/*
 * tools.c
 */

#include <unistd.h>
#include "headers/tools.h"

time_t stringToTime(char *timestamp)
{
	struct tm tmdate = {0};
	tmdate.tm_year = atoi(&timestamp[0]) - 1900;
	tmdate.tm_mon = atoi(&timestamp[5]) - 1;
	tmdate.tm_mday = atoi(&timestamp[8]);
	tmdate.tm_hour = atoi(&timestamp[11]);
	tmdate.tm_min = atoi(&timestamp[14]);
	tmdate.tm_sec = atoi(&timestamp[17]);
	time_t t = mktime( &tmdate ) - timezone;

	return t;
}

static char *util_cat(char *dest, char *end, const char *str)
{
    while (dest < end && *str)
        *dest++ = *str++;
    return dest;
}

size_t join_str(char *out_string, size_t out_bufsz, const char *delim, char **chararr)
{
    char *ptr = out_string;
    char *strend = out_string + out_bufsz;
    while (ptr < strend && *chararr)
    {
        ptr = util_cat(ptr, strend, *chararr);
        chararr++;
        if (*chararr)
            ptr = util_cat(ptr, strend, delim);
    }
    return ptr - out_string;
}

void initialiserDonnees(Banque *maBanque)
{
	// Ouvrir une connexion à la base de données
	PGconn *conn = PQconnectdb("user=user password=user dbname=solubanque host=localhost port=5432");
	if (PQstatus(conn) != CONNECTION_OK)
	{
	    fprintf(stderr, "La connexion à la base de données a échoué : %s", PQerrorMessage(conn));
	    PQfinish(conn);
	    exit(1);
	}
	char query[MAX_QUERY_SIZE];

	// Exécuter une requête SQL pour récupérer les données de la table Banque
	PGresult *res_banque = PQexec(conn, "SELECT identifiant, nom FROM public.banque WHERE identifiant = '1'");

	// Exécuter une requête SQL pour récupérer les données de la table Client
	PGresult *res_clients = PQexec(conn, "SELECT identifiant, nom, prenom, identifiantbanque FROM public.client WHERE identifiantbanque = '1' ORDER BY nom, prenom");
	int nbClients = PQntuples(res_clients);

	// Parcourir le résultat de la requête et stocker les données dans la variable maBanque
	Banque banque;
	strcpy(banque.identifiant, PQgetvalue(res_banque, 0, 0));
	strcpy(banque.nom, PQgetvalue(res_banque, 0, 1));
	banque.nbClients = nbClients;
	*maBanque = banque;

	// Parcourir le résultat de la requête et stocker les données dans la variable maBanque->clients
	for (int i = 0; i < nbClients; i++)
	{
		Client client;
		strcpy(client.identifiant, PQgetvalue(res_clients, i, 0));
		strcpy(client.nom, PQgetvalue(res_clients, i, 1));
		strcpy(client.prenom, PQgetvalue(res_clients, i, 2));
		strcpy(client.identifiantBanque, PQgetvalue(res_clients, i, 3));

		// Exécuter une requête SQL pour récupérer les données de la table Compte
		snprintf(query, MAX_QUERY_SIZE, "SELECT identifiant, nom, solde, identifiantclient FROM public.compte WHERE identifiantclient = '%s' ORDER BY nom", client.identifiant);
		PGresult *res_comptes = PQexec(conn, query);
		int nbComptes = PQntuples(res_comptes);


		client.nbComptes = nbComptes;
		maBanque->clients[i] = client;



		// Parcourir le résultat de la requête et stocker les données dans la variable maBanque->clients[i]->comptes
		for (int j = 0 ; j < nbComptes ; j++)
		{
			Compte compte;
			strcpy(compte.identifiant, PQgetvalue(res_comptes, j, 0));
			strcpy(compte.nom, PQgetvalue(res_comptes, j, 1));
			compte.solde = atoi(PQgetvalue(res_comptes, j, 2));
			strcpy(compte.identifiantClient, PQgetvalue(res_comptes, j, 3));


			// Exécuter une requête SQL pour récupérer les données de la table Transaction
			snprintf(query, MAX_QUERY_SIZE, "SELECT identifiant, libelle, dateoperation, montant, identifiantcrediteur, identifiantdebiteur FROM public.transaction WHERE identifiantcrediteur = '%s' OR identifiantdebiteur = '%s' ORDER BY dateoperation", compte.identifiant, compte.identifiant);
			PGresult *res_transactions = PQexec(conn, query);
			int nbTransactions = PQntuples(res_transactions);


			compte.nbTransactions = nbTransactions;
			maBanque->clients[i].comptes[j] = compte;



			// Parcourir le résultat de la requête et stocker les données dans la variable maBanque->clients[i]->comptes[j]->transactions
			for (int k = 0 ; k < nbTransactions ; k++)
			{
				Transaction transaction;
				strcpy(transaction.identifiant, PQgetvalue(res_transactions, k, 0));
				strcpy(transaction.libelle, PQgetvalue(res_transactions, k, 1));
				transaction.dateOperation = stringToTime((PQgetvalue(res_transactions, k, 2)));
				transaction.montant = atoi(PQgetvalue(res_transactions, k, 3));
				strcpy(transaction.identifiantCrediteur, PQgetvalue(res_transactions, k, 4));
				strcpy(transaction.identifiantDebiteur, PQgetvalue(res_transactions, k, 5));
				maBanque->clients[i].comptes[j].transactions[k] = transaction;


			}
		}
	}

	// Fermer la connexion à la base de données
	PQfinish(conn);
}


void enregistrerGenerique(char *nomTable, char *identifiant, char **colNames, char **colValues, size_t nbCols)
{
	char query[MAX_QUERY_SIZE];

	// Connexion à la base de données
	PGconn *conn = PQconnectdb("user=user password=user dbname=solubanque host=localhost port=5432");
	if (PQstatus(conn) != CONNECTION_OK) {
		fprintf(stderr, "Connexion à la base de données a échoué : %s", PQerrorMessage(conn));
		PQfinish(conn);
		exit(1);
	}

	// Chercher l'élément dans la base de données
	snprintf(query, MAX_QUERY_SIZE, "SELECT COUNT(*) FROM %s WHERE identifiant='%s'", nomTable, identifiant);
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
		// La ligne n'existe pas dans la base de données, donc nous devons insérer une nouvelle ligne
		snprintf(query, 2048, "INSERT INTO %s (identifiant", nomTable);
		for (size_t i = 0; i < nbCols; i++) {
			char *colName = colNames[i];
			strcat(query, ", ");
			strncat(query, colName, strlen(colName));
		}
		strncat(query, ") VALUES ('", 15);
		strncat(query, identifiant, strlen(identifiant));
		strcat(query, "'");
		for (size_t i = 0; i < nbCols; i++) {
			char *colValue = colValues[i];
			strcat(query, ", '");
			strncat(query, colValue, strlen(colValue));
			strcat(query, "'");
		}
		strcat(query, ")");
		res = PQexec(conn, query);
		if (PQresultStatus(res) != PGRES_COMMAND_OK) {
			fprintf(stderr, "Échec de l'insertion : %s", PQerrorMessage(conn));
			PQclear(res);
			PQfinish(conn);
			exit(1);
		}
	}
	// L'élément existe déjà dans la base de données
	else
	{
		// Si le nombre de colonnes à modifier passées en argument est supérieur à zéro, il s'agit d'une édition
		if (nbCols > 0)
		{
			snprintf(query, 2048, "UPDATE %s SET ", nomTable);
			for (size_t i = 0; i < nbCols; i++) {
				char *colName = colNames[i];
				char *colValue = colValues[i];
				if (i != 0)
				{
					strcat(query, ", ");
				}
				strncat(query, colName, strlen(colName));
				strcat(query, " = '");
				strncat(query, colValue, strlen(colValue) + 2);
				strcat(query, "'");
			}
			strcat(query, " WHERE identifiant = '");
			strncat(query, identifiant, strlen(identifiant));
			strcat(query, "'");
			res = PQexec(conn, query);
			if (PQresultStatus(res) != PGRES_COMMAND_OK) {
				fprintf(stderr, "Échec de l'édition : %s", PQerrorMessage(conn));
				PQclear(res);
				PQfinish(conn);
				exit(1);
			}
		}
		// S'il n'y a aucune colonne à modifier, il s'agit d'une suppression
		else
		{
			snprintf(query, 2048, "DELETE FROM %s ", nomTable);
			strcat(query, " WHERE identifiant = '");
			strncat(query, identifiant, strlen(identifiant));
			strcat(query, "'");
			res = PQexec(conn, query);
			if (PQresultStatus(res) != PGRES_COMMAND_OK) {
				fprintf(stderr, "Échec de la suppression : %s", PQerrorMessage(conn));
				PQclear(res);
				PQfinish(conn);
				exit(1);
			}
		}
	}

	// Fermer la connexion à la base de données
	PQclear(res);
	PQfinish(conn);
}

void toolsLog(const char *message)
{
    FILE *fichier_log;
    const char *filename = "logs.txt";
    fichier_log = fopen(filename, "a");
    if (fichier_log != NULL) {
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char s[64];
        strftime(s, sizeof(s), "%c", tm);
        fprintf(fichier_log, "%s - %s\n", s, message);
        fclose(fichier_log);
    } else {
        printf("Impossible d'ouvrir le fichier de log.\n");
    }
}

void genererIdentifiantUnique(char *outputBuffer)
{
		char identifiant[17] = {0};
		// Génère un nombre aléatoire entre 10000000 et 99999999
		int nombreAleatoire = (rand() % 90000000) + 10000000;
		snprintf(identifiant, sizeof(identifiant), "%08d", nombreAleatoire);
		strncpy(outputBuffer, identifiant, 16);
}
