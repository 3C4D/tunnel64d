// Prorotypes des fonctions de la bibliothèque iftun

#ifndef IFTUN_H_
#define IFTUN_H_

// Permet d'allouer une interface TUN
int tun_alloc(char *dev);

// Envoi perpetuel de ce qui arrive dans src dans dst
void transfert(int src, int dst, int out);

#endif
