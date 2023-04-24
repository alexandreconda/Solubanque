/*
 * tools.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "headers/tools.h"

void genererIdentifiantUnique(char *outputBuffer)
{
		char identifiant[17] = {0};
		// Génère un nombre aléatoire entre 10000000 et 99999999
		int nombreAleatoire = (rand() % 90000000) + 10000000;
		snprintf(identifiant, sizeof(identifiant), "%08d", nombreAleatoire);
		strncpy(outputBuffer, identifiant, 16);
}
