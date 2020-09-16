#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista)
{
	lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t));
	lista_eventos_t *aux = *lista;
	if (item_novo == NULL)
		return false;
	item_novo->evento = evento;
	item_novo->prox = NULL;

	if (*lista == NULL)
	{
		*lista = item_novo;
	}
	else
	{
		while (aux->prox != NULL)
		{
			aux = aux->prox;
		}
		aux->prox = item_novo;
	}
}

//terceira questao
bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista)
{

	if (*lista == NULL || (*lista)->evento->tempo > evento->tempo)
	{
		return lista_eventos_adicionar_inicio(evento, lista);
	}
	else if ((*lista)->prox == NULL)
	{
		return lista_eventos_adicionar_fim(evento, lista);
	}
	else
	{
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
		printf("alvo%d\n", aux->evento->alvo);
		aux = aux->prox;
	}
}

int main(int argc, char *argv[1]){
	evento_t *d = malloc(sizeof(evento_t)); // declara as struct
	lista_eventos_t *l = NULL;				// declara as struct

	evento_t *d2 = malloc(sizeof(evento_t));

	d->alvo = 1;
	d->tempo = 1.54;
	d->tipo = 4;

	lista_eventos_adicionar_fim(d, &l);
	d2->alvo = 3;
	d2->tempo = 4.37;
	d2->tipo = 1;

	//lista_eventos_adicionar_inicio(d, &l);
	lista_eventos_adicionar_fim(d2, &l);

	//lista_eventos_adicionar_ordenado()
	//lista_eventos_listar(l);

	/*
	FILE *fp = NULL;
	fp = fopen(argv[1], "r+");
	if(fp == NULL){
		printf("arquivo nao existe!\n");
		return 1;
	}

	double tempo;
	int alvo, tipo;
	while (fscanf(fp, "%lf %d %d", &tempo, &alvo, &tipo) != EOF){ // le o arquivo pelo terminal
		d->alvo = alvo;
		d->alvo = tempo;
		d->alvo = tipo;
	}
	
	//printf("%3.6lf\t%d\t%d\n", d.tempo, d.alvo, d.tipo);
	//if (l->prox->prox != NULL) printf("0");
	//lista_eventos_listar(l);*/
}