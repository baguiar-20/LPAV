#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main(int argc, char *argv[]){

    FILE *mpg_file = fopen(argv[1], "rb");
   
    if(mpg_file == NULL){
        printf("Erro ao abrir o arquivo!\n");
    }
    
    int tam = atoi(argv[2])*1048576;

    int p=1;

    unsigned char *buffer_sequence = (char *) calloc(tam+1, sizeof(char));
    
    unsigned char code_prefix[4];
    char str[100] = {0};
    
    sprintf(str,"video_parte_%d.mpg", p);
    
    FILE *video_parte = fopen(str, "wb");
    
    size_t tam_arq = 0, tam_buffer = 0;

    while(fread(&code_prefix, sizeof(char), 4, mpg_file) >= 4){
        
        if(memcmp(code_prefix,"\x00\x00\x01\xB3", 4) != 0){
            buffer_sequence[tam_buffer++] = code_prefix[0];
            fseek(mpg_file, -3, SEEK_CUR);
            continue;
        }

        else{
            memcpy(&buffer_sequence[tam_buffer], code_prefix, 4);
            tam_buffer += 4;
            if(tam_arq+tam_buffer > tam){
                fclose(video_parte);
                sprintf(str,"video_parte_%d.mpg", ++p);
                video_parte = fopen(str,"wb");
                fwrite(buffer_sequence, sizeof(char), tam_buffer, video_parte);
                tam_arq = tam_buffer; 
                tam_buffer = 0;
            }
            else{
                fwrite(buffer_sequence, sizeof(char), tam_buffer, video_parte);
                tam_arq += tam_buffer; 
                tam_buffer = 0;
            }

        }
    
    }

    fclose(video_parte);
    fclose(mpg_file);
    free(buffer_sequence);

}


