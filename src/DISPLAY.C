#include <stdio.h>
#include <stdlib.h>
#include <fg.h>
#include "node.h"


/**********************/
void show_orgs()
{
struct organism *org;
int 		i, j, num=1, total, x, y, lastnumcells=0, last;
char		key;
char		string[110];
fg_box_t	nbox, xbox, lbox, blankbox, topbox, cellbox, itembox;
fg_msm_cursor_t arrow = {arrow_matrix,{0,0,7,14}, 0, 14};
unsigned int 	status, last_status;
fg_coord_t 	xx, yy;
int		stop=0, response;
fg_color_t 	pcols[10] = {2,3,4,5,6,9,10,12,13,14};

nbox [FG_X1] = 0;
nbox [FG_Y1] = 581;
nbox [FG_X2] = 98;
nbox [FG_Y2] = 597;

lbox [FG_X1] = 0;
lbox [FG_Y1] = 561;
lbox [FG_X2] = 98;
lbox [FG_Y2] = 577;

xbox [FG_X1] = 0;
xbox [FG_Y1] = 541;
xbox [FG_X2] = 98;
xbox [FG_Y2] = 557;

topbox[FG_X1] = 100;
topbox[FG_X2] = 799;
topbox[FG_Y1] = 541;
topbox[FG_Y2] = 597;

blankbox[FG_X1] = 0;
blankbox[FG_X2] = 394;

cellbox[FG_Y1]=400;
cellbox[FG_Y2]=420;
cellbox[FG_X1]=100;
cellbox[FG_X2]=140;

fg_msm_setcursor(arrow);
fg_msm_motion(0);
fg_msm_setcurpos(fg_box_width(fg_displaybox)/2, fg_box_height(fg_displaybox)/2);
fg_msm_showcursor();     
fg_fillbox(FG_BLUE, FG_MODE_SET, ~0, nbox);
fg_fillbox(FG_BLUE, FG_MODE_SET, ~0, lbox);
fg_fillbox(FG_RED, FG_MODE_SET, ~0, xbox);
fg_drawbox(FG_LIGHT_BLUE,FG_MODE_SET,~0,FG_LINE_SOLID,nbox,fg.displaybox);
fg_drawbox(FG_LIGHT_BLUE,FG_MODE_SET,~0,FG_LINE_SOLID,lbox,fg.displaybox);
fg_drawbox(FG_LIGHT_RED,FG_MODE_SET,~0,FG_LINE_SOLID,xbox,fg.displaybox);
fg_puts(FG_WHITE, FG_MODE_SET, ~0, FG_ROT0, 10, 582, "NEXT", fg.displaybox);
fg_puts(FG_WHITE, FG_MODE_SET, ~0, FG_ROT0, 10, 562, "LAST", fg.displaybox);
fg_puts(FG_WHITE, FG_MODE_SET, ~0, FG_ROT0, 10, 542, "EXIT", fg.displaybox);          
sprintf(string,"    CYCLES: %8.0f",cycles);        
fg_puts(FG_WHITE, FG_MODE_SET, ~0, FG_ROT0, 550, 580, string,fg.displaybox);
sprintf(string,"POPULATION: %8d",numorgs);        
fg_puts(FG_WHITE, FG_MODE_SET, ~0, FG_ROT0, 550, 565, string,fg.displaybox);
sprintf(string,"   SPAWNED: %8.0f", numspawned);
fg_puts(FG_WHITE, FG_MODE_SET, ~0, FG_ROT0, 550, 550, string,fg.displaybox);
fg_drawbox(FG_BLUE,FG_MODE_SET,~0,FG_LINE_SOLID,topbox,fg.displaybox);	

show_colour_table();
show_inputs();

itembox[FG_Y1]=400;
itembox[FG_Y2]=420;
itembox[FG_X1]=0;
itembox[FG_X2]=98;
org = root;
while(!stop){	
	if(lastnumcells>org->numcells){
        	blankbox[FG_Y1]=420-(lastnumcells*22);
                blankbox[FG_Y2]=420-(org->numcells*22);
		fg_fillbox(FG_BLACK,FG_MODE_SET,~0,blankbox);  
                }                      
	lastnumcells = org->numcells;                
	itembox[FG_Y1]=400;
	itembox[FG_Y2]=420;
        show_bug_details(org, num);
	for(i=0;i<org->numcells;i++){        	
                sprintf(string,"Cell: %2d",i+1); 			
		fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,cellbox[FG_X1]-80,cellbox[FG_Y1]+3,string,fg.displaybox);
		fg_drawbox(FG_BLUE,FG_MODE_SET,~0,FG_LINE_SOLID,itembox,fg.displaybox);	
                itembox[FG_Y1]-=22;
                itembox[FG_Y2]-=22;
        	for(j=0;j<NUMINPUTS;j++){             	
                        fg_fillbox(pcols[org->cells[i]->inout[j]],FG_MODE_SET,~0,cellbox);
                	sprintf(string,"%2d",org->cells[i]->next[j]+1); 			
			fg_puts(FG_BLACK,FG_MODE_SET,~0,FG_ROT0,cellbox[FG_X1]+10,cellbox[FG_Y1]+3,string,fg.displaybox);
			cellbox[FG_X1]+=42;
                        cellbox[FG_X2]+=42;                        
                        }
		cellbox[FG_X1]=100;
                cellbox[FG_X2]=140;
                cellbox[FG_Y1]-=22;
                cellbox[FG_Y2]-=22;                        
		}  
	cellbox[FG_Y1]=400;
        cellbox[FG_Y2]=420;                  
	response=0;

	while(!response){        
	        fg_flush();
		last_status = status;
		status = fg_msm_getstatus(&xx, &yy);  
                if(kbhit())	key = getch();      
        	if((key == 'n')||((fg_pt_inbox(nbox, xx, yy))&&(status == FG_MSM_LEFT))) {        	
			get_release(FG_WHITE,10,582,"NEXT");
                        org = org->next;              
                        if(org==NULL){
                        	org = root;
                                num = 0;
                                }
                        response++;
                	num++;
                        key = 'w';
	                }                         
        	else if((key == 'l')||((fg_pt_inbox(lbox, xx, yy))&&(status == FG_MSM_LEFT))) {        	
			get_release(FG_WHITE,10,562,"LAST");
                        last = num-1;
                        if(last < 1){                                                	
                  		while(org->next!=NULL){
                                	org = org->next;
                                        num++;
                                	}	                                	         
                        	}
			else {   
                        	org = root;
                                num = 1;                            
	                        while(num!=last){
        	                	org = org->next;
                	                num++;
                        	        }                       
				}                                        
                        response++;
                        key = 'w';
	                }                          
		else if((key == 'x')||((fg_pt_inbox(xbox, xx, yy))&&(status == FG_MSM_LEFT))){
                        get_release(FG_WHITE,10,542,"EXIT");
        		stop++;
                        key = 'w';
                        response++;
                        }
		}                        
        
        }
fg_msm_hidecursor();                        
}

/************************/
void show_colour_table()
{
char		string[110];
fg_box_t	itembox;
int 		i=0;
fg_color_t 	pcols[10] = {2,3,4,5,6,9,10,12,13,14};

/* COLOUR CODING TABLE */
itembox[FG_Y1]=410;
itembox[FG_Y2]=420;
itembox[FG_X1]=440;
itembox[FG_X2]=450;

sprintf(string,"Move Left");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,itembox[FG_X2]+3,itembox[FG_Y1]-2,string,fg.displaybox);
fg_fillbox(pcols[i++],FG_MODE_SET,~0,itembox);	
itembox[FG_Y1]-=22;
itembox[FG_Y2]-=22;
sprintf(string,"Move Right");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,itembox[FG_X2]+3,itembox[FG_Y1]-2,string,fg.displaybox);
fg_fillbox(pcols[i++],FG_MODE_SET,~0,itembox);	
itembox[FG_Y1]-=22;
itembox[FG_Y2]-=22;
sprintf(string,"Move Ahead");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,itembox[FG_X2]+3,itembox[FG_Y1]-2,string,fg.displaybox);
fg_fillbox(pcols[i++],FG_MODE_SET,~0,itembox);	
itembox[FG_Y1]-=22;
itembox[FG_Y2]-=22;
sprintf(string,"Pher Left");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,itembox[FG_X2]+3,itembox[FG_Y1]-2,string,fg.displaybox);
fg_fillbox(pcols[i++],FG_MODE_SET,~0,itembox);	
itembox[FG_Y1]-=22;
itembox[FG_Y2]-=22;
sprintf(string,"Pher Right");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,itembox[FG_X2]+3,itembox[FG_Y1]-2,string,fg.displaybox);
fg_fillbox(pcols[i++],FG_MODE_SET,~0,itembox);	
itembox[FG_Y1]-=22;
itembox[FG_Y2]-=22;
sprintf(string,"Pher Ahead");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,itembox[FG_X2]+3,itembox[FG_Y1]-2,string,fg.displaybox);
fg_fillbox(pcols[i++],FG_MODE_SET,~0,itembox);	
itembox[FG_Y1]-=22;
itembox[FG_Y2]-=22;
sprintf(string,"Turn Left");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,itembox[FG_X2]+3,itembox[FG_Y1]-2,string,fg.displaybox);
fg_fillbox(pcols[i++],FG_MODE_SET,~0,itembox);	
itembox[FG_Y1]-=22;
itembox[FG_Y2]-=22;
sprintf(string,"Turn Right");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,itembox[FG_X2]+3,itembox[FG_Y1]-2,string,fg.displaybox);
fg_fillbox(pcols[i++],FG_MODE_SET,~0,itembox);	
itembox[FG_Y1]-=22;
itembox[FG_Y2]-=22;
sprintf(string,"Stay Still");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,itembox[FG_X2]+3,itembox[FG_Y1]-2,string,fg.displaybox);
fg_fillbox(pcols[i++],FG_MODE_SET,~0,itembox);	
itembox[FG_Y1]-=22;
itembox[FG_Y2]-=22;
sprintf(string,"Reproduce");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,itembox[FG_X2]+3,itembox[FG_Y1]-2,string,fg.displaybox);
fg_fillbox(pcols[i++],FG_MODE_SET,~0,itembox);	
}

/******************/
void show_inputs()
{
char		string[110];
fg_box_t	itembox;

/* TOP OF ORGANISM TABLE */
itembox[FG_Y1]=422;
itembox[FG_Y2]=538;
itembox[FG_X1]=100;
itembox[FG_X2]=140;
sprintf(string,"Nothing");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT90,115,425,string,fg.displaybox);
fg_drawbox(FG_BLUE,FG_MODE_SET,~0,FG_LINE_SOLID,itembox,fg.displaybox);	
itembox[FG_X1]+=42;
itembox[FG_X2]+=42;
sprintf(string,"Food");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT90,157,425,string,fg.displaybox);
fg_drawbox(FG_BLUE,FG_MODE_SET,~0,FG_LINE_SOLID,itembox,fg.displaybox);	
itembox[FG_X1]+=42;
itembox[FG_X2]+=42;
sprintf(string,"Wall");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT90,199,425,string,fg.displaybox);
fg_drawbox(FG_BLUE,FG_MODE_SET,~0,FG_LINE_SOLID,itembox,fg.displaybox);	
itembox[FG_X1]+=42;
itembox[FG_X2]+=42;
sprintf(string,"Same Organism");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT90,241,425,string,fg.displaybox);
fg_drawbox(FG_BLUE,FG_MODE_SET,~0,FG_LINE_SOLID,itembox,fg.displaybox);	
itembox[FG_X1]+=42;
itembox[FG_X2]+=42;
sprintf(string,"Dff Organism");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT90,283,425,string,fg.displaybox);
fg_drawbox(FG_BLUE,FG_MODE_SET,~0,FG_LINE_SOLID,itembox,fg.displaybox);	
itembox[FG_X1]+=42;
itembox[FG_X2]+=42;
sprintf(string,"Same Pheromone");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT90,325,425,string,fg.displaybox);
fg_drawbox(FG_BLUE,FG_MODE_SET,~0,FG_LINE_SOLID,itembox,fg.displaybox);	
itembox[FG_X1]+=42;
itembox[FG_X2]+=42;
sprintf(string,"Dff Pheromone");        
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT90,367,425,string,fg.displaybox);
fg_drawbox(FG_BLUE,FG_MODE_SET,~0,FG_LINE_SOLID,itembox,fg.displaybox);	
}

/************************/
void	show_bug_details(org, num)
struct organism *org;
int		num;
{
char		string[100];
fg_box_t	box;

box[FG_Y1]=422;
box[FG_Y2]=538;
box[FG_X1]=0;
box[FG_X2]=98;
fg_fillbox(FG_BLACK,FG_MODE_SET,~0,box);
fg_drawbox(FG_BLUE,FG_MODE_SET,~0,FG_LINE_SOLID,box,fg.displaybox);	

sprintf(string,"BUG %5d",num);        
fg_puts(FG_YELLOW,FG_MODE_SET,~0,FG_ROT0,box[FG_X1]+5,box[FG_Y2]-20,string,fg.displaybox);

sprintf(string,"COL %5d",org->col);
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,box[FG_X1]+5,box[FG_Y2]-40,string,fg.displaybox);

sprintf(string,"AGE %5d",org->age);   
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,box[FG_X1]+5,box[FG_Y2]-60,string,fg.displaybox);
        
sprintf(string,"GEN %5d",org->gen);   
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,box[FG_X1]+5,box[FG_Y2]-80,string,fg.displaybox);

sprintf(string,"KIDS %4d",(org->kids+org->mutants));	
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,box[FG_X1]+5,box[FG_Y2]-100,string,fg.displaybox);

box[FG_Y1]=422;
box[FG_Y2]=472;
box[FG_X1]=601;
box[FG_X2]=765;
fg_fillbox(FG_BLACK,FG_MODE_SET,~0,box);
box[FG_Y2]=442;
box[FG_X2]=700;
sprintf(string,"Energy %4d", org->energy);
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,box[FG_X1]+15,box[FG_Y2]+3,string,fg.displaybox);
sprintf(string,"0");
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,box[FG_X1]-15,box[FG_Y1]+3,string,fg.displaybox);
sprintf(string,"%4d",org->maxenergy);
fg_puts(FG_WHITE,FG_MODE_SET,~0,FG_ROT0,box[FG_X2]+3,box[FG_Y1]+3,string,fg.displaybox);
box[FG_X2] = 601 + ((int) ( MIN(MAX(0.0, org->energy), org->maxenergy) * (100.0/org->maxenergy)));
fg_fillbox(FG_RED,FG_MODE_SET,~0,box);
box[FG_X1]=MIN(box[FG_X2]+1,700);
box[FG_X2]=700;
fg_fillbox(FG_GRAY,FG_MODE_SET,~0,box);
}
