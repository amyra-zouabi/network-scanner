#include <stdio.h>
#include <pcap.h>
#include <arpa/inet.h>
#include <netinet/ip.h>  // Inclure pour struct ip
#include <netinet/ether.h>  // Inclure pour ether_ntoa
#include <json-c/json.h>
#include "scanner.h"

void packet_handler(u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
    struct ether_header *eth_header = (struct ether_header *)packet;
    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {
        struct ip *ip_header = (struct ip*)(packet + sizeof(struct ether_header));
        struct in_addr ip_src = ip_header->ip_src;
        struct in_addr ip_dst = ip_header->ip_dst;

        printf("Source IP: %s\n", inet_ntoa(ip_src));
        printf("Destination IP: %s\n", inet_ntoa(ip_dst));
        printf("Source MAC: %s\n", ether_ntoa((struct ether_addr *)eth_header->ether_shost));
        printf("Destination MAC: %s\n", ether_ntoa((struct ether_addr *)eth_header->ether_dhost));

        // Convert the information to JSON
        json_object *jobj = json_object_new_object();
        json_object_object_add(jobj, "source_ip", json_object_new_string(inet_ntoa(ip_src)));
        json_object_object_add(jobj, "destination_ip", json_object_new_string(inet_ntoa(ip_dst)));
        json_object_object_add(jobj, "source_mac", json_object_new_string(ether_ntoa((struct ether_addr *)eth_header->ether_shost)));
        json_object_object_add(jobj, "destination_mac", json_object_new_string(ether_ntoa((struct ether_addr *)eth_header->ether_dhost)));

        FILE *fp = fopen("devices.json", "a");
        fprintf(fp, "%s\n", json_object_to_json_string(jobj));
        fclose(fp);

        json_object_put(jobj);
    }
}

