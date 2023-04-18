/*
 * client.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "headers/client.h"

void afficherClient(Client *client)
{
	printf("%-6d %-10s %-10s\n", client->numero, client->nom, client->prenom);
}

