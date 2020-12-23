#include <stdio.h>
#include <conio.h>
#include <bios.h>
#include <dos.h>

#define ESC 283
#define F1 15104
#define F2 15360
#define F3 15616
#define F4 15872

int main()
{
    int ch,
        j,
        x = 26,
        y = 6;
    const int x1 = 15,
              y1 = 8,
              x2 = 65,
              y2 = 18;
    clrscr();
    window(x1,y1,x2,y2);
    textbackground(3);
    clrscr();
    textcolor(0);

    do{
        clrscr();
        gotoxy(x,y); //Переводим курсор в положение x,y
        cprintf("*");
        while (bioskey(1) == 0);  //Использование прерывания INT 16h
        ch = bioskey(0);
        switch (ch)
    	{
            case F2: //Вверх -  F2
                if (y > 1)
                    y--;
                break;
            case F3: //Вниз - F3
                if (y < y2-y1+1)
                    y++;
                break;
            case F4: //Вправо - F4
                if (x < x2-x1+1)
                    x++;
                break;
            case F1: //Влево - F1
                if (x > 1)
                    x--;
                break;
            case ESC:  //Выход - ESC
                j = 0;
                break;
            default:
            break;
    	}
    }
    while(j);
    return 0;
}
