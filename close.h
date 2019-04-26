//***************************************************//
//  GIANFRANCO DE SOUZA HARRES      - GRR: 20180103  //
//  VINICIUS AUGUSTO DILAY DE PAULA - GRR: 20182597  //
//***************************************************//
//                    CLOSE.H                        //
//***************************************************//
//              Header para close.c                  //
//***************************************************//

#ifndef __close__
#define __close__

#include "defs.h"

// Libera Malloc do mapa
void free_mapa(tp_map *map);

// Fecha a windwow
void close_window (WINDOW *local_win);

// Salva score do jogador
void save_score (tp_hero p);

#endif
