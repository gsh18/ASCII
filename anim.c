//***************************************************//
//  GIANFRANCO DE SOUZA HARRES      - GRR: 20180103  //
//  VINICIUS AUGUSTO DILAY DE PAULA - GRR: 20182597  //
//***************************************************//
//                     ANIM.C                        //
//***************************************************//
//     Imprime o cenario e as animações do jogo      //
//***************************************************//

#include "anim.h"

// Imprime uma celula da matriz por vez
void print_cel (int x, int y, int celula) {

  start_color();
  init_pair(1, COLOR_CYAN, COLOR_BLACK); // PERSONAGEM
  init_pair(2, COLOR_WHITE, COLOR_BLACK); // PEDRA
  init_pair(3, COLOR_MAGENTA, COLOR_MAGENTA); //TERRA
  init_pair(4, COLOR_YELLOW, COLOR_MAGENTA);  //CRISTAL
  init_pair(5, COLOR_WHITE, COLOR_RED); //SAIDA OFF
  init_pair(6, COLOR_WHITE, COLOR_GREEN); //SAIDA ON
  init_pair(7, COLOR_BLACK, COLOR_BLACK); //PAREDE
  init_pair(8, COLOR_BLACK, COLOR_BLACK); //VAZIO
  init_pair(9, COLOR_RED, COLOR_BLACK); // PERSONAGEM SEGUNDA COR

  x*=2;
  y*=2;

  switch (celula) {
  case VAZIO:
    attron(COLOR_PAIR(8));
    mvaddch(x,y,' ');
    mvaddch(x+1,y,' ');
    mvaddch(x,y+1,' ');
    mvaddch(x+1,y+1,' ');
    attroff(COLOR_PAIR(8));
    break;

  case PEDRA:
      attron(COLOR_PAIR(2) | A_BOLD);
      mvaddch(x  , y,   'O');
      mvaddch(x+1, y,   'O');
      mvaddch(x  , y+1, 'O');
      mvaddch(x+1, y+1, 'O');
      attroff(COLOR_PAIR(2));
    break;

  case CRISTAL:
    attron(COLOR_PAIR(4));
    mvaddch(x,y,'$');
    mvaddch(x+1,y,'$');
    mvaddch(x,y+1,'$');
    mvaddch(x+1,y+1,'$');
    attroff(COLOR_PAIR(4));
    break;

  case PERSONAGEM:
    attron(COLOR_PAIR(9) | A_BOLD);
    mvaddch(x,y,'|');
    attroff(COLOR_PAIR(9));
    attron(COLOR_PAIR(1) | A_BOLD);
    mvaddch(x+1,y,'/');
    mvaddch(x,y+1,'\\');
    mvaddch(x+1,y+1,'\\');
    attroff(COLOR_PAIR(1));
    break;

  case TERRA:
    attron(COLOR_PAIR(3));
    mvaddch(x,y,'#');
    mvaddch(x,y+1,'#');
    mvaddch(x+1,y,'#');
    mvaddch(x+1,y+1,'#');
    attroff(COLOR_PAIR(3));
    break;

  case PAREDE:
    attron(COLOR_PAIR(7) | A_BOLD);
    mvaddch(x,y,':');
    mvaddch(x+1,y,':');
    mvaddch(x,y+1,':');
    mvaddch(x+1,y+1,':');
    attroff(COLOR_PAIR(7));

    break;

  case SAIDAOFF:
    attron(COLOR_PAIR(5));
    mvaddch(x,y,'\\');
    mvaddch(x+1,y,'/');
    mvaddch(x,y+1,'/');
    mvaddch(x+1,y+1,'\\');
    attroff(COLOR_PAIR(5));
    break;

  case SAIDAON:
    attron(COLOR_PAIR(6) | A_BOLD);
    mvaddch(x,y,'/');
    mvaddch(x+1,y,'|');
    mvaddch(x,y+1,'\\');
    mvaddch(x+1,y+1,'|');
    attroff(COLOR_PAIR(6));

    break;
  }
}

// Imprime o mapa
void print_map (tp_map map,tp_hero p) {

  // imprime o mapa todo
  for (int i = 0; i < map.lin; i++)
    for (int j = 0; j < map.col; j++)
      print_cel(i, j, map.cels[i][j]);
  printw("\ncristais: %02d   score: %d  vidas: %d", map.cristais, p.score.pontos, p.vida);
  mvprintw( 30, 80, "h : help" );

}


// Caso de morte do personagem
void morte (tp_map mapa, tp_hero p) {
  p.x *= 2;
  p.y *= 2;
  int aux;
  WINDOW *w;

  for (int j = 0; j < 10; j++) {
    //Animacao de morte do personagem
    for (int i = p.x-2; i < p.x+4; i++)
      for (int j = p.y-2; j < p.y+4; j++) {
	aux = rand()%4;
	if (aux > 1) mvaddch(i,j,'*');
	else if (aux == 1)  mvaddch(i,j,' ');
	else if (aux == 0)  mvaddch(i,j,'+');
      }
    mvaddch(p.x,p.y-1,'P');
    mvaddch(p.x,p.y,'O');
    mvaddch(p.x,p.y+1,'W');
    mvaddch(p.x,p.y+2,'!');
    refresh();
    usleep(200000);
  }

  if (p.vida == 0) {
    //Box de game over
    w = newwin(24,44,5,25);
    box(w, 0, 0);
    mvwprintw( w, 1, 1, "    NO!                          MNO!" );
    mvwprintw( w, 2, 1, "   MNO!!                        MNNOO!" );
    mvwprintw( w, 3, 1, "  MMNO!                           MNNOO!" );
    mvwprintw( w, 4, 1, " MNOONNOO!   MMMMMMMMMMPPPOII!   MNNO!!!!" );
    mvwprintw( w, 5, 1, "  !O! NNO! MMMMMMMMMMMMMPPPOOOII!! NO!" );
    mvwprintw( w, 6, 1, "     ! MMMMMMMMMMMMMPPPPOOOOIII! !" );
    mvwprintw( w, 7, 1, "      MMMMMMMMMMMMPPPPPOOOOOOII!!" );
    mvwprintw( w, 8, 1, "      MMMMMOOOOOOPPPPPPPPOOOOMII!" );
    mvwprintw( w, 9, 1, "      MMMMM      OPPMMP     ,OMI!" );
    mvwprintw( w, 10, 1, "      MMMM::   o ,OPMP, o   ::I!" );
    mvwprintw( w, 11, 1, "        NNM:::.,,OOPM!P, ::::!!" );
    mvwprintw( w, 12, 1, "       MMNNNNNOOOOPMO!!IIPPO!!O!" );
    mvwprintw( w, 13, 1, "       MMMMMNNNNOO:!!:!!IPPPPOO!" );
    mvwprintw( w, 14, 1, "           MMMONNMMNNNIIIOO!" );
    mvwprintw( w, 15, 1, "         MN MOMMMNNNIIIIIO! OO" );
    mvwprintw( w, 16, 1, "        MNO! IiiiiiiiiiiiI OOOO" );
    mvwprintw( w, 17, 1, "   NNN MNO!   O!!!!!!!!!O   OONO NO!" );
    mvwprintw( w, 18, 1, "  MNNNNNO!    OOOOOOOOOOO    MMNNON!" );
    mvwprintw( w, 19, 1, "    MNNNNO!    PPPPPPPPP    MMNON!" );
    mvwprintw( w, 20, 1, "       OO!                   ON!" );
    mvwprintw( w, 21, 1, "              GAME OVER       " );
    mvwprintw( w, 22, 1, "Seu score sera guardado em scores.txt" );


    wrefresh(w);

    sleep(5);
  }
}

//ANIMAÇAO DE VITORIA
int vitoria (tp_map mapa,tp_hero p) {

  // checa se chegou na saida;
  if ((p.y == mapa.col-2) && (p.x == mapa.lin-2)) {

    p.x *= 2;
    p.y *= 2;
    WINDOW *w;

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN); //COR DA SAIDA

    attron(COLOR_PAIR(1));
    mvaddch(p.x,p.y,'\\');
    mvaddch(p.x+1,p.y,' ');
    mvaddch(p.x,p.y+1,' ');
    mvaddch(p.x+1,p.y+1,'\\');
    refresh();
    usleep(200000);

    mvaddch(p.x,p.y,'|');
    mvaddch(p.x+1,p.y,' ');
    mvaddch(p.x,p.y+1,' ');
    mvaddch(p.x+1,p.y+1,'|');
    refresh();
    usleep(200000);

    mvaddch(p.x,p.y,'/');
    mvaddch(p.x+1,p.y,' ');
    mvaddch(p.x,p.y+1,' ');
    mvaddch(p.x+1,p.y+1,'/');
    refresh();
    usleep(200000);

    mvaddch(p.x,p.y,'-');
    mvaddch(p.x+1,p.y,' ');
    mvaddch(p.x,p.y+1,' ');
    mvaddch(p.x+1,p.y+1,'-');
    refresh();
    usleep(200000);

    mvaddch(p.x,p.y,'\\');
    mvaddch(p.x+1,p.y,' ');
    mvaddch(p.x,p.y+1,' ');
    mvaddch(p.x+1,p.y+1,'\\');
    refresh();
    usleep(200000);

    mvaddch(p.x,p.y,'|');
    mvaddch(p.x+1,p.y,' ');
    mvaddch(p.x,p.y+1,' ');
    mvaddch(p.x+1,p.y+1,'|');
    refresh();
    usleep(200000);

    mvaddch(p.x,p.y,'/');
    mvaddch(p.x+1,p.y,' ');
    mvaddch(p.x,p.y+1,' ');
    mvaddch(p.x+1,p.y+1,'/');
    refresh();
    usleep(200000);

    mvaddch(p.x,p.y,'-');
    mvaddch(p.x+1,p.y,' ');
    mvaddch(p.x,p.y+1,' ');
    mvaddch(p.x+1,p.y+1,'-');
    refresh();
    usleep(200000);
    attroff(COLOR_PAIR(1));

    //Box de nivel passado
    w = newwin(13,45,5,25);
    box(w, 0, 0);

    mvwprintw( w, 5, 1, "     PARABENS, VOCE PASSOU ESSA FASE!!!" );
    wrefresh( w );
    sleep(4);

    return 1;
  }
  else return 0;
}


// Menu inicial
void print_menu( tp_hero *p) {
  WINDOW *w;

  int ch, i = 0, j = 0;

  initscr();
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK); // MENU

  //Cria a janela e e suas bordas
  w = newwin( 32, 96, 1, 1 );
  box( w, 0, 0 );

  //Printa o menu
  wattron( w, COLOR_PAIR(1) | A_BOLD );
  mvwprintw( w, i+3, 2, "              _____             _       _         _____            _           " );
  mvwprintw( w, i+4, 2, "             |  __ \\           (_)     | |       |  __ \\          | |        " );
  mvwprintw( w, i+5, 2, "             | |  | | __ _  ___ _  ___ | | ___   | |  | | __ _ ___| |__        " );
  mvwprintw( w, i+6, 2, "             | |  | |/ _` |/ __| |/ _ \\| |/ _ \\  | |  | |/ _` / __| '_ \\    " );
  mvwprintw( w, i+7, 2, "             | |__| | (_| | (__| | (_) | | (_) | | |__| | (_| \\__ \\ | | |    " );
  mvwprintw( w, i+8, 2, "             |_____/ \\__,_|\\___|_|\\___/|_|\\___/  |_____/ \\__,_|___/_| |_| " );

  mvwprintw( w, 15, 1, "                             APERTE ENTER PARA JOGAR                                   " );
  mvwprintw( w, 20, 1, "  COMANDOS:                               OBJETIVO:                                    " );
  mvwprintw( w, 21, 1, "  Setas ou WASD para movimentacao         Voce é Daciolo e está preso em uma caverna, " );
  mvwprintw( w, 22, 1, "  F2: cria mapa aleatorio                 para poder sair dela, precisa abrir a porta. " );
  mvwprintw( w, 23, 1, "  F3: cria mapa estatico                  Infelizmente, para abrir a porta é necessario" );
  mvwprintw( w, 24, 1, "  h : tela de ajuda(in-game)              coletar os cristais que estão perdidos pela  " );
  mvwprintw( w, 25, 1, "  q : sair do jogo                        caverna, e CUIDADO COM AS PEDRAS, elas podem " );
  mvwprintw( w, 26, 1, "                                          cair em cima de você!!!                      " );



  mvwprintw( w, 30, 2, "GIANFRANCO DE SOUZA        VINICIUS DILAY" );
  wrefresh( w );

  //recebe entrada
  while(( ch = wgetch(w)) != '\n'){
    switch( ch ) {
    case 'q':
      endwin();
      exit (0);
    }
  }

  mvwprintw( w, 15, 1, "                             Digite seu nome e aperte enter                            " );
  mvwprintw( w, 19, 1, "                                    APENAS 3 LETRAS                                    " );
  mvwprintw( w, 20, 1, "                                                                                       " );
  mvwprintw( w, 21, 1, "                                                                                       " );
  mvwprintw( w, 22, 1, "                                                                                       " );
  mvwprintw( w, 23, 1, "                                                                                       " );
  mvwprintw( w, 24, 1, "                                                                                       " );
  mvwprintw( w, 25, 1, "                                                                                       " );
  mvwprintw( w, 26, 1, "                          Seu score sera guardado em scores.txt                         " );
  wrefresh( w );

  echo();
  mvwprintw( w, 21, 30, " " );

  // recebe nome do jogador para o scores.txt
  while((( ch = wgetch(w)) != '\n') && (j != 3)){
    p->score.nome[j] = ch;
    j++;

  }
  noecho();
  wattroff( w, COLOR_PAIR(1) | A_BOLD );
  delwin( w );
  endwin();
}
