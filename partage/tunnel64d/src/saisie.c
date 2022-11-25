// Fonctions de saisie

#include <stdlib.h>
#include <stdio.h>
#include "saisie.h"

// Saisie du fichier de configuration de la machine pour le tunnel
info_config_t saisie_config(){
  info_config_t infos;
  FILE *conf;
  char c;

  char *format[] = {  // Différents formats à chercher
    "dev=%s\n",
    "portin=%s\n",
    "portout=%s\n",
    "ipout=%s\n",
  };

  char *refs[] = {    // Références où stocker les informations trouvées
    infos.dev,
    infos.portin,
    infos.portout,
    infos.ipout
  };

  // Vérification de l'existence du fichier
  if((conf = fopen(FICHIER_CONF, "r")) == NULL){
    fprintf(stderr, "Erreur, impossible d'ouvrir %s, ARRET...\n", FICHIER_CONF);
    exit(-1);
  }

  for(int i = 0; i < 4; i++){
    while(!fscanf(conf, format[i], refs[i])){
      c = '$';
      while(c != EOF && c != '\n'){ // On passe à la ligne suivante
        c = fgetc(conf);
      }
    }
  }

  return infos;
}
