/*
Aluno: Luciano Gigantelli Zago - RA:182835
Turma S

Esse codigo tem como objetivo processar uma agenda telefonica com o uso de funcoes e string

*/

#include <stdio.h>
#include <string.h>

// Declaracao de vetores de strings
typedef char string[60];
string nome[20], endereco[20];

// Declaracao das variaveis usadas
long long int cpf[20], telefone[20], celular[20];
int i, quantidade[2] = {0, 0}, tipo[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
char busca[60];

// Funcao inserir
int inserir() {

	// Declaracao local da variavel de valor de retorno, se nao ler nada � 0
	int retorno=0;

	// Declaracao de variaveis auxiliares
	int tipoAux;
	long long int cpfAux, telAux, celAux;
	char nomeAux[60], endAux[60];

	// Leitura dos dados em variaveis auxiliares
	scanf("%d", &tipoAux);
	scanf(" %[^\n]s", nomeAux);
	scanf("%011lld", &cpfAux);
	scanf(" %[^\n]s", endAux);
	scanf("%010lld", &telAux);
	scanf("%011lld", &celAux);

	// Se a agenda do tipo estiver lotada, sai da funcao
	if ((tipoAux==1 && quantidade[0]==10) || (tipoAux==2 && quantidade[1]==10))
	return retorno;

	// Laco para variar o contador de indice
	for (i=0; i<20; i++){

		// Se o tipo estiver com 0, esta livre e salva os dados nessa posicao
		if (tipo[i]==0) {

			// Salva os dados
			tipo[i] = tipoAux;
			strcpy(nome[i], nomeAux);
			cpf[i] = cpfAux;
			strcpy(endereco[i], endAux);
			telefone[i] = telAux;
			celular[i] = celAux;

			// Contador de numero de contatos por tipo
			// Se for pessoal
			if (tipo[i]==1)
			quantidade[0]++;

			// Se for profissional
			if (tipo[i]==2)
			quantidade[1]++;

			// Se conseguiu ler, retorna 1
			retorno=1;

			// Sai do laco
			break;
		}
	}

	return retorno;

}

// Funcao excluir
int excluir() {

	// Declaracao local da variavel de valor de retorno, se nao ler nada � 0
	int retorno=0;

	// Declaracao de variavel auxiliar para o tipo
	int tipoAux;

	// Leitura de elementos para procurar
	scanf("%1d", &tipoAux);
	scanf(" %[^\n]s", busca);

	// Laco para varir o indice i
	for (i=0; i<20; i++){

		// Condicao para encontrar o nome com o tipo
		if ((strcmp(busca, nome[i]) == 0) && (tipoAux == tipo[i])){

			// Contador de numero de contatos por tipo
			// Se for pessoal
			if (tipoAux==1)
			quantidade[0]--;

			// Se for profissional
			if (tipoAux==2)
			quantidade[1]--;

			// Laco para variar o indice i e copiar os proximos elementos para os anteriores
			for (i=i; i<(quantidade[0]+quantidade[1]); i++) {

				// Copia os dados para as respectivas posicoes anteriores
				tipo[i] = tipo[i+1];
				strcpy(nome[i], nome[i+1]); // Uso de funcao que copia string
				cpf[i] = cpf[i+1];
				strcpy(endereco[i], endereco[i+1]); // Uso de funcao que copia string
				telefone[i] = telefone[i+1];
				celular[i] = celular[i+1];

			}

			// Deixa o ultimo como vazio
			tipo[(quantidade[0]+quantidade[1])]=0;
			strcpy(nome[(quantidade[0]+quantidade[1])], "");
			cpf[(quantidade[0]+quantidade[1])] = 0;
			strcpy(endereco[(quantidade[0]+quantidade[1])], "");
			telefone[(quantidade[0]+quantidade[1])] = 0;
			celular[(quantidade[0]+quantidade[1])] = 0;

			// Se conseguiu executar, retorna 1
			retorno=1;

			// Sai do laco
			break;
		}

	}
	return retorno;

}

// Funcao alterar
int alterar() {

	// Declaracao local da variavel de valor de retorno, se nao alterar nada � 0
	int retorno=0;

	// Declaracao de variavel auxiliar para o tipo
	int tipoAux;

	// Leitura de elementos para procurar
	scanf("%d", &tipoAux);
	scanf(" %[^\n]s", busca);

	// Laco para variar o indice i
	for (i=0; i<20; i++){

		// Condicao para encontrar o nome com o tipo
		if ((strcmp(busca,nome[i]) == 0) && (tipoAux == tipo[i])){

			// Leitura dos elementos para alterar e salvar nas respectivas posicoes
			scanf("%011lld", &cpf[i]);
			scanf(" %[^\n]s", endereco[i]);
			scanf("%010lld", &telefone[i]);
			scanf("%011lld", &celular[i]);

			// Se conseguiu executar, retorna 1
			retorno=1;

			// Sai do laco
			break;
		}
	}

	return retorno;

}

// Funcao buscar
int buscar() {

	// Declaracao local da variavel de valor de retorno, se nao encontrar nada � 0
	int retorno=0;

	// Declaracao de variavel auxiliar para o tipo
	int tipoAux;

	// Leitura de elementos para procurar
	scanf("%d", &tipoAux);
	scanf(" %[^\n]s", busca);

	// Laco para variar o indice i
	for (i=0; i<20; i++){

		// Condicao para encontrar o nome com o tipo
		if ((strcmp(busca,nome[i]) == 0) && (tipoAux == tipo[i])){

			// Impressao dos dados bucados
			printf("%s\n", nome[i]);
			printf("%011lld\n", cpf[i]);
			printf("%s\n", endereco[i]);
			printf("%lld\n", telefone[i]);
			printf("%lld\n", celular[i]);

			// Se conseguiu imprimir, retorna 1
			retorno=1;

			// Sai do laco
			break;
		}
	}

	return retorno;

}

// Funcao listar (modo � o parametro)
int listar(int modo) {

	// Declaracao local da variavel de valor de retorno, se nao listar nada � 0
	int retorno=0;

	// Condicao se o parametro for 1, listar os contatos pessoais
	if (modo==1){

		// Laco para variar o indice i
		for (i=0; i<20; i++){

			// Seleciona os contatos do tipo 1 (pessoais)
			if (tipo[i]==1) {

				// Imprime os dados
				printf("%s\n", nome[i]);
				printf("%011lld\n", cpf[i]);
				printf("%s\n", endereco[i]);
				printf("%lld\n", telefone[i]);
				printf("%lld\n", celular[i]);

				// Se conseguiu imprimir, retorna 1
				retorno=1;
			}
		}

	}

	// Condicao se o parametro for 2, listar os contatos pessoais
	if (modo==2){

		// Laco para variar o indice i
		for (i=0; i<20; i++){

			// Seleciona os contatos do tipo 2 (profissionais)
			if (tipo[i]==2) {

				// Imprime os dados
				printf("%s\n", nome[i]);
				printf("%011lld\n", cpf[i]);
				printf("%s\n", endereco[i]);
				printf("%lld\n", telefone[i]);
				printf("%lld\n", celular[i]);

				// Se conseguiu imprimir, retorna 1
				retorno=1;
			}
		}
	}

	return retorno;
}

int main(){

	// Declaracao de variaveis locais
	int loop=1, numero=0;
		
	// Laco para repetir ate selecionar a opcao 0
	while (loop) {

		// Leitura da opcao digitada
		scanf("%1d", &numero);

		// Selecionador dependendo do numero digitado
		switch(numero){

			// 0: sai do programa
			case 0:	loop = 0;
			printf("Obrigado!\n");
			break;

			// 1: Funcao inserir
			case 1:	if(inserir())

			// Se o retorno for 1, imprime:
			printf("Inserido com sucesso!\n");

			else
			// Se o retorno for 0, imprime:
			printf("Desculpe, agenda lotada!\n");
			break;

			// 2: Funcao excluir
			case 2:	if(excluir())

			// Se o retorno for 1, imprime:
			printf("Excluido com sucesso!\n");

			else
			// Se o retorno for 0, imprime:
			printf("Desculpe, contato %s nao existe!\n", busca);
			break;

			// 3: Funcao alterar
			case 3:	if(alterar())

			// Se o retorno for 1, imprime:
			printf("Alterado com sucesso!\n");

			else
			// Se o retorno for 0, imprime:
			printf("Desculpe, contato %s nao existe!\n", busca);
			break;

			// 4: Funcao buscar
			case 4:	if(buscar())

			// Se o retorno for 1, imprime:
			printf("Buscado com sucesso!\n");

			else
			// Se o retorno for 0, imprime:
			printf("Desculpe, contato %s nao existe!\n", busca);
			break;

			// 5: Funcao listar contatos pessoais
			case 5:	if(listar(1))

			// Se o retorno for 1, imprime:
			printf("Listado com sucesso!\n");

			else
			// Se o retorno for 0, imprime:
			printf("Desculpe, agenda vazia!\n");
			break;

			// 6: Funcao listar contatos profissionais
			case 6:	if(listar(2))

			// Se o retorno for 1, imprime:
			printf("Listado com sucesso!\n");

			else
			// Se o retorno for 0, imprime:
			printf("Desculpe, agenda vazia!\n");
			break;

			// 6: Funcao listar todos os contatos
			case 7:
			// Lista primeiro os pessoais
			if(listar(1))

			// Se o retorno for 1, imprime:
			printf("Listado com sucesso!\n");

			else
			// Se o retorno for 0, imprime:
			printf("Desculpe, agenda vazia!\n");

			// Lista depois os profissionais
			if(listar(2))

			// Se o retorno for 1, imprime:
			printf("Listado com sucesso!\n");

			else
			// Se o retorno for 0, imprime:
			printf("Desculpe, agenda vazia!\n");

			break;

		}
	}

	return 0;
}
