// Prorotypes de fonctions permettant au tunnel d'être bidirectionnel

#ifndef PARALLELE_H_
#define PARALLELE_H_

typedef struct{
  char dev[42];         // Le descripteur de fichier (l'interface TUN)
  char portout[8];      // Port où écrire
  char portin[8];       // Port où écouter
  char lan[42];         // LAN à atteindre par le tunnel
  char ipout[42];       // IP à atteindre via la socket
} info_config_t;

typedef struct{
  int df;               // Le descripteur de fichier (l'interface TUN)
  char *hote;           // Le nom de l'hôte (si besoin)
  char *portout;        // Le port où écrire
  char *portin;         // Le port où écouter
} donnees_tunnel_t;

// Permet de démarrer parallèlement le tunnel dans les deux directions
void demarrer_tunnel(info_config_t infos);

#endif
