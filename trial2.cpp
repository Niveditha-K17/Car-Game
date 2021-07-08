#include <conio.h>
#include <stdio.h>
#include <graphics.h>
#include <dos.h>
#include <ctype.h>
#include <stdlib.h>

static int c1;
static int c2;
static int r;
static const int i =0;
static int d;
static int count;
static int tc;
static int tc2;

void car();
void control();
void road();
void traffic(int t1,int t2);
void crash(int,int);
void initialize();
void scoreboard();
void main()
{
    int gd = DETECT, gm;
    initgraph(&gd,&gm,"..\\bgi");
    initialize();
    do
    {
		control();
		road();
    }while(i!=20);

    getch();
    closegraph();
}

void road()
{
    do
    {
	gotoxy(40,2);
	printf("SCORE:%d",count);
	gotoxy(40,3);
	printf("-PRESS E TO QUIT THE GAME");
	gotoxy(40,4);
	printf("-PRESS W TO MOVE THE CAR UP");
	gotoxy(40,5);
	printf("-PRESS A TO MOVE THE CAR LEFT");
	gotoxy(40,6);
	printf("-PRESS S TO MOVE THE CAR DOWN");
	gotoxy(40,7);
	printf("-PRESS D TO MOVE THE CAR RIGHT");
	line(10,10,10,600); //right boundary of the road
	line(200,10,200,600); //left boundary of the road
	setcolor(6);
	car();
	if(tc==500) //traffic car control
	{
	    tc=0;
	    tc2 =random(150);
	    count += 2;
	}
	traffic(tc2+15,10+tc);
	tc += 10;
	setcolor(15);
	line(105,100+r,105,200+r); //middle road
	r = r+8;
	d = d+8;
	line(105,300+d,105,400+d); //middle road
	if(r==400) // As max Y coordinate = 500
	    r =0;
	if(d==200)
	    d=-200;
	delay(50);
	clearviewport();
    }while(!kbhit());
}

void traffic(int t1,int t2)
{
    bar(t1+5,t2,t1+25,t2+60);
    ellipse(t1-1,t2+7,0,360,1,6);
    ellipse(t1+32,t2+7,0,360,1,6);
    ellipse(t1-1,t2+30,0,360,1,6);
    ellipse(t1+32,t2+30,0,360,1,6);
    crash(t1+5,t2);
}

void control()
{
    char ch;
    ch = getch();
    if(c2==-95)
	c2 = -90;
    if(c2==65)
	c2 = 60;
    switch(ch)
    {
	case 'w':
	{
	    c1 = c1+5;
	    break;
	}
	case 's':
	{
	    c1 = c1-5;
	    break;
	}
	case 'd':
	{
	    c2 = c2+5;
	    break;
	}
	case 'a':
	{
	    c2 = c2-5;
	    break;
	}
	case 'E':
	{
	    nosound();
	    exit(0);
	}

    }
}

void car()
{
    bar(100+c2,150-c1,130+c2,190-c1);
    ellipse(98+c2,157-c1,0,160,1,6);
    ellipse(132+c2,157-c1,0,160,1,6);
    ellipse(98+c2,182-c1,0,160,1,6);
    ellipse(132+c2,182-c1,0,160,1,6);

}

void initialize()
{
    c1=0,c2=0; 
    r=0,d=0;
    tc= 0,tc2=0; 
    count=0; 
}

void scoreboard()
{
    clearviewport();
    setcolor(1);
    settextstyle(2,0,100);
    outtextxy(200,125,"GAME OVER!\n");
    gotoxy(35,12);
    settextstyle(2,0,15);
    setcolor(3);
    //outtextxy(220,50,"SCORE");
    printf("SCORE: %d\n",count);
    setcolor(13);
    settextstyle(3,0,2);
    outtextxy(62,260,"Press Spacebar to play again and 'esc' to exit:\n");
    char choice;
    choice = getch();
    switch(tolower(choice))
    {
        case ' ':
            initialize();
            main();
            break;
        case 'e':
            exit(0);
            break;
        default:
            exit(0);
        
    }

}

void crash(int x1, int y1)
{
     if ( (x1+20 >=100+c2) && (x1<= 130+c2) && (y1+60>=150-c1)  && (y1<=190-c1))
	 scoreboard(); 
}
