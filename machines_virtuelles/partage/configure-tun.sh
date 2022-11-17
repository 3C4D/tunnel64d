# Fichier de configuration de l'interface TUN

# Activation de tun0 dans le cas ou elle serait inactive
ip link set tun0 up

# Ajout d'une IPv6 à tun0
ip -6 a add fc00:1234:ffff::1/64 dev tun0
