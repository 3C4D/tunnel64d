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

#define MAXLIGNE 80

// Retransmet par TCP le contenu d'une interface vers l'autre extremité
void ext_in(int src, char *hote, char *port){
  struct addrinfo *resol;     // Structure pour la résolution de nom
  char *ipv6_tmp;             // Notation IPv6
  char ip[NI_MAXHOST];        // Addresse IPv4 (noation pointée)
  int sd;                     // Descripteur de fichier de la socket

  // Résolution de l'hôte
  if(getaddrinfo(hote, port, NULL, &resol) < 0){
    fprintf(stderr, "Erreur durant la résolution de l'adresse, ARRET...\n");
    exit(-1);
  }

  // Allocation de l'adresse IPv6
  ipv6_tmp = malloc(INET6_ADDRSTRLEN);
  if(ipv6_tmp == NULL){
    fprintf(stderr, "Erreur d'allocation, ARRET...\n");
    exit(-1);
  }

  sprintf(
    ip,
    "%s",
    inet_ntop(
      AF_INET6,
      ((struct sockaddr_in6*)resol->ai_addr)->sin6_addr.s6_addr,
      ipv6_tmp,
      INET6_ADDRSTRLEN
    )
  );

  // Création d'une socket TCP/IP
  if((sd=socket(resol->ai_family, resol->ai_socktype, resol->ai_protocol)) < 0){
    fprintf(stderr, "Erreur durant l'allocation de la socket, ARRET...\n");
    exit(-1);
  }

  printf("\nNuméro de socket : %i\n\nTentative de connexion %s %s\n\n", sd, ip, port);

  // Tentative de connexion à l'hôte
  if(connect(sd, resol->ai_addr, sizeof(struct sockaddr_in6)) < 0){
    fprintf(stderr, "Erreur de connexion à l'hôte demandé, ARRET...\n");
    exit(-1);
  }

  // Libération de la mémoire de la structure de résolution
  freeaddrinfo(resol);

  // On ne souhaite pas de flags dans l'appel à send, c'est équivalent à write
  // On peut donc directement transferer d'un descripteur à un autre
  transfert(src, sd);

  /* Destruction de la socket */
  close(sd);

  printf("\nFin de la session.\n\n");
}
