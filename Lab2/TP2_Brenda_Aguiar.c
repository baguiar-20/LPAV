#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

int tabela_hash_tam;

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

//hash

typedef lista_pessoas tabela_hash;

///////////funcoes lista encadeada//////////

//adiciona na lista encadeada
bool lista_pessoas_adicionar(dado_pessoa *pessoa, lista_pessoas **lista){
	lista_pessoas *item_novo = malloc(sizeof(lista_pessoas));
	lista_pessoas *aux = *lista;
	if (item_novo == NULL) return false;
	
	item_novo->pessoa = pessoa;
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

//lista a lista encadeada
void lista_eventos_listar(lista_pessoas *lista){
	lista_pessoas *aux = lista;
	while (aux != NULL){
		printf("-%s\t%lld\t%d\n",aux->pessoa->nome, aux->pessoa->cpf, aux->pessoa->idade);
		aux = aux->prox;
	}
}

//cria um tipo pessoa
dado_pessoa* criar_pessoa(char nome[50], long long int cpf, int idade) {
    dado_pessoa *pessoa = (dado_pessoa*)malloc(sizeof(dado_pessoa));
	if(pessoa == NULL) printf("foi n");
	pessoa->cpf = cpf;
	pessoa->idade = idade;
	strcpy(pessoa->nome, nome);
    return pessoa;
}
////////////funcoes hash/////////////

//Aloca memória para um vetor de ponteiros para listas encadeadas e faz cada ponteiro de lista (elemento do vetor) apontar para nulo.

tabela_hash **tabela_hash_pessoas_criar(){ 
	tabela_hash **tab = (tabela_hash **)malloc(sizeof(tabela_hash*)*tabela_hash_tam);
 	for(int i = 0; i < tabela_hash_tam; i++){
  		tab[i] = NULL;
 	}
	 return tab;
}


//funcao hash
int funcao_hash(dado_pessoa *dp){
  return(dp->cpf % tabela_hash_tam);
}

///Adiciona a pessoa na lista encadeada localizada na posição do vetor especificado pela função acima

bool tabela_hash_pessoas_adicionar(dado_pessoa *dp, tabela_hash **tab){
	int key = funcao_hash(dp);
	
	lista_pessoas_adicionar(dp, &tab[key]);
	
	return true;
}

//lista as pessoas da hash

void tabela_hash_pessoas_listar(tabela_hash **tab){

	for (int i=0; i< tabela_hash_tam; i++){
		printf("POSIÇÃO %d DA TABELA HASH\n", i);
		lista_eventos_listar(tab[i]);
	}

}

////////////////////////////////////////////////////


int main(int argc, char *argv[]){

	dado_pessoa *dp;
	tabela_hash_tam = atoi(argv[1]);
	tabela_hash **tab = tabela_hash_pessoas_criar();
	
	FILE *fp = NULL;
	fp = fopen(argv[2], "r+");

	if(fp == NULL){
		printf("arquivo nao existe!\n");
		return 1;
	}

	char nome[50];
	int idade=0;
	long long int cpf=0;

	while(fscanf(fp,"%50[^\t]\t%lld\t%d\n", nome, &cpf, &idade) != EOF){ // le o arquivo pelo terminal
		dp = criar_pessoa(nome, cpf, idade);
		tabela_hash_pessoas_adicionar(dp, tab);
	}
	tabela_hash_pessoas_listar(tab);
}