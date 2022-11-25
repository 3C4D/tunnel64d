# Fichier de configuration de l'interface TUN

# Le fichier doit être exécuté avec un argument
if [ $# -eq 1 ]; then
  # Activation de l'interface dans le cas ou elle serait inactive
  ip link set $1 up

  # Ajout d'une IPv6 à tun0
  ip -6 addr add fc00:1234:ffff::1/32 dev $1
else
  echo "Le nombre d'argument est insuffisant"
fi
