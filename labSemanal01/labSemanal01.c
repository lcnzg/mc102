/*
Aluno: Luciano Gigantelli Zago - RA: 182835
Turma S

Esse codigo tem como objetivo transformar uma data inicial a partir de uma regra estabelecida pelo usuario
(numero de dias no mes e numero de meses no ano usados na data) e converter um numero de dias em base 6
para base 10 e adiciona-lo na data escolhida.

*/

#include<stdio.h>

int main(void)
{
  // Declaracao das variaveis usadas como inteiros
  int d1, m1, a1, N, M, X, d2, m2, a2, XB10;

  scanf("%d/%d/%d %d %d %d", &d1, &m1, &a1, &N, &M, &X); // Leitura das variaveis inseridas pelo usuario

  /* Conversao do numero de 8 digitos de base 6 para um numero de base 10,
  isolando os algarismos e mulltiplicando-os pelas potencias de 6 */
  XB10 = ((X/10000000)*279936) + ((X%10000000)/1000000*46656) + ((X%1000000)/100000*7776)
  + ((X%100000)/10000*1296) + ((X%10000)/1000*216) + ((X%1000)/100*36) + ((X%100)/10*6) + X%10;

  d2 = (d1+XB10-1)%N + 1; // Obtem o dia final (subtrai 1 e soma no final para nao aparecer dia 0)

  m2 = (((d1+XB10-1)/N)+m1-1)%M + 1; // Obtem mes final (subtrai 1 e soma depois para nao aparecer mes 0)

  a2 = ((((d1+XB10-1)/N)+m1-1)/M)+a1; // Obtem ano final (subtrai 1 para contar corretamente os dias e meses)

  printf("%1d/%1d/%1d\n", d2, m2, a2); // Exibe o resultado na tela no formato de data pedido

  return 0;
}
