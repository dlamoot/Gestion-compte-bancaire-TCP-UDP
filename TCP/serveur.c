//
//  serveur.c
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
#include "serveur.h"


int main(void){
    
    // socket serveur
    int socketServer = socket(AF_INET, SOCK_STREAM, 0);   // création du socket avec deux arguments :AF_INET domaine d'adresse(IPV4), type de socket SOCK_STREAM(TCP)
    printf("[+]Socket serveur cree avec succes\n");       // on attend la lecture
    struct sockaddr_in addrServer;                        // configuration de l'adresse du serveur par le type sockaddr_in
    addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");  // adresse locale meme pour tout le monde
    addrServer.sin_family = AF_INET ;                     // AF_INET pour les adresse IPV4
    addrServer.sin_port = htons(1999) ;                   // choix du port
    
    //Connexion serveur
    bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer));
    printf("[+]bind : %d\n", socketServer);
    
    //Attend que le client se connecte
    listen(socketServer, 5);                  // Autorisation de 5 utilisateurs
    printf("[+]listen...\n");                 // En attente de lecture
    
    // Recuperation données client
    struct sockaddr_in addrClient;
    socklen_t csize = sizeof(addrClient);
    int socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);
    printf("[+]On accepte \n");

    printf("[+]client: %d\n",socketClient);
    printf("******************************************************\n");

    // Demande d'identifiant au client
    char demande_id[100] = "-Saisissez votre identifiant : ";
    send(socketClient, demande_id, strlen(demande_id)+1, 0);
    printf("%s\n",demande_id);

    client c1;
    
    // Reception de l'identifiant du client
    recv(socketClient, c1.id, sizeof(c1.id), 0);
    printf("vous etes bien : %s\n",c1.id);
    printf("*****************************************************\n");

    // Demande de numero de compte au client
    char demande_num[100] = "-Saisissez votre numero de compte :";
    send(socketClient, demande_num, strlen(demande_num)+1, 0);
    printf("%s\n",demande_num);

    // Reception du numero de compte du client
    recv(socketClient, c1.num, sizeof(c1.num), 0);
    printf("%s\n",c1.num);

    printf("***************************************************\n");

    // Demande du mot de passe au client
    char demande_mdp[100] = "-Saisissez votre mot de passe : ";
    send(socketClient, demande_mdp, strlen(demande_mdp)+1, 0);
    printf("%s\n",demande_mdp);

    // Reception du mot de passe du client
    recv(socketClient, c1.mdp, sizeof(c1.mdp), 0);
    printf("%s\n",c1.mdp);

    printf("*******************************************************\n");

    // Affectation de l'identifiant, du mot de passe et du numero de compte de chaque client
    client cpt1 = {"test", "hein", "00000001"};
    client cpt2 = {"essai", "de", "00000002"};
    int quit = 0;
    char text[100];
    char reply[100];
    int histo[10];
    int solde =100;
    
    // comparaison de l'identifiant, du mot de passe et de du numero de compte que la client a saisi avec les informations présentes dans notre base de donnée pour verifier si l'une de ces informations existent ou sont fausses.
    if((((strcmp(c1.id,cpt1.id) == 0) && (strcmp(c1.mdp,cpt1.mdp) == 0) && (strcmp(c1.num,cpt1.num)==0)) || ((strcmp(c1.id,cpt2.id) == 0) && (strcmp(c1.mdp,cpt2.mdp) == 0)&& (strcmp(c1.num,cpt2.num) == 0))))
    {
        
        // Informations saisies correctes
        char bien[100] ="-Bienvenue sur votre compte bancaire\n";
        send(socketClient, bien, strlen(bien)+1, 0);
        printf("%s\n",bien);
        quit = 1;
       
    }
    else
    {
        // Informations saisies fausses
        char bien[100] = "\nMot de passe ou identifiant incorrecte\n";
        send(socketClient, bien, strlen(bien)+1, 0);
        printf("%s\n",bien);
        
        EXIT_FAILURE; // Fin du programme
    }
    while(quit){
        recv(socketClient, text, sizeof(text), 0);
        printf("%s\n",text);
        if(strcmp(text,"FIN")==0)
        {
            quit = 0;
        }
        else if(text[0]=='1')
        {
            int temp;
            sscanf(text,"1 Le client ajoute %d",&temp);
            solde += temp;
            for (int r = 9; r > 0; r--)
            {
                histo[r] = histo[r-1];
            }
            histo[0] = 1;
            sprintf(reply,"OK");
            send(socketClient, reply, strlen(reply)+1, 0);
        }
        else if(text[0]=='2')
        {
            int temp;
            sscanf(text,"2 Le client retire %d",&temp);
            solde -= temp;
            for (int r = 9; r > 0; r--)
            {
                histo[r] = histo[r-1];
            }
            histo[0] = 2;
            sprintf(reply,"OK");
            send(socketClient, reply, strlen(reply)+1, 0);
        }
        else if(text[0]=='3')
        {
            for (int r = 9; r > 0; r--)
            {
                histo[r] = histo[r-1];
            }
            histo[0] = 3;
            sprintf(reply,"OK %d",solde);
            send(socketClient, reply, strlen(reply)+1, 0);
        }
        else if(text[0]=='4')
        {
            for (int r = 9; r > 0; r--)
            {
                histo[r] = histo[r-1];
            }
            histo[0] = 4;
            send(socketClient, histo, strlen(histo)+1, 0);
        }
    }

    close(socketClient); // Fermeture socket client
    close(socketServer); // Fermeture socket serveur
    printf("close\n");
}
