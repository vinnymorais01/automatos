#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
/* Alunos: João Martins RA: 1552260
 * 		 	Felipe Minorelli RA: 1551167
*/
int main (){
	
	FILE *fp = fopen("testeAutomatosDetermNDetermi.txt", "r"); 
	
	char line[256];
	char getAlfabeto [200];
	char alfabeto [200];
	char getEstados[200];
	char estados[200];
	char estados2[200];
	char getFinal[200];
	char getInicial[200];
	char inicial [200];
	char inicial2[200];
	char final [200];
	char final2[200];		
	char entrada[200];
	int i,j=0;
	int tam_alfa;
	int tam_estados;		
	int tam_inicial;		
	int tam_final;
	int atual;
	int inicio;
	char resultado;
	
	
	
	
	//Pega alfabeto e limpa
{	
	fgets(line,sizeof(line),fp);
	sscanf(line,"%[^\n]",getAlfabeto);
	
	tam_alfa=strlen(getAlfabeto);
	
	for(i=0;i<tam_alfa;i++){
		
		if(isspace(getAlfabeto[i]));
		
		else{
			alfabeto[j]=getAlfabeto[i];
			j++;
		}
	}
	tam_alfa=tam_alfa/2;

}
	//Pega estados e limpa
{
	fgets(line,sizeof(line),fp);
	sscanf(line,"%[^\n]",getEstados);
	
	tam_estados=strlen(getEstados);
	
		
	for(i=0,j=0;i<tam_estados;i++){

		if(isdigit(getEstados[i])){
			estados2[j]=getEstados[i];
			j++;
		}
		
		else{
			
		}
	}
	
	tam_estados=tam_estados/2+1;
	
	
		for(i=0,j=0;i<tam_estados;i++){
		
		if(isspace(estados2[i]));
		
		else{
			estados[j]=estados2[i];
			j++;
		}
	}
	tam_estados=tam_estados/2+1;
}
	//Pega inicial e limpa
{		
		fgets(line,sizeof(line),fp);
		sscanf(line,"%[^\n]",getInicial);

	tam_inicial=strlen(getInicial);
	
		
	for(i=0,j=0;i<tam_inicial;i++){

		if(isdigit(getInicial[i])){
			inicial2[j]=getInicial[i];
			j++;
		}
		
		else{

		}
	}
	
	tam_inicial=tam_inicial/2+1;
	
	
		for(i=0,j=0;i<tam_inicial;i++){
		
		if(isspace(inicial2[i]));
		
		else{
			inicial[j]=inicial2[i];
			j++;
		}
	}
	tam_inicial=tam_inicial/2;
		inicio=atoi(inicial);
}
	//Pega final e limpa
{
		fgets(line,sizeof(line),fp);
		sscanf(line,"%[^\n]",getFinal);

	tam_final=strlen(getFinal);
	
		
	for(i=0,j=0;i<tam_final;i++){

		if(isdigit(getFinal[i])){
			final2[j]=getFinal[i];
			j++;
		}
		else{

		}
	}
	
	tam_final=tam_final/2+1;
	
	
		for(i=0,j=0;i<tam_final;i++){
		
		if(isspace(final2[i]));
		
		else{
			final[j]=final2[i];
			j++;
		}
	}
	tam_final=tam_final/2;
		
}
	char matriz [tam_alfa] [tam_estados];
	//Criação de transições
{	
	

	if(alfabeto[0]<alfabeto[1]){
	for(i=0;i<tam_estados;i++){
		for(j=0;j<tam_alfa;j++){
			fgets(line,sizeof(line),fp);
			sscanf(line,"%*s %*s %*c%c",&matriz[i][j]);
			}
	}
}
	
	else {
		for(i=0;i<tam_estados;i++){
		for(j=tam_alfa;j>0;j--){
			fgets(line,sizeof(line),fp);
			sscanf(line,"%*s %*s %*c%c",&matriz[i][j-1]);
			}
		}
}

}
	//Scan da entrada do usuario
{
	printf("Digite a entrada a ser testada no automato: ");
	scanf("%s",entrada);
	printf("\n");	
}
	//Que comessem as comparações
{
	for(i=tam_estados;i=0;i--){
		if(estados[i]=='0'){
			atual=inicio;
			break;
		}
		else
		atual=inicio-1;
	}
	
	i=0;
	while (entrada[i]!='\0'){
		for(j=0;j<tam_alfa;j++){
			if(alfabeto[j]==entrada[i]){	
			atual=matriz[atual][j] - '0';		
			}
		}
		i++;
	}
	
	resultado= (char)(atual+'0');

		for(i=0;i<tam_final;i++){
			if(resultado==final[i]){
			printf("Palavra aceita");
			break;
		}
		printf("Palavra nao aceita");
	}		
}
	return 0;
}
