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
  iptables -t nat -A POSTROUTING -o eth0 -s 192.168.1.1/24 -j MASQUERADE
  iptables -t nat -A POSTROUTING -o eth0 -s 192.168.2.1/24 -j MASQUERADE
  iptables -t nat -A POSTROUTING -o eth0 -s 192.168.3.1/24 -j MASQUERADE
  iptables -t nat -A POSTROUTING -o eth0 -s 192.168.7.1/24 -j MASQUERADE

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

### EXTERIEUR DMZ PUBLIQUE

  iptables -A FORWARD -p tcp -i eth0 -d 192.168.7.10 -o eth1 -m multiport --destination-port 80,443 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth1 -s 192.168.7.10 -o eth0 -m multiport --source-port 80,443 -m state --state ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth0 -d 192.168.7.11 -o eth1 --dport 53 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth1 -s 192.168.7.11 -o eth0 --sport 53 -m state --state ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p udp -i eth0 -d 192.168.7.11 -o eth1 --dport 53 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p udp -i eth1 -s 192.168.7.11 -o eth0 --sport 53 -m state --state ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth0 -d 192.168.7.12 -o eth1 -m multiport --destination-port 80,873 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth1 -s 192.168.7.12 -o eth0 -m multiport --source-port 22,873 -m state --state ESTABLISHED -j LOG_ACCEPT

### Machines DMZ SANDWICH


#### DNS vers extérieur

  iptables -A FORWARD -p tcp -i eth3 -s 192.168.2.10 -o eth0 --dport 53 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p udp -i eth3 -s 192.168.2.10 -o eth0 --dport 53 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth0 -d 192.168.2.10 -o eth3 --sport 53 -m state --state ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p udp -i eth0 -d 192.168.2.10 -o eth3 --sport 53 -m state --state ESTABLISHED -j LOG_ACCEPT

#### HTTP(S) vers extérieur et vers WEB

  iptables -A FORWARD -p tcp -i eth3 -s 192.168.2.11 -o eth0 --dport 80 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p udp -i eth3 -s 192.168.2.12 -o eth0 --dport 443 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth0 -d 192.168.2.11 -o eth3 --sport 80 -m state --state ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p udp -i eth0 -d 192.168.2.12 -o eth3 --sport 443 -m state --state ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth3 -s 192.168.2.11 -o eth1 -d 192.168.7.10 --dport 80 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth1 -s 192.168.7.10 -o eth3 -d 192.168.2.11 --sport 80 -m state --state ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth3 -s 192.168.2.12 -o eth1 -d 192.168.7.10 --dport 443 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth1 -s 192.168.7.10 -o eth3 -d 192.168.2.12 --sport 443 -m state --state ESTABLISHED -j LOG_ACCEPT

#### MAIL vers extérieur

  iptables -A FORWARD -p tcp -i eth3 -s 192.168.2.13 -o eth0 -m multiport --destination-port 25,143,993 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth0 -d 192.168.2.13 -o eth3 -m multiport --source-port 25,143,993 -m state --state ESTABLISHED -j LOG_ACCEPT

### Machines R1 et R2

#### Autoriser R1 à contacter PROCESSOR en SSH

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.10 -o eth2 -d 192.168.4.10 --dport 22 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth2 -s 192.168.4.10 -o eth4 -d 192.168.3.10 --sport 22 -m state --state ESTABLISHED -j LOG_ACCEPT

#### Autoriser Rs à utiliser le serveur SSH

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.0/24 -o eth2 -d 192.168.1.10 --dport 22 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth2 -s 192.168.1.10 -o eth4 -d 192.168.3.0/24 --sport 22 -m state --state ESTABLISHED -j LOG_ACCEPT

#### Autoriser Rs à accéder au server Web

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.0/24 -o eth1 -d 192.168.7.10 --dport 80 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.0/24 -o eth1 -d 192.168.7.10 --dport 443 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth1 -s 192.168.7.10 -o eth4 -d 192.168.3.0/24 --sport 80 -m state --state ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth1 -s 192.168.7.10 -o eth4 -d 192.168.3.0/24 --sport 443 -m state --state ESTABLISHED -j LOG_ACCEPT

#### Autoriser Rs à accéder à l'internet

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.0/24 -o eth0 --dport 80 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.0/24 -o eth0 --dport 443 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth0 -d 192.168.3.0/24 -o eth4 --sport 80 -m state --state ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth0 -d 192.168.3.0/24 -o eth4 --sport 443 -m state --state ESTABLISHED -j LOG_ACCEPT

#### Autoriser Rs à accéder au serveur MAIL

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.0/24 -o eth3 -d 192.168.2.13 -m multiport --destination-port 25,143,993 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth3 -s 192.168.2.13 -o eth4 -d 192.168.3.0/24 -m multiport --source-port 25,143,993 -m state --state ESTABLISHED -j LOG_ACCEPT

#### Autoriser Rs à accéder à RSYNC

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.0/24 -o eth1 -d 192.168.7.12 --dport 873 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth1 -s 192.168.7.12 -o eth4 -d 192.168.3.0/24 --sport 873 -m state --state ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.0/24 -o eth1 -d 192.168.7.12 --dport 22 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth1 -s 192.168.7.12 -o eth4 -d 192.168.3.0/24 --sport 22 -m state --state ESTABLISHED -j LOG_ACCEPT

#### Autoriser Rs à accéder à NFS

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.0/24 -o eth2 -d 192.168.1.12 -m multiport --destination-port 111,2049 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth2 -s 192.168.1.12 -o eth4 -d 192.168.3.0/24 -m multiport --source-port 111,2049 -m state --state ESTABLISHED

  iptables -A FORWARD -p udp -i eth4 -s 192.168.3.0/24 -o eth2 -d 192.168.1.12 -m multiport --destination-port 111,2049 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p udp -i eth2 -s 192.168.1.12 -o eth4 -d 192.168.3.0/24 -m multiport --source-port 111,2049 -m state --state ESTABLISHED

#### Autoriser Mountd

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.0/24 -o eth2 -d 192.168.1.12 -m multiport --destination-port 644,645 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth2 -s 192.168.1.12 -o eth4 -d 192.168.3.0/24 -m multiport --source-port 644,645 -m state --state ESTABLISHED

#### Autoriser Rs à accéder au DNS et LDNS

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.0/24 -o eth3 -d 192.168.2.10 --dport 53 -m state --state NEW,ESTABLISHED -j ACCEPT
  iptables -A FORWARD -p udp -i eth4 -s 192.168.3.0/24 -o eth3 -d 192.168.2.10 --dport 53 -m state --state NEW,ESTABLISHED -j ACCEPT
  iptables -A FORWARD -p tcp -i eth3 -s 192.168.2.10 -o eth4 -d 192.168.3.0/24 --sport 53 -m state --state ESTABLISHED -j ACCEPT
  iptables -A FORWARD -p udp -i eth3 -s 192.168.2.10 -o eth4 -d 192.168.3.0/24 --sport 53 -m state --state ESTABLISHED -j ACCEPT

#### Autoriser Rs à accéder à FTP

  iptables -A FORWARD -p tcp -i eth4 -s 192.168.3.0/24 -o eth2 -d 192.168.1.11 -m multiport --destination-port 21 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT

  iptables -A FORWARD -p tcp -i eth2 -s 192.168.1.11 -o eth4 -d 192.168.3.0/24 -m multiport --source-port 20,21 -m state --state NEW,ESTABLISHED

### POUBELLE

  iptables -A FORWARD -j LOG_DROP
  iptables -A INPUT -j LOG_DROP
  iptables -A OUTPUT -j LOG_DROP
