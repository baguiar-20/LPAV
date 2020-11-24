#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>


struct ethernet_hdr_t{    
    uint8_t  daddr[6];  // Endereco MAC de destino    
    uint8_t  saddr[6];  // Endereco MAC de origem (source)    
    uint16_t protocol;  // Protocolo da camada superior (IP!)
} ;

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

    fread(ethernet_hdr, sizeof(struct ethernet_hdr_t), 14, tcp_ip_file);

    printf("Lendo Ethernet...\n");
    printf("--> MAC de Origem: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", ethernet_hdr->daddr[0],ethernet_hdr->daddr[1], ethernet_hdr->daddr[2], ethernet_hdr->daddr[3], ethernet_hdr->daddr[4], ethernet_hdr->daddr[5]);
    printf("--> MAC de Destino: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", ethernet_hdr->saddr[0],ethernet_hdr->saddr[1], ethernet_hdr->saddr[2], ethernet_hdr->saddr[3], ethernet_hdr->saddr[4], ethernet_hdr->saddr[5]);

    fread(ip_hdr, sizeof(ip_hdr_t), 20, tcp_ip_file);
    printf("Lendo IP...\n");
    printf("--> Versão do IP: %d\n", ip_hdr->version);
    printf("--> Tamanho do cabeçalho: %d bytes\n", ip_hdr->hdr_len*4);
    printf("--> Tamanho do pacote: %d bytes\n", ntohs(ip_hdr->hdr_len));
    fseek( tcp_ip_file, ip_hdr->hdr_len*4 - sizeof(ip_hdr_t), SEEK_CUR);

    fread(tcp_hdr, sizeof(tcp_hdr_t), 32, tcp_ip_file);
    printf("Lendo tcp...\n");
    printf("--> Porta de Origem: %d\n", ntohs(tcp_hdr->sport));
    printf("--> Porta de Destino: %d\n", ntohs(tcp_hdr->dport));
    printf("--> Tamanho do cabeçalho: %d bytes\n", tcp_hdr->hdr_len * 4);
    fseek( tcp_ip_file, tcp_hdr->hdr_len*4 - sizeof(tcp_hdr_t), SEEK_CUR);

    printf("Lendo Dados (HTTP) ..\n");
    int tam_dados = ntohs(ip_hdr->tot_len) - (ip_hdr->hdr_len*4) - (tcp_hdr->hdr_len*4);
    printf("--> Tamanho dos dados: %d bytes\n", tam_dados);
    printf("--> Dados: \n");
    
    int c, i;
    char buffer[tam_dados];
    //printf("%d\n", fgetc(tcp_ip_file));

    c = fgetc(tcp_ip_file);
    printf( "%c\n", c);
    
    for( i=0; (i < tam_dados) && ( feof( tcp_ip_file ) == 0 ); i++ ){
        buffer[i] = (char)c;
        c = fgetc(tcp_ip_file);
        printf( "%c\n", buffer[i]);
    }
    //buffer[i] = '\0';
    //printf( "%s\n", buffer );

}