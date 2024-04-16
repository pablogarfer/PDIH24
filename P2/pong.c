#include <ncurses.h>
#include <unistd.h>

#define DELAY 100000


int main(int argc, char *argv[]) {
 int rows, cols;
 int x = 10, y = 5;
 int max_y = 15, max_x = 70;
 int next_x = 0;
 int directionx = 1;
 int next_y = 0;
 int directiony = 1;
 int p1x = 5, p1y = 10, p2x = 65, p2y = 10;
 int ch = 0;
 bool play = true;


 initscr();
 start_color();
 init_pair(1, COLOR_BLACK, COLOR_WHITE);
 noecho();
 cbreak();
 curs_set(0);
 //nodelay(stdscr, TRUE);
 getmaxyx(stdscr, rows, cols);

 WINDOW * inicio = newwin(rows, cols, 0, 0);
 wbkgd(inicio, COLOR_PAIR(1));
 mvwprintw(inicio, 1, 1, "AUTOR: Pablo García Fernández");
 mvwprintw(inicio, 2, 1, "Jugador 1: ARRIBA -> W, ABAJO -> S");
 mvwprintw(inicio, 3, 1, "Jugador 2: ARRIBA -> Flecha Arriba, ABAJO -> Flecha Abajo");
 mvwprintw(inicio, 4, 1, "Pulse cualquier tecla para empezar a jugar");
 box(inicio, '|', '-'); 
 wrefresh(inicio);
 getch();
 timeout(0);
 
 while(play) {
 	clear();

	// Se dibujan los bordes del campo
    for (int i = 0; i < max_x; i++){
        mvprintw(0, i, "-");   		//Pinta la linea inferior 
        mvprintw(max_y, i, "-"); 	//Pinta la linea superior
    }
    for (int i = 1; i < max_y; i++){
        mvprintw(i, 0, "|");   		//Pinta la linea izquierda
        mvprintw(i, max_x, "|");  	//Pinta la linea derecha
    }
	//Pintamos la pelota y ambas raquetas
 	mvprintw(y, x, "o");
	for (int i = 0; i< 4; i++){
		mvprintw(p1y + i, p1x, "|");
		mvprintw(p2y + i, p2x, "|");
	}
 	//mvprintw(p1y, p1x, "|");
 	refresh();

    ch = getch();
	switch (ch)
	{
	case 'w':
		if(p1y > 1){
			p1y -= 1;
		}
		break;
	case 's':
		if(p1y+4 < max_y){
			p1y += 1;
		}
		break;
	case 65:   //Flecha arriba
		if(p2y > 1){	
			p2y -= 1;
		}	
		break;
	case 66:   //flecha abajo
		if(p2y+4 < max_y){
			p2y += 1;
		}		
		break;
	}
 	
 	usleep(DELAY);

 	next_x = x + directionx;
 	next_y = y + directiony;

	//La pelota rebota si toca en los límites superior o inferior
	if (next_y >= max_y || next_y <= 0) {
 		directiony*= -1;
 	} else {
 		y+= directiony;
 	}

	//La pelota rebota si da en alguna las raquetas de los jugadores
    if ((next_y >= p1y && next_y <p1y+4) && next_x==p1x + 1) {
 		directionx*= -1;
 	}

	if ((next_y >= p2y && next_y <p2y+4) && next_x==p2x -1) {
 		directionx*= -1;
 	} 

	//Si la pelota sale por el lado izquierdo o derecho , se pregunta si quiere continuar
	if (next_x >= max_x || next_x < 0) {
 		timeout(-1);

        WINDOW * final = newwin(rows, cols, 0, 0);
        wbkgd(final, COLOR_PAIR(1));
        mvwprintw(final, 5, 10, "Se ha marcado un gol");
		mvwprintw(final, 6, 10, "Si quiere salir pulse F o pulse cualquier otra tecla para seguir jugando");
		box(final, '|', '-'); 
		wrefresh(final);

		char tecla = getch();
		if(tecla == 'f')
			play = false;
		else{
			timeout(0);
			x = 10;
			y = 5;
		}	
 	} else {
 		x+= directionx;
 	}
 }

 endwin();
 return 0;
}