//***************************************************//
//  GIANFRANCO DE SOUZA HARRES      - GRR: 20180103  //
//  VINICIUS AUGUSTO DILAY DE PAULA - GRR: 20182597  //
//***************************************************//
//                     MAIN.C                        //
//***************************************************//
//    Executa sequencialmente todos os arquivos      //
//***************************************************//

#include "defs.h"
#include "anim.h"
#include "inic.h"
#include "logic.h"
#include "close.h"


int main () {
  WINDOW *helpscr;
  WINDOW *gamescr;
  tp_map *cenario;
  tp_hero daciolo;
  int ch, aux;


  // inicializa variaveis
  cenario = (tp_map*) malloc(6);
  inic_mat(KEY_F(2),cenario);
  inic_hero(*cenario, &daciolo);

  // inicializa ncurses
  initscr();
  raw();
  nodelay(stdscr,TRUE);
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);

  // menu do jogo
  print_menu(&daciolo);

  // primeiro print de tela
  gamescr = open_gamewindow(cenario->lin,cenario->col);
  fisica(cenario,&ch,&daciolo);
  print_map(*cenario,daciolo);
  refresh();

  ch = getch();
  // loop do jogo
  while (daciolo.vida > 0) {

    switch(ch) {
    case 'H':
    case 'h':
      ch = 'a';
      helpscr = open_helpwindow();
      while ((ch = getch()) != 'h');
      close_window(helpscr);
      break;

    case 'q':
    case 'Q':
      daciolo.vida = 0;
      break;

    case KEY_F(3):
    case KEY_F(2):
      morte(*cenario,daciolo);
      close_window(gamescr);
      gamescr = open_gamewindow(cenario->lin,cenario->col);
      inic_mat(ch,cenario);
      daciolo.x = 1;
      daciolo.y = 1;
      fisica(cenario,&ch,&daciolo);
      print_map(*cenario,daciolo);
      refresh();
      break;

    default:
      movimentacao(cenario,ch,&daciolo);
      break;

    }

    ch = getch();
    fisica(cenario,&ch,&daciolo);
    abrirSaida(cenario);

    print_map(*cenario,daciolo);
    refresh();

    aux = vitoria(*cenario,daciolo);
    if (aux) {
      ch = KEY_F(2);
      close_window(gamescr);
      gamescr = open_gamewindow(cenario->lin,cenario->col);
      inic_mat(ch,cenario);
      daciolo.x = 1;
      daciolo.y = 1;
      fisica(cenario,&ch,&daciolo);
      print_map(*cenario,daciolo);
      refresh();
      ch = 0;
    }
    
  }

  // animacao de finalizacao
  morte(*cenario,daciolo);



  // encerramento
  save_score (daciolo);
  free_mapa(cenario);
  close_window(gamescr);
  endwin();

  return 0;
}
