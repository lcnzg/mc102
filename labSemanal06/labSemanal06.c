/*
Aluno: Luciano Gigantelli Zago - RA: 182835
Turma S

Programa que usa de recursoes em funcoes e vetores
para identificar o funcionario mais produtivo em uma empresa

*/

// Inclusao das bibliotecas utilizadas nos programas
#include <stdio.h>
#include <string.h>
#include <math.h>


// Definicao da estrutura funcionarios
typedef struct sFunc funcionarios;

struct sFunc {

	char nome[30];
	double pAbsoluta;
	double pRelativa;
	char chefe[30];
	int nivel;
	int subordinados;
	double salario;
	double qualidade;

};

// Declaracao das funcoes
void inicializaVetor(funcionarios vetor[], int nFunc);
int chefe(int indice, funcionarios vetor[], int nFunc);
int nivel(int indice, funcionarios vetor[], int nFunc);
double salP(int indice, funcionarios vetor[], int nFunc);
double sal(int indice, funcionarios vetor[], double soma, double total);
double p(int indice, funcionarios vetor[], int nFunc);
double logL(double valor);
int sub(int indice, funcionarios vetor[], int nFunc);
double qual(int fator, int indice, funcionarios vetor[]);


// Funcao que inicializa o vetor para o chefe
void inicializaVetor(funcionarios vetor[], int nFunc){

	// Declaracao de variaveis locais
	int i;

	// Laco para percorrer o vetor
	for (i=0; i<nFunc; i++)

		// Inicializa a string chefe
		strcpy(vetor[i].chefe, "-1");
}


// Funcao que encontra indice do chefe no vetor
int chefe(int indice, funcionarios vetor[], int nFunc){

	// Declaracao de variaveis locais
	int indiceC, j=0;

	// Laco para procurar o indice do chefe no vetor
    for (indiceC=0; indiceC<nFunc; indiceC++) {

        // Se encontrou, termina o laco
        if (strcmp(vetor[indice].chefe, vetor[indiceC].nome) == 0) {
            j=1;
            break;

        }
    }

    // Se nao tiver chefe, retorna -1
    if (j==0)
        indiceC = -1;

    // Retorna o indice do chefe
	return indiceC;

}

// Funcao recursiva de nivel de hierarquia
int nivel(int indice, funcionarios vetor[], int nFunc){

	// Declaracao de variaveis locais
	int valor, indiceC;

	// Encontra o indice do chefe
	indiceC = chefe(indice, vetor, nFunc);

	// Se for o presidente, que nao tem chefe, retorna nivel 1
	if (strcmp(vetor[indice].chefe, "-1") == 0){

        valor = 1;
	}

    // Se nao for o presidente, calcula o nivel
    else {

        // Calcula o nivel do chefe recursivamente e soma 1
        valor = nivel(indiceC, vetor, nFunc) + 1;

    }

    // Retorna o valor do nivel
	return valor;

}


// Funcao recursiva de salario proporcional
double salP(int indice, funcionarios vetor[], int nFunc){

	// Declaracao de variaveis locais
	double salario;
	int indiceC;

    // Encontra o indice do chefe
	indiceC = chefe(indice, vetor, nFunc);

    // Salario proporcional do presidente
	if (indiceC == -1)
        return 1;

    // Formula recursiva do salario proporcional
    salario = vetor[indiceC].subordinados;
    salario /= salario + 1;
    salario *= salP(indiceC, vetor, nFunc);

    // Retorna o valor do salario proporcional
	return salario;

}


// Funcao de salario final
double sal(int indice, funcionarios vetor[], double soma, double total){

	// Declaracao de variaveis locais
	double salario;

    // Calculo para encontrar o salario induvidual com base na proporcao total e individual e o gasto em salarios
	salario = total;
	salario /= soma;
	salario *= vetor[indice].salario;

    // Retorna o valor do salario final
	return salario;

}


// Funcao recursiva de producao relativa
double p(int indice, funcionarios vetor[], int nFunc){

	// Declaracao de variaveis locais
	int j;
	double pRel, soma=0;

	// Inicia producao relativa com a producao absoluta
    pRel = vetor[indice].pAbsoluta;

    // Se nao tiver subordinados, sua prod relativa � igual a absoluta
	if (vetor[indice].subordinados == 0) {

        // Retorna o valor absoluto
        return pRel;

	}

	// Se tiver subordinados
	else {

        // Laco para percorrer o vetor e encontrar os subordinados
        for (j=0; j<nFunc; j++) {

            if (strcmp(vetor[j].chefe, vetor[indice].nome) == 0) {

                // Uso da recursao no calculo do somatorio
                soma += p(j, vetor, nFunc);

            }
        }

        // Continuacao da formula
        pRel += (soma)/(vetor[indice].subordinados);
        pRel /= 2;

        // Retorna o valor apos o calculo
        return pRel;

	}
}


// Funcao recursiva do log*
double logL(double valor){

	// Declaracao de variaveis locais
	double retorno;

	// Condicao para a funcao terminar
	if (valor <= 1) {

		retorno = 0;
	}

	// Condicao para a funcao repetir
	else {

		retorno = 1 + logL(log2(valor));
	}

	// Retorna o valor da funcao
	return retorno;
}

// Funcao que encontra numero de subordinados
int sub(int indice, funcionarios vetor[], int nFunc){

	// Declaracao de variaveis locais
	int nSub = 0, j;

	// Laco para procurar subordinados, se achar, aumenta em 1
    for (j=0; j<nFunc; j++) {

        if (strcmp(vetor[j].chefe, vetor[indice].nome) == 0) {
            nSub++;

        }
    }

    // Retorna a quantidade de subordinados
	return nSub;
}

// Funcao que calcula a qualidade
double qual(int fator, int indice, funcionarios vetor[]){

	// Declaracao de variaveis locais
	double valor;

	// Formula da qualidade
	valor = logL((double)vetor[indice].nivel);
	valor = valor + 1;
	valor *= fator;
	valor *= vetor[indice].pRelativa;
	valor /= log2(vetor[indice].salario);

	// Retorna o valor da funcao
	return valor;
}


// Funcao principal
int main (void) {

	// Declaracao de variaveis locais
	int f, n, i, j;
	double t, somaProp=0, qualidade=0;
	char nomeAux[30];

	// Leitura variaveis de entrada
	scanf("%lf ", &t);
	scanf("%d ", &f);
	scanf("%d", &n);

	// Declaracao de um vetor de estrutura
	funcionarios vFunc[n];

	// Inicializa string de chefes
	inicializaVetor(vFunc, n);

	// Laco para ler os nomes e as produtividades absolutas
	for (i=0; i<n; i++) {

        scanf("%s", vFunc[i].nome);
        scanf("%lf", &vFunc[i].pAbsoluta);

	}

    // Laco para leitura dos chefes
    for (j=0; j<(n-1); j++){

        scanf("%s", nomeAux);

        for (i=0; i<n; i++) {

            if (strcmp(nomeAux, vFunc[i].nome) == 0) {
                scanf("%s", vFunc[i].chefe);
                break;
            }
        }
    }

    // Salva valores das funcoes no vetor atrav�s de lacos
    for (i=0; i<n; i++) {

        vFunc[i].nivel = nivel(i, vFunc, n);
        vFunc[i].subordinados = sub(i, vFunc, n);
   }

    for (i=0; i<n; i++) {

        vFunc[i].pRelativa = p(i, vFunc, n);
        vFunc[i].salario = salP(i, vFunc, n);
        somaProp += vFunc[i].salario;
    }

    for (i=0; i<n; i++) {

        vFunc[i].salario = sal(i, vFunc, somaProp, t);

    }


    // Procura maior qualidade e salva o indice da pessoa
    for (i=0; i<n; i++){

        vFunc[i].qualidade = qual(f, i, vFunc);

        if (qualidade <= vFunc[i].qualidade) {
            qualidade = vFunc[i].qualidade;
            j = i;
        }
    }

    // Imprime o nome do funcionario escolhido e sua qualidade
    printf ("%s %.2lf\n", vFunc[j].nome, qualidade);

    // Termina a funcao principal
	return 0;

}
