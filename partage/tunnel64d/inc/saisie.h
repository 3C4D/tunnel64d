// Prorotypes des fonctions de saisie (et structures)

#ifndef SAISIE_H_
#define SAISIE_H_

#define FICHIER_CONF "/vagrant/params_VM1"

typedef struct{
  char dev[42];
  char ipin[42];
  char ipout[42];
  char portin[8];
  char portout[8];
} info_config;

#endif
