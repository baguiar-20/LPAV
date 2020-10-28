#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct zip_file_hdr {
    int signature;
    short version;
    short flags;
    short compression;
    short mod_time;
    short mod_date;
    int crc;
    int compressed_size;
    int uncompressed_size;
    short name_length;
    short extra_field_length;
    } __attribute__ ((packed));


int main(int argc, char *argv[]){

    int i =1; 

    FILE *zip_file = fopen(argv[1], "rb");

    struct zip_file_hdr *file_hdr = malloc(sizeof(struct zip_file_hdr));

    
    while(zip_file){

        fread(file_hdr, sizeof(struct zip_file_hdr), 1, zip_file);
        
        if(file_hdr->signature == 0x04034b50){
            printf("Arquivo %d ..\n", i);

            char * nome_arquivo = malloc(file_hdr->name_length+1);
            
            fread(nome_arquivo, sizeof(char), file_hdr->name_length, zip_file);
            
            nome_arquivo[file_hdr->name_length+1] = '\0';

            printf("  --> Nome do arquivo: %s\n", nome_arquivo);
            printf("  --> Tamanho Compactado: %d\n", file_hdr->compressed_size);
            printf("  --> Tamanho Descompactado: %d\n", file_hdr->uncompressed_size);
            
            free(nome_arquivo);

            fseek(zip_file, file_hdr->extra_field_length +file_hdr->compressed_size, SEEK_CUR);
        }
        else break;

        i++;
    }
    fclose(zip_file);
}