/*
Aluno: Luciano Gigantelli Zago - RA: 182835
Turma S

Esse programa tem como objetivo a construcao de uma rede rede de contatos
com analise de afinidade entre eles, com o uso de funcoes, vetores e ponteiros

*/

#include <stdio.h> // funcoes basicas
#include <string.h> // uso de strings
#include <math.h> // contas com raiz


// Criacao da estrutura Pessoa
struct Pessoa
{

  char nome[200];

  // Subestrutura data
  struct
  {

    int dia; //*p+200
    int mes; //*p+204
    int ano; //*p+208

  } data;

  char genero; //*p+212

  char preferencia; //*p+213

};

// Criacao da estrutura Aresta
struct Aresta
{

  char *ponteiro1; //ponteiro para pessoa que respondeu
  char *ponteiro2; //ponteiro para pessoa que recebeu a nota
  int afinidade; //nota recebida

};

// Declaracao de funcoes
double peso(char *p1, char *p2, int n, struct Aresta *vAresta);
int centralidade(char *p1, int n, struct Aresta *vAresta);
int soundex(char *p, char *aux);
int numerologia(char *p, int diaP, int mesP, int anoP);
double similaridade(char *cod1, char *cod2);
double sintonia(char *p1, char *p2, int dia, int mes, int ano, int n, struct Aresta *vAresta);

// Funcao principal
int main()
{

  // Declaracao de variaveis locais
  int dia, mes, ano, n, i, c, j;
  double sint, sint2;
  char *pessoaPopular, *pessoaSintonia;

  // Leituras iniciais
  scanf("%d/%d/%d", &dia, &mes, &ano);
  scanf("%d", &n);

  // Declaracao de vetores de estruturas
  struct Pessoa vPessoa[n];
  struct Aresta vAresta[n*n]; //n*(n-1)/2

  // Leitura da entrada e armazenamento nos vetores
  for (i=0; i<n; i++)
  {

    scanf("%[^\n]s", vPessoa[i].nome);
    scanf("%d/%d/%d ", &vPessoa[i].data.dia, &vPessoa[i].data.mes, &vPessoa[i].data.ano);
    scanf("%c %c ", &vPessoa[i].genero, &vPessoa[i].preferencia);

    for (j=0; j<n; j++)
    {

      // Valor do indice da aresta
      c = (i*n) + j;

      vAresta[i].ponteiro1 = vPessoa[i].nome;
      vAresta[i].ponteiro2 = vPessoa[j].nome;

      scanf("%d", &vAresta[c].afinidade);
    }
  }


  // Funcao que calcula a centralidade (pessoa mais popular)

  // Zera variavel auxiliar
  c = 0;

  // Laco para calcular a centralidade de todas as pessoas
  for (i=0; i<n; i++)
  {

    j = centralidade(vAresta[i].ponteiro1, n, vAresta);

    // Salva a centralidade maxima em c e a pessoa mais popular no ponteiro
    if (j>c)
    {
      c = j;
      pessoaPopular = vAresta[i].ponteiro1;
    }

  }

  // Laco para procurar a maior sintonia da pessoa popular com alguem
  for (i=0; i<n; i++)
  {

    // Funcao que calcula a sintonia com a pessoa mais popular
    sint2 = sintonia(pessoaPopular, vAresta[i].ponteiro1, dia, mes, ano, n, vAresta);

    // Salva a sintonia maxima
    if (sint2>sint)
    {
      sint = sint2;
      pessoaSintonia = vAresta[i].ponteiro1;
    }
  }

  // Imprime a melhor combinacao
  printf("%s combina com %s com %.2lf de sintonia s2", pessoaPopular, pessoaSintonia, sint);

  return 0;
}

// Funcao peso
double peso(char *p1, char *p2, int n, struct Aresta *vAresta)
{

  // Declaracao de variaveis auxiliares
  int i, af1, af2;
  double peso;

  // Laco para procurar o valor das afinidades
  for(i=0; i<n*n; i++)
  {

    // Procura a afinidade 1
    if (strcmp(p1, vAresta[i].ponteiro1) == 0) {
      if (strcmp(p2, vAresta[i].ponteiro2) == 0)
      af1 = vAresta[i].afinidade;
    }

    // Procura a afinidade 2
    if (strcmp(p2, vAresta[i].ponteiro1) == 0) {
      if (strcmp(p1, vAresta[i].ponteiro2) == 0)
      af2 = vAresta[i].afinidade;
    }
  }

  // Afinidade maxima se for a mesma pessoa
  if (p1==p2) {
    af1=10;
    af2=10;
  }

  // Calculo do peso como media geometrica das afinidades
  peso = sqrt(af1*af2);

  // Aresta so existe se peso for maior ou igual a 5
  if (peso<5)
  peso=0;

  // Retorna o valor do peso para a funcao
  return peso;
}

// Funcao que cria o soundex
int soundex(char *p, char aux[]) {

  // Declaracao de variaveis auxiliares
  char cod[5];
  int i, j = 1;

  // Salva a primeira letra
  cod[0] = p[0];

  // Calcula os numeros para o restante do nome

  // Laco para percorrer o nome ou o codnome ate o final
  while (p[j] != ' ' && i != 3) {
    for (i=1; i<4; i++) {
      if (p[j] == ('g' || 'j')) {
        cod[i] = '1';
        j++;
      }

      if (p[j] == ('s' || 'z' || 'x')) {
        cod[i] = '2';
        j++;
      }

      if (p[j] == ('c' || 'k' || 'q')) {
        cod[i] = '3';
        j++;
      }

      if (p[j] == ('b' || 'p')) {
        cod[i] = '4';
        j++;
      }
      if (p[j] == ('m' || 'n')) {
        cod[i] = '5';
        j++;
      }
      if (p[j] == ('d' || 't')) {
        cod[i] = '6';
        j++;
      }
      if (p[j] == ('f' || 'v')) {
        cod[i] = '7';
        j++;
      }

      if (p[j] == ('l')) {
        cod[i] = '8';
        j++;
      }

      if (p[j] == ('r')) {
        cod[i] = '9';
        j++;
      }

      // Desconsidera essas letras (repete a leitura no codnome)
      if (p[j] == ('a' || 'e' || 'i' || 'o' || 'u' || 'y' || 'h' || 'w')) {
        cod[i] = '0';
        j++;
        i--;
      }

      // Desconsidera codificacoes repetidas
      if (p[j-1]==p[j-2])
      i--;
    }
  }

  // Se o nome for curto, preenche o codnome com 0
  for (i=i; i<4; i++)
  cod[i] = '0';

  // Finaliza a string
  cod[4] = '\0';

  // Salva o codnome gerado na variavel soundex
  strcpy(aux, cod);

  return 0;
}

// Funcao para calcular a numerologia
int numerologia(char *p, int diaP, int mesP, int anoP) {

  // Declaracao de variaveis locais
  int diaN, mesN, anoN, aux, aux2, idade, num;

  // Obtencao da data de nacimento pelo vetor
  diaN = *(p+200);
  mesN = *(p+204);
  anoN = *(p+208);

  // Calculo da numerologia inicial
  aux = (diaN/10) + (diaN%10);
  aux += (mesN/10) + (mesN%10);
  aux += (anoN/1000);
  aux += (anoN/100);
  aux += (anoN/10) + (anoN%10);

  // Laco para tornar a soma em 1 digito
  do {
    aux2 = (aux/100);
    aux2 += (aux/10) + (aux%10);

    // Troca o valor entre as variaveis
    aux = aux2;
  }
  while ((aux2/10) != 0);

  // Calculo da idade
  idade = anoP - anoN;

  if ((mesN - mesP) > 0)
  idade--;

  else if ((diaN - diaP) > 0)
  idade--;

  // Calculo da numerologia final
  while (idade >= 100)
  idade /= 10;

  num = (100*aux + 10*idade);

  // Retorna o valor da numerologia
  return num;

}

// Funcao que mede a similaridade dos codnomes
double similaridade(char *cod1, char *cod2)
{

  // Declaracao de variaveis auxiliares
  double valor;
  int i;

  // Laco para contar os caracteres iguais
  for (i=0; i<4; i++) {

    // Se os caracteres forem iguais, soma 1
    if (cod1[i]==cod2[i])
    valor++;
  }

  // Divisao por 4 para manter entre 0 e 1
  valor /= 4;

  return valor;
}

// Funcao que mede a centralidade dos vertices
int centralidade(char *p1, int n, struct Aresta *vAresta){

  // Declaracao de variaveis auxiliares
  int i, centralidade = 0;

  // Quantidade de arestas ligantes em uma pessoa
  // Laco para percorrer os vetores
  for(i=0; i<n; i++) {

    // Se a aresta existir, aumenta a centralidade
    if (peso(p1, vAresta[i].ponteiro2, n, vAresta) != 0)
    centralidade++;
  }

  // Retorna o valor da centralidade
  return centralidade;
}

// Funcao que calcula a sintonia da pessoa
double sintonia(char *p1, char *p2, int dia, int mes, int ano, int n, struct Aresta *vAresta) {

  char codnome1[5], codnome2[5], soundexAux[5], codnasc1[4], codnasc2[4];
  double sint;

  // Salva o soundex da pessoa 1
  soundex(p1, soundexAux);
  strcpy(codnome1, soundexAux);

  // Salva o soundex da pessoa 2
  soundex(p2, soundexAux);
  strcpy(codnome2, soundexAux);

  // Converte numerologia em uma string
  sprintf(codnasc1, "%d", numerologia(p1, dia, mes, ano));
  sprintf(codnasc2, "%d", numerologia(p2, dia, mes, ano));

  sint = 3*(similaridade(codnome1, codnome2));
  sint += 5*(similaridade(codnasc1, codnasc2));
  sint += (peso(p1, p2, n, vAresta))/5;
  sint /= 10;

  // Se a preferencia e o genero n�o baterem, a sintonia � 0
  if ((*(p1+212) != *(p2+213)) || (*(p2+212) != *(p1+213)))
  sint = 0;

  // Valor de retorno para a funcao
  return sint;
}
