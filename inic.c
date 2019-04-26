//***************************************************//
//  GIANFRANCO DE SOUZA HARRES      - GRR: 20180103  //
//  VINICIUS AUGUSTO DILAY DE PAULA - GRR: 20182597  //
//***************************************************//
//                    INIC.C                         //
//***************************************************//
//       Possui funcoes que inicializam o jogo       //
//***************************************************//

#include "inic.h"


// Inicia matriz do mapa
void inic_mat (int tam, tp_map *map) {

  FILE *in_map;

  // define qual mapa e gera
   switch (tam) {
  // estatico
  case KEY_F(3):

    in_map = fopen("matriz.txt","r");

    if (in_map == NULL) {
      printf("matriz padrao nao encontrada");
      inic_mat(KEY_F(2), map);
      break;
    }

    fscanf(in_map, "%d", &map->lin);
    fscanf(in_map, "%d", &map->col);
    fscanf(in_map, "%d", &map->cristais);

    printw("%d %d %d", map->lin,map->col,map->cristais);
    map->cels = malloc(map->lin * sizeof(int*));
    map->cels[0] = malloc(map->lin * map->col * sizeof(int));
    for(int i = 1; i < map->lin; i++)
      map->cels[i] = map->cels[0] + i * map->col;

    for (int i = 0; i < map->lin; i++) {
      for (int j = 0; j < map->col; j++) {
	fscanf(in_map,"%d", &map->cels[i][j]);
      }
    }

    fclose(in_map);
    break;

  // aleatorio
  case KEY_F(2):
    map->lin = 15;
    map->col = 45;
    map->cristais = 0;

    map->cels = malloc(map->lin * sizeof(int*));
    map->cels[0] = malloc(map->lin * map->col * sizeof(int));
    for(int i = 1; i < map->lin; i++)
      map->cels[i] = map->cels[0] + i * map->col;

    random_map(map);

    // seta personagem
    map->cels[1][1] = PERSONAGEM;
    // seta saida
    map->cels[map->lin-2][map->col-2] = SAIDAOFF;

    break;
  }
}


// Gerador do mapa aleatorio
void random_map(tp_map *map){
  int aux;

  // gerando seed baseado no relogio
  srand(time(NULL));

  // demonstracao de atribuicao para a impressao
  for (int i = 0; i < map->lin; i++) {
    for(int j = 0; j < map->col; j++) {

      // atribuindo parades
      if ((i == 0) || (j == 0) || (i == map->lin-1) || (j == map->col-1))
	map->cels[i][j] = PAREDE;
      else if ((i == 8) && ((j > 3 ) && (j < 30)))
	map->cels[i][j] = PAREDE;
      else if ((i < 5) && (j == 29))
	map->cels[i][j] = PAREDE;
      // atribuindo valores das cels
      else {
	// numeros aleatorios de 0 a 9
	aux = rand()%10;

	// 20% de chance de pedra
	// reduzir chances de aparecer
	if ((aux < 3) && (aux > 0))
    //evita travar comeco e fim do jogo
    if (((j < 4 ) && (i < 4)) || ((i > map->lin-4) && (j > map->col-4)) || (((i < 10) && (i > 6)) && ((j > 28) && (j < 31))))
      map->cels[i][j] = VAZIO;
    else
      map->cels[i][j] = PEDRA;

	// 60% de c,hance de terra
	else if (aux > 2 && aux < 9)
	  map->cels[i][j] = TERRA;

	// 10% de chance de cristal
	// reduzir chance de aparecer
	else if (aux == 9) {
	  aux = rand()%10;
	  if (aux < 4) {
	    map->cels[i][j] = CRISTAL;
	    map->cristais++;
	  }
	  else map->cels[i][j] = TERRA;

	}

	// 10% de chance de vazio
	else
	  map->cels[i][j] = VAZIO;
      }
    }
  }

}

// Gera e seta personagem
void inic_hero (tp_map mapa, tp_hero *personagem) {
  int ch;

  personagem->x = 1;
  personagem->y = 1;
  personagem->vida = 3;

  for (int i = 0; i > 3; i++) {
    ch = getch();
    personagem->score.nome[i] = ch;
  }

  personagem->score.pontos = 0;

}


// Abre janela de help
WINDOW *open_helpwindow() {

  WINDOW *w;

  w = newwin(20,86,7,2);
  box(w, 0, 0);
  mvwprintw( w, 1, 1, "  COMANDOS:                           OBJETIVO:                           " );
  mvwprintw( w, 2, 1, "  Setas ou WASD para movimentacao     Voce é Daciolo e está preso em uma  " );
  mvwprintw( w, 3, 1, "  F2: cria mapa aleatorio             caverna,para poder sair dela,       " );
  mvwprintw( w, 4, 1, "  F3: cria mapa estatico              precisa abrir a porta. Infelizmente," );
  mvwprintw( w, 5, 1, "  h : tela de ajuda(in-game)          para abrir a porta é necessario     " );
  mvwprintw( w, 6, 1, "  q : sair do jogo                    coletar os cristais que estão       " );
  mvwprintw( w, 7, 1, "                                      perdidos pela caverna, e CUIDADO COM" );
  mvwprintw( w, 8, 1, "                                      AS PEDRAS, elas podem cair em cima  " );
  mvwprintw( w, 9, 1, "                                      de você!!!                          " );
  mvwprintw( w, 11, 1, "  Você possui três vidas, cada cristal adiciona 10 pontos em seu score.  " );
  mvwprintw( w, 12, 1, "  Para que a porta do proximo nivel seja aberta é preciso que sobre no   " );
  mvwprintw( w, 13, 1, "  maximo 10 cristais no mapa.                                            " );
  mvwprintw( w, 14, 1, "  As pedras podem rolar caso estejam empilhadas e haja espaços vazios ao " );
  mvwprintw( w, 15, 1, "  lado delas                                                             " );

  wrefresh(w);

  return w;
}


// Window do jogo
WINDOW *open_gamewindow(int lin, int col) {

  WINDOW *local_win;

  local_win = newwin(lin*2,col*2,1,1);
  box(local_win, 0, 0);

  wrefresh(local_win);

  return local_win;
}
