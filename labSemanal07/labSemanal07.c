/*
Aluno: Luciano Gigantelli Zago - RA: 182835
Turma S

Programa com o objetivo da utilizacao de funcoes e structs
com alocacao dinamica e criptografia
para a criacao de uma agenda em um consultorio medico

*/

// Inclusao das bibliotecas utilizadas nos programas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definicao da estrutura doenca
struct doenca {

  char cid[4];
  char nome[101];
};

typedef struct doenca sDoenca;

// Definicao da estrutura medico
struct medico {

  unsigned int crm;
  char nome[101];
};

typedef struct medico sMedico;


// Definicao da estrutura consulta
struct consulta {

  char paciente[101];
  char data[11];
  char cid[4];
  unsigned int crm;
  struct consulta *prox;
};

typedef struct consulta sConsulta;

// Funcao calcula o determinante da chave OK
int dChave(int *chave) {

  int det;

  det = (*chave) * (*(chave + 3));
  det += (-1) * (*(chave + 2)) * (*(chave + 1));

  return det;
}

// Funcao que calcula a inversa do determinante OK
int invDet(int det) {

  int invD = 0;

  while (1) {

    invD++;

    if ((det * invD) % 26 == 1)
    return invD;
  }
}

// Funcao que calcula a matriz inversa da chave OK
void iChave(int *chave, int *invChave, int invD) {

  *invChave = (((*(chave + 3) * (invD)) % 26) + 26) % 26;
  *(invChave + 1) = ((((-1) * (*(chave + 1)) * (invD)) % 26) + 26) % 26;
  *(invChave + 2) = ((((-1) * (*(chave + 2)) * (invD)) % 26) + 26) % 26;
  *(invChave + 3) = ((((*chave) * (invD)) % 26) + 26) % 26;

  return;
}


// Funcao encriptar nome
char *enc(char *orig, int *chave, char *cript) {

  unsigned short i, t;

  // Salva o tamanho do nome criptografado
  t = strlen(orig);

  // Laco para percorrer a string
  for (i = 1; i < t; i += 2) {

    // Realiza a criptografia
    cript[i - 1] = ((((chave[0] * (orig[i - 1] - 65) + (chave[1] * (orig[i] - 65))) % 26) + 26) % 26) + 65;
    cript[i] = ((((chave[2] * (orig[i - 1] - 65) + (chave[3] * (orig[i] - 65))) % 26) + 26) % 26) + 65;

  }

  cript[t] = '\0';

  return cript;
}


// Funcao desencriptar nome OK
char *dec(char *cript, int *invChave, char *orig) {

  unsigned short i, t;

  // Salva o tamanho do nome criptografado
  t = strlen(cript);

  // Laco para percorrer a string
  for (i = 1; i < t; i += 2) {

    // Realiza a descriptografia
    orig[i - 1] = ((((invChave[0] * (cript[i - 1] - 65) + (invChave[1] * (cript[i] - 65))) % 26) + 26) % 26) + 65;
    orig[i] = ((((invChave[2] * (cript[i - 1] - 65) + (invChave[3] * (cript[i] - 65))) % 26) + 26) % 26) + 65;
  }

  orig[t] = '\0';

  return orig;
}

sConsulta *inicio(sConsulta *inic, int *invChave, char *orig) {

  if (inic == NULL)
  return NULL;

  while (strcmp(dec(inic->paciente, invChave, orig), dec(inic->prox->paciente, invChave, orig)) > 0)
    inic = inic->prox;

  return inic;
}

// Funcao para buscar lista encadeada OK
sConsulta *buscaL(char *nome, sConsulta *inic, int *invChave, char *orig) {

  sConsulta *apontador;

  apontador = inic;

  while (strcmp(dec(apontador->paciente, invChave, orig), nome) != 0) {
    apontador = apontador->prox;
  }

  // Retorna o apontador do contato encontrado
  return apontador;
}

// Retorna posicao de um nome no vetor Doencas OK
int buscaD(char *nome, sDoenca *vetor, int qtd) {

  unsigned short i;

  for (i = 0; i < qtd; i++) {
    if (strcmp(nome, vetor[i].nome) == 0) {
      break;
    }
  }

  return i;
}

// Retorna posicao de um nome no vetor Medicos OK
int buscaM(char *nome, sMedico *vetor, int qtd) {

  unsigned short i;

  for (i = 0; i < qtd; i++) {
    if (strcmp(nome, (vetor[i].nome)) == 0)
    break;
  }

  return i;
}


// Funcao adicionar
sConsulta *add(char *nomeCript, char *pData, char *pCid, unsigned int crm, sConsulta *inic, int *invChave, char *orig) {

  char pNome[101], nomeAnt[101], nomeProx[101];
  sConsulta *pConsulta;
  sConsulta *apontador;

  // Alocacao dinamica
  pConsulta = (sConsulta *) malloc(sizeof(sConsulta));

  // Salva os dados
  strcpy(pConsulta->paciente, nomeCript);
  strcpy(pConsulta->data, pData);
  strcpy(pConsulta->cid, pCid);
  pConsulta->crm = crm;

  apontador = inic;

  // Salva localmente o nome descriptografado
  dec(nomeCript, invChave, pNome);

  // Excecao se a lista esta vazia
  if (apontador == NULL) {
    apontador = pConsulta;
    (pConsulta->prox) = pConsulta;
  }

  else
  do {
    apontador = apontador->prox;

    // Salva localmente o nome anterior e o nome do prox
    dec(apontador->paciente, invChave, nomeAnt);
    dec((apontador->prox)->paciente, invChave, nomeProx);

  } while ((strcmp(pNome, nomeAnt) < 0) && (strcmp(pNome, nomeProx) > 0));

  (pConsulta->prox) = (apontador->prox);
  (apontador->prox) = pConsulta;

  return apontador;
}

// Funcao remover
void rm(char *nomeDesc, sConsulta *inic, int *chave, char *cript) {

  char nomeCript[101];
  sConsulta *apontador, *aux;

  strcpy(nomeCript, enc(nomeDesc, chave, cript));

  apontador = inic;

  // Encontra ordenacao
  while (1) {

    if (strcmp(nomeCript, (apontador->prox)->paciente) == 0) {

      aux = (apontador->prox);

      // Altera o apontador do anterior
      inic = apontador;
      inic->prox = aux->prox;

      // Libera a memoria
      free(aux);

      break;
    }

    // Passa para o proximo item da lista
    apontador = apontador->prox;

  }
  return;
}

// Funcao altera diagnostico OK
void altdiag(char *nomeDesc, char *doenca, sDoenca *vetorD, int qtd, sConsulta *inic, int *invChave, char *orig) {

  strcpy(((buscaL(nomeDesc, inic, invChave, orig))->cid), (vetorD[buscaD(doenca, vetorD, qtd)].cid));
}

// Funcao altera data OK
void altdata(char *nomeDesc, char *data, sConsulta *inic, int *invChave, char *orig) {

  strcpy(((buscaL(nomeDesc, inic, invChave, orig))->data), data);
}

// Funcao altera medico OK
void altmed(char *nomeDesc, char *nomeMed, sMedico *vetorM, int qtd, sConsulta *inic, int *invChave, char *orig) {

  (buscaL(nomeDesc, inic, invChave, orig))->crm = (vetorM[buscaM(nomeMed, vetorM, qtd)].crm);
}

// Funcao para imprimir o relatorio das consultas
void relatorio(char letra, sConsulta *inic, int *invChave, char *orig) {

  sConsulta *apontador;
  char nomeAnt[101];
  char nomeProx[101];

  // Salva o inic
  apontador = inic;

  // Excessao, 1 paciente
  if ((inic->prox) == inic)
  printf("%s %s %s %u", dec(inic->paciente, invChave, orig), inic->data, inic->cid, inic->crm);

  // Encontra apontador para letra
  else
  while (1) {

    inic = inic->prox;

    // Salva as decodificacoes localmente
    dec(inic->paciente, invChave, nomeAnt);
    dec((inic->prox)->paciente, invChave, nomeProx);

    if (strcmp(nomeProx, &letra) > 0) {

      break;
    }
  }
  inic = (inic->prox);

  // Imprime
  do {

    inic = (inic->prox);

    printf("%s %s %s %u\n", dec(inic->paciente, invChave, orig), inic->data, inic->cid, inic->crm);

  } while (inic != apontador->prox->prox);

  return;
}


// Funcao principal
int main(void) {

  // Declaracao de variaveis locais
  unsigned short int nDoencas, nMedicos, i;
  unsigned int crm;
  int chave[4], invChave[4], det, invD;
  char letra;
  char modo[8], nome[101], data[11], cid[4], nomeAux[101];
  char cript[101];
  char orig[101];

  // Definicao de ponteiros de estrutura
  sDoenca *pDoenca;
  sMedico *pMedico;
  sConsulta *inic = NULL;

  // Leitura da quantidade de doencas
  scanf(" %hu", &nDoencas);

  // Alocacao dinamica do vetor de doencas
  pDoenca = (sDoenca *) malloc(nDoencas * sizeof(sDoenca));

  // Leitura do codigo e nome das doencas
  for (i = 0; i < nDoencas; i++) {

    scanf("%s %[^\n]s", pDoenca[i].cid, pDoenca[i].nome);
  }

  // Leitura da quantidade de medicos
  scanf(" %hu", &nMedicos);

  // Alocacao dinamica do vetor de medicos
  pMedico = (sMedico *) malloc(nMedicos * sizeof(sMedico));

  // Leitura do codigo e nome dos medicos
  for (i = 0; i < nMedicos; i++) {

    scanf("%u %[^\n]s", &pMedico[i].crm, pMedico[i].nome);
  }


  // Leitura chave
  scanf("%d %d %d %d", &chave[0], &chave[1], &chave[2], &chave[3]);

  // Calcula o determinante
  det = dChave(chave);

  // Calcula o inverso do determinante
  invD = invDet(det);

  // Calcula a inversa e salva em invChave
  iChave(chave, invChave, invD);

  // Leitura da letra de inicio
  scanf("%c", &letra);


  // Operacoes
  do {

    scanf("%s", modo);

    inic = inicio(inic, invChave, orig);

    // Sai do laco no fim
    if (strcmp(modo, "0") == 0)
    break;

    // Operacao adicionar
    if (strcmp(modo, "add") == 0) {

      scanf(" %s %s %s %u", nome, data, cid, &crm);
      inic = add(nome, data, cid, crm, inic, invChave, orig);
    }

    // Operacao remover
    if (strcmp(modo, "rm") == 0) {

      scanf(" %s", nome);
      rm(nome, inic, chave, cript);
    }

    // Operacao alterar diagnostico
    if (strcmp(modo, "altdiag") == 0) {

      scanf(" %s %[^\n]s", nome, nomeAux);
      altdiag(nome, nomeAux, pDoenca, nDoencas, inic, invChave, orig);
    }

    // Operacao alterar data
    if (strcmp(modo, "altdata") == 0) {

      scanf(" %s %s", nome, data);
      altdata(nome, data, inic, invChave, orig);
    }

    // Operacao alterar medico
    if (strcmp(modo, "altmed") == 0) {

      scanf(" %s %[^\n]s", nome, nomeAux);
      altmed(nome, nomeAux, pMedico, nMedicos, inic, invChave, orig);
    }

  } while (1);

  // Imprimir relatorio
  relatorio(letra, inic, invChave, orig);

  return 0;
}
