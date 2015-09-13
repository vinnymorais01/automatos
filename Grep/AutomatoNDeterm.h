#include "PilhaEstado.h"
#define epsilon '('
#define epsilon2 ')'
#define tamavetor 255

State* criarEstado(int id, State** t, State* l);//criar estado
void imprimirEstado(State* state); //imprimir estado
State* exprestoNdeter(char* exp); //converter exp para nfa
State** criarVetor();
int runNFA(State* start, char* str, State* last);
int id;

State* criarEstado(int id, State** t, State* l)
{
	State* s = (State*) malloc(sizeof(State));
	s->id = id;
	s->trans = t;
	s->last = l;
	return s;
}

//Converte expressão regular para Automato Não Deterministico
State* exprestoNdeter(char* exp)
{
	int i = 0;
	id = 0;
	int c;
	StackState* stack = createStackState(100);
	State** vector;
	State *state0, *state1, *state2, *state3, *state4, *state5;
	while(exp[i]!='\0')
	{
		if(exp[i] == '.')//concatenação
		{
			popState(stack, &state2);
			popState(stack, &state1); //desempilha dois estados

			vector = criarVetor();
			vector[epsilon] = state2; //insere transação epsilon para state2

			state3 = state1->last; //procurar ultimo estado de state1
			state3->trans = vector; //seta o vetor de transação para o vetor criado

			state1->last = state2->last;
			state2->last = NULL;
			pushState(stack, state1); //empilha estado
		}
		else if(exp[i] == '+') //uniao
		{
			popState(stack, &state2);
			popState(stack, &state1);//desempilha dois estados

			vector = criarVetor();//cria um vetor
			vector[epsilon] = state1;//epsilon
			vector[epsilon2] = state2;

			state4 = criarEstado(id, NULL,NULL); //cria estado auxiliar(final)
			id++;
			state0 = criarEstado(id, vector,state4);//cria um estado(inicial) com vector = vector criado
			id++;

			vector = criarVetor();
			vector[epsilon] = state4;//epsilon
			state3 = state1->last;//procurar ultimo estado de state1
			state3->trans = vector;

			vector = criarVetor();
			vector[epsilon] = state4;//epsilon
			state5 = state2->last;//procurar ultimo estado de state2
			state5->trans = vector;

			state0->last = state4;
			state2->last = NULL;
			state1->last = NULL;

			pushState(stack,state0);
		}
		else if(exp[i] == '*')//Fecho de Kleene
		{
			popState(stack, &state1);
			state2 = criarEstado(id, NULL,NULL); //cria estado auxiliar(final)
			id++;

			vector = criarVetor();
			vector[epsilon] = state1;
			vector[epsilon2] = state2;

			state1->last->trans = vector;
			state3 = criarEstado(id, vector,state2);//cria um estado(inicial) com vetor = vetor criado
			id++;

			state1->last = NULL;
			pushState(stack,state3);
		}
		else
		{
			state0 = criarEstado(id,NULL,NULL);//cria um estado auxiliar com vetor = NULL
			id++;
			vector = criarVetor(); //criar um vetor
            		c = exp[i];
			vector[c] = state0; //insere a letra no vetor apontando para o s0
			state1 = criarEstado(id,vector,state0); //cria um estado com vetor = vetor criada
			id++;
			pushState(stack,state1); //empilha estado
		}
		i++;
	}
	popState(stack, &state0);
	return state0;
}


void imprimirEstado(State* state)
{
	printf("id: %d\n", state->id);
}

State** criarVetor()
{
	State** vector = (State**)malloc(tamavetor*sizeof(State*));
    int i;
	for(i=0;i<tamavetor;i++)
	{
		vector[i] = NULL;
	}
	return vector;
}

int runNFA(State* start, char* str, State* last)
{
	if(start==NULL || start->id == -1)
		return 0;
	int ok = 0;
	State* aux = start;
	int i = 0;
	int n;
    if(aux->trans!=NULL)
        ok = ok || runNFA(aux->trans[epsilon], str+i, last) || runNFA(aux->trans[epsilon2], str+i, last);
    if(str!=NULL)
    {
        n = str[i];
        while((str[i]!='\0') && (aux->trans!=NULL) && (aux->trans[n]!=NULL))
        {
            aux = aux->trans[n];
            i++;
            if(aux->trans!=NULL)
            {
                if(str[i]!='\0')
                    ok = ok || runNFA(aux->trans[epsilon], str+i, last) || runNFA(aux->trans[epsilon2], str+i, last);
                else
                    ok = ok || runNFA(aux->trans[epsilon], '\0', last) || runNFA(aux->trans[epsilon2], '\0', last);
            }
            if(str[i]!='\0')
                n = str[i];
        }
        if(aux==last && str[i]=='\0')
            return 1;
        else
            return ok;
    }
    else
        if(aux==last)
            return 1;
        else
            return ok;
}
