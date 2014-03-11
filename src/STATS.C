#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include "node.h"
#include <fg.h>

/*******************************/
int *count_species(num)
int	*num;
{
struct organism *org;
int		i, *found;

if((found=calloc(50,sizeof(int)))==NULL){
	printf("no mem for species list\n");
        exit(1);
        }
org=root;
i=0;
while(org!=NULL){
	if(!member(found,org->col,50)){
        	found[i++]=org->col;   
                (*num)++;
                }     
	org=org->next;
        }
return(found);             
}

/*******************************/
int member(f, c, s)
int	*f,c,s;
{
int i;

for(i=0;i<s;i++){
	if(*f==c)
        	return(1);
	f++;
        }
return(0);                        
}

/*******************************/
void read_stats()
{
int		no, ns, sl[50], i, j, cnt, maxpop=0, maxsp=0;
float		size;
double		c, tc, numsamps;
fg_line_t	nsline,noline,tline,index;
fg_box_t	tbox,obox,nbox,sbox;
char		buff[60];
unsigned int 	status, last_status;
fg_coord_t 	x, y;
int		end=NO,step;

obox[FG_X1]=0;
obox[FG_X2]=799;
obox[FG_Y1]=200;
obox[FG_Y2]=400;

sbox[FG_X1]=0;
sbox[FG_X2]=799;
sbox[FG_Y1]=0;
sbox[FG_Y2]=200;

nbox[FG_X1]=0;
nbox[FG_X2]=799;
nbox[FG_Y1]=400;
nbox[FG_Y2]=599;

fg_init_vesa2();
fg_drawbox(FG_WHITE,FG_MODE_SET,~0,FG_LINE_SOLID,nbox,fg.displaybox);
fg_drawbox(FG_WHITE,FG_MODE_SET,~0,FG_LINE_SOLID,obox,fg.displaybox);
fg_drawbox(FG_WHITE,FG_MODE_SET,~0,FG_LINE_SOLID,sbox,fg.displaybox);
fg_puts(FG_YELLOW, FG_MODE_SET, ~0, FG_ROT0, 350, 579,"Number of Species",fg.displaybox);
fg_puts(FG_YELLOW, FG_MODE_SET, ~0, FG_ROT0, 350, 379,"Number of Organisms",fg.displaybox);
fg_puts(FG_YELLOW, FG_MODE_SET, ~0, FG_ROT0, 350, 179,"Lineage Display",fg.displaybox);
        
tline[FG_X1]=1;
tline[FG_X2]=798;

noline[FG_X1]=0;
noline[FG_Y1]=201;
nsline[FG_X1]=0;
nsline[FG_Y1]=401;

/* read all to find out maximum cycles */
rewind(sfp);
numsamps=0.0;
while(!feof(sfp)){
        numsamps+=1.0;
	fread(&c,sizeof(double),1,sfp);
        fread(&no,sizeof(int),1,sfp);
        if(no>maxpop)	maxpop=no;
        fread(&ns,sizeof(int),1,sfp);
        if(ns>maxsp)	maxsp=ns;
        for(i=0;i<ns;i++)
        	fread(&sl[i],sizeof(int),1,sfp);
        }          
numsamps--;        
size = 800/numsamps;
if(maxpop<10)	maxpop = 10;
if(maxsp<10)	maxsp = 10;
sprintf(buff,"CYCLES: %8.0f",(numsamps-1)*STATSAMP);
fg_puts(FG_LIGHT_GREEN, FG_MODE_SET, ~0, FG_ROT0, 650, 579,buff,fg.displaybox);

/* NUMBER OF SPECIES */ 
i=0;
step=(int)(200/maxsp); 
index[FG_X1]=1;
index[FG_X2]=799;
do{
	i+=(int)(maxsp/10);
        index[FG_Y1]=399+(int)(i*step);
        index[FG_Y2]=index[FG_Y1];
	fg_drawline(FG_GRAY,FG_MODE_SET,~0,FG_LINE_DENSE_DOTTED,index);
        sprintf(buff,"%3d",i);        
	fg_puts(FG_YELLOW,FG_MODE_SET,~0,FG_ROT0,2,392+(int)(i*step),buff,fg.displaybox);         
        } while(index[FG_Y1]<575);        


/* POPULATION */        
i=0;
index[FG_X1]=1;
index[FG_X2]=799;
do{
	i++;
        index[FG_Y1]=199+(i*20);
        index[FG_Y2]=index[FG_Y1];
	fg_drawline(FG_GRAY,FG_MODE_SET,~0,FG_LINE_DENSE_DOTTED,index);
        sprintf(buff,"%3d",(int)((i*20)/(200/maxpop)));        
	fg_puts(FG_YELLOW,FG_MODE_SET,~0,FG_ROT0,2,192+(i*20),buff,fg.displaybox);     	        	               
        } while(index[FG_Y1]<375);        


/* TIME */ 
step=80;
cnt=0;
i=0;
index[FG_Y1]=1;
index[FG_Y2]=599;
do{
	cnt+=step;
	index[FG_X1]=cnt;
	index[FG_X2]=index[FG_X1];
	fg_drawline(FG_GRAY,FG_MODE_SET,~0,FG_LINE_DASH_DOTTED,index);
        sprintf(buff,"%.0f",((cnt/size)*STATSAMP));
	fg_puts(FG_YELLOW,FG_MODE_SET,~0,FG_ROT0,cnt+2,2,buff,fg.displaybox);
        } while(cnt<(800-step));

index[FG_X1]=1;
index[FG_X2]=798;
index[FG_Y2]=index[FG_Y1]=19;        
fg_drawline(FG_WHITE,FG_MODE_SET,~0,FG_LINE_SOLID,index);
                        
rewind(sfp);
for(j=0;j<numsamps;j++){
	fread(&c,sizeof(double),1,sfp);
        fread(&no,sizeof(int),1,sfp);
        fread(&ns,sizeof(int),1,sfp);

        noline[FG_X2]=(int)(j*size);
        noline[FG_Y2]=(no*(int)(200/maxpop))+199;                
        if(j>0)
	        fg_drawline(FG_LIGHT_RED,FG_MODE_SET,~0,FG_LINE_SOLID,noline);
	noline[FG_X1]=noline[FG_X2];
	noline[FG_Y1]=noline[FG_Y2];        
        
        nsline[FG_X2]=(int)(j*size);
        nsline[FG_Y2]=(ns*(int)(200/maxsp))+399;             
        if(j>0)
        	fg_drawline(FG_LIGHT_MAGENTA,FG_MODE_SET,~0,FG_LINE_SOLID,nsline);
	nsline[FG_X1]=nsline[FG_X2];
	nsline[FG_Y1]=nsline[FG_Y2];        

	for(i=0;i<ns;i++){
        	fread(&sl[i],sizeof(int),1,sfp);
                if(j>0){
	               	tbox[FG_X1]=(int)((j-1)*size);
        	        tbox[FG_X2]=(int)(j*size);
        		tbox[FG_Y1]=(sl[i]+60);
	                tbox[FG_Y2]=tbox[FG_Y1];
		        fg_fillbox(((tbox[FG_Y1]%15)+1),FG_MODE_SET,~0,tbox);
                        }
        	}            
        }              
                
/* ensure positioned at end of file */             
if(fseek(sfp,0L,SEEK_END)){
	printf("error getting to end of file\n");
        exit(1);
        }
        
while(end==NO){
        last_status = status;
	status = fg_msm_getstatus(&x, &y);
	if(status == FG_MSM_LEFT) end=YES;	
	if(kbhit()){
        	getch(); 
                end=YES; 
                }
        }
fg_term();
}

/*******************************/
void write_stats()
{
int	num=0, *species, i;

species = count_species(&num);
fwrite(&cycles,sizeof(double),1,sfp);
fwrite(&numorgs,sizeof(int),1,sfp);
fwrite(&num,sizeof(int),1,sfp);
for(i=0;i<num;i++)
	fwrite(&species[i],sizeof(int),1,sfp);
free(species);
}

/*******************************/
void open_stats_file(code)
int	code;
{
if(code == NEW){
	if((sfp = fopen(statfile,"w+b"))==NULL){
        	printf("error opening new stats file\n");
                exit(1);
                }
	}               
else{      
	if((sfp = fopen(statfile,"a+b"))==NULL){
        	printf("error opening existing stats file\n");
                exit(1);
                }
        }
}

