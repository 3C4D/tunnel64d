// Fonctions gérant les extrémités du tunnel

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "iftun.h"

// Crée un serveur et écoute sur un port donné, redirige sur une interface
void ext_out(int dest, char *port){
  struct addrinfo * resol;    // Structure de résolution

  // Configuration : toute interface, mode connecté
  struct addrinfo indic = {AI_PASSIVE,            // Toute interface
                          PF_INET,SOCK_STREAM,0,  // Mode connecté
                          0,NULL,NULL,NULL};

  struct sockaddr_in client;  // Adresse du client (de la socket du client)
  char hotec[NI_MAXHOST];     // Nom d'hote du client
  char portc[NI_MAXSERV];     // Port du client
  int sd, nd;                 // Descripteurs de fichier de la socket
  int len, port_on;

  len = sizeof(struct sockaddr_in);
  port_on = 1;

  // Résolution
  if(getaddrinfo(NULL, port, &indic, &resol) < 0){
    fprintf(stderr, "Erreur durant la résolution de l'adresse, ARRET...\n");
    exit(-1);
  }

  // Création de la socket TCP/IP
  if((sd = socket(resol->ai_family,resol->ai_socktype,resol->ai_protocol)) < 0){
    fprintf(stderr, "Erreur durant l'allocation de la socket, ARRET...\n");
    exit(-1);
  }

  // On s'assure que le port soit réutilisable rapidement
  port_on = 1;
  if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &port_on, sizeof(port_on)) < 0){
    fprintf(stderr, "Erreur, options de la socket, ARRET...\n");
    exit(-1);
  }

  // Association de la socket à l'adresse par résolution
  if(bind(sd, resol->ai_addr, sizeof(struct sockaddr_in)) < 0){
    fprintf(stderr, "Erreur durant l'association de la socket, ARRET...\n");
    exit(-1);
  }

  // Libération de la mémoire de la structure de résolution
  freeaddrinfo(resol);

  // La socket est prete à écouter sur le port
  if(listen(sd, SOMAXCONN) < 0){
    fprintf(stderr, "Erreur durant l'initialisation de l'ecoute, ARRET...\n");
    exit(-1);
  }

  while(1){ // Attente continuelle de clients
    if((nd = accept(sd, (struct sockaddr *)&client, (socklen_t*)&len)) < 0){
      fprintf(stderr, "Erreur durant l'acceptation de connexion, ARRET...\n");
      exit(-1);
    }

    if(
      getnameinfo(
        (struct sockaddr*)&client, len, hotec, NI_MAXHOST,
        portc, NI_MAXSERV, 0
      ) < 0 ){
      fprintf(stderr, "Erreur durant la resolution du client, ARRET...\n");
    }else{
      fprintf(stderr, "\nConnexion etablie avec %s port=%s\n", hotec, portc);
    }

    transfert(nd, dest);
  }
}


// Retransmet par TCP le contenu d'une interface vers l'autre extremité
void ext_in(int src, char *hote, char *port){
  struct addrinfo *resol;     // Structure pour la résolution de nom
  char ip[NI_MAXHOST];        // Addresse IPv4 (noation pointée)
  int sd;                     // Descripteur de fichier de la socket

  // Résolution de l'hôte
  if(getaddrinfo(hote, port, NULL, &resol) < 0){
    fprintf(stderr, "Erreur durant la resolution de l'adresse, ARRET...\n");
    exit(-1);
  }

  // Extraction de l'IP
  sprintf(ip, "%s", inet_ntoa(((struct sockaddr_in*)resol->ai_addr)->sin_addr));

  // Création d'une socket TCP/IP
  if((sd=socket(resol->ai_family, resol->ai_socktype, resol->ai_protocol)) < 0){
    fprintf(stderr, "Erreur durant l'allocation de la socket, ARRET...\n");
    exit(-1);
  }

  fprintf(stderr, "\nTentative de connexion avec %s\n\n", ip);

  // Tentative de connexion à l'hôte
  while(connect(sd, resol->ai_addr, sizeof(struct sockaddr_in)) < 0){
    fprintf(stderr, ".");
    sleep(1);
  }
  putchar('\n');

  // Libération de la mémoire de la structure de résolution
  freeaddrinfo(resol);

  // On ne souhaite pas de flags dans l'appel à send, c'est équivalent à write
  // On peut donc directement transferer d'un descripteur à un autre
  transfert(src, sd);

  /* Destruction de la socket */
  close(sd);

  printf("\nFin de la session.\n\n");
}
