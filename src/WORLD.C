#include <stdio.h>
#include <stdlib.h>
#include <fg.h>
#include "node.h"

/***************************/
void create_world()
{
char		in;
fg_box_t	pbox, rbox, bbox, sbox, ibox, mbox, dbox;
fg_msm_cursor_t arrow = {arrow_matrix,{0,0,7,14}, 0, 14};
unsigned int 	status, last_status;
fg_coord_t 	x, y;
int		response;

pbox [FG_X1] = BL;
pbox [FG_Y1] = 140;
pbox [FG_X2] = BR;
pbox [FG_Y2] = 149;

rbox [FG_X1] = BL;
rbox [FG_Y1] = 130;
rbox [FG_X2] = BR;
rbox [FG_Y2] = 139;

bbox [FG_X1] = BL;
bbox [FG_Y1] = 120;
bbox [FG_X2] = BR;
bbox [FG_Y2] = 129;

sbox [FG_X1] = BL;
sbox [FG_Y1] = 110;
sbox [FG_X2] = BR;
sbox [FG_Y2] = 119;

ibox [FG_X1] = BL;
ibox [FG_Y1] = 100;
ibox [FG_X2] = BR;
ibox [FG_Y2] = 109;

mbox [FG_X1] = BL;
mbox [FG_Y1] = 90;
mbox [FG_X2] = BR;
mbox [FG_Y2] = 99;

dbox [FG_X1] = BL;
dbox [FG_Y1] = 80;
dbox [FG_X2] = BR;
dbox [FG_Y2] = 89;

fg_puts(FG_GRAY, FG_MODE_SET, ~0, FG_ROT0, 92, 158,"Choose Wall Layout",fg.displaybox);	
fg_puts(FG_RED, FG_MODE_SET, ~0, FG_ROT0, 90, 160,"Choose Wall Layout",fg.displaybox);
fg_fillbox(21,FG_MODE_SET,~0,pbox);
fg_fillbox(22,FG_MODE_SET,~0,rbox);
fg_fillbox(23,FG_MODE_SET,~0,bbox);
fg_fillbox(24,FG_MODE_SET,~0,sbox);
fg_fillbox(25,FG_MODE_SET,~0,ibox);
fg_fillbox(26,FG_MODE_SET,~0,mbox);
fg_fillbox(27,FG_MODE_SET,~0,dbox);
fg_puts(35, FG_MODE_SET, ~0, FG_ROT0, 110, 140,"Plain",fg.displaybox);	
fg_puts(36, FG_MODE_SET, ~0, FG_ROT0, 110, 130,"Rocky",fg.displaybox);	
fg_puts(37, FG_MODE_SET, ~0, FG_ROT0, 110, 120,"Boxed",fg.displaybox);	
fg_puts(38, FG_MODE_SET, ~0, FG_ROT0, 110, 110,"Split",fg.displaybox);	
fg_puts(39, FG_MODE_SET, ~0, FG_ROT0, 110, 100,"Inner",fg.displaybox);
fg_puts(40, FG_MODE_SET, ~0, FG_ROT0, 110, 90,"Maze",fg.displaybox);
fg_puts(41, FG_MODE_SET, ~0, FG_ROT0, 110, 80,"Diamond",fg.displaybox);

response = 0;
wipe_world();
while(!response){
	fg_flush();
	last_status = status;
	status = fg_msm_getstatus(&x, &y);	        
	if(kbhit()) in = getch();
	if((in == 'p')||((fg_pt_inbox(pbox, x, y))&&(status == FG_MSM_LEFT))){
                get_release(35,110,140,"Plain");
        	plain_world();
                response++;
		}
	else if((in == 'r')||((fg_pt_inbox(rbox, x, y))&&(status == FG_MSM_LEFT))){
                get_release(36,110,130,"Rocky");
		rock_world();
                response++;        
		}    
	else if((in == 'b')||((fg_pt_inbox(bbox, x, y))&&(status == FG_MSM_LEFT))){
                get_release(37,110,120,"Boxed");
        	box_world();
                response++;
		}
	else if((in == 's')||((fg_pt_inbox(sbox, x, y))&&(status == FG_MSM_LEFT))){
                get_release(38,110,110,"Split");
        	split_world();
                response++;
		}   
	else if((in == 'i')||((fg_pt_inbox(ibox, x, y))&&(status == FG_MSM_LEFT))){
                get_release(39,110,100,"Inner");
        	inner_world();
                response++;
		}      
	else if((in == 'm')||((fg_pt_inbox(mbox, x, y))&&(status == FG_MSM_LEFT))){
                get_release(40,110,90,"Maze");
        	maze_world();
                response++;
		}                                                 
	else if((in == 'd')||((fg_pt_inbox(dbox, x, y))&&(status == FG_MSM_LEFT))){
                get_release(41,110,80,"Diamond");
        	diamond_world();
                response++;
		}                                                 
	}                   	
}

/***************************/
void diamond_world()
{
int	i,j;

for(i=0;i<ISIZE;i++)
	for(j=0;j<JSIZE;j++){
        	if((i==0) || (i==ISIZE-1) || (j==0) || (j==JSIZE-1))
                	world[i][j] = WALL;
		else if((rand()%2) == 1)
                        world[i][j] = FOOD;  	                        
		}                        
for(i=1;i<ISIZE-1;i+=2)
	for(j=1+((int)(i/2));j<MIN(i,JSIZE-1);j+=2)
        	world[i][j] = WALL;
	                
}

/***************************/
void maze_world()
{
int i,j,k,xstep;

for(i=0;i<ISIZE;i++)
	for(j=0;j<JSIZE;j++){
        	if((i==0) || (i==ISIZE-1) || (j==0) || (j==JSIZE-1))
                	world[i][j] = WALL;
		else if((rand()%2) == 1)
                        world[i][j] = FOOD;  	                        
		}  
xstep = (int) ISIZE/4;                
for(i=1;i<4;i++){
	for(j=1;j<JSIZE-1;j++)
        	world[i*xstep][j]=WALL;
	for(j=(int)(JSIZE/2)-3;j<(int)(JSIZE/2)+4;j++)
        	world[i*xstep][j]=NOTHING;
	for(k=(i*xstep)-4;k<(i*xstep)+5;k++){  
        	world[k][(int)(JSIZE/2)-3] = WALL;
                world[k][(int)(JSIZE/2)+3] = WALL;
                }                           
        }
                
xstep = (int) ISIZE/5;                
for(i=1;i<5;i++){
	for(j=1;j<JSIZE-1;j++){
        	if(i==1)
	        	world[(i*xstep)-3][j]=WALL; 
		else if(i==4)                        
        		world[(i*xstep)+3][j]=WALL; 
                else
	        	world[i*xstep][j]=WALL; 
                }
	for(j=1;j<4;j++){
        	if(i==1)
	        	world[(i*xstep)-3][j]=NOTHING; 
		else if(i==4)                        
        		world[(i*xstep)+3][j]=NOTHING; 
                else
	        	world[i*xstep][j]=NOTHING; 
                }
	for(j=JSIZE-4;j<JSIZE-1;j++){
        	if(i==1)
	        	world[(i*xstep)-3][j]=NOTHING; 
		else if(i==4)                        
        		world[(i*xstep)+3][j]=NOTHING; 
                else
	        	world[i*xstep][j]=NOTHING; 
                }
	}                
}

/***************************/
void wipe_world()
{
int i,j;

for(i=0;i<ISIZE;i++)
	for(j=0;j<JSIZE;j++)
        	world[i][j] = NOTHING;
}

/***************************/
void split_world()
{
int i,j;

for(i=0;i<ISIZE;i++)
	for(j=0;j<JSIZE;j++){
        	if((i==0) || (i==ISIZE-1) || (j==0) || (j==JSIZE-1))
                	world[i][j] = WALL;
		else if((rand()%2) == 1)
                        world[i][j] = FOOD;  	                        
		}  
for(i=1;i<18;i++)
	world[31][i]=WALL; 
for(i=20;i<JSIZE-1;i++)
	world[31][i]=WALL;         
}

/***************************/
void plain_world()
{
int	i,j;

for(i=0;i<ISIZE;i++)
	for(j=0;j<JSIZE;j++){
        	if((i==0) || (i==ISIZE-1) || (j==0) || (j==JSIZE-1))
                	world[i][j] = WALL;
		else if((rand()%2) == 1)
                        world[i][j] = FOOD;  	                        
		}                        
}

/***************************/
void inner_world()
{
int	i,j;

for(i=0;i<ISIZE;i++)
	for(j=0;j<JSIZE;j++){
        	if((i==0) || (i==ISIZE-1) || (j==0) || (j==JSIZE-1))
                	world[i][j] = WALL;
		else if((rand()%2) == 1)
                        world[i][j] = FOOD;  	                        
		} 
for(i=10;i<(ISIZE-10);i++)
	for(j=10;j<(JSIZE-10);j++)
        	if((i==10) || (i==(ISIZE-11)) || (j==10) || (j==(JSIZE-11)))
                	world[i][j] = WALL;                               
world[30][10] = NOTHING;
world[31][10] = NOTHING;                                
}

/***************************/
void rock_world()
{
int	i,j;

for(i=0;i<ISIZE;i++)
	for(j=0;j<JSIZE;j++){
        	if((i==0) || (i==ISIZE-1) || (j==0) || (j==JSIZE-1))
                	world[i][j] = WALL;
                else {
                	if((rand()%2) == 1)
                        	world[i][j] = FOOD;  		
                        else if((rand()%10)==1)
                        	world[i][j] = WALL;
			else                                
                        	world[i][j] = NOTHING;
                        }
                }                    
}

/***************************/
void box_world()
{
int	i,j,n,x;

for(i=0;i<ISIZE;i++)
	for(j=0;j<JSIZE;j++){
        	if((i==0) || (i==ISIZE-1) || (j==0) || (j==JSIZE-1))
                	world[i][j] = WALL;
                else
                	if((rand()%2) == 1)
                        	world[i][j] = FOOD;  		
                        else
                        	world[i][j] = NOTHING;
                }                    
for(i=1;i<ISIZE-1;i++)
	world[i][20]=WALL; 
for(j=0;j<JSIZE;j++){
	world[20][j] = WALL;
        world[40][j] = WALL;
        }
for(i=22;i<39;i++){
	for(j=22;j<JSIZE;j++)
        	if(rand()%8==0) world[i][j] = WALL;
        for(n=1;n<19;n++)
        	if(rand()%15==0) world[i][n] = WALL;
        }
world[20][(rand()%14)+4] = NOTHING;
world[40][(rand()%14)+24] = NOTHING;
world[(rand()%6)+2][20] = NOTHING;
world[(rand()%6)+24][20] = NOTHING;
world[(rand()%6)+56][20] = NOTHING;                        
for(i=2;i<ISIZE-2;i++)
	if(world[i][20]==NOTHING) world[i-1][20] = NOTHING;        
for(j=2;j<JSIZE-2;j++){
	if(world[20][j]==NOTHING) world[20][j-1] = NOTHING;
        if(world[40][j]==NOTHING) world[40][j-1] = NOTHING;
        }
}

/***************************/
int CheckExit()
{
char		in;
fg_box_t	ybox, nbox;
fg_msm_cursor_t arrow = {arrow_matrix,{0,0,7,14}, 0, 14};
unsigned int 	status, last_status;
fg_coord_t 	x, y;

ybox [FG_X1] = BL;
ybox [FG_Y1] = 130;
ybox [FG_X2] = BR;
ybox [FG_Y2] = 139;

nbox [FG_X1] = BL;
nbox [FG_Y1] = 120;
nbox [FG_X2] = BR;
nbox [FG_Y2] = 129;

fg_puts(FG_GRAY, FG_MODE_SET, ~0, FG_ROT0, 107, 158,"Are You Sure ?",fg.displaybox);	
fg_puts(FG_RED, FG_MODE_SET, ~0, FG_ROT0, 105, 160,"Are You Sure ?",fg.displaybox);
fg_fillbox(21,FG_MODE_SET,~0,ybox);
fg_fillbox(22,FG_MODE_SET,~0,nbox);
fg_puts(35, FG_MODE_SET, ~0, FG_ROT0, 140, 130,"YES",fg.displaybox);	
fg_puts(36, FG_MODE_SET, ~0, FG_ROT0, 140, 120,"NO",fg.displaybox);

while(1){
	fg_flush();
	last_status = status;
	status = fg_msm_getstatus(&x, &y);	        
	if(kbhit()) in = getch();
	if((in == 'y')||((fg_pt_inbox(ybox, x, y))&&(status == FG_MSM_LEFT))){
		get_release(35,140,130,"YES");
        	return(YES);
		}
	else if((in == 'n')||((fg_pt_inbox(nbox, x, y))&&(status == FG_MSM_LEFT))){
		get_release(36,140,120,"NO");
		return(NO);        
		}                                    
	}                   	
}
