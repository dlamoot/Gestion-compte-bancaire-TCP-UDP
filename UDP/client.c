//
//  client.c
//  Projet!reseaux
//
//  Created by David Lamoot on 12/01/2025.
//

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int tentativeConnexion = 0;

// Structure pour les informations du compte
typedef struct {
    float solde;
    float historique[10];
} InfoCompte;

// Structure pour les informations du client
typedef struct {
    char *id_client;
    char *password;
    InfoCompte compte;
} user;

//Boucle principale du programme
int main(void) {
    // Variables pour la connexion
    int socketSocket;
    struct sockaddr_in serveur_addr;
    int serveur_struct_length = sizeof(serveur_addr);
    
    // Creation du socket
    socketSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


    // Verification de la creation de la socket
    if (socket < 0) {
        printf("Creation de socket impossible\n");
        return -1;
    }

    // Variables pour le menu
    int choixNum = 0;
    char receptionMenu[156];
    //variables pour la connexion
    char receptionConnexion[11];
    char receptionMessageConnexion[61];

    //variables pour les transactions
    char serveurDemandeId[50];
    char clientDemandeId[50];
   
    //variables pour les transactions
    char serveurDemandeMDP[50];
    char clientDemandeMDP[50];
   
    // Initialisation de la structure pour la connexion
    serveur_addr.sin_family = AF_INET;
    serveur_addr.sin_port = htons(10000);
    serveur_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Variables pour les transactions
    int connexion = 0;
    char receptionQuestionAjout[50];
    float envoiAjout;
    char receptionMessageAjout[88];
    char receptionConfirmationAjout[31];
    char receptionQuestionRetrait[20];
    float envoiRetrait;
    char receptionMessageRetrait[75];
    float receptionValeurSolde;
    char receptionMessageRetrait2[55];
    char receptionConfirmationRetrait[30];
    char receptionValeurSolde1[20];
    char receptionMessageSolde1[29];
    char receptionMessageSolde2[20];
    char receptionMessageHistorique[51];
    float tabHistorique[10];
    char miseForme1[6];
    char miseForme2[5];
    char receptionRetourMenu[21];
    char receptionMessageDeconnexion[11];
    char receptionCaractereDeconnexion[3];
    char receptionChoixNum[69];

  // Boucle pour la connexion
    while (connexion == 0) {
        do {
            // Initialisation des variables pour les transactions
            memset(serveurDemandeId, '\0', sizeof(serveurDemandeId));
            memset(clientDemandeId, '\0', sizeof(clientDemandeId));
            
            printf("Identifiant: ");
            scanf("%s", clientDemandeId);
            
            if (sendto(socketSocket, clientDemandeId, strlen(clientDemandeId), 0,(struct sockaddr *)&serveur_addr, serveur_struct_length) < 0) {
                printf("Envoie du message impossible\n");
                return -1;
            }
            
            if (recvfrom(socketSocket, serveurDemandeId, sizeof(serveurDemandeId), 0,(struct sockaddr *)&serveur_addr,&serveur_struct_length) < 0) {
                printf("Erreur\n");
                return -1;
            }
            
            memset(serveurDemandeMDP, '\0', sizeof(serveurDemandeMDP));
            memset(clientDemandeMDP, '\0', sizeof(clientDemandeMDP));
            
            // Demande du mot de passe
            printf("Mot de passe: ");
            scanf("%s", clientDemandeMDP);
            
            if (sendto(socketSocket, clientDemandeMDP, strlen(clientDemandeMDP), 0,(struct sockaddr *)&serveur_addr, serveur_struct_length) < 0) {
                printf("Envoi de message impossible\n");
                return -1;
            }
            
            // Si mot de passe incorrect
            if (recvfrom(socketSocket, serveurDemandeMDP, sizeof(serveurDemandeMDP), 0, (struct sockaddr *)&serveur_addr, &serveur_struct_length) < 0) {
                printf("Erreur\n");
                return -1;
            }
            recvfrom(socketSocket, &connexion, sizeof(int), 0,(struct sockaddr *)&serveur_addr, &serveur_struct_length);
            
            // Connexion reussie
            if (connexion == 1) {
                recvfrom(socketSocket, receptionConnexion, sizeof(receptionConnexion), 0,(struct sockaddr *)&serveur_addr, &serveur_struct_length);
                printf("\n%s %s\n", receptionConnexion, clientDemandeId);
            }
            
            // Connexion echouee
            else {
                recvfrom(socketSocket, receptionMessageConnexion,sizeof(receptionMessageConnexion), 0,(struct sockaddr *)&serveur_addr, &serveur_struct_length);
                printf("%s\n", receptionMessageConnexion);
            }
            
            // Boucle pour la connexion
        }
        while (connexion== 0);
        
        // Boucle pour le menu
        while (choixNum != 5) {
            // Initialisation des variables pour les transactions
            recvfrom(socketSocket, receptionMenu, sizeof(receptionMenu), 0,(struct sockaddr *)&serveur_addr, &serveur_struct_length);
            printf("%s", receptionMenu);
            scanf("%d", &choixNum);
            sendto(socketSocket, &choixNum, sizeof(int), 0,(struct sockaddr *)&serveur_addr, serveur_struct_length);
            
            // Choix 1 : Ajout d'argent
            if (choixNum == 1) {
                //On demande le montant à ajouter
                recvfrom(socketSocket, receptionQuestionAjout,sizeof(receptionQuestionAjout), 0, (struct sockaddr *)&serveur_addr, &serveur_struct_length);
                printf("%s", receptionQuestionAjout);
                scanf("%f", &envoiAjout);
                sendto(socketSocket, &envoiAjout, sizeof(float), 0,(struct sockaddr *)&serveur_addr, serveur_struct_length);
                
                // Si le montant est positif, on l'ajoute
                if (envoiAjout <= 0) {
                    recvfrom(socketSocket, receptionMessageAjout,sizeof(receptionMessageAjout), 0,(struct sockaddr *)&serveur_addr, &serveur_struct_length);
                    printf("%s", receptionMessageAjout);
                }
                
                else {
                    // Si le montant est négatif, on le rend positif
                    recvfrom(socketSocket, receptionConfirmationAjout, sizeof(receptionConfirmationAjout), 0, (struct sockaddr *)&serveur_addr, &serveur_struct_length);
                    printf("%s", receptionConfirmationAjout);
                }
            }
            
            // Choix 2 : Retrait d'argent
            else if (choixNum == 2) {
                // On demande le montant à retirer
                recvfrom(socketSocket, receptionQuestionRetrait,sizeof(receptionQuestionRetrait), 0, (struct sockaddr *)&serveur_addr, &serveur_struct_length);
                printf("%s", receptionQuestionRetrait);
                scanf("%f", &envoiRetrait);
                sendto(socketSocket, &envoiRetrait, sizeof(float), 0, (struct sockaddr *)&serveur_addr, serveur_struct_length);
                
                if (envoiRetrait == 0) {
                    // Si le montant est nul, on affiche un message d'erreur
                    recvfrom(socketSocket, receptionMessageRetrait,sizeof(receptionMessageRetrait), 0, (struct sockaddr *)&serveur_addr, &serveur_struct_length);
                    printf("%s", receptionMessageRetrait);
                }
                else {
                    // Si le montant est négatif, on le rend positif
                    if (envoiRetrait < 0) {
                        envoiRetrait = -envoiRetrait;
                    }
                    recvfrom(socketSocket, &receptionValeurSolde,sizeof(receptionValeurSolde), 0,(struct sockaddr *)&serveur_addr, &serveur_struct_length);
                    if (envoiRetrait > receptionValeurSolde) {
                        recvfrom(socketSocket, receptionMessageRetrait2,sizeof(receptionMessageRetrait2), 0, (struct sockaddr *)&serveur_addr, &serveur_struct_length);
                        printf("%s", receptionMessageRetrait2);
                    }
                    
                    else {
                        recvfrom(socketSocket, receptionConfirmationRetrait,sizeof(receptionConfirmationRetrait), 0, (struct sockaddr *)&serveur_addr, &serveur_struct_length);
                        printf("%s", receptionConfirmationRetrait);
                    }
                }
            }
            
            //Choix 3 : Affichage Historique
            else if (choixNum == 4) {
                printf("Historique des transactions :\n");
                // Affichage de l'historique des transactions
                for (int i = 0; i < 10; i++) {
                    float transaction;
                    recvfrom(socketSocket, &transaction, sizeof(float), 0, (struct sockaddr *)&serveur_addr, &serveur_struct_length);
                    printf("Transaction %d : %.2f\n", i + 1, transaction);
                }
                char finHistorique[100];
                recvfrom(socketSocket, finHistorique, sizeof(finHistorique), 0, (struct sockaddr *)&serveur_addr, &serveur_struct_length);
                printf("%s\n", finHistorique);
            }
            
            //Choix 5 : Déconnexion
            else if (choixNum == 5) {
                // Message de déconnexion
                recvfrom(socketSocket, receptionMessageDeconnexion,sizeof(receptionMessageDeconnexion), 0, (struct sockaddr *)&serveur_addr, &serveur_struct_length);
                // Affichage du message de déconnexion
                printf("%s", receptionMessageDeconnexion);
                printf("%s", clientDemandeId);
                recvfrom(socketSocket, receptionCaractereDeconnexion,sizeof(receptionCaractereDeconnexion), 0,  (struct sockaddr *)&serveur_addr, &serveur_struct_length);
                printf("%s", receptionCaractereDeconnexion);
            }
            
            // Choix invalide
            else {
                //On reçoit un message d'erreur
                recvfrom(socketSocket, receptionChoixNum, sizeof(receptionChoixNum), 0,(struct sockaddr *)&serveur_addr, &serveur_struct_length);
                //On affiche un message d'erreur
                printf("%s\n", receptionChoixNum);
            }
        }
    }
    
    //Fermeture du socket
    close(socketSocket);
   return 0;
}
