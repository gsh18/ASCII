//***************************************************//
//  GIANFRANCO DE SOUZA HARRES      - GRR: 20180103  //
//  VINICIUS AUGUSTO DILAY DE PAULA - GRR: 20182597  //
//***************************************************//
//                    INIC.H                         //
//***************************************************//
//   Header para a inicializar corretamente o jogo   //
//***************************************************//

#ifndef __inic__
#define __inic__

#include "defs.h"

// Inicia matriz do mapa
void inic_mat (int tam, tp_map *map);

// Gera e seta personagem
void inic_hero(tp_map mapa, tp_hero *personagem);

// Gerador do mapa aleatorio
void random_map(tp_map *map);

// Abre janela de help
WINDOW *open_helpwindow();

// Window do jogo
WINDOW *open_gamewindow(int lin, int col);

#endif
