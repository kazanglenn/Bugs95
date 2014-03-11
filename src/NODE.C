#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <fg.h>
#include <time.h>
#include "node.h"


/********************************/
main()
{
struct organism	*org,*tmp;
int		cnt=0;
unsigned int 	status, last_status;
fg_coord_t 	x, y;

randomize();
fg_init_vga13();
intro();
going = NO;
menu();
while(numorgs>0){
	last_status = status;
	status = fg_msm_getstatus(&x, &y);	
	if(kbhit()){getch(); menu();}
	else if(status == FG_MSM_LEFT) menu(); 
        cnt++;
        if(cnt==STATSAMP) {cnt=0; write_stats();}
	reproduce_food();
        cycles++;
        org = root;
        while(org!=NULL){
        	if(org->energy>0){
                	action(org);
                        org=org->next;
                        }
		else{
                	tmp=org->next;
                	kill(org);    
                        org=tmp;                    
                        }
		}
	if(root==NULL){
        	menu();
                }
	}                
fg_term();  
fclose(sfp);
exit(0);
}

/*******************/
int count_orgs()
{
struct organism *org;
int num = 0;

org = root;
while(org!=NULL){
	org=org->next;
        num++;
        }
return(num);
}        

/*******************/
void create_orgs()
{
int i;
struct organism *tmp;

root = makerandom();
tmp=root;
world[tmp->i][tmp->j]=ORG;
for(i=1;i<numorgs;i++){
	tmp->next = makerandom();
        tmp=tmp->next;
        world[tmp->i][tmp->j]=ORG;
        }
tmp->next = NULL;        
}

/*******************/
int getinput(org)
struct organism *org;
{
if((world[org->i+idif[org->dir]][org->j+jdif[org->dir]] <= REPRODUCE)&&
	(world[org->i+idif[org->dir]][org->j+jdif[org->dir]] != ORG))
	return(world[org->i+idif[org->dir]][org->j+jdif[org->dir]]);
else if(world[org->i+idif[org->dir]][org->j+jdif[org->dir]]==ORG)
	return(org_type((org->i+idif[org->dir]),(org->j+jdif[org->dir]),org->col));
else if((world[org->i+idif[org->dir]][org->j+jdif[org->dir]]-FIXED)==org->col)
        return(SPH);
else
        return(DPH);	                                        
}

/*******************/
int org_type(i,j,col)
int	i,j,col;
{
struct organism	*tmp;
int type=0;
static int	retvals[2] = {SORG, DORG};

tmp=root;
while(tmp!=NULL){
	/*if diff species found return 1, else 0*/
	if((tmp->i==i)&&(tmp->j==j)&&(tmp->col!=col))
        	type=1;
	tmp=tmp->next;
        }        
return(retvals[type]);                        	
}

/*******************/
int getoutput(input,org)
int input;
struct organism *org;
{
return(org->cells[org->current_cell]->inout[input]);
}

/*******************/
void randomize()
{
time_t		ntime;
srand(time(&ntime));
}

/*******************/
void action(org)
struct organism	*org;
{
int	output,input;

input = getinput(org);
output = getoutput(input,org);
if(((output==REPRODUCE)||(org->energy>org->maxenergy))&&(numorgs<MAXNUMORGS)){
	spawn(org);
        org->energy -= 2;
        }
else if(((output==REPRODUCE)||(org->energy>org->maxenergy))&&(numorgs>=MAXNUMORGS))
	org->energy -= 1;        
else
	move(org,output);        
org->current_cell = org->cells[org->current_cell]->next[input];        
org->age++;
}

/******************/
void spawn(org)
struct organism	*org;
{
struct organism	*tmp;

tmp = root;
while(tmp->next != NULL)
	tmp = tmp->next;
tmp->next = copy_values(org);        
tmp->next->next = NULL;
world[tmp->next->i][tmp->next->j]=ORG;
numorgs++;
numspawned++;
}

/*******************/
void move(org,output)
struct organism	*org;
int		output;
{
int moved,oi,oj,od;

moved = 0;
oi=org->i;
oj=org->j;
od=org->dir;
switch (output) {
	case PLEFT:{
        	switch(org->dir){
                	case NORTH:{
                        	if((world[org->i-1][org->j]) != WALL){
                                	org->i = org->i-1;
                                	org->dir = WEST;
                                        moved++;
                                        }
                                break;
                        	}
                        case EAST:{
                        	if((world[org->i][org->j+1]) != WALL){
                                	org->j = org->j+1;
	                                org->dir = NORTH;
                                        moved++;
                                	}
                                break;
                        	}                        	
                        case SOUTH:{
                        	if((world[org->i+1][org->j]) != WALL){
                                	org->i = org->i+1;
        	                        org->dir = EAST;
                                        moved++;
                                        }
                                break;                        	                        
                        	}
                        case WEST:{
                        	if((world[org->i][org->j-1]) != WALL){
                                	org->j = org->j-1;
	                                org->dir = SOUTH;
                                        moved++;
                                        }
                                break;
                        	}                                                	
                	}
        	break;
                }
	case LEFT:{
        	switch(org->dir){
                	case NORTH:{
                        	if((world[org->i-1][org->j]) != WALL){
                                	org->i = org->i-1;
                                	org->dir = WEST;
                                        moved++;
                                        }
                                break;
                        	}
                        case EAST:{
                        	if((world[org->i][org->j+1]) != WALL){
                                	org->j = org->j+1;
	                                org->dir = NORTH;
                                        moved++;
                                	}
                                break;
                        	}                        	
                        case SOUTH:{
                        	if((world[org->i+1][org->j]) != WALL){
                                	org->i = org->i+1;
        	                        org->dir = EAST;
                                        moved++;
                                        }
                                break;                        	                        
                        	}
                        case WEST:{
                        	if((world[org->i][org->j-1]) != WALL){
                                	org->j = org->j-1;
	                                org->dir = SOUTH;
                                        moved++;
                                        }
                                break;
                        	}                                                	
                	}
        	break;
                }
	case PRIGHT:{
        	switch (org->dir){
                	case NORTH:{
                        	if((world[org->i+1][org->j]) != WALL){
                                	org->i = org->i+1;
	                                org->dir = EAST;
                                        moved++;
                                        }
                                break;                        	                        
                        	}                        
                        case EAST:{
                        	if((world[org->i][org->j-1]) != WALL){
                                	org->j = org->j-1;
	                                org->dir = SOUTH;
                                        moved++;
                                        }
                                break;                        	                        
                        	}                         
                        case SOUTH:{
                        	if((world[org->i-1][org->j]) != WALL){
                                	org->i = org->i-1;
	                                org->dir = WEST;
                                        moved++;
                                        }
                                break;
                        	}                        
                        case WEST:{
                        	if((world[org->i][org->j+1]) != WALL){
                                	org->j = org->j+1;
	                                org->dir = NORTH;
                                        moved++;
                                        }
                                break;
                        	}                            
                	}
        	break;
                }                
        case RIGHT:{
        	switch (org->dir){
                	case NORTH:{
                        	if((world[org->i+1][org->j]) != WALL){
                                	org->i = org->i+1;
	                                org->dir = EAST;
                                        moved++;
                                        }
                                break;                        	                        
                        	}                        
                        case EAST:{
                        	if((world[org->i][org->j-1]) != WALL){
                                	org->j = org->j-1;
	                                org->dir = SOUTH;
                                        moved++;
                                        }
                                break;                        	                        
                        	}                         
                        case SOUTH:{
                        	if((world[org->i-1][org->j]) != WALL){
                                	org->i = org->i-1;
	                                org->dir = WEST;
                                        moved++;
                                        }
                                break;
                        	}                        
                        case WEST:{
                        	if((world[org->i][org->j+1]) != WALL){
                                	org->j = org->j+1;
	                                org->dir = NORTH;
                                        moved++;
                                        }
                                break;
                        	}                            
                	}
        	break;
                }
	case PAHEAD:{
        	switch (org->dir){
                	case NORTH:{
                        	if((world[org->i][org->j+1]) != WALL){
                                	org->j = org->j+1;
                                        moved++;
                                        }
                                break;
                        	}                            
                        case EAST:{
                        	if((world[org->i+1][org->j]) != WALL){
                                	org->i = org->i+1;
                                        moved++;
                                        }
                                break;                        	                        
                        	}                        
                        case SOUTH:{
                        	if((world[org->i][org->j-1]) != WALL){
                                	org->j = org->j-1;
                                        moved++;
                                        }
                                break;                        	                        
                        	}                             
                        case WEST:{
                        	if((world[org->i-1][org->j]) != WALL){
                                	org->i = org->i-1;
                                        moved++;
                                        }
                                break;
                        	}                        
                	}        
        	break;
                }                
        case AHEAD:{
        	switch (org->dir){
                	case NORTH:{
                        	if((world[org->i][org->j+1]) != WALL){
                                	org->j = org->j+1;
                                        moved++;
                                        }
                                break;
                        	}                            
                        case EAST:{
                        	if((world[org->i+1][org->j]) != WALL){
                                	org->i = org->i+1;
                                        moved++;
                                        }
                                break;                        	                        
                        	}                        
                        case SOUTH:{
                        	if((world[org->i][org->j-1]) != WALL){
                                	org->j = org->j-1;
                                        moved++;
                                        }
                                break;                        	                        
                        	}                             
                        case WEST:{
                        	if((world[org->i-1][org->j]) != WALL){
                                	org->i = org->i-1;
                                        moved++;
                                        }
                                break;
                        	}                        
                	}        
        	break;
                }
        case STILL:{
        	break;
        	}
	case TLEFT:{
        	switch(org->dir){
                	case NORTH:{
                        	org->dir = WEST;
                                break;
                        	}
                        case EAST:{
                        	org->dir = NORTH;
                                break;
                        	}
			case SOUTH:{
                        	org->dir = EAST;
                                break;
                        	}
			case WEST:{
                        	org->dir = SOUTH;
                                break;
                        	}                                                                
                	}
                moved++;
        	}
	case TRIGHT:{
        	switch(org->dir){
                	case NORTH:{
                        	org->dir = EAST;
                                break;
                        	}
                        case EAST:{
                        	org->dir = SOUTH;
                                break;
                        	}
			case SOUTH:{
                        	org->dir = WEST;
                                break;
                        	}
			case WEST:{
                        	org->dir = NORTH;
                                break;
                        	}                                                                
                	}
		moved++;                                
        	}                                      
	}
/* ENERGY LOSE: 1=still 2=turning on spot 3=moving around */        
if(moved>0){
	if(world[org->i][org->j]==FOOD)
        	org->energy+=25;   
	else if((world[org->i][org->j]==ORG)&&(no_orgs(org->i,org->j) > 1))
        	eat_orgs(org);	                                                 
	if((output!=TLEFT)&&(output!=TRIGHT)) 
        	org->energy -= 3;               
	else if((output==TLEFT)||(output==TRIGHT))                              
        	org->energy -= 2;
        world[org->i][org->j]=ORG;
        print_blank(oi,oj);
        print_org(org->i,org->j,org->dir,org->col);
        if((org->i!=oi)||(org->j!=oj)){
	        if(no_orgs(oi,oj)==0){
	        	if((output!=PLEFT)&&(output!=PRIGHT)&&(output!=PAHEAD)){
	        		world[oi][oj] = NOTHING;          	                        	        
        	                }
			else{
                		world[oi][oj] = org->col+FIXED;
        	                print_pheromone(oi,oj,org->col);                        
		                }
                	}
		}
	}                
else{
	print_org(org->i,org->j,org->dir,org->col);
	org->energy -= 1;	
        }
}

/*******************/
void kill(org)
struct organism	*org;
{
struct organism	*tmp, *last;

if(org==root){
	root=org->next;
        world[org->i][org->j]=NOTHING;
        print_blank(org->i,org->j);
        freeorg(org);
	}
else{
	last=root;
        tmp=root;
        while(tmp!=org){
        	last=tmp;
                tmp=tmp->next;
                }
        world[org->i][org->j]=NOTHING;
        print_blank(org->i,org->j);                
	last->next=tmp->next;
        freeorg(org);                
	}
numorgs--;        
}

/************************************************/
/* WRITTEN SO THAT ORG DOES NOT EAT ITSELF...	*/
/* IF TMP = ORG, BY STORING BOTH ENERGY'S 	*/
/* NOW NO TWO ORGS CAN SHARE A SPACE (for long)	*/
/************************************************/
void eat_orgs(org)
struct organism	*org;
{
struct organism	*tmp;

tmp=root;
/* will scan for all now...*/
while(tmp!=NULL){				/* ie not its child*/
        if((org->i==tmp->i)&&(org->j==tmp->j)&&(org!=tmp)&&(tmp->age>1)){
        	if(tmp->col!=org->col){ /* same species are peaceful..NOW */
	            	org->energy+=tmp->energy;
                        tmp->energy=0;
                        }               
                }           
	tmp=tmp->next;
        }
}                                                                


/*******************/
int no_orgs(oi,oj)
int	oi,oj;
{
struct organism	*tmp;
int num=0;

tmp=root;
while(tmp!=NULL){
	if((tmp->i==oi)&&(tmp->j==oj))
        	num++;
	tmp=tmp->next;
        }
return(num);                        	
}

/******************/
void freeorg(org)
struct organism *org;
{
int	i;

for(i=0;i<org->numcells;i++)
	free(org->cells[i]);
free(org->cells);         
free(org);        
}

/*******************/
struct organism *copy_values(parent)
struct organism *parent;
{
struct organism *tmp;
int		i, j, k, change=0, x, y;

if((tmp = calloc(1, sizeof(struct organism))) == NULL){
	printf("no memory to spawn organisms\n");
        getch();
        exit(1);
        }
tmp->current_cell = 0;
tmp->col = parent->col;
tmp->gen = parent->gen + 1;
tmp->age = 0;
tmp->mutants = 0;
tmp->kids = 0;

if(rand()%10==1){
	x=rand()%2;
        if(x==1)	tmp->maxenergy=MIN(parent->maxenergy+50,MAXEN);
	else 		tmp->maxenergy=MAX(parent->maxenergy-50,MINEN);               	
	}
else        
	tmp->maxenergy = parent->maxenergy;
/* SAME PLACE... DIFF DIR */
tmp->i = parent->i;
tmp->j = parent->j;

tmp->dir = rand()%4;
if(parent->energy > 1){
	tmp->energy = (int) parent->energy/2;
	parent->energy = (int) parent->energy/2;
        }
else 
	tmp->energy = 0;
x = rand()%40;
if(x==0){
	tmp->numcells = MAX(parent->numcells - 1, 1);
        change+=5;
        }
else if(x==1){
	tmp->numcells = MIN(MAXCELLS,parent->numcells + 1);
        change+=5;
        }
else
	tmp->numcells = parent->numcells;
if((tmp->cells = calloc(tmp->numcells, sizeof(struct cell *))) == NULL){
	printf("no memory to initialise organism nodes\n");
       	exit(1);
       	}
for(j=0;j<tmp->numcells;j++){                     
        if((tmp->cells[j] = calloc(1,sizeof(struct cell))) == NULL){
                printf("can't allocate mem for a node\n");
                exit(1);
                }
	x = rand()%parent->numcells;                
	for(k=0;k<NUMINPUTS;k++){               
        	if(j>=parent->numcells){
                	/* copy a parent cell */                	
                	if(rand()%20==1)
	                	tmp->cells[j]->inout[k] = rand()%NUMOUTPUTS;
			else
                                tmp->cells[j]->inout[k] = parent->cells[x]->inout[k];
	                tmp->cells[j]->next[k] = parent->cells[x]->next[k];
                        /*for each new node, make one connection to it*/
	                tmp->cells[rand()%(tmp->numcells-1)]->next[rand()%4] = tmp->numcells-1;
                        }
                else{
                	tmp->cells[j]->inout[k] = parent->cells[j]->inout[k];
                        tmp->cells[j]->next[k] = parent->cells[j]->next[k];
                        }
                }
	}
/* one in 8 (was 10) chance of 1 mutation on top of new/less nodes */        
if(rand()%8 == 0)        
	x = 1;        
else
	x = 0;        
/* only one change of value */
for(y=0;y<x;y++){
	if(rand()%2 == 1){
        	if(rand()%20==1)
			tmp->cells[rand()%tmp->numcells]->inout[rand()%NUMINPUTS] = rand()%NUMOUTPUTS;              
		else
        		tmp->cells[rand()%tmp->numcells]->inout[rand()%NUMINPUTS] = rand()%(NUMOUTPUTS-1);              
                }
	else
		tmp->cells[rand()%tmp->numcells]->next[rand()%NUMINPUTS] = rand()%tmp->numcells;        	               
        }

/*a new species only arises from new num states */
if((change > MAXMUTATIONS)||(tmp->numcells!=parent->numcells))
	tmp->col = (rand()%100)-10;   /*ie allow gradual change*/

if(tmp->numcells < parent->numcells)
	stop_false_calls(tmp);

if(x==0)	parent->kids++;
else		parent->mutants++;        

return(tmp);        
}

/********************************/
void stop_false_calls(org)
struct organism *org;
{
int i,j;

for(i=0;i<org->numcells;i++)
	for(j=0;j<NUMINPUTS;j++)
        	if(org->cells[i]->next[j] > (org->numcells-1))
                	org->cells[i]->next[j] = rand()%org->numcells;	                                                
}

/********************************/
struct organism *makerandom()
{
struct organism *tmp;
int		i, j, k;

if((tmp = calloc(1, sizeof(struct organism))) == NULL){
	printf("no memory to initialise separate organisms\n");
        exit(1);
        }
tmp->current_cell = 0;
tmp->col = (rand()%100)-10;
tmp->gen = 0;
tmp->age = 0;
tmp->mutants = 0;
tmp->kids = 0;
tmp->maxenergy = 600+((rand()%4)*100); 		/* 600 - 900 */
do{
	tmp->i = (rand()%(ISIZE-2))+1;
	tmp->j = (rand()%(JSIZE-2))+1;
 } while(world[tmp->i][tmp->j] == WALL);        
world[tmp->i][tmp->j] = ORG;
tmp->dir = rand()%4;
tmp->energy = tmp->maxenergy-200;	/* start energy */
tmp->numcells = 1+(rand()%5);
if((tmp->cells = calloc(tmp->numcells, sizeof(struct cell *))) == NULL){
	printf("no memory to initialise organism nodes\n");
       	exit(1);
       	}
for(j=0;j<tmp->numcells;j++){                     
        if((tmp->cells[j] = calloc(1,sizeof(struct cell))) == NULL){
                printf("can't allocate mem for a node\n");
                exit(1);
                }
	for(k=0;k<NUMINPUTS;k++){
        	if(rand()%500 == 1)
	                tmp->cells[j]->inout[k] = rand()%NUMOUTPUTS;
		else
                	tmp->cells[j]->inout[k] = rand()%(NUMOUTPUTS-1);                        
                tmp->cells[j]->next[k] = rand()%tmp->numcells;
                }
	}                       
return(tmp);        
}

/***************************/
void reproduce_food()
{
int	i,j;
int	c;

for(i=1;i<ISIZE-1;i++)
	for(j=1;j<JSIZE-1;j++)
        	if(world[i][j] == FOOD)
                	if(rand()%80 == 1){
                	c = rand()%4;
                        if((world[i+idif[c]][j+jdif[c]] == NOTHING)||(world[i+idif[c]][j+jdif[c]] > ORG)){
                        	world[i+idif[c]][j+jdif[c]] = FOOD;
                                print_plant(i+idif[c], j+jdif[c]);
                                }         
			}                                                       			
for(i=1;i<ISIZE-1;i++)
	for(j=1;j<JSIZE-1;j++)
        	if((world[i][j] == NOTHING)||(world[i][j] > ORG)){
                	if(rand()%5000==1){
                		world[i][j] = FOOD; /*reseeding*/                                                                                       	
                                print_plant(i,j);
                                }
			}                                
}


/***************************/
void print_org(i,j,dir,col)
int	i,j,dir,col;
{
int		a, m, n;

a = 0;
world[i][j] = ORG;
for(m=i*5;m<(i*5)+5;m++)
	for(n=j*5;n<(j*5)+5;n++)
        	switch(dir) {
                case NORTH:{
                	if(norg[a] != 0)
				fg_drawdot(norg[a++]+col,FG_MODE_SET,~0,m,n);                   	
                        else
                        	fg_drawdot(norg[a++],FG_MODE_SET,~0,m,n);
                        break;
                	}
                case EAST:{
                	if(eorg[a] != 0)
				fg_drawdot(eorg[a++]+col,FG_MODE_SET,~0,m,n);                   
                        else
                        	fg_drawdot(eorg[a++],FG_MODE_SET,~0,m,n);
                	break;
                	}
                case SOUTH:{
                	if(sorg[a] != 0)
	                	fg_drawdot(sorg[a++]+col,FG_MODE_SET,~0,m,n);   
                	else
                        	fg_drawdot(sorg[a++],FG_MODE_SET,~0,m,n);
                        break;
                	}
                case WEST:{
                	if(worg[a] != 0)
				fg_drawdot(worg[a++]+col,FG_MODE_SET,~0,m,n);                   
        		else
                        	fg_drawdot(worg[a++],FG_MODE_SET,~0,m,n);
                	break;                
                	}  
                }
}
/********************************/
void print_plant(i,j)
int	i,j;
{
int		a, m, n;

a = 0;
for(m=i*5;m<(i*5)+5;m++)
	for(n=j*5;n<(j*5)+5;n++)
		fg_drawdot(plant[a++],FG_MODE_SET,~0,m,n);             
}

/********************************/
void print_pheromone(i,j,c)
int	i,j,c;
{
fg_drawdot((25+c),FG_MODE_SET,~0,(i*5)+2,(j*5)+2);             
}

/********************************/
void print_blank(i, j)
int	i,j;
{
fg_box_t	box;

box [FG_X1] = (i*5);
box [FG_Y1] = (j*5);
box [FG_X2] = (i*5)+4;
box [FG_Y2] = (j*5)+4;                        	                                                             
fg_fillbox(FG_BLACK, FG_MODE_SET, ~0, box);
}

/********************************/
void print_world()
{
int		i,j,m,n,a;
fg_box_t	box;

for(i=0;i<ISIZE;i++)
	for(j=0;j<JSIZE;j++){
		if(world[i][j] == NOTHING)
                	print_blank(i,j);                                                
                else if(world[i][j] == FOOD)
                        print_plant(i,j);     
                else if(world[i][j] > ORG)
                        print_pheromone(i,j,(world[i][j]-FIXED));                                                                                                  
                else if(world[i][j] == WALL){
	               	a = 0;
                	for(m=i*5;m<(i*5)+5;m++)
                        	for(n=j*5;n<(j*5)+5;n++)
                                	fg_drawdot(wall[a++],FG_MODE_SET,~0,m,n);                                
                        }                 
                } 
}

/********************************/
void free_all_orgs()
{
int	i;
struct organism	*tmp, *org;

org = root;
while(org!=NULL){
	tmp = org->next;
        freeorg(org); 
        org = tmp;          
        }
root = NULL;        
}
