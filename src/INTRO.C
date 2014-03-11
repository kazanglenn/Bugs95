/************************************************************
	    MY INTRO SCREEN FOR FUTURE PROGRAMS...
*************************************************************/        


#include <stdio.h>
#include <fg.h>
#include <conio.h>
#include "node.h"

void intro(void)
{
fg_box_t	box;
int 		i, j;
int		arr[MMM][MMM];
int		way[MMM][MMM];

/*initialise the array*/
for(i = 0; i < MMM; i++)
	for(j = 0; j < MMM; j++){
        	if((i+j) < MMM){
                	arr[i][j] = i + j;
                        way[i][j] = UP;
                        }
		else{
                	arr[i][j] = arr[i][j-1] - 1;                        
                        way[i][j] = DOWN;
                        }
                }
                
box [FG_X1] = 0;
box [FG_X2] = 319;
/* 140-143 top    46-49 bottom */
box [FG_Y1] = 143;
box [FG_Y2] = 146;
fg_fillbox(FG_RED, FG_MODE_SET, ~0, box);
box [FG_Y1] = 43;
box [FG_Y2] = 46;
fg_fillbox(FG_RED, FG_MODE_SET, ~0, box);

fg_puts(FG_GRAY, FG_MODE_SET, ~0, FG_ROT0, 70, 15,
	"Kazan Glenn", fg.displaybox);
fg_puts(FG_GREEN, FG_MODE_SET, ~0, FG_ROT0, 68, 17,
	"Kazan Glenn", fg.displaybox);

fg_puts(FG_GRAY, FG_MODE_SET, ~0, FG_ROT0, 200, 15,
	"1995", fg.displaybox);
fg_puts(FG_GREEN, FG_MODE_SET, ~0, FG_ROT0, 198, 17,
	"1995", fg.displaybox);
        
fg_puts(FG_GRAY, FG_MODE_SET, ~0, FG_ROT0, 22, 160, 
	"Evolutionary Process Demonstration", fg.displaybox);
fg_puts(FG_RED, FG_MODE_SET, ~0, FG_ROT0, 20, 162, 
	"Evolutionary Process Demonstration", fg.displaybox);       
       
print_title(155,82);
                                                                
/* graphics loop */        
while(!kbhit()){	 	                                                                      
	for(i = 0; i < MMM; i++)
		for(j = 0; j < MMM; j++){
                	box [FG_X1] = (i*MAXDIM);
			box [FG_Y1] = (j*MAXDIM) + EXTRA;
			box [FG_X2] = (i*MAXDIM)+(MAXDIM-1);
			box [FG_Y2] = (j*MAXDIM)+(MAXDIM-1) + EXTRA;
                        fg_fillbox((arr[i][j]+(MMM+1)), FG_MODE_SET, ~0, box);                    
                        }  
	for(i = MMM; i < MMM*2; i++)
		for(j = MMM; j < MMM*2; j++){
                	box [FG_X1] = (i*MAXDIM);
			box [FG_Y1] = (j*MAXDIM) + EXTRA;
			box [FG_X2] = (i*MAXDIM)+(MAXDIM-1);
			box [FG_Y2] = (j*MAXDIM)+(MAXDIM-1) + EXTRA;
                        fg_fillbox((arr[i-MMM][j-MMM]+(MMM+1)), FG_MODE_SET, ~0, box);                        
                        }           
	for(i = MMM; i < MMM*2; i++)
		for(j = 0; j < MMM; j++){
                	box [FG_X1] = (i*MAXDIM);
			box [FG_Y1] = (j*MAXDIM) + EXTRA;
			box [FG_X2] = (i*MAXDIM)+(MAXDIM-1);
			box [FG_Y2] = (j*MAXDIM)+(MAXDIM-1) + EXTRA;
                        fg_fillbox((arr[i-MMM][j]+(MMM+1)), FG_MODE_SET, ~0, box);                       
                        }           
	for(i = 0; i < MMM; i++)
		for(j = MMM; j < MMM*2; j++){
                	box [FG_X1] = (i*MAXDIM);
			box [FG_Y1] = (j*MAXDIM) + EXTRA;
			box [FG_X2] = (i*MAXDIM)+(MAXDIM-1);
			box [FG_Y2] = (j*MAXDIM)+(MAXDIM-1) + EXTRA;
                        fg_fillbox((arr[i][j-MMM]+(MMM+1)), FG_MODE_SET, ~0, box);                        
                        }                                                                                  
	for(i = 0; i < MMM; i++)
		for(j = 0; j < MMM; j++){
                	if(way[i][j] == UP){
                        	if(arr[i][j] < MMM-1)
                                	arr[i][j]++;
                                else{
                                	way[i][j] = DOWN;
                                        arr[i][j]--;
                                        }
                        	}
                        else if(way[i][j] == DOWN){
                        	if(arr[i][j] > 0)
                                	arr[i][j]--;
				else{
                                	way[i][j] = UP;                                        
                                        arr[i][j]++;
                                        }
                        	}
                	}
        }
getch();
}


/*******************/
void print_title(x, y)
int	x, y;
{
int	i,j=30;
fg_box_t bugs_box = {0,0,88,22};
char bugs_matrix [276] =
	{
0x00,0x00,0x01,0x08,0x08,0x80,0x00,0x00,0x00,0x00,0x00,0x00,	/*                        X    X       X   X                                                 */
0x07,0xff,0x00,0xf0,0x07,0x00,0x7f,0x80,0x00,0x03,0xfc,0x00,	/*      XXXXXXXXXXX        XXXX         XXX         XXXXXXXX                     XXXXXXXX    */
0x08,0xff,0x80,0x60,0x02,0x00,0xff,0xc0,0x00,0x07,0xfe,0x00,	/*     X   XXXXXXXXX        XX           X         XXXXXXXXXX                   XXXXXXXXXX   */
0x08,0xc0,0xc0,0x60,0x02,0x01,0x80,0x60,0x00,0x0e,0x03,0x00,	/*     X   XX      XX       XX           X        XX        XX                 XXX       XX  */
0x04,0xc0,0x40,0x60,0x02,0x03,0x00,0x30,0x00,0x18,0x01,0x80,	/*      X  XX       X       XX           X       XX          XX               XX          XX */
0x00,0xc0,0x60,0x60,0x02,0x02,0x00,0x10,0x00,0x10,0x08,0x80,	/*         XX       XX      XX           X       X            X               X        X   X */
0x00,0xc0,0x20,0x60,0x02,0x02,0x00,0x00,0x00,0x10,0x08,0x80,	/*         XX        X      XX           X       X                            X        X   X */
0x00,0xc0,0x20,0x60,0x02,0x02,0x00,0x00,0x00,0x10,0x07,0x00,	/*         XX        X      XX           X       X                            X         XXX  */
0x00,0xc0,0x60,0x60,0x02,0x02,0x00,0x00,0x00,0x10,0x00,0x00,	/*         XX       XX      XX           X       X                            X              */
0x00,0xc0,0x40,0x60,0x02,0x02,0x01,0xff,0xff,0x18,0x00,0x00,	/*         XX       X       XX           X       X        XXXXXXXXXXXXXXXXX   XX             */
0x00,0xff,0xc0,0x60,0x02,0x02,0x00,0x00,0x00,0x0c,0x00,0x00,	/*         XXXXXXXXXX       XX           X       X                             XX            */
0x00,0xc0,0x40,0x60,0x02,0x02,0x01,0xff,0xff,0x07,0xfe,0x00,	/*         XX       X       XX           X       X        XXXXXXXXXXXXXXXXX     XXXXXXXXXX   */
0x01,0x80,0x60,0x60,0x02,0x02,0x00,0x08,0x02,0x00,0x03,0x00,	/*        XX        XX      XX           X       X             X         X               XX  */
0x01,0x80,0x30,0x60,0x02,0x02,0x00,0x08,0x06,0x00,0x01,0x80,	/*        XX         XX     XX           X       X             X        XX                XX */
0x03,0x00,0x10,0x60,0x02,0x02,0x00,0x08,0x0c,0x00,0x00,0x80,	/*       XX           X     XX           X       X             X       XX                  X */
0x06,0x00,0x10,0x60,0x02,0x02,0x00,0x08,0x08,0x10,0x00,0x80,	/*      XX            X     XX           X       X             X       X      X            X */
0x06,0x00,0x10,0x60,0x06,0x03,0x00,0x18,0x09,0x18,0x01,0x80,	/*      XX            X     XX          XX       XX           XX       X  X   XX          XX */
0x07,0xf0,0x30,0x78,0x1c,0x01,0x80,0x30,0x06,0x0c,0x03,0x00,	/*      XXXXXXX      XX     XXXX      XXX         XX         XX         XX     XX        XX  */
0x0c,0x1f,0xe2,0x8f,0xf0,0x00,0xff,0xe0,0x00,0x07,0xfe,0x00,	/*     XX     XXXXXXXX   X X   XXXXXXXX            XXXXXXXXXXX                  XXXXXXXXXX   */
0x18,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*    XX                  X                                                                  */
0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*   XX                                                                                      */
0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/*  XX                                                                                       */
0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	/* XX                                                                                        */
	};
for(i=0;i<5;i++)      
fg_drawmatrix(j+=2,FG_MODE_SET,~0,FG_ROT0,x--,y++,bugs_matrix,bugs_box,fg.displaybox);
}
