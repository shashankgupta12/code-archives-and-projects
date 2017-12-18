#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<process.h>
#include<string.h>
void screen1();
void screen2();
void screen3();
void screen4();
void screen5();
void showdesc(char[],char[]);
void addnode(char[],char[],char[],struct ll1*);
void addheadnode(char[],char[]);
void createnode(struct ll1*,char[]);
void createheadnode(char[],char[]);
int check(char[],char[]);
int initmouse();
void hidemouse();
void showmouse();
void getcord(int*,int*,int*);
void restrictmouseptr(int,int,int,int);
union REGS in,out;
typedef struct ll
{
	char date[20];
	char time[20];
	struct ll *next;
}node;
node *head2=NULL,*temp2,*prev2;
typedef struct ll1
{
	char name[20];
	char pwd[20];
	struct ll *next;
	struct ll1 *down;
}hnode;
hnode *head1=NULL,*temp1,*prev1,*ctr=NULL;
typedef struct file_handling1
{
	char name[20];
	char pwd[20];
}file1;
file1 f1;
typedef struct file_handling2
{
	char date[20];
	char time[20];
}file2;
file2 f2;
typedef struct file_handling3
{
	char date[20];
	char time[20];
	char desc[200];
}file3;
file3 f3;
void main()
{
	int g=DETECT,m;
	char temp[25];
	FILE *fp;
	initgraph(&g,&m,"d:\\tc\\bgi");
	cleardevice();
	fp=fopen("name.txt","r");
	while(fread(&f1,sizeof(f1),1,fp)==1)
		createheadnode(f1.name,f1.pwd);
	fclose(fp);
	screen1();
	getch();
	closegraph();
}
int initmouse()
{
	in.x.ax=0;
	int86(0x33,&in,&out);
	return out.x.ax;
}
void restrictmouseptr(int x1,int y1,int x2,int y2)
{
	in.x.ax=7;
	in.x.cx=x1;
	in.x.dx=x2;
	int86(0x33,&in,&out);
	in.x.ax=8;
	in.x.cx=y1;
	in.x.dx=y2;
	int86(0x33,&in,&out);
}
void showmouse()
{
	union REGS in,out;
	in.x.ax=1;
	int86(0x33,&in,&out);
}
void hidemouse()
{
	union REGS in,out;
	in.x.ax=2;
	int86(0x33,&in,&out);
}
void getcord(int *x,int *y,int *click)
{
	union REGS in,out;
	in.x.ax=3;
	int86(0x33,&in,&out);
	*x=out.x.cx;
	*y=out.x.dx;
	*click=out.x.bx;
}
void screen5()
{
	cleardevice();
	setfillstyle(11,RED);
	bar(8,50,642,420);
	setfillstyle(11,BLUE);
	bar(28,70,622,400);
	setcolor(WHITE);
	settextstyle(0,HORIZ_DIR,2);
	outtextxy(220,110,"Project by:");
	outtextxy(220,125,"___________");
	settextstyle(0,HORIZ_DIR,3);
	outtextxy(48,180,"SAHIL UPADHYAY 13503865");
	outtextxy(48,230,"SHASHANK GUPTA 13503888");
	outtextxy(41,280,"PRINKAL AGARWAL 13503899");
	delay(5000);
	exit(0);
}
void screen4()
{
	char date[20],time[20];
	int status,x,y,click,temp1=0,temp2=0,temp3=0,ch;
	hidemouse();
	cleardevice();
	setfillstyle(7,RED);
	bar(100,50,520,150);
	settextstyle(4,HORIZ_DIR,7);
	setcolor(WHITE);
	outtextxy(140,51,"MY DIARY");
	setcolor(GREEN);
	rectangle(100,170,300,200);
	settextstyle(1,HORIZ_DIR,1);
	setcolor(WHITE);
	outtextxy(170,173,"DATE");
	setcolor(GREEN);
	rectangle(330,170,520,200);
	settextstyle(1,HORIZ_DIR,1);
	setcolor(WHITE);
	outtextxy(400,173,"TIME");
	rectangle(100,220,520,225);
	setfillstyle(1,CYAN);
	bar(580,400,750,450);
	settextstyle(1,HORIZ_DIR,2);
	setcolor(BLACK);
	outtextxy(590,412,"EXIT");
	if(status==0)
		printf("Mouse not initialized\n");
	else
	{
		showmouse();
		while(!kbhit())
		{
			getcord(&x,&y,&click);
			gotoxy(1,1);
			printf("\b\b\b\b\b\b\b\b\b\b%d %d",x,y);
			if((x>100)&&(x<300)&&(y>170)&&(y<200)&&(temp1==0)&&(ch!=1))
			{
				hidemouse();
				setfillstyle(1,0);
				bar(103,173,297,197);
				showmouse();
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					restrictmouseptr(100,170,300,200);
					gotoxy(14,12);
					hidemouse();
					fflush(stdin);
					gets(date);
					goto l9;
				}
				temp1=1;
			}
			if(!((x>100)&&(x<300)&&(y>170)&&(y<200))&&(temp1==1)&&(ch!=1))
			{
				hidemouse();
				setcolor(GREEN);
				rectangle(100,170,300,200);
				settextstyle(1,HORIZ_DIR,1);
				setcolor(WHITE);
				outtextxy(170,173,"DATE");
				temp1=0;
				showmouse();
			}
			if((x>330)&&(x<520)&&(y>170)&&(y<200)&&(temp2==0)&&(ch!=1))
			{
				hidemouse();
				setfillstyle(1,0);
				bar(333,173,517,197);
				showmouse();
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					l9:
					bar(333,173,517,197);
					restrictmouseptr(330,170,520,120);
					gotoxy(43,12);
					fflush(stdin);
					gets(time);
					ch=1;
					restrictmouseptr(0,0,getmaxx(),getmaxy());
					showdesc(date,time);
					showmouse();
				}
				temp2=1;
			}
			if(!((x>330)&&(x<520)&&(y>170)&&(y<200))&&(temp2==1)&&(ch!=1))
			{
				hidemouse();
				setcolor(GREEN);
				rectangle(330,170,520,200);
				settextstyle(1,HORIZ_DIR,1);
				setcolor(WHITE);
				outtextxy(400,173,"TIME");
				temp2=0;
				showmouse();
			}
			if((x>580)&&(x<750)&&(y>400)&&(y<450)&&(temp3==0))
			{
				setfillstyle(1,WHITE);
				hidemouse();
				bar(580,400,750,450);
				settextstyle(1,HORIZ_DIR,2);
				setcolor(BLACK);
				outtextxy(590,412,"EXIT");
				showmouse();
				temp3=1;
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					hidemouse();
					delay(500);
					screen3();
				}
			}
			if(!((x>580)&&(x<750)&&(y>400)&&(y<450))&&(temp3==1))
			{
				setfillstyle(1,CYAN);
				hidemouse();
				bar(580,400,750,450);
				settextstyle(1,HORIZ_DIR,2);
				setcolor(BLACK);
				outtextxy(590,412,"EXIT");
				showmouse();
				temp3=0;
			}
		}
	}
}
void screen3()
{
	char date[20],time[20],desc[200];
	int status,x,y,click,temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,temp6=0,ch=0;
	cleardevice();
	setfillstyle(7,RED);
	bar(100,50,520,150);
	settextstyle(4,HORIZ_DIR,7);
	setcolor(WHITE);
	outtextxy(140,51,"MY DIARY");
	setfillstyle(11,BLUE);
	bar(450,170,550,230);
	settextstyle(0,HORIZ_DIR,2);
	setcolor(WHITE);
	outtextxy(470,193,"SAVE");
	setfillstyle(11,BLUE);
	bar(450,250,550,310);
	settextstyle(0,HORIZ_DIR,2);
	setcolor(WHITE);
	outtextxy(470,273,"VIEW");
	setfillstyle(11,BLUE);
	bar(450,330,550,390);
	settextstyle(0,HORIZ_DIR,2);
	setcolor(WHITE);
	outtextxy(454,353,"LOGOUT");
	setcolor(WHITE);
	rectangle(70,170,400,390);
	setcolor(GREEN);
	rectangle(72,172,398,388);
	rectangle(74,174,234,214);
	rectangle(236,174,396,214);
	rectangle(74,216,396,386);
	settextstyle(0,HORIZ_DIR,1);
	setcolor(WHITE);
	outtextxy(84,190,"DATE");
	outtextxy(246,190,"TIME");
	outtextxy(84,232,"DIARY");
	if(status==0)
		printf("Mouse not initialised\n");
	else
	{
		showmouse();
		while(!kbhit())
		{
			getcord(&x,&y,&click);
			gotoxy(1,1);
			printf("\b\b\b\b\b\b\b\b%d %d",x,y);
			if((x>450)&&(x<550)&&(y>330)&&(y<390)&&(temp1==0))
			{
				setfillstyle(11,YELLOW);
				hidemouse();
				bar(450,330,550,390);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(454,353,"LOGOUT");
				showmouse();
				temp1=1;
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					ctr=NULL;
					hidemouse();
					delay(500);
					screen1();
				}
			}
			if(!((x>450)&&(x<550)&&(y>330)&&(y<390))&&(temp1==1))
			{
				setfillstyle(11,BLUE);
				hidemouse();
				bar(450,330,550,390);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(454,353,"LOGOUT");
				showmouse();
				temp1=0;
			}
			if((x>450)&&(x<550)&&(y>250)&&(y<310)&&(temp3==0))
			{
				setfillstyle(11,YELLOW);
				hidemouse();
				bar(450,250,550,310);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(470,273,"VIEW");
				showmouse();
				temp3=1;
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
					screen4();
			}
			if(!((x>450)&&(x<550)&&(y>250)&&(y<310))&&(temp3==1))
			{
				setfillstyle(11,BLUE);
				hidemouse();
				bar(450,250,550,310);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(470,273,"VIEW");
				showmouse();
				temp3=0;
			}
			if((x>74)&&(x<234)&&(y>174)&&(y<214)&&(temp4==0)&&(ch!=1))
			{
				hidemouse();
				setfillstyle(1,0);
				bar(76,176,232,212);
				showmouse();
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					hidemouse();
					bar(76,176,232,212);
					restrictmouseptr(74,174,234,214);
					gotoxy(12,13);
					fflush(stdin);
					gets(date);
					goto l5;
				}
				temp4=1;
			}
			if(!((x>74)&&(x<234)&&(y>174)&&(y<214))&&(temp4==1)&&(ch!=1))
			{
				hidemouse();
				settextstyle(0,HORIZ_DIR,1);
				setcolor(WHITE);
				outtextxy(84,190,"DATE");
				showmouse();
				temp4=0;
			}
			if((x>236)&&(x<396)&&(y>174)&&(y<214)&&(temp5==0)&&(ch!=1))
			{
				hidemouse();
				setfillstyle(1,0);
				bar(238,176,394,212);
				showmouse();
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					l5:
					hidemouse();
					bar(238,176,394,212);
					restrictmouseptr(236,174,396,214);
					gotoxy(32,13);
					fflush(stdin);
					gets(time);
					goto l6;
				}
				temp5=1;
			}
			if(!((x>236)&&(x<396)&&(y>174)&&(y<214))&&(temp5==1)&&(ch!=1))
			{
				hidemouse();
				settextstyle(0,HORIZ_DIR,1);
				setcolor(WHITE);
				outtextxy(246,190,"TIME");
				showmouse();
				temp5=0;
			}
			if((x>74)&&(x<396)&&(y>216)&&(y<386)&&(temp6==0)&&(ch!=1))
			{
				hidemouse();
				setfillstyle(1,0);
				bar(76,218,394,384);
				showmouse();
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					l6:
					hidemouse();
					bar(76,218,394,384);
					restrictmouseptr(74,216,396,386);
					gotoxy(12,15);
					fflush(stdin);
					gets(desc);
					ch=1;
					restrictmouseptr(0,0,getmaxx(),getmaxy());
					showmouse();
					showmouse();
					showmouse();
				}
				temp6=1;
			}
			if(!((x>74)&&(x<396)&&(y>216)&&(y<386))&&(temp6==1)&&(ch!=1))
			{
				hidemouse();
				settextstyle(0,HORIZ_DIR,1);
				setcolor(WHITE);
				outtextxy(84,232,"DIARY");
				showmouse();
				temp6=0;
			}
			if((x>450)&&(x<550)&&(y>170)&&(y<230)&&(temp2==0))
			{
				setfillstyle(11,YELLOW);
				hidemouse();
				bar(450,170,550,230);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(470,193,"SAVE");
				showmouse();
				temp2=1;
				in.x.ax=3;
				int86(0x33,&in,&out);
				if((out.x.bx==1)&&(ch==1))
				{
					hidemouse();
					cleardevice();
					setfillstyle(11,RED);
					bar(258,202,360,250);
					settextstyle(0,HORIZ_DIR,2);
					setcolor(WHITE);
					outtextxy(270,220,"SAVED");
					showmouse();
					addnode(date,time,desc,ctr);
					delay(2000);
					screen3();
				}
			}
			if(!((x>450)&&(x<550)&&(y>170)&&(y<230))&&(temp2==1))
			{
				setfillstyle(11,BLUE);
				hidemouse();
				bar(450,170,550,230);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(470,193,"SAVE");
				showmouse();
				temp2=0;
			}
		}
	}
}
void screen2()
{
	char name[20],email[30],pwd[20];
	int status,x,y,click,temp1=0,ch;
	cleardevice();
	setfillstyle(7,RED);
	bar(100,50,520,150);
	settextstyle(4,HORIZ_DIR,7);
	setcolor(WHITE);
	outtextxy(140,51,"MY DIARY");
	setfillstyle(1,YELLOW);
	bar(120,170,215,200);
	settextstyle(0,HORIZ_DIR,2);
	setcolor(BLACK);
	outtextxy(135,180,"NAME");
	setcolor(GREEN);
	rectangle(300,170,500,200);
	setfillstyle(1,YELLOW);
	bar(120,220,215,250);
	settextstyle(0,HORIZ_DIR,2);
	setcolor(BLACK);
	outtextxy(130,230,"EMAIL");
	setcolor(GREEN);
	rectangle(300,220,500,250);
	setfillstyle(1,YELLOW);
	bar(120,270,215,300);
	settextstyle(0,HORIZ_DIR,2);
	setcolor(BLACK);
	outtextxy(140,280,"PWD");
	setcolor(GREEN);
	rectangle(300,270,500,300);
	setfillstyle(2,BLUE);
	bar(230,340,380,393);
	settextstyle(0,HORIZ_DIR,2);
	setcolor(WHITE);
	outtextxy(242,360,"CONTINUE");
	if(status==0)
		printf("Mouse not initialised\n");
	else
	{
		showmouse();
		while(!kbhit())
		{
			getcord(&x,&y,&click);
			gotoxy(1,1);
			printf("\b\b\b\b\b\b\b\b%d %d",x,y);
			if((x>300)&&(x<500)&&(y>170)&&(y<200))
			{
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					hidemouse();
					restrictmouseptr(300,170,500,200);
					gotoxy(39,12);
					fflush(stdin);
					gets(name);
					goto l3;
				}
			}
			if((x>300)&&(x<500)&&(y>220)&&(y<250))
			{
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					l3:
					restrictmouseptr(300,220,500,250);
					gotoxy(39,15);
					fflush(stdin);
					gets(email);
					goto l4;
				}
			}
			if((x>300)&&(x<500)&&(y>270)&&(y<300))
			{
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					l4:
					restrictmouseptr(300,270,500,300);
					gotoxy(39,18);
					fflush(stdin);
					gets(pwd);
					ch=1;
					showmouse();
					restrictmouseptr(0,0,getmaxx(),getmaxy());
				}
			}
			if((x>243)&&(x<387)&&(y>350)&&(y<395)&&(temp1==0))
			{
				setfillstyle(2,YELLOW);
				hidemouse();
				bar(230,340,380,393);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(242,360,"CONTINUE");
				showmouse();
				temp1=1;
				in.x.ax=3;
				int86(0x33,&in,&out);
				if((out.x.bx==1)&&(ch==1))
				{
					addheadnode(name,pwd);
					hidemouse();
					delay(500);
					screen3();
				}
			}
			if(!((x>243)&&(x<387)&&(y>350)&&(y<395))&&(temp1==1))
			{
				setfillstyle(2,BLUE);
				hidemouse();
				bar(230,340,380,393);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(242,360,"CONTINUE");
				showmouse();
				temp1=0;
			}
		}
	}
}
void screen1()
{
	char name[20],pwd[20];
	int status,x,y,click,temp1=0,temp2=0,temp3=0,temp4=0,temp5=0,val,ch;
	cleardevice();
	setfillstyle(7,RED);
	bar(100,50,520,150);
	settextstyle(4,HORIZ_DIR,7);
	setcolor(WHITE);
	outtextxy(140,51,"MY DIARY");
	setcolor(GREEN);
	rectangle(161,174,466,220);
	settextstyle(0,HORIZ_DIR,2);
	setcolor(WHITE);
	outtextxy(245,190,"Username");
	setcolor(GREEN);
	rectangle(161,234,466,280);
	settextstyle(0,HORIZ_DIR,2);
	setcolor(WHITE);
	outtextxy(245,250,"PASSWORD");
	setfillstyle(11,BLUE);
	bar(243,300,387,343);
	settextstyle(0,HORIZ_DIR,2);
	setcolor(WHITE);
	outtextxy(275,316,"LOGIN");
	setfillstyle(11,BLUE);
	bar(243,350,387,395);
	settextstyle(0,HORIZ_DIR,2);
	setcolor(WHITE);
	outtextxy(252,365,"NEW USER");
	setfillstyle(1,CYAN);
	bar(580,400,750,450);
	settextstyle(1,HORIZ_DIR,2);
	setcolor(BLACK);
	outtextxy(590,412,"EXIT");
	status=initmouse();
	if(status==0)
		printf("Mouse not initialised\n");
	else
	{
		showmouse();
		while(!kbhit())
		{
			getcord(&x,&y,&click);
			gotoxy(1,1);
			printf("\b\b\b\b\b\b\b\b\b\b%d %d",x,y);
			if((x>161)&&(x<466)&&(y>174)&&(y<220)&&(temp4==0)&&(ch!=1))
			{
				hidemouse();
				setfillstyle(1,0);
				bar(163,175,463,217);
				showmouse();
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					restrictmouseptr(161,174,466,220);
					gotoxy(23,13);
					hidemouse();
					fflush(stdin);
					gets(name);
					goto label;
				}
				temp4=1;
			}
			if(!((x>161)&&(x<466)&&(y>174)&&(y<220))&&(temp4==1)&&(ch!=1))
			{
				hidemouse();
				setfillstyle(1,0);
				bar(161,174,466,220);
				setcolor(GREEN);
				rectangle(161,174,466,220);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(245,190,"Username");
				showmouse();
				temp4=0;
			}
			if((x>161)&&(x<466)&&(y>234)&&(y<280)&&(temp5==0)&&(ch!=1))
			{
				hidemouse();
				setfillstyle(1,0);
				bar(163,237,463,277);
				showmouse();
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					label:
					bar(163,237,463,277);
					restrictmouseptr(160,233,466,280);
					gotoxy(23,17);
					fflush(stdin);
					gets(pwd);
					val=check(name,pwd);
					if(val==1)
					{	restrictmouseptr(0,0,getmaxx(),getmaxy());
						ch=1;
						showmouse();
					}
					else
						screen1();
				}
				temp5=1;
			}
			if(!((x>161)&&(x<466)&&(y>234)&&(y<280))&&(temp5==1)&&(ch!=1))
			{
				hidemouse();
				setfillstyle(1,0);
				bar(161,234,466,280);
				setcolor(GREEN);
				rectangle(161,234,466,280);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(245,250,"PASSWORD");
				showmouse();
				temp5=0;
			}
			if((x>243)&&(x<387)&&(y>350)&&(y<395)&&(temp1==0))
			{
				setfillstyle(11,YELLOW);
				hidemouse();
				bar(243,350,387,395);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(252,365,"NEW USER");
				showmouse();
				temp1=1;
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					hidemouse();
					delay(500);
					screen2();
				}
			}
			if(!((x>243)&&(x<387)&&(y>350)&&(y<395))&&(temp1==1))
			{
				setfillstyle(11,BLUE);
				hidemouse();
				bar(243,350,387,395);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(252,365,"NEW USER");
				showmouse();
				temp1=0;
			}
			if((x>243)&&(x<387)&&(y>300)&&(y<343)&&(temp2==0))
			{
				setfillstyle(11,YELLOW);
				hidemouse();
				bar(243,300,387,343);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(275,316,"LOGIN");
				showmouse();
				temp2=1;
				in.x.ax=3;
				int86(0x33,&in,&out);
				if((out.x.bx==1)&&(ch==1))
				{
					hidemouse();
					delay(500);
					screen3();
				}
			}
			if(!((x>243)&&(x<387)&&(y>300)&&(y<343))&&(temp2==1))
			{
				setfillstyle(11,BLUE);
				hidemouse();
				bar(243,300,387,343);
				settextstyle(0,HORIZ_DIR,2);
				setcolor(WHITE);
				outtextxy(275,316,"LOGIN");
				showmouse();
				temp2=0;
			}
			if((x>580)&&(x<750)&&(y>400)&&(y<450)&&(temp3==0))
			{
				setfillstyle(1,WHITE);
				hidemouse();
				bar(580,400,750,450);
				settextstyle(1,HORIZ_DIR,2);
				setcolor(BLACK);
				outtextxy(590,412,"EXIT");
				showmouse();
				temp3=1;
				in.x.ax=3;
				int86(0x33,&in,&out);
				if(out.x.bx==1)
				{
					hidemouse();
					delay(500);
					screen5();
				}
			}
			if(!((x>580)&&(x<750)&&(y>400)&&(y<450))&&(temp3==1))
			{
				setfillstyle(1,CYAN);
				hidemouse();
				bar(580,400,750,450);
				settextstyle(1,HORIZ_DIR,2);
				setcolor(BLACK);
				outtextxy(590,412,"EXIT");
				showmouse();
				temp3=0;
			}
		}
	}
}
void showdesc(char date[],char time[])
{
	char tp[30],flag='g';
	FILE *fd;
	strcpy(tp,ctr->name);
	strcat(tp,"1.txt");
	fd=fopen(tp,"r");
	while(fread(&f3,sizeof(f3),1,fd)==1)
	{
		if((strcmp(f3.date,date)==0)&&(strcmp(f3.time,time)==0))
		{
			printf("\n\n\n\n\t\t%s",f3.desc);
			flag='f';
			break;
		}
	}
	if(flag!='f')
		printf("\n\n\n\nDate and time do not exist in diary\n\n");
}
int check(char name[],char pwd[])
{
	temp1=head1;
	while(temp1!=NULL)
	{
		if((strcmp(temp1->name,name)==0)&&(strcmp(temp1->pwd,pwd)==0))
		{
			ctr=temp1;
			return 1;
		}
		temp1=temp1->down;
	}
	return 0;
}
void addnode(char date[],char time[],char desc[],hnode *ctr)
{
	char tp[40],tp1[40];
	FILE *ft;
	FILE *fs;
	strcpy(tp,ctr->name);
	strcat(tp,".txt");
	ft=fopen(tp,"a");
	strcpy(f2.date,date);
	strcpy(f2.time,time);
	fwrite(&f2,sizeof(f2),1,ft);
	fclose(ft);
	strcpy(tp1,ctr->name);
	strcat(tp1,"1.txt");
	fs=fopen(tp1,"a");
	strcpy(f3.date,date);
	strcpy(f3.time,time);
	strcpy(f3.desc,desc);
	fwrite(&f3,sizeof(f3),1,fs);
	fclose(fs);
	head2=ctr->next;
	if(head2==NULL)
	{
		head2=(node*)malloc(sizeof(node));
		strcpy(head2->date,date);
		strcpy(head2->time,time);
		head2->next=NULL;
		ctr->next=head2;
	}
	else
	{
		prev2=head2;
		while(prev2->next!=NULL)
			prev2=prev2->next;
		temp2=(node*)malloc(sizeof(node));
		strcpy(temp2->date,date);
		strcpy(temp2->time,time);
		temp2->next=NULL;
		prev2->next=temp2;
	}
}
void addheadnode(char name[],char pwd[])
{
	FILE *ft;
	strcpy(f1.name,name);
	strcpy(f1.pwd,pwd);
	ft=fopen("name.txt","a");
	fwrite(&f1,sizeof(f1),1,ft);
	fclose(ft);
	if(head1==NULL)
	{
		head1=(hnode*)malloc(sizeof(hnode));
		strcpy(head1->name,name);
		strcpy(head1->pwd,pwd);
		head1->next=NULL;
		head1->down=NULL;
	}
	else
	{
		prev1=head1;
		while(prev1->down!=NULL)
			prev1=prev1->down;
		temp1=(hnode*)malloc(sizeof(hnode));
		strcpy(temp1->name,name);
		strcpy(temp1->pwd,pwd);
		temp1->next=NULL;
		temp1->down=NULL;
		prev1->down=temp1;
	}
}
void createnode(hnode *temp,char nm[])
{
	char tp[30];
	FILE *fs;
	strcpy(tp,nm);
	strcat(tp,".txt");
	fs=fopen(tp,"r");
	while(fread(&f2,sizeof(f2),1,fs)==1)
	{
		if(head2==NULL)
		{
			head2=(node*)malloc(sizeof(node));
			strcpy(head2->date,f2.date);
			strcpy(head2->time,f2.time);
			head2->next=NULL;
			temp->next=head2;
		}
		else
		{
			prev2=head2;
			while(prev2->next!=NULL)
				prev2=prev2->next;
			temp2=(node*)malloc(sizeof(node));
			strcpy(temp2->date,f2.date);
			strcpy(temp2->time,f2.time);
			temp2->next=NULL;
			prev2->next=temp2;
		}
	}
	fclose(fs);
}
void createheadnode(char nm[],char pwd[])
{
	if(head1==NULL)
	{
		head1=(hnode*)malloc(sizeof(hnode));
		strcpy(head1->name,nm);
		strcpy(head1->pwd,pwd);
		head1->down=NULL;
		head1->next=NULL;
		temp1=head1;
	}
	else
	{
		prev1=head1;
		while(prev1->down!=NULL)
			prev1=prev1->down;
		temp1=(hnode*)malloc(sizeof(hnode));
		strcpy(temp1->name,nm);
		strcpy(temp1->pwd,pwd);
		temp1->next=NULL;
		temp1->down=NULL;
		prev1->down=temp1;
	}
	createnode(temp1,nm);
}