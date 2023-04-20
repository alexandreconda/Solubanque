/*
 * compte.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers/compte.h"

void afficherCompte(Compte *compte)
{
	printf("%-6d %-10s %-10.2f€\n", compte->numero, compte->nom, compte->solde);
}
