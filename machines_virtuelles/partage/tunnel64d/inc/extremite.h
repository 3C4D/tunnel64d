// Prorotypes de fonctions gérant les extrémités du tunnel

#ifndef EXTREMITE_H_
#define EXTREMITE_H_

// Crée un serveur et écoute sur un port donné, redirige sur la sortie standard
void ext_out(int dest, char *port);

// Retransmet par TCP le contenu d'une interface vers l'autre extremité
void ext_in(int src, char *hote, char *port);

#endif
