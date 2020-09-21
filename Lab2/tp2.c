#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

//gcc -o teste tp1.c
//  ./teste arquivo.txt

//struct para os dados
struct dado_pessoa{
	char nome[50];
	long long int cpf;
	int idade;
};

typedef struct dado_pessoa dado_pessoa;

//struct para a lista encadeada
struct lista_pessoas{
	dado_pessoa *pessoa;
	struct lista_pessoas *prox;
};

typedef struct lista_pessoas lista_pessoas;

typedef lista_pessoas ** tabela_hash;

/////////////////////////
///Hash





//////////////////////

bool lista_eventos_adicionar_fim(evento_t *evento, lista_eventos_t **lista){
	lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t));
	lista_eventos_t *aux = *lista;
	if (item_novo == NULL) return false;
	
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


//questao1

void lista_eventos_listar(lista_eventos_t *lista){
	lista_eventos_t *aux = lista;
	while (aux != NULL){
		printf("%3.6lf\t%d\t%d\n", aux->evento->tempo, aux->evento->alvo, aux->evento->tipo);
		aux = aux->prox;
	}
}


dado_pessoa* criar_evento(char nome, long long int cpf, int idade) {
    dado_pessoa *pessoa = malloc(sizeof(dado_pessoa));
	if(pessoa == NULL) return 1;
	pessoa->cpf = cpf;
	pessoa->idade = idade;
	pessoa->nome = nome;
    return pessoa;
}
/////////////////////////

tabela_hash tabela_hash_pessoas_criar(tabela_hash *tabela_hash){
	int i;
 	for(i = 0; i < tabela_hash_tam; i++){
  		tabela_hash[i] = NULL;
 	}
}
int funcao_hash(lista_pessoas *pessoa){
  return(tabela_hash_tam %  pessoa->pessoa->cpf);
}

bool tabela_hash_pessoas_adicionar(lista_pessoas *pessoa, tabela_hash tabela_hash){
	int posicao = funcao_hash(pessoa);
	tabela_hash[posicao] = &pessoa;
}



////////////////////////


int main(int argc, char *argv[1]){
	// declara a lista de o struct
	lista_pessoas *p = NULL;
	dado_pessoa *dp;
	
	FILE *fp = NULL;

	fp = fopen(argv[2], "r+");
	if(fp == NULL){
		printf("arquivo nao existe!\n");
		return 1;
	}
	int tabela_hash_tamç = atoi(argv[1]);
	double tempo;
	int alvo, tipo;
	while (fscanf(fp,"%lf\t%d\t%d\n", &tempo, &alvo, &tipo) != EOF){ // le o arquivo pelo terminal
		e = criar_evento(tempo, alvo, tipo);
		//lista_eventos_adicionar_inicio(e, &l);
		//lista_eventos_adicionar_fim(e, &l);
		lista_eventos_adicionar_ordenado(e, &l);
	}
	lista_eventos_listar(l);
}