/*
Aluno: Luciano Gigantelli Zago - RA: 182835
Turma S

Esse codigo tem como objetivo processar uma imagem, lendo-a como matriz RGB, tranformando-a em cinza e aplicando um filtro
atraves do metodo de convolucao de matrizes e resultar em uma imagem PGM

*/

#include<stdio.h>

// Declara as variaveis que serao utilizadas no problema
int d, x, largura, altura, repeticao, intensidade, contadorP=0, i, j, b, k, l;


// Declara as matrizes que serao utilizadas no problema
int matrizM[9][9]; // Matriz de convolucao
int matrizR[600][600]; // Matriz vermelha
int matrizG[600][600]; // Matriz Verde
int matrizB[600][600]; // Matriz Azul
int matrizC[600][600]; // Matriz Cinza
int matrizFiltro[600][600]; // Matriz apos a Convolucao


int main(void)
{
	// Le o divisor da 3 fase
	scanf("%d", &d);

	// Le a ordem da matriz quadrada
	scanf("%d", &x);


	// LEITURA DA MATRIZ M (convolucao)
	// Laco para variar a linha
	for (i=0; i<x; i++){

		// Laco para variar a coluna
		for (j=0; j<x; j++) {

			// Le os elementos da matrizM (convolucao)
			scanf("%d", &matrizM[i][j]);

		}		
	}

	// Le a resolucao da imagem em pixels
	scanf("%d %d", &largura, &altura);


	// LEITURA DE MATRIZES CORES

	// Zera variaveis contadoras
	i=0;
	j=0;

	// Laco para parar a leitura
	while(contadorP<(largura*altura*3)){

		// Condicao para preencher matriz vermelha
		if (contadorP < largura*altura){

			// Le os parametros repeticao e intensidade da vermelha
			scanf("%d %d", &repeticao, &intensidade);

			// Soma a quantidade de valores lidos em contadorP
			contadorP += repeticao;

			// Laco para variar a linha
			while (i<altura){

				// Laco para variar a coluna
				while (j<largura) {

					// Preenche a matriz vermelha
					matrizR[i][j] = intensidade;

					// Diminui o numero da repeticao
					repeticao--;

					// Se nao couber na mesma linha, pula para a de baixo
					if (j==(largura-1)) {
						i++;
						j=0;

					}

					else
					// Pula para a proxima coluna
					j++;


					// Se ja escreveu todas as repeticoes, sai do loop e le novamente
					if (repeticao==0)
					break;

				}

				// Se ja escreveu todas as repeticoes, sai do loop e le novamente
				if (repeticao==0)
				break;

			}

			// Zera os contadores para ler uma nova matriz
			if (contadorP == largura*altura){
				i=0;
				j=0;
			}

		}

		else {

			// Preenche matriz verde
			if (contadorP < largura*altura*2) {

				// Le os parametros repeticao e intensidade da verde
				scanf("%d %d", &repeticao, &intensidade);

				// Soma a quantidade de valores lidos em contadorP
				contadorP += repeticao;

				// Laco para variar a linha
				while (i<altura){

					// Laco para variar a coluna
					while (j<largura) {

						// Preenche a matriz verde
						matrizG[i][j] = intensidade;

						// Diminui o numero da repeticao
						repeticao--;

						// Se nao couber na mesma linha, pula para a de baixo
						if (j==(largura-1)) {
							i++;
							j=0;

						}

						else
						// Pula para a proxima coluna
						j++;

						// Se ja escreveu todas as repeticoes, sai do loop e le novamente
						if (repeticao==0)
						break;

					}

					// Se ja escreveu todas as repeticoes, sai do loop e le novamente
					if (repeticao==0)
					break;

				}

				// Zera os contadores para ler uma nova matriz
				if (contadorP == largura*altura*2){
					i=0;
					j=0;
				}

			}

			// Preenche matriz azul
			else {

				// Le os parametros repeticao e intensidade da azul
				scanf("%d %d", &repeticao, &intensidade);

				// Soma a quantidade de valores lidos em contadorP
				contadorP += repeticao;

				// Laco para variar a linha
				while (i<altura){

					// Laco para variar a coluna
					while (j<largura) {

						// Preenche a matriz azul
						matrizB[i][j] = intensidade;

						// Diminui o numero da repeticao
						repeticao--;

						// Se nao couber na mesma linha, pula para a de baixo
						if (j==(largura-1)) {
							i++;
							j=0;

						}

						else
						// Pula para a proxima coluna
						j++;

						// Se ja escreveu todas as repeticoes, sai do loop e le novamente
						if (repeticao==0)
						break;

					}

					// Se ja escreveu todas as repeticoes, sai do loop e le novamente
					if (repeticao==0)
					break;

				}
			}
		}
	}

	// ESCALA DE CINZA

	// Laco para variar a coluna
	for (j=0; j<largura; j++){

		// Laco para variar a linha
		for(i=0; i<altura; i++){

			// Preenche a matriz de cinza
			matrizC[i][j] = (matrizR[i][j] + matrizG[i][j] + matrizB[i][j])/3;

		}
	}

	// Matriz Filtro

	// Laco para variar a coluna
	for (j=0; j<largura; j++){

		// Laco para variar a linha
		for(i=0; i<altura; i++){

			// Copia todos os elementos para a matriz Filtro
			matrizFiltro[i][j] = matrizC[i][j];

		}
	}


	// CONVOLUCAO

	// Calculo do tamanho da borda (uso de inteiro)
	b = x/2;

	// Laco para variar a linha
	for (i=b; i<(altura-b); i++){

		// Laco para variar a coluna
		for (j=b; j<(largura-b); j++){

			// Zera o elemento para poder sobreescrever
			matrizFiltro[i][j] = 0;

			// Laco para variar a linha da matriz M
			for (k=0; k<x; k++){

				// Laco para variar a coluna da matriz M
				for (l=0; l<x; l++){

					// Aplica o filtro baseado na matriz M
					matrizFiltro[i][j] += (matrizM[k][l]*matrizC[i+k-b][j+l-b]);

				}
			}

			// Divisao do elemento por d
			matrizFiltro[i][j] /= d;

			// Truncamento
			if (matrizFiltro[i][j]<0)
			matrizFiltro[i][j]=0;

			if (matrizFiltro[i][j]>255)
			matrizFiltro[i][j]=255;

		}
	}

	// IMPRESSAO

	printf("P2\n");
	printf("%d %d\n", largura, altura);
	printf("255\n");

	// Laco para variar a linha
	for(i=0; i<altura; i++){

		// Laco para variar a coluna
		for(j=0; j<largura; j++){

			// Imprime os elementos da matriz Final
			if (j==(largura-1))
			printf("%d\n", matrizFiltro[i][j]);

			else
			printf("%d ", matrizFiltro[i][j]);

		}
	}

	return 0;
}
