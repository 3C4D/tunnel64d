// Fonctions de saisie

#include <stdlib.h>
#include <stdio.h>
#include "saisie.h"

info_config saisie_config(){
  info_config infos;
  FILE *conf;
  char c;

  char *format[] = {  // Différents formats à chercher
    "dev=%s\n",
    "ipin=%s\n",
    "portin=%s\n",
    "ipout=%s\n",
    "portout=%s\n",
  };

  char *refs[] = {    // Références où stocker les informations trouvées
    infos.dev,
    infos.ipin,
    infos.portin,
    infos.ipout,
    infos.portout
  };

  // Vérification de l'existence du fichier
  if((conf = fopen(FICHIER_CONF, "r")) == NULL){
    fprintf(stderr, "Erreur, impossible d'ouvrir %s, ARRET...\n", FICHIER_CONF);
    exit(-1);
  }

  for(int i = 0; i < 5; i++){
    while(!fscanf(conf, format[i], refs[i])){
      c = '$';
      while(c != EOF && c != '\n'){ // On passe à la ligne suivante
        c = fgetc(conf);
      }

      if(c == EOF){ // Fin de fichier atteinte sans tout trouvé
        fprintf(stderr, "Erreur de formatage : %s, ARRET...\n", FICHIER_CONF);
        exit(-1);
      }
    }
  }

  return infos;
}
