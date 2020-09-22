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

typedef lista_pessoas ** tabela_hash;

///////////funcoes lista encadeada///////////

bool lista_eventos_adicionar_fim(dado_pessoa *pessoa, lista_pessoas **lista){
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

void lista_eventos_listar(lista_pessoas *lista){
	lista_pessoas *aux = lista;
	while (aux != NULL){
		printf("%s\t%lld\t%d\n",aux->pessoa->nome, aux->pessoa->cpf, aux->pessoa->idade);
		aux = aux->prox;
	}
}


dado_pessoa* criar_pessoa(char nome[50], long long int cpf, int idade) {
    dado_pessoa *pessoa = malloc(sizeof(dado_pessoa));
	if(pessoa == NULL) printf("foi n");
	//pessoa->cpf = cpf;
	//pessoa->idade = idade;
	//strcpy(pessoa->nome, nome);
    return pessoa;
}
////////////funcoes hash/////////////

tabela_hash **tabela_hash_pessoas_criar(){ //falha de segmentação?
	tabela_hash **tab = (tabela_hash **)malloc(sizeof(tabela_hash*)*tabela_hash_tam);
 	for(int i = 0; i < tabela_hash_tam; i++){
  		tab[i] = NULL;
 	}
	 return tab;
}

int funcao_hash(dado_pessoa *dp){
  return(dp->cpf % tabela_hash_tam);
}



bool tabela_hash_pessoas_adicionar(dado_pessoa *dp, tabela_hash tabela_hash){
	int key = funcao_hash(dp);
	//dado_pessoa *aux = tabela_hash[key];
	tabela_hash[key]->pessoa = dp;
	return true;
}

/////////////////////////////
/*bool tabela_hash_pessoas_adicionar(dado_pessoa *dp, tabela_hash tabela_hash){
 int i = 0;
 int chave = funcaoHash(num);
 Dados* aux = tab[chave];
 while(aux != NULL)
 {
  if(aux->info == num)
  {
   break;
  }
  aux = aux->prox;
 }
 if(aux == NULL)
 {
  aux = (Dados*)malloc(sizeof(Dados));
  aux->info = num;
  aux->prox = tab[chave];
  tab[chave] = aux;
 }
}
*/
////////////////////////


int main(int argc, char *argv[1]){
	// declara a lista de o struct
	lista_pessoas *lp = NULL;
	dado_pessoa *dp;
	tabela_hash tab = tabela_hash_pessoas_criar();

	FILE *fp = NULL;
	fp = fopen(argv[2], "r+");
	if(fp == NULL){
		printf("arquivo nao existe!\n");
		return 1;
	}
	tabela_hash_tam = atoi(argv[1]);
	printf("%d", tabela_hash_tam);
	
	char nome[50];
	int idade;
	long long int cpf;

	while (fscanf(fp,"%50[^\t]%lld\t%d\n", nome, &cpf, &idade) != EOF){ // le o arquivo pelo terminal
		dp = criar_pessoa(nome, cpf, idade);
		
		//lista_eventos_adicionar_fim(dp, &lp);
		//printf("%s\t%lld\t%d\n", dp->nome, dp->cpf, dp->idade);
		tabela_hash_pessoas_adicionar(dp, tab);
		
	}
	//lista_eventos_listar(p);
}