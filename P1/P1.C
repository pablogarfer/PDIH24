#include <stdio.h>
#include <dos.h>
#include <string.h>

#define BYTE unsigned char

BYTE txtcolor = 1;
BYTE bgcolor = 0;

void mi_pausa(){
    union REGS inregs, outregs;
    inregs.h.ah = 8;
    int86(0x21, &inregs, &outregs);
}

void mi_exit(){
	union REGS inregs, outregs;
	inregs.x.ax = 0x4C00;
	int86(0x21, &inregs, &outregs);
}

void clrscr(){
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void gotoxy(int x, int y){
    union REGS inregs, outregs;
    inregs.h.ah = 0x02;
    inregs.h.bh = 0x00;
    inregs.h.dh = y;
    inregs.h.dl = x;
    int86(0x10,&inregs,&outregs);
    return;
}

void setcursortype(int tipo_cursor){
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;
    switch(tipo_cursor){
        case 0: //Invisible
            inregs.h.ch = 010;
            inregs.h.cl = 000;
            break;
        case 1: //Normal
            inregs.h.ch = 010;
            inregs.h.cl = 010;
            break;
        case 2: //Grueso
            inregs.h.ch = 000;
            inregs.h.cl = 010;
            break;
    }
    int86(0x10, &inregs, &outregs);
}

void setvideomode(BYTE modo){
    union REGS inregs, outregs;
    inregs.h.al = modo;
    inregs.h.ah = 0x00;
    int86(0x10, &inregs, &outregs);
}

void pixel(int x, int y, BYTE C){
    union REGS inregs, outregs;
    inregs.x.cx = x;
    inregs.x.dx = y;
    inregs.h.al = C;
    inregs.h.ah = 0x0C;
    int86(0x10, &inregs, &outregs);
}

char getvideomode(){
    union REGS inregs, outregs;
    inregs.h.ah = 0x0F;
    int86(0x10, &inregs, &outregs);
    return outregs.h.al;
}

void getch(){  
    union REGS inregs, outregs;
	char caracter;

	inregs.h.ah = 1;
	int86(0x21, &inregs, &outregs);

	caracter = outregs.h.al;
	printf("\nSe ha pulsado: %c", caracter);
}

void textcolor(BYTE color){
    txtcolor = color;
}

void backgroundcolor(BYTE color){
    bgcolor = color;
}

void cputchar(char c){
    union REGS inregs, outregs;
	inregs.h.ah = 0x09;
	inregs.h.al = c;   
	inregs.h.bl = bgcolor << 4 | txtcolor;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;
	int86(0x10,&inregs,&outregs);
}

void asciiart(){
    clrscr();
    gotoxy(21,10);
    printf("(\\_/)");
    gotoxy(20,11);
    printf("(=^.^=)");
    gotoxy(19,12);
    printf("('')_('')");
}


int main(){
    int mode;
    clrscr();
    printf("\nGotoxy: Coloca el cursor en una posición determinada");

    gotoxy(20,20);
    printf("XX");       
    printf("\nPulsa una tecla para continuar");
    mi_pausa();
    clrscr();

    printf("\nSetcursortype: Fija el aspecto del cursor");

    printf("\nCursor invisible: ");
    setcursortype(0);
    mi_pausa();
    printf("\nCursor grueso: ");
    setcursortype(2);
    mi_pausa();
    printf("\nCursor normal: ");
    setcursortype(1);
    mi_pausa();

    printf("\nPulsa una tecla para continuar");
    mi_pausa();

    printf("\nSetvideomode: Fijar el modo de video");
    setvideomode(4); //Modo gráfico de 4 colores
    pixel(10,40,0);
    pixel(15,50,1);
    pixel(20,60,2);
    pixel(25,70,3);

    mi_pausa();
    setvideomode(3); //Modo texto 16 colores

    printf("\nPulsa una tecla para continuar");
    mi_pausa();

    printf("\nGetvideomode: Obtener el modo de video actual");
    mode = getvideomode();
    printf("\nModo de video %i", mode);
    mi_pausa();

    printf("\nPulsa una tecla para continuar");
    mi_pausa();

    printf("\nGetch: Se captura una tecla y se imprime por pantalla");
    getch();

    printf("\nPulsa una tecla para continuar");
    mi_pausa();

    printf("\nTextcolor, background color y cputchar: Modifica color de primer plano, fondo y poner un caracter");
    textcolor(1);
    backgroundcolor(4);
    cputchar('A');

    mi_pausa();

    textcolor(128);
    backgroundcolor(2);
    cputchar('A');

    mi_pausa();
    asciiart();
    mi_pausa();

    mi_exit();
}