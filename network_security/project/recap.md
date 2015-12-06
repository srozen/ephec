# Activer internet sur netkit

- Déterminer sur quelle interface tourne netkit sur la vm (nk_tap_user) et
déterminer l'ip de celle-ci (10.1.0.15)
- Définir, sur router du netkit, la route par défaut vers cette interface : "route add default gw 10.1.0.15"
- Sur la vm, activer le nat pour que les paquets transitent.
- D'abord déterminer sur quelle interface la vm est reliée au pc physique (eth6)
- "iptables -t nat -I POSTROUTING 1 -o eth6 -j MASQUERADE"
- "iptables -I FORWARD 1 -i nk_tap_user -j ACCEPT"
- "echo "1" > /proc/sys/net/ipv4/ip_forward"

# DEBUG

iptables -N LOG_DROP
iptables -A LOG_DROP -j LOG --log-prefix '[Dropped] : '
iptables -A LOG_DROP -j DROP

iptables -N LOG_ACCEPT
iptables -A LOG_ACCEPT -j LOG --log-prefix '[Accepted] : '
iptables -A LOG_ACCEPT -j ACCEPT

########
## F1 ##
########

## POSTROUTING [VALID]

iptables -t nat -F POSTROUTING
iptables -t nat -A POSTROUTING -s 192.168.1.1/24 -j MASQUERADE
iptables -t nat -A POSTROUTING -s 192.168.2.1/24 -j MASQUERADE
iptables -t nat -A POSTROUTING -s 192.168.3.1/24 -j MASQUERADE
iptables -t nat -A POSTROUTING -s 192.168.7.1/24 -j MASQUERADE

## PREROUTING []

########
## F2 ##
########

## Utilisation des proxies Web

### HTTP
  * Changer la ligne http_port et ajouter "transparent" a la fin pour faire du proxy transparent (forcément non?)
  iptables -t nat -A PREROUTING -i eth1 -s 192.168.6.0/24 -p tcp --dport 80 -j DNAT --to-destination 192.168.5.11:3128

  ### HTTPS
  * Le SSL a ici une couille dans le pâté, SQUID a pas l'air configuré pour gérer ça, néamoins avec un ajout de transparent
  * Comme pour l'autre squid, lynx a l'air permissif
  iptables -t nat -A PREROUTING -i eth1 -s 192.168.6.0/24 -p tcp --dport 443 -j DNAT --to-destination 192.168.5.12:3128


## Règles d'acceptance

### DNS
  iptables -A FORWARD -p tcp --dport 53 -i eth1 -s 192.168.6.0/24 -o eth0 -d 192.168.5.10 -j ACCEPT
  iptables -A FORWARD -p tcp --sport 53 -i eth0 -s 192.168.5.10 -o eth1 -d 192.168.6.0/24 -j ACCEPT
  iptables -A FORWARD -p udp --dport 53 -i eth1 -s 192.168.6.0/24 -o eth0 -d 192.168.5.10 -j ACCEPT
  iptables -A FORWARD -p udp --sport 53 -i eth0 -s 192.168.5.10 -o eth1 -d 192.168.6.0/24 -j ACCEPT

### HTTP
  iptables -A FORWARD -p tcp --dport 3128 -i eth1 -s 192.168.6.0/24 -o eth0 -d 192.168.5.11 -j ACCEPT
  iptables -A FORWARD -p tcp --sport 3128 -i eth0 -s 192.168.5.11 -o eth1 -d 192.168.6.0/24 -j ACCEPT

### MAIL
  iptables -A FORWARD -p tcp --dport 25 -i eth1 -s 192.168.6.0/24 -o eth0 -d 192.168.5.13 -j ACCEPT
  iptables -A FORWARD -p tcp --dport 143 -i eth1 -s 192.168.6.0/24 -o eth0 -d 192.168.5.13 -j ACCEPT
  iptables -A FORWARD -p tcp --dport 993 -i eth1 -s 192.168.6.0/24 -o eth0 -d 192.168.5.13 -j ACCEPT
  iptables -A FORWARD -p tcp -i eth0 -s 192.168.5.13 -o eth1 -s 192.168.6.0/24 -j ACCEPT

#########
## FW3 ##
#########
