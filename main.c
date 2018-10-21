/*
 * O que falta fazer:
 * - Testar e concertar cases da ordenação pela 2ª letra
 * - Validar ano da data_nasc
 * - Função de remover registro por string
 * - Função de visualizar registro por string
 * - Parte de arquivos
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CONTATO 101
#define TRUE 1
#define FALSE 0

//Info do nó da lista
typedef struct contato{
  char nome[MAX_CONTATO];
  char telefone[11];
  char endereco[MAX_CONTATO];
  unsigned int cep;
  char data_nasc[11];
}Contato;

//Nó da lista
typedef struct agenda{
  Contato *info;
  struct agenda *ant, *prox;
}Agenda;

typedef struct cabecalho{
  Agenda *inicio, *fim;
  int tamanho; //Quantidade de contatos da agenda
}Cabecalho;

Cabecalho* inicia_cabecalho();
Agenda* cria_contato(char *nome, char *tel, char *end, int cep, char *nasc); //aloca novo contato da agenda
void insertion_sort_contato(Cabecalho *c, Agenda *novo); //insere contato na agenda ordenado pelo nome
void imprime_agenda(Cabecalho *c); //imprime lista já ordenada
int valida_nome_endereco(char *vetor);
int valida_telefone(char *tel);
int valida_cep(int cep);
int valida_data_nasc(char *data_nasc);
void sair(Cabecalho *c); //altera arquivo e libera agenda
//void remover_contatos_por_string(); //remove todos os contatos que tiverem a string de entrada
//void imprime_contatos_por_string(); //imprime todos os contatos que tiverem a string de entrada

int main(int argc, char const *argv[]){
  Cabecalho *c;
  int opc = 0;

  c = inicia_cabecalho();

  /*
   * MENU
   */
  do{
    printf("\n\n>>>>>>> LISTA DE CONTATOS <<<<<<<\n\n1) Inserir novo registro;\n2) Remover registros por string;\n3) Visualizar registro por string;\n4) Imprimir lista em ordem alfabética;\n5) Sair;\n\nDIGITE SUA ESCOLHA: ");
    scanf("%d", &opc);
    getchar();

    switch (opc){
      case 1:{
          int cep, valida;
          char nome[MAX_CONTATO], endereco[MAX_CONTATO], tel[11], data_nasc[11];
          Agenda *novo;

          //Nome
          valida = FALSE;
          while (valida != TRUE) {
            printf("\nDigite o nome completo: ");
            scanf("%[^\n]", nome);
            getchar();
            valida = valida_nome_endereco(nome);
          }

          //Telefone
          valida = FALSE;
          while (valida != TRUE) {
            printf("\nDigite o telefone: ");
            scanf("%[^\n]", tel);
            getchar();
            valida = valida_telefone(tel);
          }

          //Endereço
          valida = FALSE;
          while (valida != TRUE) {
            printf("\nDigite o endereco: ");
            scanf("%[^\n]", endereco);
            getchar();
            valida = valida_nome_endereco(endereco);
          }

          //CEP
          valida = FALSE;
          while (valida != TRUE) {
            printf("\nDigite o CEP: ");
            scanf("%d", &cep);
            getchar();
            valida = valida_cep(cep);
          }

          //Data de nascimento
          valida = FALSE;
          while (valida != TRUE) {
            printf("\nDigite data de nascimento: ");
            scanf("%[^\n]", data_nasc);
            getchar();
            valida = valida_data_nasc(data_nasc);
          }

          novo = cria_contato(nome, tel, endereco, cep, data_nasc);
          insertion_sort_contato(c, novo);
      }break;

      case 2:{

      }break;

      case 3:{

      }break;

      case 4:
        imprime_agenda(c);
        break;
    }

  }while(opc > 0 && opc < 5);

  if(opc == 5) //Gravar lista no arquivo, liberar ponteiros e sair;
    sair(c);

  return 0;
}/*FIM-main*/

void sair(Cabecalho *c){
  //Libera lista
  Agenda *atual = c->inicio, *aux;

  for(aux = atual; aux != NULL; atual = aux){
    aux = aux->prox;
    free(atual->info);
    free(atual);
  }

  free(c);
}/*FIM-sair*/

void imprime_agenda(Cabecalho *c){
  Agenda *atual = c->inicio, *aux;

  for(aux= atual; aux != NULL; atual = aux){
    printf("\n\n%s\n%s\n%s\n%05d\n%s\n", atual->info->nome, atual->info->telefone, atual->info->endereco, atual->info->cep, atual->info->data_nasc);
    aux= aux->prox;
  }
}/*FIM-imprime_agenda*/

int valida_nome_endereco(char *vetor){
  int tam;
  tam = (int)strlen(vetor);
  if(tam > (MAX_CONTATO - 1))
    return FALSE; //Não validou
  else
    return TRUE; //Validou

}/*FIM-valida_nome_endereco*/

int valida_telefone(char *tel){
  int tam, digitos;
  tam = (int)strlen(tel);
  digitos = FALSE;

  for(int i = 0; i < 10; i++){
    if(i == 5 && tel[i] != '-')
      digitos = TRUE;
    else if(i != 5 && (tel[i] < '0' || tel[i] > '9'))
      digitos = TRUE;
  }

  if(tam != 10 || digitos)
    return FALSE; //Não validou
  else
    return TRUE; //Validou

}/*FIM-valida_telefone*/

int valida_cep(int cep){
  if(cep < 0 || cep > 99999)
    return FALSE; //Não validou
  else
    return TRUE; //Validou

}/*FIM-valida_cep*/

int valida_data_nasc(char *data_nasc){
  int tam, digitos, dia, mes;
  tam = (int)strlen(data_nasc);
  digitos = FALSE;

  for(int i = 0; i < 10; i++){
    if((i == 2 || i == 5) && data_nasc[i] != '/')
      digitos = TRUE;
    else if(i != 2 && i != 5 && ( ((int)data_nasc[i]) < 48 || ((int)data_nasc[i]) > 57) )
      digitos = TRUE;
  }

  if(digitos == FALSE){
    dia = (((int)data_nasc[0] - 48) * 10) + ((int)data_nasc[1] - 48);
    mes = (((int)data_nasc[3] - 48) * 10) + ((int)data_nasc[4] - 48);

    if((dia < 1 || dia > 31) || (mes < 1 || mes > 12))
      digitos = TRUE;
  }

  if(tam != 10 || digitos)
    return FALSE; //Não validou
  else
    return TRUE; //Validou
}/*FIM-valida_data_nasc*/

void insertion_sort_contato(Cabecalho *c, Agenda *novo){
  Agenda *inicio = c->inicio;
  Agenda *atual = NULL;
  Agenda *aux = NULL;
  int achou, achou2; //Booleano

  if(c->inicio == NULL){ //CASO 1: Lista vazia
    novo->prox = novo->ant = NULL;
    c->inicio = c->fim = novo;
    c->tamanho++;

  }else if(novo->info->nome[0] < c->inicio->info->nome[0]){ //CASO 2: 2º nó da lista - vai para o inicio da lista
    novo->prox = c->inicio;
    novo->ant = c->inicio->ant;
    c->inicio->ant = novo;
    c->inicio = novo;
    c->tamanho++;

  }else if(novo->info->nome[0] == c->inicio->info->nome[0]){ //CASO 2: 2º nó da lista- ordena pela 2ª letra

    if(novo->info->nome[1] < c->inicio->info->nome[1]){
      novo->prox = c->inicio;
      novo->ant = c->inicio->ant;
      c->inicio->ant = novo;
      c->inicio = novo;
      c->tamanho++;
    }else{

    }

  }else{ //CASO GERAL: Percorre lista até achar a posição correta para inserir o nó
    atual = c->inicio;
    achou = achou2 = FALSE;

    for(aux= atual; aux != NULL; atual = aux){

      if(novo->info->nome[0] < atual->info->nome[0]){
        achou = TRUE;
        break;

      }else if(novo->info->nome[0] == atual->info->nome[0]){ //Ordena pela 2ª letra
        printf("Segunda letra\n");
        achou2 = TRUE;
        break;

      }else{
        aux = aux->prox;
      }

    }

    if(achou2 == TRUE && novo->info->nome[1] < atual->info->nome[1]){ //Ordena pela 2ª letra [Insere antes]
      novo->ant = atual->ant;
      novo->prox = atual;
      atual->ant->prox = novo;
      atual->ant = novo;
      c->tamanho++;

    }else if(achou2 == TRUE && novo->info->nome[1] != atual->info->nome[1]){ //Ordena pela 2ª letra [Insere depois]
      novo->ant = atual;
      novo->prox = atual->prox;
      atual->prox->ant = novo;
      atual->prox = novo;
      c->tamanho++;

    }else if(achou == TRUE){ //Insere o nó no meio da lista ordenada
      novo->prox = atual;
      novo->ant = atual->ant;
      atual->ant->prox = novo;
      atual->ant = novo;
      c->tamanho++;

    }else{ //Insere no final da lista (agenda)
      novo->ant = c->fim;
      novo->prox = c->fim->prox;
      c->fim->prox = novo;
      c->fim = novo;
      c->tamanho++;

    }

  }

}/*FIM-insertion_sort_contato*/

Cabecalho* inicia_cabecalho(){
  Cabecalho *c = NULL;

  c = (Cabecalho*) malloc(sizeof(Cabecalho));

  if(c == NULL)
    exit(-1);

  c->inicio = NULL;
  c->fim = NULL;
  c->tamanho = 0;

  return c;
}/*FIM-inicia_cabecalho*/

Agenda* cria_contato(char *nome, char *tel, char *end, int cep, char *nasc){
  Contato *novo_contato = NULL;
  Agenda *a = NULL;

	novo_contato = (Contato*) malloc(sizeof(Contato));

	if (novo_contato == NULL){
		printf("\nProblema de memoria.\n");
		exit(-1);
	}

  strcpy(novo_contato->nome , nome);
  strcpy(novo_contato->telefone , tel);
  strcpy(novo_contato->endereco , end);
  strcpy(novo_contato->data_nasc , nasc);
  novo_contato->cep = cep;

  a = (Agenda*) malloc(sizeof(Agenda));

  if (a == NULL)
		exit(-10);

  a->info = novo_contato;
  a->ant = NULL;
  a->prox = NULL;

  return a;
}/*FIM-cria_contato*/
