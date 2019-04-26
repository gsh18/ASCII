//***************************************************//
//  GIANFRANCO DE SOUZA HARRES      - GRR: 20180103  //
//  VINICIUS AUGUSTO DILAY DE PAULA - GRR: 20182597  //
//***************************************************//
//                     DEFS.C                        //
//***************************************************//
//   Contém defines / structs para organizar o jogo  //
//***************************************************//

#ifndef __defs__
#define __defs__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#define VAZIO 0
#define PERSONAGEM 1
#define TERRA 2
#define SAIDAOFF 3
#define SAIDAON 4
#define PAREDE 5
#define PEDRA 6
#define CRISTAL 7


// Struct do mapa
typedef struct mapa {
  // tamanho da matriz 
  int lin;
  int col;

  int cristais;  // quantidade de cristais no mapa
  int **cels;    // matriz mapa
} tp_map;


// Struct do placar
typedef struct placar {
  char nome[4];
  int pontos;
}tp_placar;


// Struct do personagem
typedef struct daciolo {
  // coordenada em que se encontra o rockforge
  int x;
  int y;
  // auxilio para a logica do jogo
  int vida;
  tp_placar score;
} tp_hero;

#endif
