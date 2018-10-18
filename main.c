#include <stdio.h>
#include <stdlib.h>
#define MAX_CONTATO 101

//criar struct cabecalho com: inicio, fim e tamanho da agenda [FALTA FAZER]

typedef struct contato{
  char nome[MAX_CONTATO]; //validar tamanho [FALTA FAZER]
  char telefone[11]; //validar tamanho e formato [FALTA FAZER]
  char endereco[MAX_CONTATO]; //validar tamanho [FALTA FAZER]
  unsigned int cep; //validar tamanho MAX_CEP 4 [FALTA FAZER]
  char data_nasc[11]; //validar tamanho e formato [FALTA FAZER]
}Contato;

typedef struct agenda{
  Contato *info;
  struct agenda *ant, *prox;
}Agenda;

Agenda* cria_contato(char *nome, char *tel, char *end, int cep, char *nasc); //aloca novo contato da agenda
//void insertion_sort_contato(); //insere contato na agenda ordenado pelo nome
//void remover_contatos_por_string(); //remove todos os contatos que tiverem a string de entrada
//void imprime_contatos_por_string(); //imprime todos os contatos que tiverem a string de entrada
//void imprime_agenda(); //imprime lista já ordenada
//void sair(); //altera arquivo e libera agenda

int main(){



  return 0;
}

Agenda* cria_contato(char *nome, char *tel, char *end, int cep, char *nasc){
  Contato *novo_contato;
  Agenda *a;

	novo_contato = (Contato*) malloc(sizeof(Contato));

	if (novo_contato == NULL){
		printf("\nNao foi possivel criar um novo contato.\n");
		exit(-1);
	}

  novo_contato->nome = nome;
  novo_contato->telefone = tel;
  novo_contato->endereco = end;
  novo_contato->cep = cep;
  novo_contato->data_nasc = nasc;

  a = (Agenda*) malloc(sizeof(Agenda));

  if (a == NULL)
		exit(-1);

  a->info = novo_contato;
  a->ant = NULL;
  a->prox = NULL;

  return a;

}
