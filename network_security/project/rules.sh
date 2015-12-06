#!/bin/bash


##############
# REGLES NAT #
##############



################
# REGLES DE F3 #
################

R1=192.168.3.10
SSH=192.168.1.10
PROCESSOR=192.168.4
FTP=92.168.1.12
# Default DROP

	iptables -P INPUT DROP
	iptables -P OUTPUT DROP
	iptables -P FORWARD DROP

# Processor - accessible uniquement par R1 et SSH - en SSH

	# Autorise forwarding d'une connexion NEW ou ETABLIE en ssh depuis R1 vers Processor
	iptables -A FORWARD -p tcp -s $R1 -d $PROCESSOR --dport ssh --state NEW,ESTABLISHED -j ACCEPT
	iptables -A FORWARD -p tcp -s $PROCESSOR -d $R1 --sport ssh --state ESTABLISHED -j ACCEPT

	# Autorise le forwarding d'une connexion NEW ou ETABLIE en ssh depuis SSH vers Processor
	# et inversément pour une établie pour les réponses de SSH
	iptables -A FORWARD -p tcp -s $SSH -d $PROCESSOR --dport ssh --state NEW,ESTABLISHED -j ACCEPT
	iptables -A FORWARD -p tcp -s $PROCESSOR -d $SSH --sport ssh --state ESTABLISHED -j ACCEPT

# Processor - Peut communiquer avec le FTP pour obtenir les fichiers

	iptables -A FORWARD -p tcp -s $PROCESSOR -d $FTP --sport 20:21 --dport 21:22 --state NEW, ESTABLISHED -j ACCEPT
	iptables -A FORWARD -p tcp -s $FTP -d $PROCESSOR --sport 20:21 --dport 21:22 --state ESTABLISHED -j ACCEPT
