//***************************************************//
//  GIANFRANCO DE SOUZA HARRES      - GRR: 20180103  //
//  VINICIUS AUGUSTO DILAY DE PAULA - GRR: 20182597  //
//***************************************************//
//                     LOGIC.C                       //
//***************************************************//
//  Logica principal do jogo: movimentacao / fisica  //
//***************************************************//

#include "logic.h"

//Movimentaçao do personagem
void movimentacao (tp_map *mapa, int cmd, tp_hero *p) {
  switch (cmd) {
 
  case KEY_RIGHT:
  case 'd':
  case 'D':
    if ((mapa->cels[p->x][p->y+1] != PAREDE) && (mapa->cels[p->x][p->y+1] != PEDRA)) {
      if (mapa->cels[p->x][p->y+1] != SAIDAOFF) {
	if (mapa->cels[p->x][p->y+1] == CRISTAL) {
	  mapa->cristais--;
	  p->score.pontos += 10;
	}
	mapa->cels[p->x][p->y+1] = PERSONAGEM;
	mapa->cels[p->x][p->y] = VAZIO;
	p->y++;
      }
    }
    else if ((mapa->cels[p->x][p->y+1] == PEDRA) && (mapa->cels[p->x][p->y+2] == VAZIO)) {
      mapa->cels[p->x][p->y] = VAZIO;
      mapa->cels[p->x][p->y+1] = PERSONAGEM;
      mapa->cels[p->x][p->y+2] = PEDRA;
      p->y++;
    }

    break;


  case KEY_LEFT:
  case 'a':
  case 'A':
    if ((mapa->cels[p->x][p->y-1] != PAREDE) && (mapa->cels[p->x][p->y-1] != PEDRA)) {
      if (mapa->cels[p->x][p->y-1] != SAIDAOFF) {
	if (mapa->cels[p->x][p->y-1] == CRISTAL) {
	  mapa->cristais--;
	  p->score.pontos += 10;
	}
      mapa->cels[p->x][p->y-1] = PERSONAGEM;
      mapa->cels[p->x][p->y] = VAZIO;
      p->y--;
      }
    }
    else if ((mapa->cels[p->x][p->y-1] == PEDRA) && (mapa->cels[p->x][p->y-2] == VAZIO)) {
      mapa->cels[p->x][p->y] = VAZIO;
      mapa->cels[p->x][p->y-1] = PERSONAGEM;
      mapa->cels[p->x][p->y-2] = PEDRA;
      p->y--;
    }

    break;


  case KEY_UP:
  case 'w':
  case 'W':
    if ((mapa->cels[p->x-1][p->y] != PAREDE) && (mapa->cels[p->x-1][p->y] != PEDRA)){
      if (mapa->cels[p->x-1][p->y] != SAIDAOFF) {
	if (mapa->cels[p->x-1][p->y] == CRISTAL) {
	  mapa->cristais--;
	  p->score.pontos += 10;
	}
	mapa->cels[p->x-1][p->y] = PERSONAGEM;
	mapa->cels[p->x][p->y] = VAZIO;
	p->x--;
      }
    }
    break;


  case KEY_DOWN:
  case 's':
  case 'S':
    if ((mapa->cels[p->x+1][p->y] != PAREDE) && (mapa->cels[p->x+1][p->y] != PEDRA)) {
      if (mapa->cels[p->x+1][p->y] != SAIDAOFF) {
	if (mapa->cels[p->x+1][p->y] == CRISTAL) {
	  mapa->cristais--;
	  p->score.pontos += 10;
	}
      }
      mapa->cels[p->x+1][p->y] = PERSONAGEM;
      mapa->cels[p->x][p->y] = VAZIO;
      p->x++;
    }
    break;
  }
}


//Fisica da pedra e rocha
void fisica (tp_map *mapa, int *cmd, tp_hero *p) {
  int aux;

  for (int i = 1; i < mapa->lin-1; i++) {
    for (int j = 1; j < mapa->col-1; j++) {
      // faz a rocha / cristal cair
      if ((mapa->cels[i][j] >= PEDRA) && (mapa->cels[i+1][j] == VAZIO)) {
	aux = mapa->cels[i][j];
	mapa->cels[i][j] = VAZIO;
	mapa->cels[i+1][j] = aux;

	if ((mapa->cels[i+2][j] == PERSONAGEM)) {
	  p->vida--;
	  *cmd = KEY_F(2);
	}
      }
      // faz as rochas / cristais rolarem; rocha em cima de rocha;
      else if ((mapa->cels[i][j] >= PEDRA) && (mapa->cels[i+1][j] >= PAREDE)) {

	if ((mapa->cels[i][j+1] == VAZIO) && (mapa->cels[i+1][j+1] == VAZIO)) {
	  aux = mapa->cels[i][j];
	  mapa->cels[i][j] = VAZIO;
	  mapa->cels[i][j+1] = aux;
	}

	if ((mapa->cels[i][j-1] == VAZIO) && (mapa->cels[i+1][j-1] == VAZIO)) {
	  aux = mapa->cels[i][j];
	  mapa->cels[i][j] = VAZIO;
	  mapa->cels[i][j-1] = aux;
	}
      }

    }
  }
}


//Abre a saida da caverna
void abrirSaida(tp_map *mapa) {

  if (mapa->cristais < 10) {
    mapa->cels[mapa->lin- 2][mapa->col-2] = SAIDAON;
  }
}
