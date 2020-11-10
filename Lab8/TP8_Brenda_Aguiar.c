#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[]){

    FILE *mpg_file = fopen(argv[1], "rb");
    
    unsigned char code_prefix[3];
    unsigned char stream;
    
    while(fread(&code_prefix, sizeof(char), 3, mpg_file)){
        
        if(memcmp(code_prefix,"\x00\x00\x01", 3) == 0) {
            
            fread(&stream, sizeof(char), 1, mpg_file);

            if(stream == 0xBA){
                printf("--> Código: %.2x -- Pack\n", stream);
            }
            if(stream == 0xBB){
                printf("--> Código: %.2x -- System\n", stream);
            }

            else if(stream == 0xB3){
                unsigned char byte1 = fgetc(mpg_file);
                unsigned char byte2 = fgetc(mpg_file);
                unsigned char byte3 = fgetc(mpg_file);
                unsigned char byte4 = fgetc(mpg_file);
                unsigned int largura = byte1 * 16 + (byte2 >> 4);
                unsigned int altura = ( byte2 & 0x0F) * 256 + byte3;
                unsigned int frame_rate = byte4  & 0x0f;
                if(frame_rate == 1) printf("--> Código: b3 -- Sequence Header -- Width = %d, Height = %d -- Frame rate = 23.976fps\n", largura,altura);

                if(frame_rate == 2) printf("--> Código: b3 -- Sequence Header -- Width = %d, Height = %d -- Frame rate = 24.000fps\n", largura,altura);

                if(frame_rate == 3) printf("--> Código: b3 -- Sequence Header -- Width = %d, Height = %d -- Frame rate = 25.000fps\n", largura,altura);
                
                if(frame_rate == 4) printf("--> Código: b3 -- Sequence Header -- Width = %d, Height = %d -- Frame rate = 29.970fps\n", largura,altura);

                if(frame_rate == 5) printf("--> Código: b3 -- Sequence Header -- Width = %d, Height = %d -- Frame rate = 30.000fps\n", largura,altura);

                if(frame_rate == 6) printf("--> Código: b3 -- Sequence Header -- Width = %d, Height = %d -- Frame rate = 50.000fps\n", largura,altura);

                if(frame_rate == 7) printf("--> Código: b3 -- Sequence Header -- Width = %d, Height = %d -- Frame rate = 59.940fps\n", largura,altura);

                if(frame_rate == 8) printf("--> Código: b3 -- Sequence Header -- Width = %d, Height = %d -- Frame rate = 60.000fps\n", largura,altura);
            }
            else if(stream == 0xB8){
                printf("--> Código: %.2x -- Group of Pictures\n", stream);
            }
            
            else if(stream == 0x00){
                unsigned char b1 = fgetc(mpg_file);
                unsigned char b2 = fgetc(mpg_file);

                unsigned int tipo = (b2 >> 3) & 0x07;

                if(tipo == 1) printf("--> Código: %.2x -- Picture -- Tipo = I \n", stream);
                else if(tipo == 2) printf("--> Código: %.2x -- Picture -- Tipo = P \n", stream);
                else if(tipo == 3) printf("--> Código: %.2x -- Picture -- Tipo = B \n", stream);

            }
            else if(stream >= 0x01 && stream <= 0xAF){
                printf("--> Código: %.2x -- Slice\n", stream);
            }
            else if(stream >= 0xC0 && stream <= 0xDF){
                printf("--> Código: %.2x -- Packet Video\n", stream);
            }
            else if(stream >= 0xE0 && stream <= 0xEF){
                printf("--> Código: %.2x -- Packet Audio\n", stream);
            }
        }
        
        else fseek(mpg_file, -2, SEEK_CUR);

    }
    
}