#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"


int checa_mov(jogo informacoes, int linha, int coluna, char *jogada, int jog_atual, char ***tabuleiro){

  if(linha < 0 || coluna  < 0 || linha >= informacoes.tam_tabuleiro[0] || coluna >= informacoes.tam_tabuleiro[0]){
    return 0;
  }

  if(tabuleiro[linha][coluna][0] != 'v'){// verifica se a posição está vazia
    return 0;
  }

  //verifica se a direcao foi mantida. Sabe-se que ou direcao[0] == -1 ou direcao[1] = -1, nunca simultaneamente
  if( (informacoes.direcao[0] != -1) && (linha != informacoes.direcao[0]) ){
    return 0;
  }
  if( (informacoes.direcao[1] != -1) && (coluna != informacoes.direcao[1]) ){
    return 0;
  }



  //checagem vertical-----------------------------
  int cont_letra = 0;
  int cont_numero = 0;
  int total_coluna = 0;//total de jogadas na coluna

  //para cima
  int mov_linha = linha - 1; //indice da linha
  while(tabuleiro[mov_linha][coluna][0] != 'v'){
    if(jogada[0] == tabuleiro[mov_linha][coluna][0])cont_letra++;
    if(jogada[1] == tabuleiro[mov_linha][coluna][1])cont_numero++;
    total_coluna++;
    mov_linha--;
  }

  //para baixo
  mov_linha = linha + 1;
  while(tabuleiro[mov_linha][coluna][0] != 'v'){
    if(jogada[0] == tabuleiro[mov_linha][coluna][0])cont_letra++;
    if(jogada[1] == tabuleiro[mov_linha][coluna][1])cont_numero++;
    total_coluna++;
    
    mov_linha++;
  }

  if(total_coluna != 0){
    if( (cont_letra == cont_numero) || (cont_letra != 0 && cont_letra != total_coluna) || (cont_numero != 0 && cont_numero != total_coluna)){
      return 0;
    }
  }
  
  
  // checagem horizontal--------------------------
  cont_letra = 0;
  cont_numero = 0;
  int total_linha = 0;//total de jogadas na linha

  //para esquerda
  int mov_coluna = coluna - 1; //indice da coluna
  while(tabuleiro[linha][mov_coluna][0] != 'v'){
    if(jogada[0] == tabuleiro[linha][mov_coluna][0])cont_letra++;
    if(jogada[1] == tabuleiro[linha][mov_coluna][1])cont_numero++;
    total_linha++;
    mov_coluna--;
  }

  //para direita
  mov_coluna = coluna + 1;
  while(tabuleiro[linha][mov_coluna][0] != 'v'){
    
    if(jogada[0] == tabuleiro[linha][mov_coluna][0])cont_letra++;
    if(jogada[1] == tabuleiro[linha][mov_coluna][1])cont_numero++;
    total_linha++;
    mov_coluna++;
  }

  if(total_linha != 0){
    if( (cont_letra == cont_numero) || (cont_letra != 0 && cont_letra != total_linha) || (cont_numero != 0 && cont_numero != total_linha)){
    return 0;
    }
  }
  
  if(total_coluna == 0 && total_linha == 0){
    return 0;
  }

  // alem de checar a jogada, já é possível atualizar a contagem de pontos

  atualiza_pontos(informacoes, total_linha, total_coluna, jog_atual);
  
  return 1;
}

void atualiza_pontos(jogo informacoes, int total_linha, int total_coluna, int jog_atual){
  // a adição abaixo adiciona a ultima peça jogada
  if(total_coluna != 0){
    total_coluna++;
  }
  if(total_linha != 0){
    total_linha++;
  }
  
  if(total_coluna == 6){
    printf("Qwirkle na coluna, mais 6 pontos\n");
    total_coluna += 6;
  }
  if(total_linha == 6){
    printf("Qwirkle na linha, mais 6 pontos\n");
    total_linha += 6;
  }

  if(informacoes.direcao[0] == -1){ // significa que as colunas foram contadas novamente
    informacoes.pontos[jog_atual][1] += total_linha;
    informacoes.pontos[jog_atual][2] = total_coluna; //basta substituir com o novo valor
  }
  else if(informacoes.direcao[1] == -1){ //as linhas foram contadas novamente
    informacoes.pontos[jog_atual][1] = total_linha; //basta substituir com o novo valor
    informacoes.pontos[jog_atual][2] += total_coluna;
  }
  else{// é a primeira jogada da pessoa
    informacoes.pontos[jog_atual][1] = total_linha;
    informacoes.pontos[jog_atual][2] = total_coluna;
  }

}

void poe_pecas(jogo informacoes, int jog_atual){
  char letras[6] = {'A','B','C','D','E','F'};
  char numeros[6] = {'1','2','3','4','5','6'};
  int letra;
  int numero;
  
  for(int i = 0; i < 6; i++){

    int cont_total = 0;
    for(int j = 0; j < 6; j++){
      for(int k = 0; k < 6; k++){
        cont_total += informacoes.total_pecas[j][k];
      }
    }
    
    if(cont_total == 0){
      break;
    }

    if(informacoes.pecas_jogadores[jog_atual][i][0] == 'v'){
      letra = rand()% 6;
      numero = rand()% 6;
      
      while(informacoes.total_pecas[letra][numero] == 0){
        letra = rand()% 6;// o indice de total_pecas vai de 0 a 5 
        numero = rand()% 6;
      }
      informacoes.total_pecas[letra][numero] -= 1;

      informacoes.pecas_jogadores[jog_atual][i][0] = letras[letra];
      informacoes.pecas_jogadores[jog_atual][i][1] = numeros[numero];
        
    }
  }
  
 
}

int total_pecas(char letra, char numero, jogo informacoes, int modo){ //serve para por ou remover peças diretamente do total
  char letras[6] = {'A','B','C','D','E','F'};
  char numeros[6] = {'1','2','3','4','5','6'};
  
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 6; j++){
      if(letra == letras[i] && numero == numeros[j]){
        if(modo){
          informacoes.total_pecas[i][j] += 1;
          return 1;
        }
	      else if(!modo && informacoes.total_pecas[i][j] > 0){        
          informacoes.total_pecas[i][j] -= 1;
          return 1;
        }
      }
    }
  }
  return 0;
}




int imprime_tabuleiro(jogo informacoes, contadores indices, char ***tabuleiro){
  if(indices.flag_primeira_rodada == 0 && indices.n_jogadas == 0){
    return rodada(informacoes, indices, tabuleiro);
  }
  //as variaveis abaixo servirão para definir de onde as peças começam a aparecer no tabuleiro
  int linha_superior = -1;
  int linha_inferior = -1;
  int coluna_esquerda = -1;
  int coluna_direita = -1;

  int tam_tabuleiro = informacoes.tam_tabuleiro[0] - 1;
  
  for(int i = 0; i < tam_tabuleiro; i++){
    for(int j = 0; j < tam_tabuleiro; j++){
      if(linha_superior == -1 && tabuleiro[i][j][0] != 'v')linha_superior = i;
      if(linha_inferior == -1 && tabuleiro[tam_tabuleiro - i][j][0] != 'v')linha_inferior = tam_tabuleiro - i;
      if(coluna_esquerda == -1 && tabuleiro[j][i][0] != 'v')coluna_esquerda = i;
      if(coluna_direita == -1 && tabuleiro[j][tam_tabuleiro - i][0] != 'v')coluna_direita = tam_tabuleiro - i;
    }
  }
  
  // depois de definir quais são os limites do jogo, checa-se se é necessário fazer um deslocamento das peças
  if(linha_superior <= 1 || linha_inferior >= tam_tabuleiro - 2 || coluna_esquerda <= 1 || coluna_direita >= tam_tabuleiro - 2){
    return novo_tabuleiro(informacoes, linha_superior, linha_inferior, coluna_esquerda, coluna_direita, indices, tabuleiro);
  }
  printf("   ");
  for (int i = coluna_esquerda - 1; i <= coluna_direita + 1; i++){
    int aux = i - informacoes.deslocamento_x[0];
    if(aux >= 0 && aux < 10){
      printf("  %d  ", aux);
    }
    else if((aux > -10 && aux < 0) || (aux >= 10 && aux < 100)){
      printf(" %d  ", aux);
    }
    else{
      printf(" %d ", aux);
    }
  }
  printf("\n");
  
  for (int i = linha_superior - 1; i <= linha_inferior + 1; i++){
    printf("  ");
    for (int j = coluna_esquerda - 1; j <= coluna_direita + 1; j++){
      printf("-----");
    }
    printf("\n");

    int aux = i - informacoes.deslocamento_y[0];
    if(aux >= 0 && aux < 10){
      printf("%d  ", aux);
    }
    else if((aux > -10 && aux < 0) || (aux >= 10 && aux < 100)){
      printf("%d ", aux);
    }
    else{
      printf("%d", aux);
    }
    
    for (int k = coluna_esquerda - 1; k < coluna_direita + 1; k++){
      if(tabuleiro[i][k][0] != 'v'){
        printf(" %s |", tabuleiro[i][k]);
      }
      else{
        printf("    |");
      }
      
    }

    printf("\n");
  }
  printf("\n");

  return rodada(informacoes, indices, tabuleiro);
}


int novo_tabuleiro(jogo informacoes, int linha_superior, int linha_inferior, int coluna_esquerda, int coluna_direita, contadores indices, char ***tabuleiro){
  
  int tam_tabuleiro = informacoes.tam_tabuleiro[0];

  int dist_altura = (linha_superior + (tam_tabuleiro - linha_inferior - 1))/2;
  int dist_largura = (coluna_esquerda + (tam_tabuleiro - coluna_direita - 1))/2;

  
  char copia[tam_tabuleiro][tam_tabuleiro][2];
  for(int i = 0; i < tam_tabuleiro; i++){
    for(int j = 0; j < tam_tabuleiro; j++){
      copia[i][j][0] = tabuleiro[i][j][0];
      copia[i][j][1] = tabuleiro[i][j][1];
      tabuleiro[i][j][0] = 'v';
      tabuleiro[i][j][1] = '0';
    }
  }

  //é possível que não tenha mais espaço
  if(dist_altura == 2 || dist_largura == 2){// o calloc foi utilizado pois não existe a necessidade de se manter o que havia antes
    
    informacoes.tam_tabuleiro[0] += 10;

    tabuleiro = (char***)calloc(informacoes.tam_tabuleiro[0],sizeof(char**));
    if(tabuleiro == NULL){
      printf("ERRO");
      exit(1);
    }
    
    for(int i = 0; i < informacoes.tam_tabuleiro[0]; i++){
      tabuleiro[i] = (char**)calloc(informacoes.tam_tabuleiro[0],sizeof(char*));
      if(tabuleiro[i] == NULL){
        printf("ERRO");
        exit(1);
      }
      for(int j = 0; j < informacoes.tam_tabuleiro[0]; j++){
        tabuleiro[i][j] = (char*)calloc(2,sizeof(char));
        
        if(tabuleiro[i][j] == NULL){
          printf("ERRO");
          exit(1);
        }
        tabuleiro[i][j][0] = 'v';
        tabuleiro[i][j][1] = '0';
      }
    }

    dist_altura = (informacoes.tam_tabuleiro[0] - (linha_inferior - linha_superior + 1))/2;
    dist_largura = (informacoes.tam_tabuleiro[0] - (coluna_direita - coluna_esquerda + 1))/2;

  }

  informacoes.deslocamento_x[0] = dist_largura + (informacoes.deslocamento_x[0] - coluna_esquerda);
  informacoes.deslocamento_y[0] = dist_altura + (informacoes.deslocamento_y[0] - linha_superior);
  //o informacoes.deslocamento serve para o que o usuario vai ver e não para a mudança das peças de lugar
 

  //"desloca" serve para reposicionar as peças no tabuleiro, e leva em consideração a posiçaõ antiga e a nova
  int desloca_x = dist_largura - coluna_esquerda;
  int desloca_y = dist_altura - linha_superior;
  
  for(int i = 0; i < tam_tabuleiro; i++){
    for(int j = 0; j < tam_tabuleiro; j++){
      if(copia[i][j][0] != 'v'){
        tabuleiro[i + desloca_y][j + desloca_x][0] = copia[i][j][0];
        tabuleiro[i + desloca_y][j + desloca_x][1] = copia[i][j][1];
      }
    }
  }
  if(informacoes.direcao[0] != -1){
    informacoes.direcao[0] += desloca_y;
  }
  if(informacoes.direcao[1] != -1){
    informacoes.direcao[1] += desloca_x;
  }
  tam_tabuleiro = informacoes.tam_tabuleiro[0];
  
  return imprime_tabuleiro(informacoes, indices, tabuleiro);
}


int fim_jogo(jogo informacoes, char ***tabuleiro){
  int pecas_restantes = 0;
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 6; j++){
      pecas_restantes += informacoes.total_pecas[i][j];
    }
  }

  for(int i = 0; i < informacoes.n_jogadores; i++){
    for(int j = 0; j < 6; j++){
      if(informacoes.pecas_jogadores[i][j][0] != 'v'){
        pecas_restantes++;
      }
    }
  }

  if(pecas_restantes == 0){
    return 0;
  }

  return 1; 
}

void desaloca(jogo informacoes, char ***tabuleiro){// desalocação de memória

  //tabuleiro
  for(int i = 0; i < informacoes.tam_tabuleiro[0]; i++){
    for(int j = 0; j < informacoes.tam_tabuleiro[0]; j++){
      free(tabuleiro[i][j]);
    }
    free(tabuleiro[i]);
  }
  free(tabuleiro);

  //jogadores, pontos e pecas_jogadores
  for(int i = 0; i < informacoes.n_jogadores; i++){
    free(informacoes.jogadores[i]);
    free(informacoes.pontos[i]);
    for(int j = 0; j < 6; j++){
      free(informacoes.pecas_jogadores[i][j]);
    }
    free(informacoes.pecas_jogadores[i]);
  }
  free(informacoes.jogadores);
  free(informacoes.pontos);
  free(informacoes.pecas_jogadores);

  //total_pecas
  for(int i = 0; i < 6; i++){
    free(informacoes.total_pecas[i]);
  }
  free(informacoes.total_pecas);

  //direcao
  free(informacoes.direcao);

  //tam_tabuleiro
  free(informacoes.tam_tabuleiro);

  //deslocamentos
  free(informacoes.deslocamento_x);
  free(informacoes.deslocamento_y);

  exit(0);
}