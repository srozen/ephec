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

  # Autorise forwarding d'une connexion NEW ou ETABLIE en ssh depuis R1 vers Processor

  iptables -A FORWARD -p tcp -i eth1 -s 192.168.3.10 -o eth0 -d 192.168.4.10 --dport ssh -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth0 -s 192.168.4.10 -o eth1 -d 192.168.3.10 --sport ssh -m state --state ESTABLISHED -j LOG_ACCEPT

  # Autorise le forwarding d'une connexion NEW ou ETABLIE en ssh depuis SSH vers Processor et inversément pour une
  # établie pour les réponses de SSH

  iptables -A FORWARD -p tcp -i eth1 -s 192.168.1.10 -o eth0 -d 192.168.4.10 --dport ssh -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth0 -s 192.168.4.10 -o eth1 -d 192.168.1.10 --sport ssh -m state --state ESTABLISHED -j LOG_ACCEPT

### FTP

  # Processor - Peut communiquer avec le FTP pour obtenir les fichiers

  iptables -A FORWARD -p tcp -i eth0 -s 192.168.4.10 -o eth1 -d 192.168.1.11 --dport 21 -m state --state NEW,ESTABLISHED -j LOG_ACCEPT
  iptables -A FORWARD -p tcp -i eth1 -s 192.168.1.11 -o eth0 -d 192.168.4.10 -m multiport --sport 20,21 -m state --state ESTABLISHED -j LOG_ACCEPT

### POUBELLE

  iptables -A FORWARD -j LOG_DROP
  iptables -A INPUT -j LOG_DROP
  iptables -A OUTPUT -j LOG_DROP
