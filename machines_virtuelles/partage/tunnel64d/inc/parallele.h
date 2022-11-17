// Prorotypes de fonctions permettant au tunnel d'être bidirectionnel

#ifndef PARALLELE_H_
#define PARALLELE_H_

typedef struct{
  int df;               // Le descripteur de fichier (l'interface TUN)
  char *hote;           // Le nom de l'hôte (si besoin)
  char *port;           // Le port où écouter/écrire
} donnees_tunnel_t;

// Permet de démarrer parrallèlement le tunnel dans les deux directions
void demarrer_tunnel(char *interface_name, char *hote, char *port);

#endif
