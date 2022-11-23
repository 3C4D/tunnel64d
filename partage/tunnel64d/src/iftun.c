#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

// Permet d'allouer une interface TUN
int tun_alloc(char *dev){
  struct ifreq ifr;
  int fd, err;

  if((fd = open("/dev/net/tun", O_RDWR)) < 0){
    fprintf(stderr, "Erreur d'allocation d'une interface TUN, ARRET...\n");
    exit(-1);
  }

  memset(&ifr, 0, sizeof(ifr));

  ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
  if(*dev){
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  }

  if((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0){
    close(fd);
    return err;
  }

  strcpy(dev, ifr.ifr_name);
  return fd;
}

// Envoi perpetuel de ce qui arrive dans src dans dst
void transfert(int src, int dest){
  long nb_lu;
  char c[1500];

  if(src < 0 || dest < 0){  // Vérification des descripteurs
    fprintf(stderr, "Mauvais descripteurs de fichiers, transfert, ARRET...\n");
    exit(-1);
  }

  // On lit des caractères sur src continuellement
  while(1){
    nb_lu = read(src, c, 1500);
    write(dest, c, nb_lu);
  }
}
