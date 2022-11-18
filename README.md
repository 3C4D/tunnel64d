# tunnel64d

Mise en place d'un tunnel entre deux machines virtuelles permettant une
transition entre des réseaux IPv4 et IPv6

## Machines virtuelles

Pour démarrer une machine virtuelle, on se positionne dans son répertoire, par
exemple `VM1`, puis on exécute la commande `vagrant up`.

## Compilation du programme tunnel64d

Afin de compiler le programme tunnel64d depuis l'une des machines virtuelles, il
faut se mettre dans le répertoire `/mnt/partage/tunnel64d/` et exécuter la
commande `make`

## Utilisation

Pour lancer le tunnel sur la machine VM1, il faut exécuter la commande `./bin/tunnel64d 1 tun0` depuis le répertoire `/mnt/partage/tunnel64d/`.

Depuis le meme répertoire sur la machine VM3, on peut exécuter la commande
`./bin/tunnel64d 2 tun0` pour lancer le tunnel sur cette machine.
