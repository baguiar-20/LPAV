#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

//gcc -o teste questao1.c
//  ./teste arquivo.txt

//struct para os dados
struct evento_t
{
	double tempo;
	int alvo;
	int tipo;
};

typedef struct evento_t evento_t;

//struct para a lista encadeada
struct lista_eventos_t
{
	evento_t *evento;
	struct lista_eventos_t *prox;
};

typedef struct lista_eventos_t lista_eventos_t;

//primeira questao ok
bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista)
{
	lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t)); // Aloca o novo item
	if (item_novo == NULL)
		return false;			// Falta memória?
	item_novo->evento = evento; // Seta o novo item
	item_novo->prox = *lista;	// O próximo do novo item será a lista
	*lista = item_novo;			// Aqui, estamos mudando o ponteiro da lista
	return true;
}

//segunda questao
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

//terceira questao
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

//item_atual->proximo != NULL && item_atual->proximo->evento->tempo < evento->tempo

void lista_eventos_listar(lista_eventos_t *lista){
	lista_eventos_t *aux = lista;
	while (aux != NULL){
		printf("tempo: %3.6lf, alvo:%d, tipo:%d\n", aux->evento->tempo, aux->evento->alvo, aux->evento->tipo);
		aux = aux->prox;
	}
}


evento_t* criar_evento(double tempo, int alvo, int tipo) {
    evento_t *evento = malloc(sizeof(evento_t));
	evento->tempo = tempo;
	evento->alvo = alvo;
	evento->tipo = tipo;
    return evento;
}

int main(int argc, char *argv[1]){
	// declara a lista de o struct
	lista_eventos_t *l = NULL;
	evento_t *e;
	
	FILE *fp = NULL;
	fp = fopen(argv[1], "r+");
	if(fp == NULL){
		printf("arquivo nao existe!\n");
		return 1;
	}

	double tempo;
	int alvo, tipo;
	while (fscanf(fp, "%lf %d %d", &tempo, &alvo, &tipo) != EOF){ // le o arquivo pelo terminal
		e = criar_evento(tempo, alvo, tipo);
		//lista_eventos_adicionar_inicio(e, &l);
		//lista_eventos_adicionar_fim(e, &l);
		//lista_eventos_adicionar_ordenado(e, &l);
	}
	lista_eventos_listar(l);
}