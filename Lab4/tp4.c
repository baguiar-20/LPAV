#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>



///lista de eventos ordenados
struct evento_t{
	double tempo;
	int alvo;
	int tipo;
};

typedef struct evento_t evento_t;

//struct para a lista encadeada
struct lista_eventos_t{
	evento_t *evento;
	struct lista_eventos_t *prox;
};

typedef struct lista_eventos_t lista_eventos_t;



evento_t* criar_evento(double tempo, int alvo, int tipo) {
    evento_t *evento = malloc(sizeof(evento_t));
	evento->tempo = tempo;
	evento->alvo = alvo;
	evento->tipo = tipo;
    return evento;
}


bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista){
	lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t)); // Aloca o novo item
	if (item_novo == NULL)
		return false;			// Falta memória?
	item_novo->evento = evento; // Seta o novo item
	item_novo->prox = *lista;	// O próximo do novo item será a lista
	*lista = item_novo;			// Aqui, estamos mudando o ponteiro da lista
	return true;
}

bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista){
	lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t));
	lista_eventos_t *aux = *lista;
	if (item_novo == NULL)
		return false;
	item_novo->evento = evento;
	item_novo->prox = NULL;

	if (*lista == NULL){
		*lista = item_novo;
	}
	else{
		while (aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = item_novo;
	}
}
bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista){

	if (*lista == NULL || (*lista)->evento->tempo > evento->tempo){
		return lista_eventos_adicionar_inicio(evento, lista);
	}
	else if ((*lista)->prox == NULL){
		return lista_eventos_adicionar_fim(evento, lista);
	}
	else{
		lista_eventos_t *aux = *lista;
		while (aux->prox != NULL && aux->prox->evento->tempo < evento->tempo){
			aux = aux->prox;
		}
		lista_eventos_t *d3 = malloc(sizeof(lista_eventos_t));
		d3->evento = evento;
		d3->prox = aux->prox;
		aux->prox = d3;
		return true;
	}
}





//// dado dos vertice
typedef struct dado_vertice{
   int id;
   double pos_x;
   double pos_y;
   bool pacote_enviado;
}dado_vertice;

/// lista
 struct lista_vizinhos_t{
    dado_vertice *dado_vertice;
    struct lista_vizinhos_t *proximo;
    
};
typedef struct lista_vizinhos_t lista_vizinhos_t;

/////grafo
typedef struct grafo_t{
    lista_vizinhos_t **lista;
    int tamanho;
}grafo_t;




///////////////////////////////////////////////////////

bool lista_vizinhos_adicionar_inicio(dado_vertice *dv, lista_vizinhos_t **lista){
	lista_vizinhos_t *item_novo = malloc(sizeof(lista_vizinhos_t)); 
	if (item_novo == NULL) return false;			
	item_novo->dado_vertice = dv; 
	item_novo->proximo = *lista;
	*lista = item_novo;		
	return true;
}

grafo_t * criar_grafo(int tam){ ///ok
    grafo_t *grafo = (grafo_t *)malloc(sizeof(grafo_t));
    grafo->lista = calloc(tam, sizeof(lista_vizinhos_t*)); /// alocar o vetor de ponteiros do grafo com calloc
    grafo->tamanho = tam;
    return grafo;
}

dado_vertice * vertice(int id, double pos_x, double pos_y){
    dado_vertice *novo_dado_vertice = malloc(sizeof(dado_vertice));

    if(novo_dado_vertice == NULL) return NULL;
    novo_dado_vertice->id = id;
    novo_dado_vertice->pos_x = pos_x;
    novo_dado_vertice->pos_y = pos_y;
    novo_dado_vertice->pacote_enviado = false;
    
    return novo_dado_vertice;
}


void adicionar_grafo(grafo_t *grafo, dado_vertice *vertice, int pos){
   lista_vizinhos_adicionar_inicio(vertice, &grafo->lista[pos]);
}

void atualizar_grafo(grafo_t *grafo, dado_vertice *vertice, int pos){
    lista_vizinhos_adicionar_inicio(vertice, &grafo->lista[pos]->proximo);
}

void atualizar_vizinho(grafo_t *grafo, int raio_comunicacao){
    double calculo;
    for(int i=0; i < grafo->tamanho;i++){
        for(int j=0; j < grafo->tamanho; j++){
            
            if(j != i){
                calculo = sqrt(pow(grafo->lista[i]->dado_vertice->pos_x - grafo->lista[j]->dado_vertice->pos_x, 2) +
            pow(grafo->lista[i]->dado_vertice->pos_y - grafo->lista[j]->dado_vertice->pos_y, 2));
                if(calculo < raio_comunicacao){
                    dado_vertice *novo_vertice = malloc(sizeof(dado_vertice));
                    novo_vertice->id = j;
                    novo_vertice->pos_x = grafo->lista[j]->dado_vertice->pos_x;
                    novo_vertice->pos_y = grafo->lista[j]->dado_vertice->pos_y;
                    atualizar_grafo(grafo, novo_vertice, i);
                }
            }
        }
    }

}

/////// imprimir as listas do grafo///////

void lista_vizinhos_listar(lista_vizinhos_t *lista){
	lista_vizinhos_t *aux = lista->proximo;
	while (aux != NULL){
		printf("\t--> Repassando pacote para o nó %d ...\n", aux->dado_vertice->id);
		aux = aux->proximo;
	}
    printf("\n");
}

void imprimir_grafo(grafo_t * grafo){
    for(int i = 0;i<grafo->tamanho; i++){
        printf("NO %d: ", i);
        lista_vizinhos_listar(grafo->lista[i]);
    }

}
/////

void simulacao_iniciar(lista_eventos_t *lista_eventos, grafo_t *grafo){
    lista_eventos_t *aux = lista_eventos;
    int i = 0;
    while (aux != NULL){
        evento_t *prim_evento = aux->evento;
        lista_eventos = aux->prox;
        printf("[%3.6f] Nó %d recebeu pacote.\n", prim_evento->tempo, prim_evento->alvo);

        if(grafo->lista[prim_evento->alvo]->dado_vertice->pacote_enviado != true){
            lista_vizinhos_listar(grafo->lista[prim_evento->alvo]);
            
            printf("%d ", grafo->lista[prim_evento->alvo]->dado_vertice->id);

            evento_t *e = criar_evento(prim_evento->tempo + (0.1 + (grafo->lista[prim_evento->alvo]->proximo->dado_vertice->id * 0.01)), grafo->lista[prim_evento->alvo]->proximo->dado_vertice->id, 1); // tempo, alvo, tipo
            

            lista_eventos_adicionar_ordenado(e, &aux);
            grafo->lista[prim_evento->alvo]->dado_vertice->pacote_enviado = true;
        }
        //printf("%d ", aux->evento->alvo);
        aux = aux->prox;
    }
}




int main(int argc, char *argv[1]){
    
    FILE *fp;
    fp = fopen(argv[1], "r+");
    int qtd_nos = 0;
    double raio_comunicacao =0;

    fscanf(fp,"%d\t%lf\n", &qtd_nos, &raio_comunicacao);
    

    grafo_t *grafo = criar_grafo(qtd_nos);
    
    int id=0;
    double pos_x, pos_y;
    while (fscanf(fp,"%d\t%lf\t%lf\n", &id, &pos_x, &pos_y)!= EOF){
        
        dado_vertice *dv = vertice(id, pos_x, pos_y);
        adicionar_grafo(grafo, dv, id);  
   
    }
    atualizar_vizinho(grafo, raio_comunicacao);

    //imprimir_grafo(grafo);

    lista_eventos_t *l = NULL;
	evento_t *e;
    e = criar_evento(1.0, grafo->lista[0]->dado_vertice->id, 1);// tempo, alvo, tipo
    lista_eventos_adicionar_ordenado(e, &l);


    simulacao_iniciar(l, grafo);


}