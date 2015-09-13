# Linguagens formais, automatos e computabilidade (BCC34B-IC4A)
# Aluno: Luiz Felipe Fronchetti Dias RA: 1552309
# 			João Martins Filho			 RA: 1552260
#			Felipe Minorelli				 RA: 1551167
import traceback
import sys

class Stack:
     def __init__(self):
         self.items = []

     def isEmpty(self):
         return self.items == []

     def push(self, item):
         self.items.append(item)

     def pop(self):
         return self.items.pop()

     def peek(self):
         return self.items[len(self.items)-1]

     def size(self):
         return len(self.items)

def Imprimir_Pilha(Pilha):
	while not Pilha.isEmpty():
		print "Pilha Impressa: ",Pilha.pop()

# Divide linha-por-linha do meu arquivo
def Split_Lines():
	string = open('automato_pilha.txt', 'r').read()
	string = string.splitlines()
	return string
	
# Separa todos os elementos da minha linha e retorna o tamanho da lista	
def Split_Values(string):
	string = string.split()
	tamanho = len(string)
	return string, tamanho
	
def automato_pilha(pilha,meu_arquivo,sequencia,tamanho_sequencia,alfabeto_entrada,alfabeto_pilha,simbolo_epsilon,simbolo_inicial,conjunto_estados,estado_inicial,conjunto_aceitacao):
	tamanho_arquivo = len(meu_arquivo)
	tamanho_aceitacao = len(conjunto_aceitacao)
	estado_atual = estado_inicial[0]
	pilha_funcao = Stack()
	pilha_funcao = pilha	
		
	# Percorre toda a sequencia dada
	for i in range(0,tamanho_sequencia):
		print sequencia[i]
		print estado_atual
		# Percorre todas as transacoes existentes
		for j in range(7,tamanho_arquivo):
			estado_sequencia,estado_tamanho = Split_Values(meu_arquivo[j])
			if estado_atual == estado_sequencia[0] and sequencia[i] == estado_sequencia[1]:
				print "ESTADO ATUAL:", estado_atual
				print "ESTADO SEQUENCIA:", estado_sequencia[0]
				print "LETRA TRANSACAO:", estado_sequencia[1]
				print "LETRA PEGANDO:", sequencia[i]
				print "ESTADO PROXIMO:", estado_sequencia[3]
				print "PEGOU:", estado_sequencia[4]
				
				estado_atual = estado_sequencia[3]
				auxiliar = estado_sequencia[4]
				lista = list(auxiliar)
				tamanho_lista = len(lista) - 1
						
				if estado_sequencia[4] != 'epsilon':
					
					topo = pilha_funcao.pop()					
					pilha_funcao.push(topo)
					pilha_funcao.push(lista[0])
					break	
				else: 
					if pilha_funcao.isEmpty():
					   break
					else:
						pilha_funcao.pop()
						break
		
	esta_aceito = 0
	for l in range(0,tamanho_aceitacao):
		if estado_atual == conjunto_aceitacao[l]:
			esta_aceito = 1
			print "O conjunto foi aceito em: ",estado_atual
			break
	
	if not pilha_funcao.isEmpty():
		topo_pilha = pilha_funcao.peek()
		if topo_pilha[0] == 'Z':
			esta_aceito = 1
			print "A sequencia foi aceita por pilha vazia."
	
	if esta_aceito == 0:
		print "O sequencia nao foi aceita."
		
	Imprimir_Pilha(pilha_funcao)


meu_arquivo = Split_Lines()
alfabeto_entrada,tamanho_entrada = Split_Values(meu_arquivo[0])
alfabeto_pilha,tamanho_pilha = Split_Values(meu_arquivo[1])
simbolo_epsilon = meu_arquivo[2] 
simbolo_inicial,tamanho_inicial = Split_Values(meu_arquivo[3]) # Padrao: Z
conjunto_estados,tamanho_conjunto = Split_Values(meu_arquivo[4])
estado_inicial,tamanho_inicial = Split_Values(meu_arquivo[5])
conjunto_aceitacao,tamanho_aceitacao = Split_Values(meu_arquivo[6])

# Linha 1: alfabeto de entrada
# Linha 2: alfabeto da pilha
# Linha 3: simbolo que representa epsilon (padroes: B ou epsilon)
# Linha 4: simbolo inicial da pilha (padrao: Z)
# Lista 5: conjunto de estados
# Linha 6: estado inicial
# Linha 7: conjunto de estados de aceitacao
# Linhas 8 em diante: transicoes, uma por linha, no formato estado atual, simbolo atual da palavra, 
# simbolo do topo da pilha, novo estado, novos simbolos a serem empilhados (topo a esquerda, base a direita)

print "--- DADOS ----"
print "Alfabeto de entrada:", alfabeto_entrada
print "Alfabeto da Pilha :", alfabeto_pilha
print "Simbolo de Epsilon :", simbolo_epsilon 
print "Simbolo Inicial: ", simbolo_inicial
print "Conjunto de Estados: ", conjunto_estados
print "Estado Inicial: ", estado_inicial
print "Conjunto Aceitacao: ", conjunto_aceitacao
print "						"

print "--- AUTOMATO DE PILHA ---"
sequencia = raw_input('Escreva a sequencia desejada: ')
sequencia = sequencia.split()
print "Sequencia: ",sequencia
tamanho_sequencia = len(sequencia)
print "Tamanho sequencia: ", tamanho_sequencia

pilha_inicial = Stack()
pilha_inicial.push(simbolo_inicial)

automato_pilha(pilha_inicial,meu_arquivo,sequencia,tamanho_sequencia,alfabeto_entrada,alfabeto_pilha,simbolo_epsilon,simbolo_inicial,conjunto_estados,estado_inicial,conjunto_aceitacao)
