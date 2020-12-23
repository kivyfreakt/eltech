#include <graphics.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

float func(float x)
{
    return cos(x/4)*cos(x/4)+sqrt(x);
}

int main()
{
    const float PI = 3.1415;
    int graph_driver,
        graph_mode,
        graph_error_code,
        width,
        height;

    float scale,
          oldx, oldy,
          newx, newy,
          max;

    detectgraph(&graph_driver, &graph_mode);
    initgraph(&graph_driver, &graph_mode, "C:\\TURBOCPP\\BGI");
    graph_error_code = graphresult();
    if (graph_error_code != grOk)
    {
        closegraph();
        cputs("ERROR\n");
        return 255;
    }

    setbkcolor(BLACK);
    setcolor(CYAN);

    width = getmaxx();
    height = getmaxy();

    // рисуем оси
    line(width/2, 0, width/2, height);
    line(0, height/2, width, height/2);

    scale = 6;
    setcolor(WHITE);

    // рисуем функцию
    oldx = 3/2 * PI;
    oldy = func(oldx);

    max = oldy;
    while (oldx < 16*PI)
    {
        newx = oldx + PI/16;
        newy = func(newx);
        line(oldx * scale + width/2, height/2 - oldy * scale, newx * scale + width/2, height/2 - newy * scale);
        oldx = newx;
        oldy = newy;
        if (max < newy)
            max = newy;
    }

    // рисуем подписи и границы
    setcolor(RED);
    moveto(width/2 + 5, height/2 + 5);
    outtext("0");

    moveto(width/2 + 5, 2);
    outtext("y");

    moveto(width - 15, height/2 + 5);
    outtext("x");

    setlinestyle(1,0,0);
    line(3/2*PI*scale+width/2, height/2 - newy*scale, 3/2*PI*scale + width/2, height/2 + 30 );
    line(16*PI*scale+width/2, height/2 - newy*scale, 16*PI*scale + width/2, height/2 + 30 );
    moveto(3/2 * PI * scale + width/2 + 5, height/2 + 30);
    outtext("3/2*PI");
    moveto(16 * PI * scale + width/2 - 40, height/2 + 30);
    outtext("16*PI");

    setcolor(WHITE);
    char s[80];
    sprintf(s, "MAX VALUE: %f", max);
    outtextxy (1, 1, s);

    getch();
    closegraph();
    return 0;
}
