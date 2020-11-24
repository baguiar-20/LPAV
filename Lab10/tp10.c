#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


typedef struct ethernet_hdr_t {    
    uint8_t  daddr[6];  // Endereco MAC de destino    
    uint8_t  saddr[6];  // Endereco MAC de origem (source)    
    uint16_t protocol;  // Protocolo da camada superior (IP!)
} ethernet_hdr_t;

typedef struct ip_hdr_t {    
    uint8_t  hdr_len:4,  version:4; // Tamanho do Cabeçalho, // Versão do IP   
    uint8_t  tos;       // Tipo de serviço    
    uint16_t tot_len;   // Tamanho total do IP    
    uint16_t id;        // Id do pacote   
    uint16_t frag_off;  // Fragmentado?    
    uint8_t  ttl;       // Tempo de vida    
    uint8_t  protocol;  // Protocolo da camada superior (TCP!)    
    uint16_t check;     // Checksum   
    uint8_t saddr[4];   // Endereço IP de origem    
    uint8_t daddr[4];   // Endereço IP de destino
} ip_hdr_t;

typedef struct tcp_hdr_t {    
    uint16_t sport;       // Porta TCP de origem    
    uint16_t dport;       // Porta TCP de destino    
    uint32_t seq;         // Sequência    
    uint32_t ack_seq;     // Acknowledgement    
    uint8_t  reservado:4,  hdr_len:4; // Não usado      // Tamanho do cabecalho    
    uint8_t  flags;       // Flags do TCP    uint16_t window;      // Tamanho da janela    
    uint16_t check;       // Checksum    
    uint16_t urg_ptr;     // Urgente
    } tcp_hdr_t;


int main(int argc, char *argv[]){

    FILE *tcp_ip_file = fopen(argv[1], "rb");

    struct ethernet_hdr_t  *ethernet_hdr = malloc(sizeof( struct ethernet_hdr_t));
    struct ip_hdr_t  *ip_hdr = malloc(sizeof(ip_hdr_t));
    struct tcp_hdr_t  *tcp_hdr = malloc(sizeof(tcp_hdr_t));

    fread(ethernet_hdr, sizeof( ethernet_hdr_t), 14, tcp_ip_file);

    printf("Lendo Ethernet...\n");
    printf("--> MAC de Origem: %.2x \n", ethernet_hdr->daddr);
    printf("--> MAC de Destino: %.2x \n", ethernet_hdr->saddr);

    fread(ip_hdr, sizeof(ip_hdr_t), 14, tcp_ip_file);
    printf("Lendo IP...\n");




}