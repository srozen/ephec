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

#########
## FW1 ##
#########

## POLICIES

  iptables -P INPUT DROP
  iptables -P OUTPUT DROP
  iptables -P FORWARD DROP


  iptables -N LOG_DROP
  iptables -A LOG_DROP -j LOG --log-prefix '[IPTABLES DROP] = '
  iptables -A LOG_DROP -j DROP

  iptables -N LOG_ACCEPT
  iptables -A LOG_ACCEPT -j LOG --log-prefix '[IPTABLES ACCEPT] = '
  iptables -A LOG_ACCEPT -j ACCEPT

## POSTROUTING [VALID]

  iptables -t nat -F POSTROUTING
  iptables -t nat -A POSTROUTING -s 192.168.1.1/24 -j MASQUERADE
  iptables -t nat -A POSTROUTING -s 192.168.2.1/24 -j MASQUERADE
  iptables -t nat -A POSTROUTING -s 192.168.3.1/24 -j MASQUERADE
  iptables -t nat -A POSTROUTING -s 192.168.7.1/24 -j MASQUERADE

## PREROUTING [VALID]

### HTTP
  iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 80 -j DNAT --to 192.168.7.10:80
  iptables -t nat -A PREROUTING -i eth0 -p udp --dport 80 -j DNAT --to 192.168.7.10:80

### HTTPS
  iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 443 -j DNAT --to 192.168.7.10:443
  iptables -t nat -A PREROUTING -i eth0 -p udp --dport 443 -j DNAT --to 192.168.7.10:443

### DNS
  iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 53 -j DNAT --to 192.168.7.11:53
  iptables -t nat -A PREROUTING -i eth0 -p udp --dport 53 -j DNAT --to 192.168.7.11:53

### MAIL
  iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 25 -j DNAT --to 192.168.2.13:25
  iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 143 -j DNAT --to 192.168.2.13:143
  iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 993 -j DNAT --to 192.168.2.13:993

### RSYNC
  iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 873 -j DNAT --to 192.168.7.12:873

### SSH
  iptables -t nat -A PREROUTING -i eth0 -p tcp --dport 22 -j DNAT --to 192.168.7.12:22

## Règles d'acceptance

### Machines DMZ SANDWICH

#### DNS

iptables -A FORWARD -p tcp -i eth3 -s 192.168.2.10 -o eth0 --dport 53 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -A FORWARD -p udp -i eth3 -s 192.168.2.10 -o eth0 --dport 53 -m state --state NEW,ESTABLISHED -j ACCEPT
iptables -A FORWARD -p tcp -i eth0 -d 192?168.2.10 -o eth3 --sport 53 -m state --state ESTABLISHED -j ACCEPT
iptables -A FORWARD -p udp -i eth0 -d 192?168.2.10 -o eth3 --sport 53 -m state --state ESTABLISHED -j ACCEPT

### Machines R1 et R2

#### Autoriser R1 à contacter PROCESSOR en SSH

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.10 -o eth2 -d 192.168.4.10 --dport 22 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth2 -s 192.168.4.10 -o eth4 -d 192.168.3.10 --sport 22 -m state --state ESTABLISHED -j LOG_ACCEPT

#### Autoriser R2 à utiliser le serveur SSH

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.11 -o eth2 -d 192.168.1.10 --dport 22 -m state --state NEW, ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth2 -s 192.168.1.10 -o eth4 -d 192.168.3.11 --sport 22 -m state --state ESTABLISHED -j LOG_ACCEPT

#### Autoriser Rs à accéder à HTTP(S)

  iptables -A FORWARD -p tcp -i eth

#### Autoriser Rs à accéder au serveur MAIL

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.1/24 -o eth3 -d 192.168.5.13 -m multiport --destination-port 25,143,993 -m state --state NEW, ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth3 -s 192.168.5.13 -o eth4 -s 192.168.3.1/24 -m multiport --source-port 25,143,993 -m state --state ESTABLISHED -j LOG_ACCEPT

#### Autoriser Rs à accéder à RSYNC

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.1/24 -o eth1 -d 192.168.7.12 --dport 873 -m state --state NEW, ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth1 -s 192.168.7.12 -o eth4 -d 192.168.3.1/24 --sport 873 -m state --state ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.1/24 -o eth1 -d 192.168.7.12 --dport 22 -m state --state NEW, ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth1 -s 192.168.7.12 -o eth4 -d 192.168.3.1/24 --sport 22 -m state --state ESTABLISHED -j LOG_ACCEPT

#### Autoriser Rs à accéder à NFS

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.1/24 -o eth2 -d 192.168.1.12 -m multiport --destination-port 111,2049 -m state --state NEW, ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth2 -s 192.168.1.12 -o eth4 -d 192.168.1.12 -m multiport --source-port 111,2049 -m state --state ESTABLISHED

  iptables -A FORWARD -p udp -i eth4 -s 192.168.3.1/24 -o eth2 -d 192.168.1.12 -m multiport --destination-port 111,2049 -m state --state NEW, ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p udp -i eth2 -s 192.168.1.12 -o eth4 -d 192.168.1.12 -m multiport --source-port 111,2049 -m state --state ESTABLISHED

#### Autoriser Rs à accéder au DNS et LDNS

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.0/24 -o eth3 -d 192.168.2.10 --dport 53 -m state --state NEW,ESTABLISHED -j ACCEPT
  iptables -A FORWARD -p udp -i eth4 -s 192.168.3.0/24 -o eth3 -d 192.168.2.10 --dport 53 -m state --state NEW,ESTABLISHED -j ACCEPT
  iptables -A FORWARD -p tcp -i eth3 -s 192.168.2.10 -o eth4 -d 192.168.3.0/24 --sport 53 -m state --state ESTABLISHED -j ACCEPT
  iptables -A FORWARD -p udp -i eth3 -s 192.168.2.10 -o eth4 -d 192.168.3.0/24 --sport 53 -m state --state ESTABLISHED -j ACCEPT

#### Autoriser Rs à accéder à FTP

iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.1/24 -o eth2 -d 192.168.1.11 -m multiport --destination-port 20,21 --state NEW, ESTABLISHED -j LOG_ACCEPT

iptables -A FORWARD -p tcp -i eth2 -s 192.168.1.11 -o eth4 -d 192.168.1.12 -m multiport --source-port 20,21 --state ESTABLISHED

#########
## FW2 ##
#########

## Utilisation des proxies Web

### HTTP
  * Changer la ligne http_port et ajouter "transparent" a la fin pour faire du proxy transparent (forcément non?)

  iptables -t nat -A PREROUTING -i eth1 -s 192.168.6.0/24 -p tcp --dport 80 -j DNAT --to-destination 192.168.5.11:3128

### HTTPS
  * Le SSL a ici une couille dans le pâté, SQUID a pas l'air configuré pour gérer ça, néamoins avec un ajout de transparent
  * Comme pour l'autre squid, lynx a l'air permissif

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
  iptables -A FORWARD -p tcp -i eth0 -s 192.168.5.13 -o eth1 -s 192.168.6.0/24 -j LOG_ACCEPT

### POUBELLE

  iptables -A FORWARD -j LOG_DROP
  iptables -A INPUT -j LOG_DROP
  iptables -A OUTPUT -j LOG_DROP

#########
## FW3 ##
#########

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

### SSH

  * Autorise forwarding d'une connexion NEW ou ETABLIE en ssh depuis R1 vers Processor

  iptables -A FORWARD -p tcp -i eth1 -s 192.168.3.10 -o eth0 -d 192.168.4.10 --dport ssh --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth0 -s 192.168.4.10 -o eth1 -d 192.168.3.10 --sport ssh --state ESTABLISHED -j LOG_ACCEPT

  * Autorise le forwarding d'une connexion NEW ou ETABLIE en ssh depuis SSH vers Processor et inversément pour une
  * établie pour les réponses de SSH

  iptables -A FORWARD -p tcp -i eth1 -s 192.168.1.10 -o eth0 -d 192.168.4.10 --dport ssh --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth0 -s 192.168.4.10 -o eth1 -d 192.168.1.10 --sport ssh --state ESTABLISHED -j LOG_ACCEPT

### FTP

  * Processor - Peut communiquer avec le FTP pour obtenir les fichiers

  iptables -A FORWARD -p tcp -i eth0 -s 192.168.4.10 -o eth1 -d 192.168.1.12 --sport 20:21 --dport 20:21 --state NEW, ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth1 -s 192.168.1.12 -o eth0 -d 192.168.4.10 --sport 20:21 --dport 20:21 --state ESTABLISHED -j LOG_ACCEPT

### POUBELLE

  iptables -A FORWARD -j LOG_DROP
  iptables -A INPUT -j LOG_DROP
  iptables -A OUTPUT -j LOG_DROP
