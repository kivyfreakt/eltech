#include <iostream.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>

#define FIRST 0
#define SECOND 1
#define NO_ONE 3

int count;

// game functions
void draw_board(char*);
char winner(char*);
void get_computer_move(char*);
void get_players_move(char*);
void announce_winner(char);
void tictactoe_multiplayer();
void tictactoe_singleplayer();
char get_fig();
void information();

// help functions
char get_key();

int main()
{
    int graph_driver,
        graph_mode,
        graph_error_code;
    char menu_item;

    detectgraph(&graph_driver, &graph_mode);
    initgraph(&graph_driver, &graph_mode, "C:\\TURBOCPP\\BGI");
    graph_error_code = graphresult();
    if (graph_error_code != grOk)
    {
        closegraph();
        cputs("Graph mode error.\n");
        return 255;
    }

    srand(time(NULL));
    while (1)
    {
        count = 0;
        clrscr();
        cleardevice();
        setbkcolor(BLACK);
        setcolor(BLUE);
        settextstyle(10,0,1);
        outtextxy(210,0,"TIC-TAC-TOE");
        outtextxy(210,60,"1. Singleplayer");
        outtextxy(210,90,"2. Multiplayer ");
        outtextxy(210,120,"3. Information ");
        outtextxy(210,150,"0. Exit ");


        line(400,200,400,500);
        line(500,200,500,500);
        line(300,300,600,300);
        line(300,400,600,400);

        line(530,230,570,270);
        line(530,270,570,230);

        circle(450,450,20);

        menu_item = get_key();

        switch (menu_item)
        {
            case 1:
                tictactoe_singleplayer();
            break;
            case 2:
                tictactoe_multiplayer();
            break;
            case 3:
                information();
            break;
            case 0:
                exit(0);
            break;
        }
    }
}

void tictactoe_multiplayer()
{
    char board[9];
    for(int i = 0; i < 9; i++)
        board[i]='a';

    draw_board(board);
    while (winner(board) == NO_ONE)
    {
        get_players_move(board);
        draw_board(board);
    }
    announce_winner(winner(board));
}

void tictactoe_singleplayer()
{
    char human;
    char board[9]; // доска
    for(int i = 0; i < 9; i++)
        board[i]='a';

    human = rand()%2;

    draw_board(board);
    while (winner(board) == NO_ONE)
    {
        if (count%2 == human)
            get_players_move(board);
        else
        {
            get_computer_move(board);
            draw_board(board);
        }
    }
    draw_board(board);
    announce_winner(winner(board));
}

void draw_board(char a[])
{
	clrscr();
	cleardevice();
	setcolor(BLUE);
	cout<<"\n\n\n\n             1            2           3\n\n\n\n\n";
	cout<<"\n             4            5           6\n\n\n\n\n";
	cout<<"\n             7            8           9\n\n\n\n\n\n";

	line(100,50,100,350);
	line(100,50,400,50);
	line(400,50,400,350);
	line(400,350,100,350);
	line(200,50,200,350);
	line(300,50,300,350);
	line(100,150,400,150);
	line(100,250,400,250);

	if(a[0] == 'x')
	{
		line(130,80,170,120);
		line(130,120,170,80);
	}
	else if(a[0] == 'o')
		circle(150,100,20);

	if(a[1] == 'x')
	{
		line(230,80,270,120);
		line(230,120,270,80);
	}
	else if(a[1] == 'o')
		circle(250,100,20);

	if(a[2] == 'x')
	{
		line(330,80,370,120);
		line(330,120,370,80);
	}
	else if(a[2] == 'o')
		circle(350,100,20);

	if(a[3] == 'x')
	{
		line(130,180,170,220);
		line(130,220,170,180);
	}
	else if(a[3] == 'o')
		circle(150,200,20);

	if(a[4] == 'x')
	{
		line(230,180,270,220);
		line(230,220,270,180);
	}
	else if(a[4] == 'o')
		circle(250,200,20);

	if(a[5] == 'x')
	{
		line(330,180,370,220);
		line(330,220,370,180);
	}
	else if(a[5] == 'o')
		circle(350,200,20);

	if(a[6] == 'x')
	{
		line(130,280,170,320);
		line(130,320,170,280);
	}
	else if(a[6] == 'o')
		circle(150,300,20);

	if(a[7] == 'x')
	{
		line(230,280,270,320);
		line(230,320,270,280);
	}
	else if(a[7] == 'o')
		circle(250,300,20);

	if(a[8] == 'x')
	{
		line(330,280,370,320);
		line(330,320,370,280);
	}
	else if(a[8] == 'o')
		circle(350,300,20);
}

char winner(char g[])
{
    if ((g[0]=='x'&&g[3]=='x'&&g[6]=='x')||
        (g[1]=='x'&&g[4]=='x'&&g[7]=='x')||
        (g[2]=='x'&&g[5]=='x'&&g[8]=='x')||
        (g[0]=='x'&&g[1]=='x'&&g[2]=='x')||
        (g[3]=='x'&&g[4]=='x'&&g[5]=='x')||
        (g[6]=='x'&&g[7]=='x'&&g[8]=='x')||
        (g[0]=='x'&&g[4]=='x'&&g[8]=='x')||
        (g[2]=='x'&&g[4]=='x'&&g[6]=='x'))
        return 0;
    else if ((g[0]=='o'&&g[3]=='o'&&g[6]=='o')||
            (g[1]=='o'&&g[4]=='o'&&g[7]=='o')||
            (g[2]=='o'&&g[5]=='o'&&g[8]=='o')||
            (g[0]=='o'&&g[1]=='o'&&g[2]=='o')||
            (g[3]=='o'&&g[4]=='o'&&g[5]=='o')||
            (g[6]=='o'&&g[7]=='o'&&g[8]=='o')||
            (g[0]=='o'&&g[4]=='o'&&g[8]=='o')||
            (g[2]=='o'&&g[4]=='o'&&g[6]=='o'))
        return 1;
    else if(g[0]!='a'&&g[1]!='a'&&g[2]!='a'&&g[3]!='a'&&g[4]!='a'&&g[5]!='a'&&g[6]!='a'&&g[7]!='a'&&g[8]!='a'&&count!=0)
        return 2;
    else
        return 3;
}

void get_players_move(char g[])
{
    char a, end;
    do {
        draw_board(g);
        if(count%2==0)
            cout<<"           Player 1: \n";
        else
            cout<<"           Player 2: \n";
        cout<<"\n           Enter 0 to exit or Enter the place to drop ";

        if(count%2==0)
            cout<<"x";
        else
            cout<<"o";

        a = get_key();

        if(a==0)
            exit(0);
        else
        {
            if(count%2==0 && g[a-1]=='a')
            {
                g[a-1]='x';
                count++;
                end = 0;
            }
            else if(count%2!=0 && g[a-1]=='a')
            {
                g[a-1]='o';
                count++;
                end = 0;
            }
            else
                end = 1;
        }
    } while(end != 0);
}

void get_computer_move(char board[])
{
    const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
    int move = 0, i = 0;
    char found = 0;

    while(!found && move < 9)
    {
        if (board[move] == 'a')
        {
            board[move] = get_fig();
            found = winner(board) == count%2;
            board[move] = 'a';
        }
        if (!found)
            ++move;
    }
    if (!found)
    {
        move = 0;
        ++count;
        while(!found && move < 9)
        {
            if (board[move] == 'a')
            {
                board[move] = get_fig();
                found = winner(board) == count%2;
                board[move] = 'a';
            }
            if (!found)
                ++move;
        }
        --count;
    }

    if (!found)
    {
         move = 0;
         while(!found && i < 9)
         {
             move = BEST_MOVES[i];
             if (board[move] == 'a')
                found = 1;
            ++i;
         }
    }

    board[move] = get_fig();
    ++count;
}

void announce_winner(char winner)
{
    if(winner == FIRST)
        cout<<"\n\n                X Wins!! Congradulations !!";
    else if (winner == SECOND)
        cout<<"\n\n                O Wins!! Congradulations !!";
    else
        cout<<"\n\n              The match is draw!!!";
    get_key();
}

char get_fig()
{
    if (count%2 == 0)
        return 'x';
    else
        return 'o';
}

void information()
{
    clrscr();
    cleardevice();
    setbkcolor(BLACK);
    setcolor(BLUE);
    settextstyle(10,0,1);
    outtextxy(210,0,"Information");

    cout<<"\n\n\n   The goal of game is to be the first player to get 3 in a row on a 3x3 grid.";
    cout<<"\n\n   The player who is playing X always goes first.";
    cout<<"\n   Players placing X and O on the board until other player has 3 in a row";
    cout<<"\n   horizontally, vertically, or diagonally or until all squares are filled.";
    cout<<"\n\n   If a player is able to draw three X or three O in a row, then he wins.";
    cout<<"\n   If all squares are filled and noboby has made a row, then its a draw.";

    line(400,200,400,500);
    line(500,200,500,500);
    line(300,300,600,300);
    line(300,400,600,400);

    line(530,230,570,270);
    line(530,270,570,230);

    circle(450,450,20);

    get_key();
}

// help functions
char get_key()
{
    union REGS in, out;
    in.h.ah = 0x10; // функция 10h ожидание ввода символа
    int86(0x16, &in, &out); // прерывание 16h
    return out.h.al - '0';
}
