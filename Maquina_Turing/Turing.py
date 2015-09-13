'''
Felipe Torres Minorelli 1551167
Luiz Felipe Fronchetti 1552309
Joao Martins Filho 1552260
'''

class Node(object):
 
    def __init__(self, data, prev, next):
        self.data = data
        self.prev = prev
        self.next = next

class DoubleList(object):
 
    head = None
    tail = None
 
    def append(self, data):
        new_node = Node(data, None, None)
        if self.head is None:
            self.head = self.tail = new_node
        else:
            new_node.prev = self.tail
            new_node.next = None
            self.tail.next = new_node
            self.tail = new_node
 
    def remove(self, node_value):
        current_node = self.head
 
        while current_node is not None:
            if current_node.data == node_value:
                # if it's not the first element
                if current_node.prev is not None:
                    current_node.prev.next = current_node.next
                    current_node.next.prev = current_node.prev
                else:
                    # otherwise we have no prev (it's None), head is the next one, and prev becomes None
                    self.head = current_node.next
                    current_node.next.prev = None
 
            current_node = current_node.next
 
    def show(self):
        print "Show list data:"
        current_node = self.head
        while current_node is not None:
            print current_node.prev.data if hasattr(current_node.prev, "data") else None,
            print current_node.data,
            print current_node.next.data if hasattr(current_node.next, "data") else None
 
            current_node = current_node.next
        


def Split_Lines():
	string = open('sum.txt', 'r').read()
	#string = open('copy.txt', 'r').read()
	string = string.splitlines()
	return string
	
# Separa todos os elementos da minha linha e retorna o tamanho da lista	
def Split_Values(string):
	string = string.split()
	tamanho = len(string)
	return string, tamanho
	
def maquina_turing(meu_arquivo,estados_aceitacao,estado_inicial,sequencia,tamanho_sequencia,simbolo_espacobranco):
	tamanho_arquivo = len(meu_arquivo)
	tamanho_aceitacao = len(estados_aceitacao)
	estado_atual = estado_inicial[0]
	fita = DoubleList()
	bezin= tamanho_sequencia * 2
	for i in range(0,bezin):
		fita.append('B')
	
	for i in range(0,tamanho_sequencia):
		fita.append(sequencia[i])
	
	for i in range(0,bezin):
		fita.append('B')	
	
	while fita.head.data == 'B' :
		fita.head = fita.head.next
	
	aux = 0
	# Percorre toda a sequencia dada
	for j in range(0,100):
		# Percorre todas as transacoes existentes
		for j in range(5,tamanho_arquivo):
			estado_sequencia,estado_tamanho = Split_Values(meu_arquivo[j])
			#print estado_sequencia
			if estado_atual == estado_sequencia[0] and fita.head.data == estado_sequencia[1]:
				'''
				print "ESTADO ATUAL:", estado_atual
				print "ESTADO SEQUENCIA:", estado_sequencia[0]
				print "SIMBOLO ATUAL:", estado_sequencia[1]
				print "VAI : ", estado_sequencia[2]
				print "COLOCAR NA LISTA:", estado_sequencia[3]
				print "DIRECAO:", estado_sequencia[4]
				'''
				estado_atual = estado_sequencia[2]
				fita.head.data = estado_sequencia[3]
				
				if estado_sequencia[4] == 'R' :
					fita.head = fita.head.next
				if estado_sequencia[4] == 'L' :
					fita.head = fita.head.prev
	
	for i in range(0,tamanho_aceitacao):
		if estado_atual == estados_aceitacao[i]:
				aux=1
	if aux == 1:
		print 'Aceitou'
		fita.show()
	else:
		print 'Nao Aceitou'	
		fita.show()
	
	
	
	
	
meu_arquivo = Split_Lines()
alfabeto_entrada,tamanho_entrada = Split_Values(meu_arquivo[0])
alfabeto_fita,tamanho_fita = Split_Values(meu_arquivo[1])
simbolo_espacobranco = meu_arquivo[2] 
estado_inicial,tamanho_inicial = Split_Values(meu_arquivo[3]) 
estados_aceitacao,tamanho_aceitacao = Split_Values(meu_arquivo[4])

#    Linha 1: alfabeto de entrada
#    Linha 2: alfabeto da fita
#    Linha 3: simbolo que representa um espaco em branco na fita
#    Linha 4: estado inicial
#    Linha 5, coloquem uma linha indicando o conjunto de estados de aceitacao
#    Linhas 6 em diante: transicoes, uma por linha, no formato estado atual, simbolo atual,  novo estado, novo simbolo, direcao para mover a cabeca

print "--- DADOS ----"
print "Alfabeto de entrada:", alfabeto_entrada
print "Alfabeto da Pilha :", alfabeto_fita
print "Simbolo de Espaco Branco :", simbolo_espacobranco 
print "Estado Inicial: ", estado_inicial
print "Estado de Aceitacao: ", estados_aceitacao
print "						"

print "--- MAQUINA DE TURING ---"
print "~ Escreva abaixo a sequencia desejada com espacos por letra:"
sequencia = raw_input('->: ')
sequencia = sequencia.split()
print "Sequencia: ",sequencia
tamanho_sequencia = len(sequencia)
print "Tamanho sequencia: ", tamanho_sequencia

maquina_turing(meu_arquivo,estados_aceitacao,estado_inicial,sequencia,tamanho_sequencia,simbolo_espacobranco)
