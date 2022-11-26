# tunnel64d

Mise en place d'un tunnel entre deux machines virtuelles permettant une
transition entre des réseaux IPv4 et IPv6

Un rapport d'avancement du projet est fourni :
`rapport_projet/rapport_tunnel64d.pdf`

## Machines virtuelles

Pour démarrer une machine virtuelle, on se positionne dans son répertoire, par
exemple `VM1`, puis on exécute la commande `vagrant up`.

Pour démarrer toutes les machines, on peut aussi exécuter la commande
`./demarrer_machines.sh`

## Compilation et mise en place du tunnel

Le programme du tunnel est compilé par défaut en lançant la configuration
ansible des machines virtuelles ayant besoin du programme.

Si l'on souhaite compiler le programme manuellement, il faudra se placer dans le
répertoire `/mnt/partage/tunnel64d/` et exécuter la commande `make`.

## Utilisation

Le tunnel est mis en place par défaut en exécutant la configuration ansible des
machines virtuelles ayant besoin du programme.

Afin qu'une machine puisse lancer le tunnel, il faut qu'elle possède dans son
dossier un fichier `tunnel.conf` formaté comme suit :

```
...
dev=...
...
portin=...
...
portout=...
...
lan=...
...
ipout=...
...

```
- dev est l'interface dont nous voulons nous servir pour construire le tunnel
  (exemple : `tun0`).
- portin est le port où l'on souhaite écrire les données transitant par
  l'interface TUN locale
- portout est le port où l'on souhaite recevoir les données émises par l'autre
  extrémité du tunnel.
- lan est le LAN que l'on souhaite atteindre par le tunnel (afin de configurer
  le routage).
- ipout est l'adresse IPv4 de l'autre extrémité du tunnel.

Si l'on souhaite lancer manuellement le tunnel, il faudra exécuter la commande
`/mnt/partage/tunnel64d/bin/tunnel64d`. Le programme doit être compilé au
préalable.
