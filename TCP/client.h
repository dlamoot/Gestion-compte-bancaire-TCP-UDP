//
//  client.h
//  Projet!reseaux
//
//  Created by David Lamoot on 10/01/2025.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
        char id[100];
        char mdp[100];
        char num[100] ;
}client;
