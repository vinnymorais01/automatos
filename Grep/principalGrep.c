#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AutomatoNDeterm.h"
#include "PilhaExpressão.h"
#define tamTextArquivo 1000000
#define tamanhoaux 100
#define tamanhoinicial 1000000

//lendo texto de Arquivo
char* importFile(char* localArq)
{
    char c;
    int i=0;
    int tam=tamanhoinicial;
    FILE* arquivo = fopen(localArq, "r");
    if(!arquivo)
        return NULL;
    char* str = (char*)malloc(tam*sizeof(char));
    while((c=getc(arquivo))!=(char)EOF)
    {
        if(i>=tam)
        {
            tam*=2;
            str = (char*) realloc(str,tam*sizeof(char));
        }
        str[i]=c;
        i++;
    }
    fclose(arquivo);
    return str;
}

//Função para verificar na pilha o estado
int VerificacaoPilha(Stack* Pilha,char* x)
{
   int i,resposta;
   char ValorRemovido;
   char Valor_top;
   int n = strlen(x);

   i = 0;

   while(i < n)
   {
         if(x[i] == ')')
        {
            peek(Pilha,&Valor_top);
            if (sizeStack(Pilha) != 0 && Valor_top == '(')
                pop(Pilha,&ValorRemovido);
            else
            {
                clearStack(Pilha);
                return 0;
            }
        }
        else if(x[i] == ']')
        {
            peek(Pilha,&Valor_top);
            if (sizeStack(Pilha) != 0 && Valor_top == '[')
                pop(Pilha,&ValorRemovido);
            else
            {
                clearStack(Pilha);
                return 0;
            }
        }
        else if(x[i] == '}')
        {
            peek(Pilha,&Valor_top);
            if (sizeStack(Pilha) != 0 && Valor_top == '{')
                pop(Pilha,&ValorRemovido);
            else
            {
                clearStack(Pilha);
                return 0;
            }
        }
        else if (x[i] == '(' || x[i] == '[' || x[i] == '{')
            push(Pilha,x[i]);
        i++;
   }
   if (sizeStack(Pilha) == 0)
        resposta = 1;
   else
        resposta = 0;

   clearStack(Pilha);
   return resposta;

}

//Função de Conversão de Expressão Regular (idéia do site)
char* convertExpression(char* exp)
{
	int i=0,j=0;
	char c;
	char* newExp = (char*)malloc(tamanhoaux*sizeof(char));
	Stack* stack = createStack(tamanhoaux);
	while(exp[i]!='\0')
	{
		if(exp[i]=='[')
		{
			newExp[j] = '(';
			j++;
			i++;
			do
			{
				if (exp[i] == '[')
            				push(stack,exp[i]);
				else if(exp[i] == ']')
					pop(stack,&c);
                else
                {
                    newExp[j] = exp[i];
                    j++;
                    if((exp[i+1]!=']') || (!isEmptyStack(stack)) || ((exp[i+1]!=']') && (exp[i+2]!=']')))
                    {
                        if(exp[i+1]!='*' && (exp[i+1]!=']' || exp[i+2]!=']'))
                        {
                            newExp[j] = '+';
                            j++;
                        }
                        else if (exp[i+1]==']' || exp[i+2]==']')
                        {
                            newExp[j] = ')';
                            j++;
                        }
                    }
                    else
                    {
                        newExp[j] = ')';
                        j++;
                        if(exp[i+1]!='*' && exp[i+2]!='\0' && exp[i+2]!='*' && exp[i+2]!=']')
                        {
                            newExp[j] = '.';
                            j++;
                        }
                    }
                }
            i++;
            }while((exp[i]!=']') || (!isEmptyStack(stack)));
		}
		else if(exp[i]=='*')
		{
			newExp[j] = '*';
			j++;
			if(exp[i+1]=='[')
            {
                newExp[j] = '.';
                j++;
            }
		}
		else
		{
		    if(newExp[j-1]=='*')
            {
                newExp[j] = '.';
                j++;
            }
			newExp[j] = exp[i];
			j++;
			if(exp[i+1]!='\0' && exp[i+1]!='*')
			{
				newExp[j] = '.';
				j++;
			}
		}
		i++;
	}
	newExp[j] = exp[i];
	return newExp;
}

//Função para colocar prioridade no algoritmo 
int prioridade(char op)
{
    if (op == '(')
        return 1;
    else if (op == '+')
        return 2;
    else if (op == '.')
        return 3;
    else if (op == '*')
        return 4;
    return -1;
}

char* exp2post(char* exp)
{
	Stack* stack = createStack(tamanhoaux);
	char top, str;
	char* convertedExp = (char*) malloc(tamanhoaux*sizeof(char));
	int i=0, p=-1, j=0;
	while(exp[i]!='\0')
	{
		if (!peek(stack,&top))
			p=-1;
        	else
		        p=prioridade(top);
		str = exp[i];
		if(((str >= 'A')&&(str <= 'z')) || (((str>='0')&&(str<='9'))))
		{
			convertedExp[j] = str;
			j++;
		}
		else if(str=='(')
		{
			push(stack,str);
		}
		else if(str==')')
		{
			push(stack,str);
			top=')';
			while(top!='(')
			{
		                pop(stack,&top);
		                if(top!='('&&top!=')')
		                {
		                    convertedExp[j]=top;
		                    j++;
		                }
			}
		}
		else if (prioridade(str)<=p)
        	{
			pop(stack,&top);
			convertedExp[j]=top;
			j++;
			push(stack,str);
		}
		else if(prioridade(str)>p)
	        {
			push(stack,str);
		}
		i++;
	}
	while(!isEmptyStack(stack))
        {
    	    pop(stack,&top);
    	    convertedExp[j]=top;
		j++;
    	}
	convertedExp[j] = '\0';
	return convertedExp;
}

char* getSubstring(char* str,int begin, int end)
{
  
    int size = end - begin, i, j = begin;
    char* sub = (char*)malloc(size*sizeof(char));
    for(i=0;i<size;i++)
    {
        sub[i] = str[j];
	j++;
    }
    return sub;
}

int verifySubstring(char* str, State* state)
{
    int i,j, size = strlen(str), ok=0;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            ok = ok || runNFA(state,getSubstring(str,i,j),state->last);
        }
    }
    return ok;
}

void printRightLines(char* str, char* localArq, State* state)
{
	int i=0, j=0;
	char* line = (char*)malloc(tamanhoinicial*sizeof(char));
	while(str[i]!='\0')
	{
		while(str[i]!='\n')
		{
			line[j] = str[i];
			j++;
			i++;
		}
		line[j] = '\0';
		j=0;
        if(verifySubstring(line, state))
            printf("%s: %s\n",localArq,line);
		i++;
	}
}


int main(int argc,char* argv[])
{
	if(argc < 3)
	{
		printf("Modo de usar:\n ./grep expressao arquivo\n");
		return 0;
	}
    
	char* exp = (char*)malloc(tamanhoaux*sizeof(char));
	strcpy(exp,argv[1]);
	char* contentFile = (char*)malloc(tamTextArquivo*sizeof(char));
	contentFile = importFile(argv[2]);
	Stack* stack = createStack(tamanhoaux);

	if(!VerificacaoPilha(stack,exp))
		printf("Expressão Invalida\n");

	char* newExp;
	newExp = convertExpression(exp);
	printf("Expressão lida: %s\n", newExp);

	State* state = exprestoNdeter(newExp);
	printRightLines(contentFile,argv[2],state);

    return 0;
}
