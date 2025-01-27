Application de gestion de compte bancaire

Cette application permet aux utilisateurs de gérer leur compte bancaire en effectuant des opérations telles que le crédit, le débit, la consultation du solde et la visualisation de l'historique.
Compilation
Pour compiler l'application, suivez les étapes ci-dessous :
1.	Assurez-vous que vous avez installé un compilateur C (par exemple, GCC).
2.	Ouvrez un terminal et placez-vous dans le répertoire contenant le fichier "server.c" de l'application.
3.	Utilisez les commandes suivantes pour compiler les fichiers source (server et client) chacune dans un terminal différent :
-gcc server.c -o server
-gcc client.c -o client


Exécution
Une fois l'application compilée, suivez les étapes ci-dessous pour l'exécuter :
1.	Assurez-vous que le fichier exécutable "server" a été généré avec succès lors de l'étape de compilation.
2.	Ouvrez un terminal et placez-vous dans le répertoire contenant le fichier exécutable « server » ensuite « client » .
3.	Utilisez les commandes suivantes pour démarrer le serveur ensuite le client :
-./server
-./client


Identification 
TCP
 - Identifiant (test) (essai)
 - Numero de compte (00000001)(00000002)
 - Mot de passe (hein)(de)
UDP
 - Identifiant (test)
 - Mot de passe (hein)

Fonctionnalités
Le programme offre les fonctionnalités suivantes :

1. AJOUT : L'utilisateur peut ajouter des fonds à son compte bancaire.
2. RETRAIT : L'utilisateur peut retirer des fonds de son compte bancaire.
3. SOLDE : L'utilisateur peut consulter le solde actuel de son compte bancaire.
4. HISTORIQUE : L'utilisateur peut afficher les 10 dernières opérations effectuées sur son compte bancaire.
5. EXIT  : L'utilisateur peut quitter le programme.

Choisissez le numéro de la commande souhaitée à exécuter et suivez les commandes .
