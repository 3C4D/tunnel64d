// Fonction principale du programme

#include <stdlib.h>
#include <stdio.h>
#include "parallele.h"

int main(int argc, char **argv){
  if(argc < 2){
    fprintf(stderr, "Nombre d'argument invalide\n");
    exit(-1);
  }

  if(atoi(argv[1]) == 1){
    demarrer_tunnel("tun0", "172.16.2.163", "123");
  }
  if(atoi(argv[1]) == 2){
    demarrer_tunnel("tun0", "172.16.2.131", "123");
  }
  else{
    fprintf(stderr, "Argument invalide\n");
  }

  // demarrer_tunnel(argv[1], argv[2], argv[3]);

  exit(0);
}
