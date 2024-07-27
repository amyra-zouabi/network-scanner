#ifndef SCANNER_H
#define SCANNER_H

#include <pcap.h>

// Fonction de traitement des paquets
void packet_handler(u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *packet);

#endif // SCANNER_H
