//***************************************************///
//  GIANFRANCO DE SOUZA HARRES      - GRR: 20180103  //
//  VINICIUS AUGUSTO DILAY DE PAULA - GRR: 20182597  //
//***************************************************//
//                    CLOSE.C                        //
//***************************************************//
//     Libera memoria e fecha janelas / arquivos     //
//***************************************************//

#include "close.h"

// Libera malloc do mapa
void free_mapa (tp_map *map) {
  free(map->cels[0]);
  free(map->cels);
}

// Fecha a window
void close_window (WINDOW *local_win) {

  clear();
  wrefresh(local_win);
  delwin(local_win);

}

// Salva a pontuaçao do jogador
void save_score (tp_hero p) {
  FILE *score_out;
  tp_placar *scores;

  score_out = fopen ("scores.txt","a+");

  if (!score_out) {
    perror ("Não foi encontrado os highscores");
    exit(1);
  }

  scores = malloc(sizeof(tp_placar));

  fread(scores,sizeof(tp_placar),10,score_out);

  strcpy(scores->nome,p.score.nome);
  scores->pontos = p.score.pontos;

  fprintf(score_out,"\n%s    %s \n","nome:",scores->nome);
  fprintf(score_out,"%s %02d \n","pontos: ",scores->pontos);

}
