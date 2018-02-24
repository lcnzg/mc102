/*
Aluno: Luciano Gigantelli Zago - RA: 182835
Turma S

Esse codigo tem como objetivo calcular o volume de agua usado em uma maquete atraves das coordenadas dos poligonos
existentes, calcular o numero de dias de exibicao da maquete e o preco mais barato de agua gasto nessas exibicoes.

*/

#include<stdio.h>

int main(void)
{
  // Declaracao de variaveis usadas no problema

  double x0 = 0, y0 = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0, xMaior = 0, xMenor = 0, yMaior = 0, yMenor = 0;
  double areaPolig = 0, areaAux = 0, vAgua = 0, c = 0, p = 0, x = 0;
  int k = 0, i = 0, dia = 0, mes = 0, anoFinal = 0, nDias = 0, f = 0, nGaloes = 0;

  // Le o numero de poligonos
  scanf("%d", &k);

  // Laco de repeticao para o numero de ilhas
  while (i<k) {

    // Leitura das vatiaveis iniciais
    scanf(" (%lf , %lf) (%lf , %lf)", &x0, &y0, &x1, &y1);

    // Inicializar as variaveis das coordenadas extremas como validas
    if (i==0) {
      xMaior = x0;
      xMenor = x0;
      yMaior = y0;
      yMenor = y0;
    }

    // Salva as extremidades das coordenadas
    if (xMaior < x0)
    xMaior = x0;

    if (xMaior < x1)
    xMaior = x1;

    if (xMenor > x0)
    xMenor = x0;

    if (xMenor > x1)
    xMenor = x1;

    if (yMaior < y0)
    yMaior = y0;

    if (yMaior < y1)
    yMaior = y1;

    if (yMenor > y0)
    yMenor = y0;

    if (yMenor > y1)
    yMenor = y1;

    // Inicializa coordenada 2 para ser diferente da coordenada 0
    x2 = x0 + 1;
    y2 = y0 + 1;

    // Laco para leitura das coordenadas e soma das areas
    do {
      // Le a proxima coordenada
      scanf(" (%lf , %lf)", &x2, &y2);

      // Salva as extremidades das coordenadas depois da leitura do ponto 2
      if (xMaior < x2)
      xMaior = x2;

      if (xMenor > x2)
      xMenor = x2;

      if (yMaior < y2)
      yMaior = y2;

      if (yMenor > y2)
      yMenor = y2;

      // Calcula a area do triangulo formado por 1 coordenada inicial e 2 coordenadas variaveis
      areaAux = ((x0*y1) + (x2*y0) + (x1*y2) - (x2*y1) - (x0*y2) - (x1*y0))/2;

      // Salva o modulo da area se negativa
      if (areaAux < 0)
      areaAux = areaAux*(-1);

      // Soma o modulo na soma total da area dos poligonos
      areaPolig = areaPolig + areaAux;

      // Troca a coordenada do ultimo ponto para o anterior
      x1 = x2;
      y1 = y2;

    }

    while ((x0 != x2) || (y0 != y2));

    // Aumenta o numero do contador de repeticoes
    i++;
  }

  // Aumenta a margem das coordenadas em 50cm
  xMaior += 0.5;
  xMenor -= 0.5;
  yMaior += 0.5;
  yMenor -= 0.5;

  // Calcula a area total da maquete
  vAgua = (xMaior*yMenor) + (xMenor*yMaior) - (xMaior*yMaior) - (xMenor*yMenor);

  // Salva o modulo da area total se negativa
  if (vAgua < 0)
  vAgua = vAgua*(-1);

  // Calcula o volume de agua: (area total - area poligonos) x altura da maquete (conversao de unidade)
  vAgua = (vAgua - areaPolig)*0.5*1000;

  // Leitura da data de aniversario
  scanf(" %d/%d", &dia, &mes);

  // Leitura ano final
  scanf(" %d", &anoFinal);

  // Declaracao do dia d 13, mes m que varia no , ano a 2016 que varia no loop, variavel auxiliar e valor do dia da semana
  int d = 13, m = 0, a = 2016, aAux = 0, diaSemana = 0; // diaSemana: 0 - domingo, 5 - Sexta

  // Laco para repetir contagem de data de 2016 ate o ano final
  while (a <= anoFinal) {

    // Retorna o valor do mes para janeiro
    m = 1;

    // Laco para repetir contagem dde data entre os meses do ano
    while (m<=12){

      // Retorna o dia para 13
      d = 13;

      // Variavel auxiliar para realizar as contas
      aAux = a;

      // Excecao da regra para janeiro e fevereiro
      if ( m <= 2 ) {

        d = d + aAux;
        aAux--;
      }

      // Demais meses seguem essa regra
      else {

        d = d + aAux - 2;
      }

      // Calcula o dia da semana: 5 = sexta
      diaSemana = ((23 * m)/9) + d + 4 + (aAux/4) - (aAux/100) + (aAux/400);
      diaSemana = diaSemana % 7;


      // Aumenta a contagem dos dias para abrir se for sexta 13
      if (diaSemana == 5) {
        nDias++;

        // Reduz a contagem de dias para abrir se houver aniversario em sequencia de sexta 13
        if ((mes==m) && ((dia==12) || (dia==13) || (dia==14))) {
          nDias--;

        }
      }

      // Aumenta a contagem do mes
      m++;
    }

    // Nao abre se o aniversario nao existir no calendario para o ano
    if ((dia==29 && mes==2) && !(((a % 4 == 0) && (a % 100 != 0)) || (a % 400 == 0))) {
      nDias--;
    }

    // Abre no dia do aniversario para cada ano
    nDias++;

    // Aumenta a contagem do ano
    a++;

  }

  // Zera o contador novamente
  i=0;

  // Calculo do preco
  //Leitura do numero de fornecedores
  scanf(" %d", &f);

  // Laco para receber entrada de outros fornecedores
  while (i<f) {

    // Leitura do volume do galao e do custo por galao
    scanf(" %lf $%lf", &c, &p);

    // Salva o numero de galoes como inteiro
    nGaloes = (vAgua/c);

    // Arredonda o numero de galoes para cima caso seja decimal
    if ((vAgua/c) > nGaloes)
    nGaloes++;

    // Calcula o valor do custo da agua para o fornecedor inicial
    if (i == 0)
    x = nGaloes*p*nDias;

    // Condicao para salvar em x o menor valor
    if (x > nGaloes*p*nDias)
    x = nGaloes*p*nDias;

    // Aumenta a contagem do laco
    i++;

  }

  printf("A manutencao da maquete custara $%.2lf aos cofres publicos.\n", x);

  return 0;
}
