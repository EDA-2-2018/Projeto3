#include <stdio.h>

int main() {
  char ch;
  FILE *arquivo;
  
  int count = 0;
 
  char Nome[101];
  char Telefone[11];
  char Endereco[101];
  int CEP;
  char DATA_NASC[11];
  
  arquivo = fopen("contatos.txt", "r");
  
  while((fscanf(arquivo, " %[^'\n'] %[^'\n'] %[^'\n'] %d %[^'\n'] %c\n", Nome, Telefone, Endereco, &CEP, DATA_NASC, &ch))!=EOF) {
   	
   	
    printf("%s\n", Nome);
  	printf("%s\n", Telefone);
  	printf("%s\n", Endereco);
  	printf("%d\n", CEP);
	printf("%s\n", DATA_NASC);
	printf("%c\n", ch);

   	if(ch=='$')
   		count+=1;
  }

  printf("\n%d contatos cadastrados\n", count);

  fclose(arquivo); 
	
  return 0;
}