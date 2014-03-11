#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include <dos.h>
#include <fg.h>
#include <process.h>
#include <disp.h>

/********************/
char *get_file_name()
{
char		c,*name,tmp[20];

name = calloc(13,sizeof(char));
disp_open();
disp_setattr(0x17);
disp_box(0,DISP_NORMAL,15,20,17,32);
disp_move(16,21);
disp_flush();
gets(tmp);
disp_close();

strncpy(name,tmp,MIN(strlen(tmp),8));
return(name);
}

/********************/
void save_world()
{
FILE		*fp;
int		i, j, k, size;
struct organism *org;
char		*file, *sfile;
 
sfile = calloc(13,sizeof(char));

print_files("*.wor");
file = get_file_name();	/* return 8 digit string */
strcpy(sfile, file);
strcat(file,".wor\0");         
strcat(sfile,".stt\0");
fclose(sfp);
file_rename(statfile,sfile);
open_stats_file(OLD);
 
fp = fopen(file,"wb");
size = sizeof(int);
fwrite(&cycles,sizeof(double),1,fp);
fwrite(&numspawned,sizeof(double),1,fp);
fwrite(&numorgs,size,1,fp);
for(i=0;i<ISIZE;i++)
	for(j=0;j<JSIZE;j++)
        	fwrite(&world[i][j],size,1,fp);             
org = root;                
for(k=0;k<numorgs;k++){
	fwrite(&org->i,size,1,fp);
        fwrite(&org->j,size,1,fp);
        fwrite(&org->energy,size,1,fp);
        fwrite(&org->maxenergy,size,1,fp);
        fwrite(&org->age,size,1,fp);
        fwrite(&org->gen,size,1,fp);
        fwrite(&org->col,size,1,fp);
        fwrite(&org->mutants,size,1,fp);
        fwrite(&org->kids,size,1,fp);  
        fwrite(&org->numcells,size,1,fp);           
        fwrite(&org->current_cell,size,1,fp);     
        fwrite(&org->dir,size,1,fp);
        for(i=0;i<org->numcells;i++)
        	for(j=0;j<NUMINPUTS;j++){
                 	fwrite(&org->cells[i]->inout[j],size,1,fp);
		        fwrite(&org->cells[i]->next[j],size,1,fp);		                      
                        }                               	
	org = org->next;
        }      
free(file);     
free(sfile);   
fclose(fp);
}

/********************/
void load_world()
{
FILE	*fp;
int	i, j, size;
struct organism *tmp;
char		*file,*sfile;

print_files("*.wor");  
sfile = calloc(13,sizeof(char));
file = get_file_name();	/* return 8 digit string */
strcpy(sfile, file);
strcat(file,".wor\0");         
strcat(sfile,".stt\0");
fclose(sfp);
file_rename(sfile,statfile);
open_stats_file(OLD);

fp = fopen(file,"rb");	/* just remember the binary in future!!*/
size = sizeof(int);
fread(&cycles,		sizeof(double),1,fp);
fread(&numspawned,	sizeof(double),1,fp);
fread(&numorgs,		size,1,fp);
for(i=0;i<ISIZE;i++)
	for(j=0;j<JSIZE;j++)
        	fread(&world[i][j],size,1,fp);
root = read_org(fp);
tmp = root;
for(i=1;i<numorgs;i++){
	tmp->next = read_org(fp);
        tmp = tmp->next; 
        } 
tmp->next = NULL;
free(file);
free(sfile);
fclose(fp);
}

/********************/
struct organism *read_org(fp)
FILE	*fp;
{
int j, k, size;
struct organism	*tmp;

size = sizeof(int);
if((tmp = calloc(1, sizeof(struct organism))) == NULL){
	printf("no memory to load organisms\n");
        exit(1);
       	}
fread(&tmp->i,			size,1,fp);
fread(&tmp->j,			size,1,fp);
fread(&tmp->energy,		size,1,fp);
fread(&tmp->maxenergy,		size,1,fp);
fread(&tmp->age,		size,1,fp);
fread(&tmp->gen,		size,1,fp);
fread(&tmp->col,		size,1,fp);
fread(&tmp->mutants,		size,1,fp);
fread(&tmp->kids,		size,1,fp);
fread(&tmp->numcells,		size,1,fp);
fread(&tmp->current_cell,	size,1,fp);
fread(&tmp->dir,		size,1,fp);
if((tmp->cells = calloc(tmp->numcells, sizeof(struct cell *))) == NULL){
	printf("no memory to load organism nodes\n");
	exit(1);
       	}
for(j=0;j<tmp->numcells;j++){
        if((tmp->cells[j] = calloc(1,sizeof(struct cell))) == NULL){
                printf("can't allocate mem to 'load a node'\n");
                exit(1);
                }
        for(k=0;k<NUMINPUTS;k++){
                fread(&tmp->cells[j]->inout[k],size,1,fp);
                fread(&tmp->cells[j]->next[k],size,1,fp);
                }          
	}                                	               
return(tmp);       
}

/*********************/
void	print_files(type)
char	*type;
{
struct FIND 	*p;
char		buff[9];
int		i,cnt=0;

printf("file listing:\n");
p = findfirst(type,0);
while(p){
	i=0;
	while(p->name[i]!='.'){
        	buff[i]=p->name[i];
                i++;
                }
	buff[i]='\0';                
        if(strcmp(buff,"tmp")!=0){
        	cnt++;
                printf("%8s ",buff);
                }
        p = findnext();
        if(cnt==6){
        	cnt=0;
		printf("\n");
                }
	}  
}

/***********************/
void file_rename(from,to)
char *from,*to;
{
if(spawnlp(0,"cp.exe","cp.exe",from,to,NULL)==-1){
	fprintf(stderr,"failure duplicating file\n");
        getch();
        }
}

