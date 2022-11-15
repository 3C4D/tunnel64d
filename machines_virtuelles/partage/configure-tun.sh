# Fichier de configuration de l'interface TUN

# On active l'interface au cas ou elle soit dans l'état DOWN
ip link set tun0 up

# On ajoute l'IPv6 à l'interface
ip -6 a add fc00:1234:ffff::1/64 dev tun0
