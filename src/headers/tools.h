/*
 * tools.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include </usr/include/postgresql/libpq-fe.h>
#include "banque.h"

#define MAX_QUERY_SIZE 1000

#ifndef TOOLS_H_
#define TOOLS_H_

void initialiserDonnees(Banque *maBanque);

void enregistrerGenerique(char *nomTable, char *identifiant, char **colNames, char **colValues, size_t nbCols);

void toolsLog(const char *message);

void genererIdentifiantUnique(char *outputBuffer);

#endif /* TOOLS_H_ */
