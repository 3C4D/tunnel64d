// Fonction principale du programme

#include <stdlib.h>
#include <stdio.h>
#include "iftun.h"

int main(int argc, char **argv){
  int tunfd;

  printf("Création de %s\n", argv[1]);

  tunfd = tun_alloc(argv[1]);

  printf("Faire la configuration de %s...\n", argv[1]);

  printf("Appuyez sur une touche pour continuer\n");

  getchar();

  printf("Interface %s Configurée:\n",argv[1]);

  system("ip addr");

  printf("Transfert initié sur %s\n", argv[1]);

  printf("%d\n", tunfd);

  transfert(tunfd, 1);

  exit(0);
}
