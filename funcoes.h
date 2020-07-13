#ifndef FUNCOES_H
#define FUNCOES_H


typedef struct{
  int n_jogadores; //numero de jogadores
  char **jogadores; //nome dos jogadores
  int cheat; //flag para cheat mode
  int **pontos; //guarda a pontuação total e a pontuação da jogada atual de cada jogador 
  int **total_pecas; //guarda qual é a quantidade de peças disponíveis de cada tipo
  char ***pecas_jogadores; //guarda quais são as peças de cada jogador
  int *direcao; //armazena qual é a direção a ser mantida na jogada (linha/coluna)
  int *tam_tabuleiro; //guarda qual é o tamanho do tabuleiro atual
  int *deslocamento_x; //determina o posicionamento das peças no tabuleiro
  int *deslocamento_y;
}jogo;

typedef struct{
  int flag_primeira_rodada; //só serve para dizer se esse é o primeiro movimento de todos 
  int n_jogadas; //indica o numero de movimentos que foram feitos em uma rodada 
  int jog_atual; //indice do jogador atual em char **jogadores
}contadores;


int rodada(jogo informacoes, contadores indices, char ***tabuleiro);

int jogar(jogo informacoes, contadores indices, char comando[10][50], char ***tabuleiro);

int passar(jogo informacoes, contadores indices, char ***tabuleiro);

int trocar(jogo informacoes, contadores indices, char comando[10][50], char ***tabuleiro);



int checa_mov(jogo informacoes, int linha, int coluna, char *jogada, int jog_atual, char ***tabuleiro);

void atualiza_pontos(jogo informacoes, int total_linha, int total_coluna, int jog_atual);

void poe_pecas(jogo informacoes, int jog_atual);

int imprime_tabuleiro(jogo informacoes, contadores indices, char ***tabuleiro);

int novo_tabuleiro(jogo informacoes, int linha_superior, int linha_inferior, int coluna_esquerda, int coluna_direita, contadores indices, char ***tabuleiro);

int total_pecas(char letra, char numero, jogo informacoes, int modo);

int fim_jogo(jogo informacoes, char ***tabuleiro);

void desaloca(jogo informacoes, char ***tabuleiro);

#endif