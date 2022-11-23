# Fichier de configuration de l'interface TUN

# Le fichier doit être exécuté avec deux arguments
if [ $# -eq 2 ]; then
  # Activation de l'interface dans le cas ou elle serait inactive
  ip link set $1 up

  # Ajout d'une IPv6 à tun0
  ip -6 addr add fc00:1234:ffff::1/64 dev $1

  # Ajout du routage vers le LAN voulu par l'interface
  ip -6 route add $2 via fc00:1234:ffff::10
else
  echo "Le nombre d'argument est insuffisant"
fi
