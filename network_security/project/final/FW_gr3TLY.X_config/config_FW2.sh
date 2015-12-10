#########
## FW2 ##
#########

## Utilisation des proxies Web

### HTTP
  # Changer la ligne http_port et ajouter "transparent" a la fin pour faire du proxy transparent (forcément non?)

  iptables -t nat -A PREROUTING -i eth1 -s 192.168.6.0/24 -p tcp --dport 80 -j DNAT --to-destination 192.168.5.11:3128

### HTTPS
  # Le SSL a ici une couille dans le pâté, SQUID a pas l'air configuré pour gérer ça, néamoins avec un ajout de transparent
  # Comme pour l'autre squid, lynx a l'air permissif

  iptables -t nat -A PREROUTING -i eth1 -s 192.168.6.0/24 -p tcp --dport 443 -j DNAT --to-destination 192.168.5.12:3128


## Règles d'acceptance

### POLICIES

  iptables -P INPUT DROP
  iptables -P OUTPUT DROP
  iptables -P FORWARD DROP

  iptables -N LOG_DROP
  iptables -A LOG_DROP -j LOG --log-prefix '[IPTABLES DROP] = '
  iptables -A LOG_DROP -j DROP

  iptables -N LOG_ACCEPT
  iptables -A LOG_ACCEPT -j LOG --log-prefix '[IPTABLES ACCEPT] = '
  iptables -A LOG_ACCEPT -j ACCEPT

### DNS
  iptables -A FORWARD -p tcp --dport 53 -i eth1 -s 192.168.6.0/24 -o eth0 -d 192.168.5.10 -j LOG_ACCEPT
  iptables -A FORWARD -p tcp --sport 53 -i eth0 -s 192.168.5.10 -o eth1 -d 192.168.6.0/24 -j LOG_ACCEPT
  iptables -A FORWARD -p udp --dport 53 -i eth1 -s 192.168.6.0/24 -o eth0 -d 192.168.5.10 -j LOG_ACCEPT
  iptables -A FORWARD -p udp --sport 53 -i eth0 -s 192.168.5.10 -o eth1 -d 192.168.6.0/24 -j LOG_ACCEPT

### HTTP
  iptables -A FORWARD -p tcp --dport 3128 -i eth1 -s 192.168.6.0/24 -o eth0 -d 192.168.5.11 -j LOG_ACCEPT
  iptables -A FORWARD -p tcp --sport 3128 -i eth0 -s 192.168.5.11 -o eth1 -d 192.168.6.0/24 -j LOG_ACCEPT

### HTTPS
  iptables -A FORWARD -p tcp --dport 3128 -i eth1 -s 192.168.6.0/24 -o eth0 -d 192.168.5.12 -j LOG_ACCEPT
  iptables -A FORWARD -p tcp --sport 3128 -i eth0 -s 192.168.5.12 -o eth1 -d 192.168.6.0/24 -j LOG_ACCEPT

### MAIL
  iptables -A FORWARD -p tcp --dport 25 -i eth1 -s 192.168.6.0/24 -o eth0 -d 192.168.5.13 -j LOG_ACCEPT
  iptables -A FORWARD -p tcp --dport 143 -i eth1 -s 192.168.6.0/24 -o eth0 -d 192.168.5.13 -j LOG_ACCEPT
  iptables -A FORWARD -p tcp --dport 993 -i eth1 -s 192.168.6.0/24 -o eth0 -d 192.168.5.13 -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth0 -s 192.168.5.13 -o eth1 -d 192.168.6.0/24 -j LOG_ACCEPT

### POUBELLE

  iptables -A FORWARD -j LOG_DROP
  iptables -A INPUT -j LOG_DROP
  iptables -A OUTPUT -j LOG_DROP
