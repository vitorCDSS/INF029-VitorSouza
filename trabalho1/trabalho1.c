// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Vitor Chagas dos Santos Souza
//  email: vitorchagas2904@gmail.com
//  Matrícula: 20261160019
//  Semestre: segundo

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>
#include <string.h>
#include<ctype.h>

DataQuebrada quebrar_data(char sData[]);
int calcular_diasDoMes (int Mes, int Ano);

void para_minusculo(char *destino, char *origem);

int procura (int icresc, int jcresc, int *y, int *x, char palavra[], char matriz[][10]);


DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
  int datavalida = 1;
  //quebrar a string data em strings sDia, sMes, sAno
    DataQuebrada quebData = quebrar_data(data);

		if(quebData.iAno <= 0) {
			datavalida = 0;
		}

    if(quebData.iMes < 1 || quebData.iMes > 12) {
			datavalida = 0;
		}

    int diasDoMes = calcular_diasDoMes (quebData.iMes, quebData.iAno);

		if(quebData.iDia > diasDoMes || quebData.iDia <= 0) {
			datavalida = 0;
		}
        
  printf("%s\n", data);

  if (datavalida)
      return 1;
  else
      return 0;
}

int calcular_diasDoMes (int Mes, int Ano){

      switch(Mes) {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:
        return 31;
        break;

      case 4:
      case 6:
      case 9:
      case 11:
        return 30;
        break;

      case 2:
        if((Ano % 400) == 0 || ((Ano % 4) == 0 && (Ano % 100) != 0))
          return 29;
        else
          return 28;
        break;

      default:
        return 0;
		}
}

DataQuebrada quebrar_data(char sData[]){
  int icont = 0;
  int jcont = 0;
  char sDia[3];
  char sMes[3];
  char sAno[5];

   while(sData[icont] != '/'){
    sDia[jcont] = sData[icont];
    icont++;
    jcont++;
  }
  sDia[3] = '\0';
  icont++;
  jcont = 0;

  while(sData[icont] != '/'){
    sMes[jcont] = sData[icont];
    icont++;
    jcont++;
  }
  sMes[3] = '\0';
  icont++;
  jcont = 0;

  while(sData[icont] != '\0'){
    sAno[jcont] = sData[icont];
    icont++;
    jcont++;
  }
  sAno[5] = '\0';
  icont++;
  jcont = 0;

  DataQuebrada data;
  data.iDia = atoi(sDia);
  data.iMes = atoi(sMes);
  data.iAno = atoi(sAno);
  return data;
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
  

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;
    dma.qtdDias = 0;
    dma.qtdMeses = 0;
    dma.qtdAnos = 0;

    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{

      //verifique se a data final não é menor que a data inicial
      DataQuebrada idatainicial = quebrar_data(datainicial);
      DataQuebrada idatafinal = quebrar_data(datafinal);
      if(idatainicial.iAno*10000 + idatainicial.iMes*100 + idatainicial.iDia <= idatafinal.iAno*10000 + idatafinal.iMes*100 + idatafinal.iDia){
      //calcule a distancia entre as datas
        if(idatainicial.iMes != idatafinal.iMes){
          dma.qtdDias = (calcular_diasDoMes(idatainicial.iMes, idatainicial.iAno) - idatainicial.iDia) + idatafinal.iDia;
          if(calcular_diasDoMes(idatainicial.iMes, idatainicial.iAno) <= dma.qtdDias){
            dma.qtdDias -= calcular_diasDoMes(idatainicial.iMes, idatainicial.iAno);
            dma.qtdMeses = 1;
          }
          if(idatafinal.iMes >= (idatainicial.iMes + 1)){
            dma.qtdMeses += idatafinal.iMes - (idatainicial.iMes + 1);
            dma.qtdAnos = idatafinal.iAno - (idatainicial.iAno);
            dma.qtdAnos = (dma.qtdAnos < 0)? 0 : dma.qtdAnos;
          }
          else{
            dma.qtdMeses += 12 - idatainicial.iMes + idatafinal.iMes;
          }
        }
        else{
          dma.qtdDias = idatafinal.iDia - idatainicial.iDia;
          dma.qtdMeses = 0;
          dma.qtdAnos = idatafinal.iAno - idatainicial.iAno;
        }
      }
      else{
        dma.retorno = 4;
      return dma;
      }

      //se tudo der certo
      dma.retorno = 1;
      return dma;
      
    }
    
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;

    if (isCaseSensitive != 1) {
        char textinho[strlen(texto) + 1];
        char cezinho = tolower((unsigned char)c);
        para_minusculo(textinho, texto);

        for (int icont = 0; textinho[icont] != '\0'; icont++) {
            if (textinho[icont] == cezinho) {
                qtdOcorrencias++;
            }
        }
    } else {
        for (int icont = 0; texto[icont] != '\0'; icont++) {
            if (texto[icont] == c) {
                qtdOcorrencias++;
            }
        }
    }
    return qtdOcorrencias;
}

void para_minusculo(char *destino, char *origem) {
  int jcont;
	for (int icont = 0; origem[icont] != '\0'; icont++) {
          destino[icont] = tolower((unsigned char)origem[icont]);
          jcont = icont;
	}
	destino[jcont+1] = '\0';
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int jcont = 0;
    int kcont = 0;
    int sequencia = 0;
    int total = strlen(strBusca);

    for (int icont = 0; strTexto[icont] != '\0'; icont++) {
        jcont = 0;
        sequencia = 0;
        if (strTexto[icont] == strBusca[jcont]) {
            if(jcont == 0){
                int lcont = icont;                
                while(sequencia < total){
                    if (strTexto[lcont] == strBusca[jcont]){
                        jcont++;
                        sequencia++;
                        lcont++;
                    }
                    else{
                        break;   
                    }         
                }
                if(sequencia == total){
                    posicoes[kcont] = icont + 1;
                    kcont++;
                    posicoes[kcont] = lcont;
                    kcont++;
                    qtdOcorrencias++;
                }
                icont = lcont - 1;
            }
        }
      }
    //  for(int icont = 0; icont < kcont; icont++){
    //    printf("psicoes %i \n", posicoes[icont]);
    //  }
     //printf("qtd ocorrencias %i \n", qtdOcorrencias);
    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
  int mun = 0;
  int multi = 1;
  int icont = 1;
  int temp;

  while((num/multi) >= 10){
     multi*=10;                
  }
    while(multi >= 1){
      temp = (num / multi) % 10;
      multi /= 10;
      mun += temp * icont;
      
      icont*= 10;
    }
  num = mun;
  return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
    long int multi = 1;
    long int multiB = 1;
    long int icont;

    while((numerobusca/multiB) >= 10){
      multiB*=10;                
    }

    while((numerobase/multi) >= 10){
      multi*=10;                
    }
    icont = multi*10;
    multi /= multiB;

    while(multi >= 1){
      if(((numerobase%icont)/multi) == numerobusca){
        qtdOcorrencias++;
        multi /= multiB;
        icont /= multiB;
      }
      multi /= 10;
      icont /= 10;
    }

    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5])
 {
    int achou = 0;

    for(int icont = 0; icont < 8; icont++){
      for(int jcont = 0; jcont < 10; jcont++){
        if(matriz[icont][jcont] == palavra[0]){
          if(jcont <= 5 && achou == 0){
            achou = procura (0, 1, &icont, &jcont, palavra, matriz);
          }
          if(jcont <= 5 && icont <= 3 && achou == 0){
            achou = procura (1, 1, &icont, &jcont, palavra, matriz);
          }
          if(icont <= 5 && achou == 0){
            achou = procura (1, 0, &icont, &jcont, palavra, matriz);
          }
          if(jcont >= 4 && icont <= 3 && achou == 0){
            achou = procura (1, -1, &icont, &jcont, palavra, matriz);
          }
          if(jcont >= 4 && achou == 0){
            achou = procura (0, -1, &icont, &jcont, palavra, matriz);
          }
          if(jcont >= 4 && icont >= 4 && achou == 0){
            achou = procura (-1, -1, &icont, &jcont, palavra, matriz);
          }
          if(icont >= 4 && achou == 0){
            achou = procura (-1, 0, &icont, &jcont, palavra, matriz);
          }
          if(jcont <= 5 && icont >= 4 && achou == 0){
            achou = procura (-1, 1, &icont, &jcont, palavra, matriz);
          }
        }
      }
    }
     return achou;
 }

 int procura (int icresc, int jcresc, int *y, int *x, char palavra[], char matriz[][10]){

  for(int kcont = 1; kcont < 5; kcont++){
    if(matriz[*y+icresc*kcont][*x+jcresc*kcont] != palavra[kcont]){
      return 0;
    }
  }
  return 1;
 }



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}
