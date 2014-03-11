#include <stdio.h>
#include <stdlib.h>
#include <fg.h>
#include "node.h"
#include <dos.h>

/*********************/
void menu()
{
char		in='w';
fg_box_t	qbox, vbox, sbox, lbox, rbox, statbox, cbox, screen;
fg_msm_cursor_t arrow = {arrow_matrix,{0,0,7,14}, 0, 14};
unsigned int 	status, last_status;
fg_coord_t 	x, y;
int		stop=0, response;
fg_color_t far	*scrcol;

screen [FG_X1] = BL;
screen [FG_Y1] = 80;
screen [FG_X2] = BR;
screen [FG_Y2] = 170;
if((scrcol = farmalloc(fg_box_area(screen)*sizeof(fg_color_t)))==NULL){
	fprintf(stderr,"memory failure saving screen area\n");
        getch();
        exit(1);
        }
        
if(going==NO){
	fg_fillbox(FG_BLACK,FG_MODE_SET,~0,fg.displaybox);
        fg_readbox(screen, scrcol);
        }
else        
	fg_readbox(screen, scrcol);

qbox [FG_X1] = BL;
qbox [FG_Y1] = 140;
qbox [FG_X2] = BR;
qbox [FG_Y2] = 149;

lbox [FG_X1] = BL;
lbox [FG_Y1] = 130;
lbox [FG_X2] = BR;
lbox [FG_Y2] = 139;

rbox [FG_X1] = BL;
rbox [FG_Y1] = 120;
rbox [FG_X2] = BR;
rbox [FG_Y2] = 129;

vbox [FG_X1] = BL;
vbox [FG_Y1] = 110;
vbox [FG_X2] = BR;
vbox [FG_Y2] = 119;

sbox [FG_X1] = BL;
sbox [FG_Y1] = 100;
sbox [FG_X2] = BR;
sbox [FG_Y2] = 109;

statbox [FG_X1] = BL;
statbox [FG_Y1] = 90;
statbox [FG_X2] = BR;
statbox [FG_Y2] = 99;

cbox [FG_X1] = BL;
cbox [FG_Y1] = 80;
cbox [FG_X2] = BR;
cbox [FG_Y2] = 89;

strcpy(statfile,"tmp.stt");
fg_msm_setcursor(arrow);
fg_msm_setcurpos(fg_box_width(fg_displaybox)/2, fg_box_height(fg_displaybox)/2);
fg_msm_showcursor();     

/* stall while left button still depressed */
status = fg_msm_getstatus(&x, &y);
while(status==FG_MSM_LEFT){
	last_status = status;
	status = fg_msm_getstatus(&x, &y);	
        }

while(!stop){
	fg_msm_setratio(128,256);
	fg_msm_motion(0);
	fg_puts(FG_GRAY, FG_MODE_SET, ~0, FG_ROT0, 132, 158,"Menu",fg.displaybox);	
	fg_puts(FG_RED, FG_MODE_SET, ~0, FG_ROT0, 130, 160,"Menu",fg.displaybox);
        fg_fillbox(20,FG_MODE_SET,~0,qbox);
        fg_fillbox(21,FG_MODE_SET,~0,lbox);
        fg_fillbox(22,FG_MODE_SET,~0,rbox);
	fg_puts(54, FG_MODE_SET, ~0, FG_ROT0, 110, 140,"Quit",fg.displaybox);	
	fg_puts(53, FG_MODE_SET, ~0, FG_ROT0, 110, 130,"Load world",fg.displaybox);	
	fg_puts(52, FG_MODE_SET, ~0, FG_ROT0, 110, 120,"starT world",fg.displaybox);	
        if(going==YES){        	
	        fg_fillbox(23,FG_MODE_SET,~0,vbox);
        	fg_fillbox(24,FG_MODE_SET,~0,sbox);
	        fg_fillbox(25,FG_MODE_SET,~0,statbox);
        	fg_fillbox(26,FG_MODE_SET,~0,cbox);
		fg_puts(49, FG_MODE_SET, ~0, FG_ROT0, 110, 90,"Graphs",fg.displaybox);	
	        fg_puts(48, FG_MODE_SET, ~0, FG_ROT0, 110, 80,"Continue",fg.displaybox);
		fg_puts(51, FG_MODE_SET, ~0, FG_ROT0, 110, 110,"View nets",fg.displaybox);        
		fg_puts(50, FG_MODE_SET, ~0, FG_ROT0, 110, 100,"Save world",fg.displaybox);
        	}         
        response=0;
	while(!response){
		fg_flush();
		last_status = status;
		status = fg_msm_getstatus(&x, &y);	        
		if(kbhit()) in = getch();
		if((in == 'q')||((fg_pt_inbox(qbox, x, y))&&(status == FG_MSM_LEFT))){
			get_release(54,110,140,"Quit");
       	                fg_writebox(screen,scrcol);
                	if(CheckExit()==YES){
	                	fclose(sfp);
        	                free_all_orgs();
				fg_term(); 
                                farfree(scrcol);
                        	exit(0);
                                }
			else{
                        	in = 'w';
			     	response++;                           
                                fg_writebox(screen,scrcol);
                                }                                
			}
		else if(((in == 'v')||((fg_pt_inbox(vbox, x, y))&&(status == FG_MSM_LEFT)))&&(going==YES)){
			get_release(51,110,110,"View nets");
                        in = 'w';
                        if(root!=NULL){
	                	fg_msm_hidecursor();
        	        	fg_term();
				fg_init_tridenthires();
		        	show_orgs();	                       
        	                fg_term();
                	        fg_init_vga13();
                        	print_world();
	                        fg_msm_setcurpos(fg_box_width(fg_displaybox)/2, fg_box_height(fg_displaybox)/2);
        	                fg_msm_showcursor();
        		        response++;
                                }
        		}       
		else if(((in == 's')||((fg_pt_inbox(sbox, x, y))&&(status == FG_MSM_LEFT)))&&(going==YES)){
			get_release(50,110,100,"Save world");
                        in = 'w';
                        if(root!=NULL){
	                	fg_msm_hidecursor();
                        	fg_term();
                	        save_world();
        	                fg_init_vga13();
	                        fg_msm_setcurpos(fg_box_width(fg_displaybox)/2, fg_box_height(fg_displaybox)/2);
                        	fg_msm_showcursor();
                	        print_world();        	                
	                	response++;
                        	}
			}
		else if((in == 'l')||((fg_pt_inbox(lbox, x, y))&&(status == FG_MSM_LEFT))){
			get_release(53,110,130,"Load world");
        		free_all_orgs();
                	fg_msm_hidecursor();
			fg_term();
			load_world();
                        fg_init_vga13();
                        print_world();
                        fg_msm_setcurpos(fg_box_width(fg_displaybox)/2, fg_box_height(fg_displaybox)/2);
                        fg_msm_showcursor();
                        fg_readbox(screen, scrcol);
                        in = 'w';
                        going = YES;
        	        response++;
			}    
		else if((in == 't')||((fg_pt_inbox(rbox, x, y))&&(status == FG_MSM_LEFT))){
			get_release(52,110,120,"starT world");
                	fclose(sfp);
                	open_stats_file(NEW);
			cycles=0;
			numspawned=0;        
			free_all_orgs();
                        fg_writebox(screen,scrcol);
        	        create_world();
                        print_world();
                	numorgs=12;
	                create_orgs();                
                        in = 'w';
                        going = YES;
	                response++;
                        stop++;
			}                                     
		else if(((in == 'g')||((fg_pt_inbox(statbox, x, y))&&(status == FG_MSM_LEFT)))&&(going==YES)){
			get_release(49,110,90,"Graphs");
                        in = 'w';
                        /* stop bug - does not like small samples < 3 ... */
                        if(cycles>300.0){
	                	fg_msm_hidecursor();
        			fg_term();
                	        read_stats();
        	                fg_init_vga13();
	                        print_world();
                        	fg_msm_setcurpos(fg_box_width(fg_displaybox)/2, fg_box_height(fg_displaybox)/2);
                	        fg_msm_showcursor();        	                        
	                	response++;                
                        	}
	        	}                        
		else if(((in == 'c')||((fg_pt_inbox(cbox, x, y))&&(status == FG_MSM_LEFT)))&&(going==YES)){
                        get_release(48,110,80,"Continue");
                        in = 'w';
                        if(root!=NULL){                        	
                	        fg_writebox(screen,scrcol);
        	                response++;
	        	        stop++;
                        	}
	        	}        
	        }
	}           
if(root==NULL)
	going=NO;             
fg_msm_hidecursor();
farfree(scrcol);
}	

/**********************/
void get_release(col,x,y,text)
int	col, x, y;
char	*text;
{
unsigned int 	status, last_status;
fg_coord_t 	xx, yy;

fg_puts(FG_YELLOW,FG_MODE_SET,~0,FG_ROT0,x,y,text,fg.displaybox);
status = fg_msm_getstatus(&xx, &yy);
while(status==FG_MSM_LEFT){
	last_status = status;
	status = fg_msm_getstatus(&xx, &yy);	
	}	
fg_puts(col,FG_MODE_SET,~0,FG_ROT0,x,y,text,fg.displaybox);
}

