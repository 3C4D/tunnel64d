// Fonctions permettant au tunnel d'être bidirectionnel

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "iftun.h"
#include "extremite.h"
#include "parallele.h"

// Fonction appliquée par le thread lançant ext_out
void *routine_out(void *arg){
  donnees_tunnel_t *donnees = (donnees_tunnel_t *)arg;

  ext_out(donnees->df, donnees->portin);

  return NULL;
}

// Fonction appliquée par le thread lançant ext_in
void *routine_in(void *arg){
  donnees_tunnel_t *donnees = (donnees_tunnel_t *)arg;

  ext_in(donnees->df, donnees->hote, donnees->portout);

  return NULL;
}

// Permet de démarrer parallèlement le tunnel dans les deux directions
void demarrer_tunnel(info_config_t infos){
  pthread_t thread_out, thread_in;
  donnees_tunnel_t donnees;
  char configure[500];

  donnees.df = tun_alloc(infos.dev);
  donnees.portout = infos.portout;
  donnees.portin = infos.portin;
  donnees.hote = infos.ipout;
  printf("\n");

  printf("Creation de l'interface TUN : %s\n", infos.dev);

  // Rédaction de la commande configurant tun0 par le script configure-tun.sh
  snprintf(
    configure,
    sizeof(configure),
    "/mnt/partage/tunnel64d/configure-tun.sh %s",
    infos.dev
  );

  system(configure);

  // Création et lancement des deux threads
  if(pthread_create(&thread_out, NULL, routine_out, (void *)&donnees) != 0){
    fprintf(stderr, "Erreur durant la création d'un thread, ARRET...\n");
    exit(-1);
  }
  if(pthread_create(&thread_in, NULL, routine_in, (void *)&donnees) != 0){
    fprintf(stderr, "Erreur durant la création d'un thread, ARRET...\n");
    exit(-1);
  }

  // Attente des threads (qui sont normalement en boucle infinie)
  pthread_join(thread_out, NULL);
  pthread_join(thread_in, NULL);
}
