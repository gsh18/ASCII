//***************************************************//
//  GIANFRANCO DE SOUZA HARRES      - GRR: 20180103  //
//  VINICIUS AUGUSTO DILAY DE PAULA - GRR: 20182597  //
//***************************************************//
//                     LOGIC.H                       //
//***************************************************//
//  Header da logica do jogo - fisica e movimentos   //
//***************************************************//

#ifndef __logic__
#define __logic__

#include "defs.h"

//Movimentaçao do personagem
void movimentacao (tp_map *mapa, int cmd, tp_hero *p);

//Fisica da pedra e rocha
void fisica (tp_map *mapa,int *cmd, tp_hero *p);

//Abre a saida da caverna
void abrirSaida(tp_map *mapa);

#endif
