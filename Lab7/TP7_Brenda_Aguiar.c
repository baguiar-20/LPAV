#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <arpa/inet.h>

 struct png_file_hdr{
    int tamanho;
    int tipo;
};


struct chunk_data{
    int width;
    int height;
    char bit_depth;
    char colour_type;
    char compression_method;
    char filter_method;
    char interlace_method;
}__attribute__ ((packed));



int main(int argc, char *argv[]){

    int i =1; 

    FILE *png_file = fopen(argv[1], "rb");

    struct png_file_hdr *png_hdr = malloc(sizeof(struct png_file_hdr));
    
    struct chunk_data *chunk = malloc(sizeof(struct chunk_data));

    fseek(png_file, 8, SEEK_CUR);
    
    while(png_file){
        printf("Lendo chunk %d:\n", i);
        fread(png_hdr, sizeof(struct png_file_hdr), 1, png_file);
        
        printf("    --> Tamanho: %d\n",  ntohl(png_hdr->tamanho));
        printf("    --> Tipo: %.4s\n", (char*)&png_hdr->tipo);

        if(strncmp((char*)&png_hdr->tipo, "IHDR", 4) == 0){
            fread(chunk, sizeof(struct chunk_data), 1, png_file);
            printf("        --> Largura: %d\n",  ntohl(chunk->width));
            printf("        --> Altura: %d\n",  ntohl(chunk->height));
            fseek(png_file, 4, SEEK_CUR);
        }
        else if(strncmp((char*)&png_hdr->tipo, "IEND", 4) == 0) break;

        else fseek(png_file, ntohl(png_hdr->tamanho)+4, SEEK_CUR);
        i++;

        
    }
    fclose(png_file);
}