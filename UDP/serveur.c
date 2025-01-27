//
//  serveur.c
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

// Structure
// Structure de l'id_client
typedef struct {
    char *id_client; // id_client
    char *password;  // mot de passe
} user;

int main(void) {
    int socketSocket;
    struct sockaddr_in serveur_addr, client_addr;
    int client_struct_length = sizeof(client_addr);

    // Creation socket UDP
    socketSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socketSocket < 0) {
        printf("Creation du socket impossible\n");
        return -1;
    }
    
    int tentativeConnexion = 1;
    
    // Variables identifiant
    char serveurDemandeId[50];
    char clientDemandeId[50];
    
    // Variables MDP
    char serveurDemandeMDP[50];
    char clientDemandeMDP[50];

    // Menu et action de l'user
    int choixNum = 0; // ChoixNum = 0
    char envoiMenu[] =
      "Options:\n\t[ 1 ]    Recharger compte\n\t[ 2 ]    Debiter"
      " compte\n\t[ 3 ]    Aperçu solde\n\t[ 4 ]    Historique des "
      "opérations\n\t[ 5 ]   Déconnecter\n\nSélection : "; // Menu

      // Message de connexion
      char envoiConnexion[] = "Bienvenue "; // Variable envoiConnexion
      char
          envoiMessageConnexion[] = "\nIdentifiant ou Mot De Passe "
                                    "incorrect,veuillez re-essayer\n"; // Variable
                                                                       // envoiMessageConnexion

      // Partie solde

      char solde[80]; // Message solde
      float valeurSolde =0;; // Reception du solde dispo sur le txt de l'user en question
      char historique[80];     // Message historique
      float tabHistorique[10]; // Tableau de valeurs de l'historique
      float temp[10];          // Temp du tabHistorique
      int indice = 0;          // indice = 0

      // Choix 1
      char envoiQuestionAjout[] = "Somme a crediter : "; // Variable envoiQuestionAjout
      float receptionAjout; // Variable receptionAjout
      char envoiMessageAjout[] =
          "La creditation oblige une valeur strictement positive !\nVeuillez "
          "resaisir votre choix\n"; // Variable envoiMessageAjout
      char envoiConfirmationAjout[] =
          "Compte correctement credite !\n"; // Variable envoiConfirmationAjout

      // Choix 2
      char envoiQuestionRetrait[] =
          "Somme a debiter : "; // Variable envoiQuestionRetrait
      float receptionRetrait;   // Variable receptionRetrait
      char envoiMessageRetrait[] =
          "Le debit d'une valeur nulle est impossible\nVeuillez ressaisir votre "
          "choix\n"; // Variable envoiMessageRetrait
      char envoiMessageRetrait2[] = "La debit est impossible\nVeuillez resaisir "
                                    "votre choix\n"; // Variable
                                                     // receptionConfirmationRetrait
      char envoiConfirmationRetrait[] =
          "Compte correctement debite !\n"; // Variable envoiConfirmationRetrait

      // Choix 3
      float envoiValeurSolde; // Variable envoiValeurSolde
      char envoiMessageSolde1[] ="Votre solde actuel est de : "; // Variable envoiMessageSolde1
      char envoiMessageSolde2[] ="\nRetour au menu...\n"; // Variable envoiMessageSolde2

      // Choix 4
      char messageHistorique[] = "Votre historique sur vos 10 derniers mouvements "
                                 ":\n"; // Envoie du messageHistorique
      char envoiForme1[] = "\n    [     ";
      char envoiForme2[] =
          "     ]    "; // String pour la mise en forme de l'historique
      char envoiRetourMenu[] =
          "\nRetour au menu...\n\n"; // Variable envoiRetourMenu

      // Choix 5
      char envoiMessageDeconnexion[] =
          "A bientot "; // Variable envoiMessageDeconnexion
      char envoiCaractereDeconnexion[] =
          "!\n"; // Variable envoiCaractereDeconnexion

      // Autres choix
      char envoiChoixNum[] = "Aucun choix ne correspond a la saisie\nVeuillez "
                             "resaisir votre choix\n"; // Variable envoiChoixNum

      // Configuration
      serveur_addr.sin_family = AF_INET;
      serveur_addr.sin_port = htons(10000);
      serveur_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

      // Creation de chaque User
      user test;
      test.id_client = "test";
      test.password = "hein";

      user essai;
      essai.id_client = "essai";
      essai.password = "de";

      // initialisation de l'historique
      for (int i = 0; i < 10; i++) {
        tabHistorique[i] = 0;
      }

      // Connexion au port
      if (bind(socketSocket, (struct sockaddr *)&serveur_addr,
               sizeof(serveur_addr)) < 0) {
        printf("Connexion au port impossible\n");
        return -1;
      }
      // Message de connexion
      printf("CONNEXION...\n");

      int connexion;
      //connexion d'un User
      connexion = 0; // Connexion = 0
      // Tant que connexion = 0
      while (connexion == 0) {

        // Initialise les messages
        memset(serveurDemandeId, '\0', sizeof(serveurDemandeId));
        memset(clientDemandeId, '\0', sizeof(clientDemandeId));

        // Recevoir le message du client
        if (recvfrom(socketSocket, clientDemandeId, sizeof(clientDemandeId), 0,(struct sockaddr *)&client_addr, &client_struct_length) < 0) {
          printf("Recu du messsage impossible\n");
          return -1;
        }
        // Reponse au client
        strcpy(serveurDemandeId, clientDemandeId);

        if (sendto(socketSocket, serveurDemandeId, strlen(serveurDemandeId) + 1, 0,
                   (struct sockaddr *)&client_addr, client_struct_length) < 0) {
          printf("Envoie du message impossible\n");
          return -1;
        }

        // Initialise les messages
        memset(serveurDemandeMDP, '\0', sizeof(serveurDemandeMDP));
        memset(clientDemandeMDP, '\0', sizeof(clientDemandeMDP));

        // Recevoir le message du client
        if (recvfrom(socketSocket, clientDemandeMDP, sizeof(clientDemandeMDP), 0,
                     (struct sockaddr *)&client_addr, &client_struct_length) < 0) {
          printf("Recu du messsage impossible\n");
          return -1;
        }
        // Reponse au client
        strcpy(serveurDemandeMDP, clientDemandeMDP);

        if (sendto(socketSocket, serveurDemandeMDP, strlen(serveurDemandeMDP) + 1,
                   0, (struct sockaddr *)&client_addr, client_struct_length) < 0) {
          printf("Envoie du message impossible\n");
          return -1;
        }

        // si reception de l'id_client compatible avec un user inscrit
        if ((strcmp(serveurDemandeId, test.id_client) == 0 &&
             strcmp(serveurDemandeMDP, test.password) == 0) ||
            (strcmp(serveurDemandeId, essai.id_client) == 0 &&
             strcmp(serveurDemandeMDP, essai.password) == 0)) {
          // connexion = 1
          connexion = 1;
          // Envoi de l'etat de connexion qui est egal a 1
          sendto(socketSocket, &connexion, sizeof(int), 0,
                 (struct sockaddr *)&client_addr, client_struct_length);
          // Afficher la notification du message de connexion
          sendto(socketSocket, envoiConnexion, strlen(envoiConnexion) + 1, 0,
                 (struct sockaddr *)&client_addr, client_struct_length);
          // Envoi du message de connexion
          printf("L'user %s vient de se connecter\n", clientDemandeId);
        } else {
          // Envoi de l'etat de connexion qui est egal a 0
          sendto(socketSocket, &connexion, sizeof(int), 0,
                 (struct sockaddr *)&client_addr, client_struct_length);
          // Envoi du message d'erreur de connexion
          sendto(socketSocket, envoiMessageConnexion,strlen(envoiMessageConnexion) + 1, 0,(struct sockaddr *)&client_addr, client_struct_length);
          // Afficher le message d'erreur de connexion
          printf("Un user non identifie a essaye de se connecter\n");
        }
      }
    
    // infos compte USER

      //Menu et action du user
      choixNum = 0; // choixNum = 0;
      // Tant que choix != 5
    while (choixNum != 5) {
        // Envoi du menu
        sendto(socketSocket, envoiMenu, strlen(envoiMenu) + 1, 0, (struct sockaddr *)&client_addr, client_struct_length);
        // Reception du choix
        recvfrom(socketSocket, &choixNum, sizeof(int), 0,(struct sockaddr *)&client_addr, &client_struct_length);
        // Si choixNum = 1 qui correspond a AJOUT
        if (choixNum == 1) {
            // Envoi de la QuestionAJout
            sendto(socketSocket, envoiQuestionAjout, strlen(envoiQuestionAjout) + 1,0, (struct sockaddr *)&client_addr, client_struct_length);
            // Reception de l'ajout
            recvfrom(socketSocket, &receptionAjout, sizeof(float), 0,(struct sockaddr *)&client_addr, &client_struct_length);
            // Si receptionAjout inferieur ou egal a 0
            if (receptionAjout <= 0) {
                // Envoi du MessageAjout
                sendto(socketSocket, envoiMessageAjout, strlen(envoiMessageAjout) + 1, 0, (struct sockaddr *)&client_addr, client_struct_length);
            } else {
                // Afficher l'id_client et la receptionAjout
                printf("L'user %s souhaite crediter de %f\n", clientDemandeId, receptionAjout);
                valeurSolde = valeurSolde + receptionAjout; // Addition
                sendto(socketSocket, envoiConfirmationAjout, strlen(envoiConfirmationAjout) + 1, 0, (struct sockaddr *)&client_addr, client_struct_length);
                printf("L'user %s vient de crediter la somme de %f\n", clientDemandeId, receptionAjout);
                
                // Mise à jour de l'historique
                for (int i = 9; i > 0; i--) {
                    tabHistorique[i] = tabHistorique[i - 1];
                }
                tabHistorique[0] = receptionAjout;
            }
        }
        // Sinon si choixNum = 2 qui correspond a RETRAIT
        else if (choixNum == 2) {
            // Envoi de QuestionRetrait
            sendto(socketSocket, envoiQuestionRetrait,strlen(envoiQuestionRetrait) + 1, 0, (struct sockaddr *)&client_addr, client_struct_length);
            // Reception du retrait cad le solde a debite
            recvfrom(socketSocket, &receptionRetrait, sizeof(float), 0,(struct sockaddr *)&client_addr, &client_struct_length);
            // Si receptionRetrait = 0
            if (receptionRetrait == 0) {
                // Envoi du MessageRetrait
                sendto(socketSocket, envoiMessageRetrait,strlen(envoiMessageRetrait) + 1, 0, (struct sockaddr *)&client_addr, client_struct_length);
            }
            // Sinon (si receptionRetrait != 0)
            else {
                // Si receptionRetrait < 0
                if (receptionRetrait < 0) {
                    // Valeur negative transforme en valeur positive
                    receptionRetrait = -receptionRetrait;
                }
                // Afficher l'id_client et la receptionAjout qui correspond a la valeur
                // que l'user veut crediter
                printf("L'user %s souhaite retrait de %f\n", clientDemandeId,receptionRetrait);
                
                // Envoi de la valeur du solde actuel
                sendto(socketSocket, &envoiValeurSolde, sizeof(float) + 1, 0, (struct sockaddr *)&client_addr, client_struct_length);
                // Si receptionRetrait > valeurSolde
                if (receptionRetrait > valeurSolde) {
                    // Reception de MessageRetrait
                    sendto(socketSocket, envoiMessageRetrait2,sizeof(envoiMessageRetrait2), 0, (struct sockaddr *)&client_addr, client_struct_length);
                }
                else {
                    // Soustraction
                    valeurSolde = valeurSolde - receptionRetrait;
                    
                    // Envoi de envoiConfirmationRetrait
                    sendto(socketSocket, envoiConfirmationRetrait,
                           strlen(envoiConfirmationRetrait) + 1, 0, (struct sockaddr *)&client_addr, client_struct_length);
                    // Afficher l'id_client et la receptionAjout qui correspond a la valeur que l'user veut crediter
                    printf("L'user %s vient de debiter la somme de %f\n", clientDemandeId, receptionRetrait);
                    
                    // Mise à jour de l'historique
                    for (int i = 9; i > 0; i--) {
                        tabHistorique[i] = tabHistorique[i - 1];
                    }
                    tabHistorique[0] = -receptionRetrait;
                }
            }
        }
        // Sinon si choixNum = 3 qui correspond a SOLDE
        else if (choixNum == 3) {
            sprintf(solde, "Votre solde actuel est : %.2f", valeurSolde);
            printf("solde : %s\n", solde);
            // Envoi du solde
            sendto(socketSocket, solde, strlen(solde) + 1, 0, (struct sockaddr *)&client_addr, client_struct_length);
            
            // Afficher le message de consultation de solde de l'id_client
            printf("L'user %s consulte son SOLDE\n", clientDemandeId);
        }
        // Sinon si choixNum = 4 qui correspond a OPERATIONS
        else if (choixNum == 4) {
            // Envoi de l'historique au client
            for (int i = 0; i < 10; i++) {
                sendto(socketSocket, &tabHistorique[i], sizeof(float), 0, (struct sockaddr *)&client_addr, client_struct_length);
            }
            
            // Envoi d'un message de fin d'historique ou d'une indication pour revenir au menu
            char finHistorique[] = "Fin de l'historique";
            sendto(socketSocket, finHistorique, strlen(finHistorique) + 1, 0, (struct sockaddr *)&client_addr, client_struct_length);
        }
        
        // Sinon si choixNum = 5 qui correspond a la deconnexion
        else if (choixNum == 5) {
            // Envoi du message de deconnexion
            sendto(socketSocket, envoiMessageDeconnexion,strlen(envoiMessageDeconnexion) + 1, 0,(struct sockaddr *)&client_addr, client_struct_length);
            // Afficher le nom de l'id_client
            printf("L'user %s vient de se deconnecter\n", clientDemandeId);
            // Envoi du caractere point d'exclamation
            sendto(socketSocket, envoiCaractereDeconnexion,strlen(envoiCaractereDeconnexion) + 1, 0,(struct sockaddr *)&client_addr, client_struct_length);
        }
        // Sinon (si aucun des choixNum ne correspond a ce qui est attendu)
        /*(choixNum != 1 || choixNum != 2 || choixNum != 3 || choixNum != 4 ||
         choixNum != 5)*/
        else {
            // Envoi du message ChoixNum
            sendto(socketSocket, envoiChoixNum, strlen(envoiChoixNum) + 1, 0,(struct sockaddr *)&client_addr, client_struct_length);
        }
    }
    // Close the socket:
    close(socketSocket);
    return 0;
}
