#include <stdlib.h>
#include <stdio.h>

typedef struct tipoNo
{
	int dado;
	struct tipoNo *prox ;
}tipoNo;


typedef struct tipoLista
{
	struct tipoNo *prim;
}tipoLista;


void inserir(tipoLista *c , int b){
	tipoNo *aux , *novo ;

	novo = (tipoNo *) malloc(sizeof(tipoNo));
	if(novo == NULL)
  {
		exit(-1);
	}
	novo->dado = b ;
	aux = c->prim;
	if(!aux)
  {
		c->prim = novo ;
		novo->prox = NULL;
	}
	else
  {
		novo->prox= c->prim ;
		c->prim = novo;
	}
}



void mostrar(tipoLista *c){
 tipoNo *aux ;
 aux = c->prim ;
 while(aux)
 {
 	printf(" Dado:%d\n", aux->dado);
 	printf("endereco :%p\n", (void *)aux);
 	aux= aux->prox;
 }
}

void criar(tipoLista *c){
	c->prim = NULL ;
}

int main(){
	tipoLista l ;
	int b , i , q;
	criar(&l);
	scanf("quantos :%d\n", &q);
	for (i= 0 ; i < 3 ; i++){
		scanf("dado : %d", &b);
		inserir(&l,b);
	}
	mostrar(&l);
}




