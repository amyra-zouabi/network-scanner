#include <stdio.h>
#include <pcap.h>
#include <netinet/ip.h>        // Pour struct ip
#include <netinet/if_ether.h>  // Pour struct ether_header
#include <arpa/inet.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <json-c/json.h>
#include "scanner.h"
#include "gui.h"
#include <netinet/ether.h>

int main(int argc, char *argv[]) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    // Initialisation de GTK+
    gtk_init(&argc, &argv);

    // Appel de la fonction pour créer l'interface graphique
    create_gui();

    // Ouvrir l'interface réseau en mode capture
    handle = pcap_open_live("enp0s1", BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device: %s\n", errbuf);
        return 1;
    }

    // Démarrer la capture des paquets
    pcap_loop(handle, 0, packet_handler, NULL);

    // Fermer l'interface après la capture
    pcap_close(handle);

    // Lancer la boucle principale de GTK
    gtk_main();

    return 0;
}

