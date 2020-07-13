#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"


int main(void) {
  srand(time(NULL));

  jogo informacoes;

  char ***tabuleiro;
  tabuleiro = (char***)calloc(20,sizeof(char**));
  if(tabuleiro == NULL){
    printf("ERRO");
    exit(1);
  }

  for(int i = 0; i < 20; i++){
    tabuleiro[i] = (char**)calloc(20,sizeof(char*));
    if(tabuleiro[i] == NULL){
    printf("ERRO");
    exit(1);
    }

    for(int j = 0; j < 20; j++){
      tabuleiro[i][j] = (char*)calloc(2,sizeof(char));
      if(tabuleiro[i][j] == NULL){
        printf("ERRO");
        exit(1);
      }
      tabuleiro[i][j][0] = 'v';
      tabuleiro[i][j][1] = '0';
    }
  }




  informacoes.tam_tabuleiro = (int*)calloc(1, sizeof(int));
  informacoes.tam_tabuleiro[0] = 20;

  informacoes.deslocamento_x = (int*)calloc(1, sizeof(int));
  informacoes.deslocamento_x[0] = 10;

  informacoes.deslocamento_y = (int*)calloc(1, sizeof(int));
  informacoes.deslocamento_y[0] = 10;


 
  printf("Qual é o número de jogadores: ");
  scanf("%d", &informacoes.n_jogadores);

  informacoes.jogadores = (char**)calloc(informacoes.n_jogadores, sizeof(char*));
  if(informacoes.jogadores == NULL){
    printf("ERRO");
    exit(1);
  }

  char aux[50];
  for(int i = 0; i < informacoes.n_jogadores; i++){
    
    printf("Qual é o nome do %d# jogador:", (i+1));
    setbuf(stdin, NULL);
    fgets(aux, 50*sizeof(char), stdin);
    
    int j = 0;
    while(aux[j] != '\0'){
      j++;
    }
    aux[--j] = '\0';
    
    
    informacoes.jogadores[i] = (char*)calloc(j, sizeof(char));
    if(informacoes.jogadores[i] == NULL){
      printf("ERRO");
      exit(1);
    }
    
    strcpy(informacoes.jogadores[i], aux);
    
  }

  char resposta[3];
  
  while(1){
    printf("Cheat mode [S/N]:");
    fgets(resposta, 3, stdin);
    if(!strcmp(resposta,"s\n") || !strcmp(resposta,"S\n")){
      informacoes.cheat = 1;
      break;
    }
    else if(!strcmp(resposta,"n\n") || !strcmp(resposta,"N\n")){
      informacoes.cheat = 0;
      break;
    }
  }

  
  
  //vai armazenar o total de pontos de cada jogador e a pontuação de uma jogada
  informacoes.pontos = (int**)calloc(informacoes.n_jogadores, sizeof(int*));
  if(informacoes.pontos == NULL){
    printf("ERRO");
    exit(1);
  }
  for(int i = 0; i < informacoes.n_jogadores; i++){
    informacoes.pontos[i] = (int*)calloc(3, sizeof(int)); //o indice 0 será a pontuação total, o indice 1 a pontuação das linhas naquela jogada e o indice 2 será será a pontuação das colunas naquela jogada
    if(informacoes.pontos == NULL){
    printf("ERRO");
    exit(1);
    }
  }
  

  // será utilizada para recompor as peças dos jogadores
  informacoes.total_pecas = (int**)calloc(6, sizeof(int*));
  if(informacoes.total_pecas == NULL){
    printf("ERRO");
    exit(1);
  }
  for(int i = 0; i < 6; i++){
    informacoes.total_pecas[i] = (int*)calloc(6, sizeof(int));
    if(informacoes.total_pecas[i] == NULL){
      printf("ERRO");
      exit(1);
    }
    for(int j = 0; j < 6; j++){
      informacoes.total_pecas[i][j] = 3; //são 3 peças de cada tipo
    }
  }


  //vai armazenar quais são as peças que os jogadores possuem
  informacoes.pecas_jogadores = (char***)calloc(informacoes.n_jogadores,sizeof(char**));
  if(informacoes.pecas_jogadores == NULL){
    printf("ERRO");
    exit(1);
  }
  

  for(int i = 0; i < informacoes.n_jogadores; i++){
    informacoes.pecas_jogadores[i] = (char**)calloc(6,sizeof(char*));//cada jogador fica com 6 peças na mão
    if(informacoes.pecas_jogadores[i] == NULL){
    printf("ERRO");
    exit(1);
    }
    for(int j = 0; j < 6; j++){
      informacoes.pecas_jogadores[i][j] = (char*)calloc(2,sizeof(char));
      if(informacoes.pecas_jogadores[i][j] == NULL){
        printf("ERRO");
        exit(1);
      }
      informacoes.pecas_jogadores[i][j][0] = 'v';
      informacoes.pecas_jogadores[i][j][1] = '0';
    }
  }
  

  informacoes.direcao = (int*)calloc(2, sizeof(int));

  for(int i = 0; i < informacoes.n_jogadores; i++){
    poe_pecas(informacoes, i);
  }
  
  contadores indices;

  indices.flag_primeira_rodada = 0; 
  indices.n_jogadas = 0; 
  indices.jog_atual = 0;

  rodada(informacoes, indices, tabuleiro);
  
  return 0;
}

