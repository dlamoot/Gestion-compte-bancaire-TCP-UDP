//
//  client.c
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
#include "client.h"


int main(void){
    
    // socket client
    int socketClient = socket(AF_INET, SOCK_STREAM, 0);     // création du socket  avec deux arguments :AF_INET domaine d'adresse(IPV4), type de socket SOCK_STREAM(TCP)
    struct sockaddr_in addrClient;                          // configuration de l'adresse du serveur par le type sockaddr_in
    addrClient.sin_addr.s_addr = inet_addr("127.0.0.1");    // adresse locale meme pour tout le monde
    addrClient.sin_family = AF_INET ;                       // AF_INET pour les adresse IPV4
    addrClient.sin_port = htons(1999);                      // choix du port

    connect(socketClient, (const struct sockaddr *)&addrClient, sizeof(addrClient));
    printf("[+] Socket client cree et connexion au serveur avec succes \n");

    printf("---------------------------------------------------------\n");

    // Reçoit une requête du serveur pour l'identifiant
    char demande_id[100];
    recv(socketClient, demande_id, sizeof(demande_id), 0);
    printf("%s\n",demande_id);

    client c1 ; // création d'un client à partir d'une structure

    // Ecrit et envoie l'identifiant au serveur
    scanf("%s",c1.id);
    send(socketClient, c1.id, strlen(c1.id)+1, 0);

    printf("---------------------------------------------------------\n");

    // Reçoit une requête du serveur pour le numero de compte
    char demande_num[100];
    recv(socketClient, demande_num, sizeof(demande_num), 0);
    printf("%s\n",demande_num);

    
    // Ecrit et envoi le numero de compte au serveur
    scanf("%s",c1.num);
    send(socketClient, c1.num, strlen(c1.num)+1, 0);

    printf("---------------------------------------------------------\n");
    
    // Reçoit une requête du serveur pour le mot de passe
    char demande_mdp[100];
    recv(socketClient, demande_mdp, sizeof(demande_mdp), 0);
    printf("%s\n",demande_mdp);
    
    // Ecrit et envoi le le mot de passe au serveur
    scanf("%s",c1.mdp);
    send(socketClient, c1.mdp, strlen(c1.mdp)+1, 0);

    printf("_________________________________________________________\n");
    printf("_________________________________________________________\n\n");

    // Recoit une reponse du serveur sur la validité des informations
    char bien[100];
    recv(socketClient, bien, sizeof(bien), 0);
    printf("%s\n",bien);
    int n ;             // variable permettant de decider l'operation souhaitée
      int solde =2121  ;   // solde sur le compte
      int tab_dix[10] = {0,0,0,0,0,0,0,0,0,0};    // permet de stocker les 10 dernieres operations faites
      int verif[10]= {5,5,5,5,5,5,5,5,5,5};     // permet de verifier si l'operation est ajout ou un retrait
      int j = 0;
      int somme_ajoute = 0;
      int somme_retire = 0;
      int quit = 0;
      char text[100];
    // Si les informations saisies sont correctes on accede au menu
    if(strcmp(bien,"-Bienvenue sur votre compte bancaire\n") == 0 ){quit = 1;}
      while(quit){
        printf("_________________________________________________________\n");
        printf("_________________________________________________________\n");
        printf("_________________________________________________________\n");
        printf("_________________________________________________________\n");
        printf("\nAppuyez sur 1 si vous souhaitez ajouter de l'argent dans votre compte\n");
        printf("Appuyez sur 2 si vous souhaitez retirer de l'argent dans votre compte\n");
        printf("Appuyez sur 3 si vous souhaitez consulter votre solde\n");
        printf("Appuyez sur 4 si vous souhaitez consulter les 10 dernieres operations effectuees sur votre compte\n");
        printf("Appuyez sur 5 si vous souhaitez quitter l'interface \n");
        scanf("%d",&n);     // Saisi de l'operation souhaitée
        
        switch(n)
        {
                
           case 1 :
                 // cas ajout d'argent sur le compte
                 printf("---------------------------------------------------------\n");
                 printf("Solde sur votre compte : %d €\n",solde);
                 printf("Veuillez saisir la somme ajoute : \n");
                 scanf("%d",&somme_ajoute);
                 printf("***********************************************************\n");
                 solde = somme_ajoute + solde;                                              // Somme
                 printf("Votre solde est desormais de %d € sur votre compte\n\n",solde);
                 printf("________________FIN D'OPERATION____________\n\n");
                 for (int r = 9; r > 0; r--)
                 {
                  tab_dix[r] = tab_dix[r-1];
                  verif[r] = verif[r-1];
                 }
                 tab_dix[0] = solde;
                 verif[0] = 0;
                 sprintf(text,"1 Le client ajoute %d",somme_ajoute);
                 send(socketClient, text, strlen(text)+1, 0);
                 break;

           case 2 :
                 // cas retrait d'argent sur le compte
                 printf("*********************************************************\n");
                 printf("Solde sur votre compte : %d € \n",solde);
                 printf("Veuillez saisir la somme a retirer :  \n");
                 scanf("%d",&somme_retire);                                                 // Soustraction
                 printf("***********************************************************\n");
                 solde = solde - somme_retire;
                 printf("Votre solde est desormais de %d € sur votre compte\n\n",solde);
                 printf("________________FIN D'OPERATION____________\n\n");
                 for (int r = 9; r > 0; r--)
                 {
                  tab_dix[r] = tab_dix[r-1];
                  verif[r] = verif[r-1];
                 }
                 tab_dix[0] = solde;
                 verif[0] = 1;
                 sprintf(text,"2 Le client retire %d",somme_retire);
                 send(socketClient, text, strlen(text)+1, 0);
                 break;

           case 3 :
                 // cas affichage du solde du compte
                 printf("*********************************************************\n");
                 printf("\nSolde sur votre compte : %d € \n\n",solde);
                 printf("_______________FIN D'OPERATION____________\n\n");
                 for (int r = 9; r > 0; r--)
                 {
                  tab_dix[r] = tab_dix[r-1];
                  verif[r] = verif[r-1];
                 }
                 verif[0] = 2;
                 sprintf(text,"3 Le client consulte sa solde");
                 send(socketClient, text, strlen(text)+1, 0);
                 break;

           case 4 :
                // cas affichage des 10 dernières opérations sur le compte
                printf("\nVoici vos 10 dernieres operations sur votre compte\n");
                 for(j = 0 ; j<10;j++)
                 {
                    if(verif[j] == 0)
                    {
                         printf("ajout ");      // On affiche l'opération ajout
                         printf("%d €\n",tab_dix[j] ); // On affiche la valeur stocker en fonction de si on est en ajout ou retrait
                    }
                    else if(verif[j] == 1)
                    {
                         printf("retrait ");    // On affiche l'opération retrait
                         printf("%d €\n",tab_dix[j] ); // On affiche la valeur stocker en fonction de si on est en ajout ou retrait
                    }
                    else if(verif[j] == 2)
                    {
                        printf("affichage solde\n");
                    }
                    else if(verif[j] == 3)
                    {
                        printf("affichage historique\n");
                    }
                    else
                    {
                        printf("\n");
                    }
                 }
                 for (int r = 9; r > 0; r--)
                 {
                  tab_dix[r] = tab_dix[r-1];
                  verif[r] = verif[r-1];
                 }
                 verif[0] = 3;
                 sprintf(text,"4 Le client consulte l'historique");
                 send(socketClient, text, strlen(text)+1, 0);  // Tableau suivant à 1 pour signifier qu'on est dans le cas de retrait
                break ;
           case 5 :
                 // Cas ou souhaite quitté le menu sans faire d'opération
                 quit = 0;
                 sprintf(text,"FIN");
                 send(socketClient, text, strlen(text)+1, 0);
                 printf("_____________FIN D'OPERATION BONNE JOURNEE_______________\n\n");
                 printf("***********************************************************\n");
                 break ;

           default :
                 //autre possiblilité
                 printf("__________________________________________________________\n");
                 printf("\nKO mauvais choix \n\n");
                 printf("_____________FIN D'OPERATION BONNE JOURNEE_______________\n\n");
                 printf("***********************************************************\n");
           }
           recv(socketClient, bien, sizeof(bien), 0);
      }
    close(socketClient); //Fermetue du socket client
}
