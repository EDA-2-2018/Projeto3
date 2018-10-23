/*
 * O que falta fazer:
 * - Parte de arquivos
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CONTATO 101
#define ANO_ATUAL 2018
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
int valida_nome(char *vetor);
int valida_telefone(char *tel);
int valida_cep(int cep);
int valida_data_nasc(char *data_nasc);
void sair(Cabecalho *c); //altera arquivo e libera agenda
int contem_string(char *nome, char *pesquisa);
void remover_contato(Cabecalho *c, Agenda *contato);
void remover_contatos_por_string(char *pesquisa, Cabecalho *c); //remove todos os contatos que tiverem a string de entrada
void imprime_contatos_por_string(char *pesquisa, Cabecalho *c); //imprime todos os contatos que tiverem a string de entrada
void menu(Cabecalho *c);

int main(int argc, char const *argv[]){
  Cabecalho *c;

  c = inicia_cabecalho();

  menu(c);

  return 0;
}/*FIM-main*/

void menu(Cabecalho *c){
  int opc = 0;

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
        char pesquisa[MAX_CONTATO];

        printf("\nDigite a string de pesquisa para remover o(s) registro(s): ");
        scanf("%[^\n]", pesquisa);
        getchar();

        remover_contatos_por_string(pesquisa, c);

      }break;

      case 3:{
        char pesquisa[MAX_CONTATO];

        printf("\nDigite a string de pesquisa: ");
        scanf("%[^\n]", pesquisa);
        getchar();

        imprime_contatos_por_string(pesquisa, c);

      }break;

      case 4:
        imprime_agenda(c);
        break;
      default:
        while(opc < 1 || opc > 5){
          printf("\nEscolha uma opção válida: ");
          scanf("%d", &opc);
          getchar();
        }
        break;
    }

  }while(opc != 5);

  if(opc == 5) //Gravar lista no arquivo, liberar ponteiros e sair;
    sair(c);

}/*FIM-menu*/

void remover_contatos_por_string(char *pesquisa, Cabecalho *c){
  Agenda *atual = c->inicio, *aux;
  int exclua;

  for(aux= atual; aux != NULL; atual = aux){
    exclua = contem_string(atual->info->nome, pesquisa);
    if(exclua){
      remover_contato(c, atual);
      atual = c->inicio;
    }
    aux= aux->prox;
  }
}/*FIM-remover_contatos_por_string*/

void remover_contato(Cabecalho *c, Agenda *contato){

  if(c->tamanho == 0 && (c->inicio == NULL && c->fim == NULL)){
    c->tamanho = 1;

  }else if(c->tamanho == 1){
    c->inicio = c->fim = NULL;
    free(contato->info);
    free(contato);

  }else if(c->tamanho == 2 && contato == c->inicio){
    c->inicio = c->fim;
    c->inicio->prox = c->inicio->ant = NULL;
    free(contato->info);
    free(contato);

  }else if(c->tamanho == 2 && contato == c->fim){
    c->fim = c->inicio;
    c->fim->prox = c->fim->ant = NULL;
    free(contato->info);
    free(contato);

  }else if(contato == c->inicio && c->tamanho > 2){ //Remove do inicio da lista
    c->inicio = contato->prox;
    contato->prox->ant = NULL;
    free(contato->info);
    free(contato);

  }else if(contato == c->fim && c->tamanho > 2){ //Remove do final da lista
    c->fim = contato->ant;
    contato->ant->prox = NULL;
    free(contato->info);
    free(contato);
  }else{ //Remove do meio da lista
    contato->prox->ant = contato->ant;
    contato->ant->prox = contato->prox;
    free(contato->info);
    free(contato);
  }

  c->tamanho--;

}/*FIM-remover_contato*/

void imprime_contatos_por_string(char *pesquisa, Cabecalho *c){
  Agenda *atual = c->inicio, *aux;
  int imprime;

  for(aux= atual; aux != NULL; atual = aux){
    imprime = contem_string(atual->info->nome, pesquisa);
    if(imprime)
      printf("\n\n%s\n%s\n%s\n%05d\n%s\n", atual->info->nome, atual->info->telefone, atual->info->endereco, atual->info->cep, atual->info->data_nasc);
    aux= aux->prox;
  }

}/*FIM-imprime_contatos_por_string*/

int contem_string(char *nome, char *pesquisa){
  char *test;

  test = strstr(nome, pesquisa);

  if(test == NULL)
    return 0; //Não contem
  else
    return 1; //Pesquisa está dentro do nome
}/*FIM-contem_string*/

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
  printf("\nQuantidade de registros da agenda: %d\n", c->tamanho);
}/*FIM-imprime_agenda*/

int valida_nome_endereco(char *vetor){
  int tam;
  tam = (int)strlen(vetor);
  if(tam > (MAX_CONTATO - 1))
    return FALSE; //Não validou
  else
    return TRUE; //Validou

}/*FIM-valida_nome_endereco*/

int valida_nome(char *vetor){
  int tam, digitos;
  tam = (int)strlen(vetor);
  digitos = FALSE;

  for(int i = 0; i < MAX_CONTATO; i++){
    if(vetor[i] >= '0' || vetor[i] <= '9')
      digitos = TRUE;
  }

  if(tam > (MAX_CONTATO - 1) || digitos)
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
  int tam, digitos, dia, mes, ano;
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
    ano = (((int)data_nasc[6] - 48) * 1000) + (((int)data_nasc[7] - 48) * 100) + (((int)data_nasc[8] - 48) * 10) + ((int)data_nasc[9] - 48);

    if((dia < 1 || dia > 31) || (mes < 1 || mes > 12) || (ano < 1 || ano > ANO_ATUAL))
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

  }else if(novo->info->nome[0] < c->inicio->info->nome[0] && c->tamanho == 1){ //CASO 2: 2º nó da lista - vai para o inicio da lista
    novo->prox = c->inicio;
    novo->ant = c->inicio->ant;
    c->inicio->ant = novo;
    c->fim = c->inicio;
    c->inicio = novo;

  }else if(novo->info->nome[0] == c->inicio->info->nome[0] && c->tamanho == 1){ //CASO 2: 2º nó da lista- ordena pela 2ª letra

    if(novo->info->nome[1] < c->inicio->info->nome[1]){
      novo->prox = c->inicio;
      novo->ant = c->inicio->ant;
      c->inicio->ant = novo;
      c->fim = c->inicio;
      c->inicio = novo;
    }else{
      novo->prox = c->inicio->prox;
      novo->ant = c->inicio;
      c->inicio->prox = novo;
      c->fim = novo;
    }

  }else{ //CASO GERAL: Percorre lista até achar a posição correta para inserir o nó
    atual = c->inicio;
    achou = achou2 = FALSE;

    for(aux= atual; aux != NULL; atual = aux){

      if(novo->info->nome[0] < atual->info->nome[0]){
        achou = TRUE;
        break;

      }else if(novo->info->nome[0] == atual->info->nome[0]){ //Ordena pela 2ª letra
        achou2 = TRUE;
        break;

      }else{
        aux = aux->prox;
      }

    }/*FIM-for*/

    if(achou2 == TRUE && novo->info->nome[1] < atual->info->nome[1]){ //Ordena pela 2ª letra [Insere antes]

      if(atual == c->inicio){
        novo->ant = atual->ant;
        novo->prox = atual;
        c->inicio->ant = novo;
        c->inicio = novo;
      }else{
        novo->ant = atual->ant;
        novo->prox = atual;
        atual->ant->prox = novo;
        atual->ant = novo;
      }

    }else if(achou2 == TRUE && novo->info->nome[1] >= atual->info->nome[1]){ //Ordena pela 2ª letra [Insere depois]

      for(aux= atual; atual->info->nome[0] == novo->info->nome[0] && aux != NULL; atual = aux){

        if(novo->info->nome[1] <= atual->info->nome[1] && atual != c->fim){ //Insere antes no meio da lista
          novo->ant = atual->ant;
          novo->prox = atual;
          atual->ant->prox = novo;
          atual->ant = novo;
          break;

        }else if(novo->info->nome[1] < atual->info->nome[1] && atual == c->fim){ //Insere antes do último registro
          novo->ant = atual->ant;
          novo->prox = atual;
          atual->ant->prox = novo;
          atual->ant = novo;
          break;

        }else if(atual != c->fim && novo->info->nome[1] > atual->info->nome[1]){ //Insere depois no meio da lista
          novo->ant = atual;
          novo->prox = atual->prox;
          atual->prox->ant = novo;
          atual->prox = novo;
          break;

        }else if(atual == c->fim && novo->info->nome[1] >= atual->info->nome[1]){ //Insere depois no final da lista
          novo->ant = c->fim;
          novo->prox = c->fim->prox;
          c->fim->prox = novo;
          c->fim = novo;
          break;
        }else{
          aux = aux->prox;
        }

      }/*FIM-for*/

    }else if(achou == TRUE){ //Insere o nó no meio da lista ordenada
      novo->prox = atual;
      novo->ant = atual->ant;
      atual->ant->prox = novo;
      atual->ant = novo;

    }else{ //Insere no final da lista (agenda)
      novo->ant = c->fim;
      novo->prox = c->fim->prox;
      c->fim->prox = novo;
      c->fim = novo;
    }
  }

  c->tamanho++;

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
