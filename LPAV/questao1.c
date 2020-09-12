#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//struct para os dados
struct evento_t { 
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


bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista){
	lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t));// Aloca o novo item
	if (item_novo == NULL) return false; // Falta memória?
	item_novo->evento = evento;// Seta o novo item
	item_novo->prox = *lista;// O próximo do novo item será a lista
	*lista = item_novo;  // Aqui, estamos mudando o ponteiro da lista
	return true;
};

void lista_eventos_listar(lista_eventos_t *lista){

}
int main(int argc, char *argv[1]){
	evento_t d;
	lista_eventos_t *l;

	lista_eventos_adicionar_inicio(&d, &l);

	FILE *fp = NULL;
	fp = fopen(argv[1], "r+");
	if(fp == NULL){
		printf("arquivo nao existe!\n");
		return 1;
	}
	char aux;
	float tempo;
	int alvo, tipo;
	while (fscanf(fp, "%c", &aux) != EOF){
		printf("%c", aux);
	}
}