//***************************************************//
//  GIANFRANCO DE SOUZA HARRES      - GRR: 20180103  //
//  VINICIUS AUGUSTO DILAY DE PAULA - GRR: 20182597  //
//***************************************************//
//                     ANIM.H                        //
//***************************************************//
//         Header para as animações do jogo          //
//***************************************************//

#ifndef __anim__
#define __anim__

#include "defs.h"

// Printa celula recebida da funcao print_map
void print_cel (int x, int y, int celula);

// Organiza o print do mapa
void print_map (tp_map map,tp_hero p);

// Animaçao de morte do jogador
void morte (tp_map mapa, tp_hero p);

// Animaçao de vitoria do jogador
int vitoria (tp_map mapa, tp_hero p);

// Printa o menu inicial
void print_menu(tp_hero *p);

#endif
