#include <conio.h>
#include <dos.h>

const char* const colors[] =
{
    "BLACK",
    "BLUE",
    "GREEN",
    "CYAN",
    "RED",
    "MAGENTA",
    "BROWN",
    "LIGHTGRAY"
};

void scroll(unsigned char direction, unsigned char strings_number, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2)
{
    union REGS r;

    r.h.al = strings_number;
    r.h.ah = direction;
    r.h.ch = y1 - 1;
    r.h.cl = x1 - 1;
    r.h.dh = y2 - 1;
    r.h.dl = x2 - 1;
    r.h.bh = BLACK;
    int86(0x10, &r, &r);
}

int main()
{

    unsigned char x1 = 15;
    unsigned char y1 = 8;
    unsigned char x2 = 65;
    unsigned char y2 = 18;
    unsigned char S = 3;
    short T = 800;

    int text_color, text_background;

    clrscr();
    window(x1, y1, x2, y2);
    gotoxy(1,1);

    for (text_background = 0; text_background < 8 && !kbhit(); text_background++)
    {
        textbackground(text_background);
        for (text_color = 0; text_color < 16 && !kbhit(); text_color++)
        {
            textcolor(text_color);
            cprintf("Hello, World! text: %d bg: %s ", text_color, colors[text_background]);
            scroll(7, S, x1, y1, x2, y2);
            gotoxy(1,1);
            delay(T);
        }
    }

    return 0;
}
