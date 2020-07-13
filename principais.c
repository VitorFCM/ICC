#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


int rodada(jogo informacoes, contadores indices, char ***tabuleiro){ 

  int jog_atual = indices.jog_atual;
  int cont_pecas = 0;
  for(int i = 0; i < informacoes.n_jogadores; i++){
    printf("Jogador %s (score %d): ", informacoes.jogadores[i], informacoes.pontos[i][0]);
    for(int j = 0; j < 6; j++){
      if(informacoes.pecas_jogadores[i][j][0] != 'v'){
        printf("%s ", informacoes.pecas_jogadores[i][j]);
        if(i == jog_atual)cont_pecas++;
      }
    }
    printf("\n");
  }

  if( !fim_jogo(informacoes, tabuleiro)){//checa se as peças acabaram e caso tenha acabado da um exit(0)
    int total = informacoes.pontos[jog_atual][1] + informacoes.pontos[jog_atual][2];
    informacoes.pontos[jog_atual][0] += total;

    printf("Pontuação feita: %d\n", total);
    printf("Pontuação acumulada: %d\n", informacoes.pontos[jog_atual][0]);
    printf("********O jogo acabou********\n");

    int maior_pontos = -1;
    int jogador;
    for(int i = 0; i < informacoes.n_jogadores; i++){
      for(int j = 0; j < informacoes.n_jogadores; j++){
        if(informacoes.pontos[j][0] > maior_pontos){
          maior_pontos = informacoes.pontos[j][0];
          jogador = j;
        }
      }
      printf("Em %d lugar: %s, com %d pontos\n", (i+1), informacoes.jogadores[jogador], maior_pontos);
      informacoes.pontos[jogador][0] = -1;
      maior_pontos = -1;     
    }

    desaloca(informacoes, tabuleiro);
  }

  printf("Rodada de %s\n", informacoes.jogadores[jog_atual]);

  if(cont_pecas == 0){
    printf("Acabaram as peças do jogador atual\n");
    return passar(informacoes, indices, tabuleiro);
  }

  if(indices.n_jogadas == 0){
    printf("opcoes: trocar p1 [p2 p3...] | jogar p1 x y | passar\n");
    // o ponteiro direcao será alterado para guardar qual será a linha ou a coluna que deverá ser mantida nas próximas jogadas
    informacoes.direcao[0] = -1;//indice 0 será para a linha
    informacoes.direcao[1] = -1;//indice 1 será para a coluna
  }
  else{
    printf("opcoes: jogar p1 x y | passar\n");
  }
  
  
  char comando[50];
  setbuf(stdin, comando);
  fgets(comando, 50*sizeof(char), stdin);
  
  
  int i = 0, j = 0, k = 0, n_espacos = 0;
  char aux[10][50];

  while(comando[i] != '\0' && j < 10){
    while(comando[i] == ' '){
      i++;
    }
    while(comando[i] != ' ' && comando[i] != '\n'){
      aux[j][k++] = comando[i++];
    }
    aux[j][k] = '\0';
    k = 0;
    j++;
  }

  
  if(!strcmp(aux[0], "passar") || !strcmp(aux[0], "p")){
    return passar(informacoes, indices, tabuleiro);
  }
  else if(!strcmp(aux[0], "jogar") || !strcmp(aux[0], "j")){
    //checagem dos numeros
    int flag_um = 0, flag_dois = 0;
    if(aux[2][0] == '-')flag_um = 1;
    if(aux[3][0] == '-')flag_dois = 1;

    for(int i = flag_um; i < strlen(aux[2]); i++){
      if( (int)aux[2][i] < 48 || (int)aux[2][i] > 57 ){ 
        printf("Comando não identificado\n");
        return rodada(informacoes, indices, tabuleiro);
      }
    }
    for(int i = flag_dois; i < strlen(aux[3]); i++){
      if( (int)aux[3][i] < 48 || (int)aux[3][i] > 57 ){
        printf("Comando não identificado\n");
        return rodada(informacoes, indices, tabuleiro);
      }
    }
    return jogar(informacoes, indices, aux, tabuleiro);
  }// fim do comando jogar
  else if( (!strcmp(aux[0], "trocar") || !strcmp(aux[0], "t")) && (indices.n_jogadas == 0) ){
    return trocar(informacoes, indices, aux, tabuleiro);
  }
  
  printf("Comando não identificado\n");
  return rodada(informacoes, indices, tabuleiro);
}



int passar(jogo informacoes, contadores indices, char ***tabuleiro){
  int jog_atual = indices.jog_atual;

  if( indices.flag_primeira_rodada == 1){
    informacoes.pontos[jog_atual][1] = 1;
  }

  int total = informacoes.pontos[jog_atual][1] + informacoes.pontos[jog_atual][2];
  informacoes.pontos[jog_atual][0] += total;

  printf("Pontuação feita: %d\n", total);
  printf("Pontuação acumulada: %d\n", informacoes.pontos[jog_atual][0]);

  informacoes.pontos[jog_atual][1] = 0; // as pontuações da linha e da coluna são zeradas
  informacoes.pontos[jog_atual][2] = 0;
	
  poe_pecas(informacoes, jog_atual); //repoe as peças desse jogador
    
  indices.n_jogadas = 0;

  if(indices.flag_primeira_rodada != 0){
    indices.flag_primeira_rodada++; 	
  }	
    
  if( (jog_atual + 1) == informacoes.n_jogadores ){
    indices.jog_atual = 0;
    return rodada(informacoes, indices, tabuleiro);
  }
 
  indices.jog_atual++;
  return rodada(informacoes, indices, tabuleiro);
}


int jogar(jogo informacoes, contadores indices, char comando[10][50], char ***tabuleiro){
  if( (int)comando[1][0] >= 97 && (int)comando[1][0] <= 102 ){ // letras a, b, c, d, e, f
    comando[1][0] = comando[1][0] - 32;//vai deixar a letra maiucula
  }
  
  int linha = atoi(comando[2]) + informacoes.deslocamento_y[0];
  int coluna = atoi(comando[3]) + informacoes.deslocamento_x[0];
 
  if(indices.n_jogadas == 0){
    informacoes.direcao[0] = linha;
    informacoes.direcao[1] = coluna;
  }
  // a partir da segunda rodada de alguem, difine-se qual será a direção das jogadas
  else if(indices.n_jogadas == 1){
    if( (informacoes.direcao[0] != linha) && (informacoes.direcao[1] != coluna) ){ //não possui nem a linha nem a coluna em comum com a primeira jogada
      printf("*****************invalid move*****************\n");
      return imprime_tabuleiro(informacoes, indices, tabuleiro);
    }

    if(informacoes.direcao[0] != linha){
      informacoes.direcao[0] = -1;
    }
    else {             
      informacoes.direcao[1] = -1;
    }
      // caso as posiçoes digitadas forem as mesmas, o checa_mov irá retornar erro
  }
    
  int possui_peca = 0;
  int posicao_peca = 0;
  for(int i = 0; i < 6; i++){
    if( !strcmp(informacoes.pecas_jogadores[indices.jog_atual][i], comando[1]) ){
      posicao_peca = i;
      possui_peca = 1;
      break;
    }
  }

  if(possui_peca == 0 && informacoes.cheat == 0){// não possui a peça indicada no comando e o cheat mode está desligado
    printf("*****************invalid move*****************\n");
    return imprime_tabuleiro(informacoes, indices, tabuleiro);
  }
      
    
  if(possui_peca == 0 && informacoes.cheat == 1){ //caso esteja no cheat mode é necessário retirar a peça do total de peças
    int flag_achou = total_pecas(comando[1][0], comando[1][1], informacoes, 0); //ja remove a peça do total de peças

    if(flag_achou == 0){
      printf("*****************invalid move*****************\n");;
      return imprime_tabuleiro(informacoes, indices, tabuleiro);
    }
  }

    
  if(indices.flag_primeira_rodada == 0){ // é o primeiro movimento de todos, só pode ser feito na posição 0x0
    if(linha - informacoes.deslocamento_y[0] != 0 || coluna - informacoes.deslocamento_y[0] != 0){
      printf("*****************invalid move*****************\n");
      if(possui_peca == 0 && informacoes.cheat == 1){
        total_pecas(comando[1][0], comando[1][1], informacoes, 1); 
      }
      return imprime_tabuleiro(informacoes, indices, tabuleiro);
    }
  }
  else if( checa_mov(informacoes, linha, coluna, comando[1], indices.jog_atual, tabuleiro) == 0 ){ // só chega a chamar a checa_move se não for a primeira rodada
    printf("*****************invalid move*****************\n");
    if(possui_peca == 0 && informacoes.cheat == 1){
      total_pecas(comando[1][0], comando[1][1], informacoes, 1); 
    }
    return imprime_tabuleiro(informacoes, indices, tabuleiro); 
  }
    
    
  //retira a peça do usuário
  if(possui_peca){
    informacoes.pecas_jogadores[indices.jog_atual][posicao_peca][0] = 'v';
    informacoes.pecas_jogadores[indices.jog_atual][posicao_peca][1] = '0';
  }
  
    
  // poe a peça no tabuleiro
  tabuleiro[linha][coluna][0] = comando[1][0]; // letra
  tabuleiro[linha][coluna][1] = comando[1][1]; // numero

  indices.flag_primeira_rodada++;
  indices.n_jogadas++;
    
  return imprime_tabuleiro(informacoes, indices, tabuleiro);// proxima rodada do mesmo jogador
}



int trocar(jogo informacoes, contadores indices, char comando[10][50], char ***tabuleiro){
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 6; j++){

      if( (int)comando[i+1][0] >= 97 && (int)comando[i+1][0] <= 102 ){ // letras a, b, c, d, e, f
        comando[i+1][0] = comando[i+1][0] - 32;//vai deixar a letra maiucula
      }

      if( !strcmp(comando[i+1], informacoes.pecas_jogadores[indices.jog_atual][j]) ){ // o jogador possui a peça que ele pediu para trocar
        total_pecas(comando[i+1][0], comando[i+1][1], informacoes, 1); //vai adicionar a peça no total de peças
        informacoes.pecas_jogadores[indices.jog_atual][j][0] = 'v';
        informacoes.pecas_jogadores[indices.jog_atual][j][1] = '0';
        comando[i+1][0] = 'v';// para que mais peças iguais não sejam substituidas
      }
    }
  }

  poe_pecas(informacoes, indices.jog_atual); //poe novas peças aleatórias


  indices.n_jogadas = 0;

  if(indices.jog_atual + 1 == informacoes.n_jogadores){
    indices.jog_atual = 0;
    return rodada(informacoes, indices, tabuleiro);
  }

  indices.jog_atual++;
  return rodada(informacoes, indices, tabuleiro);
}


