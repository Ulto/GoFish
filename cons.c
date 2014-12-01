#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <wincon.h>


/* attributes for attr_cs function */
#define F_WHITE    0x07
#define F_REVERSE  0x70
#define F_INTENSE  (0x08|0x07)
#define F_UNDRLIN  0x01

/* console/video functions */
void ConsInit(void);
void ConsExit(void);

void cls(void);
void move_cs(int,int);
void clear_cs(int,int,int);
int  disp_cs(int,int,char *);
int  attr_cs(int,int,char *,int);


static HANDLE ifh = (HANDLE)0;
static HANDLE ofh = (HANDLE)0;
static COORD curpos;

#define A_WHITE   FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN
#define A_BRIGHT  FOREGROUND_INTENSITY|A_WHITE
#define A_REVERSE BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN
#define A_UNDER   FOREGROUND_BLUE


/* ConsInit -- call this before doing any console i/o */
void ConsInit(void)
   {
   int rc;

   rc = AllocConsole();
   ifh = GetStdHandle(STD_INPUT_HANDLE);
   ofh = GetStdHandle(STD_OUTPUT_HANDLE);
   }

/* ConsExit -- call this before exiting from "main" */
void ConsExit(void)
   {
   move_cs(24,0);
   FreeConsole();
   }


/* cls -- clear screen and position cursor at lop left (home) */
/* note: this will clear a standard 25 x 80 screen space */
/*       and can be modified to clear a larger block */
void cls(void)
   {
   int rc;
   long int rc2;

   curpos.X = 0;
   curpos.Y = 0;
   rc = FillConsoleOutputCharacter(ofh,' ',25*80,curpos,&rc2);

   curpos.X = 0;
   curpos.Y = 0;
   rc = FillConsoleOutputAttribute(ofh,A_WHITE,25*80,curpos,&rc2);

   move_cs(0,0);
   }

/* move_cs -- move cursor to a specific vert/horz coordinate */
/* where 0,0 is the top left screen position */
void move_cs(vv,hh)
   int vv,hh;
   {
   int rc;

   curpos.X = hh;
   curpos.Y = vv;
   rc = SetConsoleCursorPosition(ofh,curpos);
   rc = SetConsoleTextAttribute(ofh,A_WHITE);
   }

/* clear_cs -- clear (space fill) a section at a vert/horz coordinate */
void clear_cs(vv,hh,len)
   int vv,hh,len;
   {
   int rc;
   long int rc2;

   curpos.X = hh;
   curpos.Y = vv;
   rc = FillConsoleOutputCharacter(ofh,' ',len,curpos,&rc2);

   curpos.X = hh;
   curpos.Y = vv;
   rc = FillConsoleOutputAttribute(ofh,A_WHITE,len,curpos,&rc2);
   }

/* disp_cs -- display text at a vert/horz coordinate */
/* note: this will not move the current cursor position */
int disp_cs(vv,hh,textp)
   int vv,hh;
   char *textp;
   {
   int rc,len = (int)strlen(textp);
   long int rc2;

   curpos.X = hh;
   curpos.Y = vv;
   rc = WriteConsoleOutputCharacter(ofh,textp,len,curpos,&rc2);

   return(len);
   }

/* attr_cs -- display text at a vert/horz coordinate (with color attributes) */
int attr_cs(vv,hh,textp,attr)
   int vv,hh;
   char *textp;
   int attr;
   {
   int rc,len = (int)strlen(textp);
   long int rc2;
   int mode;

   switch (attr)
      {
      case F_INTENSE:   mode = A_BRIGHT;  break;
      case F_REVERSE:   mode = A_REVERSE; break;
      case F_UNDRLIN:   mode = A_UNDER;   break;
      case F_WHITE:
      default:          mode = A_WHITE;
      }

   curpos.X = hh;
   curpos.Y = vv;
   rc = SetConsoleCursorPosition(ofh,curpos);

   rc = SetConsoleTextAttribute(ofh,(WORD)mode);

   rc = WriteConsole(ofh,textp,len,&rc2,NULL);

   return(len);
   }
