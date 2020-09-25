#include<stdio.h>

struct dado_vertice{
   int id;
   double pos_x;
   double pos_y;
};


typedef struct dado_vertice dado_vertice;

struct lista_vizinhos_t{
    dado_vertice *dado_vertice;
    struct lista_vizinhos_t *proximo;
    
};

typedef struct lista_vizinhos_t lista_vizinhos_t;

typedef struct lista_vizinhos_t grafo;

grafo criar_grafo(int tam){

}




int main(int argc, char *argv[1]){
    grafo *grafo;

    FILE *fp;
    fp = fopen(argv[1], "r+");
    int qtd_nos=0;
    double raio_comunicacao =0;
    fscanf(fp,"%d\t%lf\n", &qtd_nos, &raio_comunicacao);

    //criar_grafo(qtd_nos);


    int id=0, i=0;
    double x, y;
    while (fscanf(fp,"%d\t%lf\t%lf\n",&id, &x, &y)!= EOF){
    

        //grafo[i].lista_vizinhos_t = NULL;
        i++;
    }
    //grafo_atualizar_vizinhos(qtd_nos, raio_comunicacao, grafo);

}