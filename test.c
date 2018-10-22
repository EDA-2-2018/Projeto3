#include <stdio.h>

int main() {
  char ch;
  FILE *arquivo;
  
  char Nome[101];
  char Telefone[11];
  char Endereco[101];
  int CEP;
  char DATA_NASC[11];
  
  arquivo = fopen("contatosssssss.txt", "r");

  if(arquivo) {
	printf("existe!\n");
	fclose(arquivo);
  }
  else{
	printf("Nao existe\n");

  	arquivo = fopen("contatosssssss.txt", "w");
  	fprintf(arquivo, "Tarra Casebolt\n96697-6327\n793 N. College St. La Vergne, TN\n37086\n26/09/1925\n$\nToney Schaffner\n95597-4268\n7596 East Vernon Drive Willingboro, NJ\n8046\n13/03/1936\n$\nMirna Halford\n97465-4294\n9841 Franklin St. Dalton, GA\n30721\n15/04/1951\n$\nBelva Yelvington\n99799-8331\n483 Roosevelt Street Ottumwa, IA\n52501\n25/09/1971\n$\nRodrigo Drews\n92130-3960\n10 Jockey Hollow Dr. Dothan, AL\n36301\n04/04/1994\n$\n");
 	fclose(arquivo);
 }
  
  arquivo = fopen("contatosssssss.txt", "r");
  
  while((fscanf(arquivo, " %[^'\n'] %[^'\n'] %[^'\n'] %d %[^'\n'] %c\n", Nome, Telefone, Endereco, &CEP, DATA_NASC, &ch))!=EOF) {

  }
	printf("%s\n", Nome);
	printf("%s\n", Telefone);
	printf("%s\n", Endereco);
	printf("%d\n", CEP);	
	printf("%s\n", DATA_NASC);
  	printf("%c\n", ch);
  	fclose(arquivo); 
	
	return 0;
}
