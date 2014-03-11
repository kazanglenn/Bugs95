#define MAX(a,b)	((a)>(b)?(a):(b)) 
#define MIN(a,b)	((a)<(b)?(a):(b)) 
#define STATSAMP	100
#define	NEW		1
#define OLD		0
#define YES		1
#define NO		0
/* button limits */
#define BL		80		/* button left edge  */
#define BR		230		/* button right edge */

/*stuff for the introduction screen*/
#define MMM 	15
#define MAXDIM 	3
#define UP 	1
#define DOWN 	0
#define EXTRA	50

/*general definitions for world and orgs*/
#define MAXNUMORGS	120
#define	NUMINPUTS	7
#define NUMOUTPUTS	10
#define MAXCELLS	50
#define ISIZE		63
#define JSIZE		40
#define MAXMUTATIONS	4
#define MAXEN		2000
#define MINEN		500

/*input*/
#define NOTHING		0
#define FOOD		1
#define WALL		2
#define SORG 		3
#define DORG		4
#define SPH		5	/* same pheromone */
#define DPH		6	/* diff pheromone */

#define FIXED		20	/* to increase value of ph's */
#define ORG		7	/* one of the four WORLD value's */

/*output*/
#define LEFT		0
#define RIGHT		1
#define AHEAD		2
#define PLEFT		3	/* leave ph */
#define PRIGHT		4	/* leave ph */
#define PAHEAD		5	/* leave ph */
#define TLEFT		6
#define TRIGHT		7
#define STILL		8
#define REPRODUCE	9	/*must be at last position- least likely*/

/*organism direction*/
#define NORTH		0
#define EAST		1
#define SOUTH		2
#define WEST		3


/* graphics primitives */
static int wall[25] =  {18,19,20,21,22,
			19,20,21,22,23,
                        20,21,22,23,24,
                        21,22,23,24,25,
                        22,23,24,25,26};  
                                                                      
static int plant[25] = { 0,147, 0,150, 0,
			145,147,148, 0, 0,
                         0, 0,148, 0, 0,
                         0, 0, 0,150,152};
                                                  
static int worg[25] = {  0, 0,24, 0, 0,
			 0,40,25,40, 0,
                        22,24,25,24,22,
                        22,28,25,28,22,
                        28, 0,25, 0,28};
                        
static int eorg[25] = { 28, 0,25, 0,28,
			22,28,25,28,22,
                        22,24,25,24,22,
                         0,40,25,40, 0,
                         0, 0,25, 0, 0};
                        
static int sorg[25] = {	0, 0,22,22,28,
			0,40,24,28, 0,
                       25,25,25,25,25,
                        0,40,24,28, 0,
                        0, 0,22,22,28};
                        
static int norg[25] = {28,22,22, 0, 0,
			0,28,24,40, 0,
                       25,25,25,25,25,
                        0,28,24,40, 0,
                       28,22,22, 0, 0};

static char arrow_matrix[15] =
{
  0x80,  /* X        */
  0xc0,  /* XX       */
  0xe0,  /* XXX      */
  0xf0,  /* XXXX     */
  0xf8,  /* XXXXX    */
  0xfc,  /* XXXXXX   */
  0xfe,  /* XXXXXXX  */
  0xff,  /* XXXXXXXX */
  0xfc,  /* XXXXXX   */
  0xf8,  /* XXXXX    */
  0xf8,  /* XXXXX    */
  0xcc,  /* XX  XX   */
  0x8c,  /* X   XX   */
  0x06,  /*      XX  */
  0x06,  /*      XX  */
};

/*reproduction coordinate adjusters*/
static int jdif[4] = {1,0,-1,0};
static int idif[4] = {0,1,0,-1};                                                             

/*print out label lists*/ 
static char 	*dirs[] = {"N","E","S","W"};
static char 	*out[] = {"L","R","A","PL","PR","PA","TL","TR","S","RE"};
static char 	*in[] = {"NO","FD","WL","SO","DO","SP","DP"};

struct organism {
	int	i;
        int	j;
        int	energy;
        int	age;
        int	gen;
        int	col;
        int	mutants;
        int	kids;
        int	numcells;
        int	current_cell;
        int	dir;
        int	maxenergy;
        struct cell **cells;
        struct organism *next;
        };

struct cell {
	int	inout[NUMINPUTS];
        int	next[NUMINPUTS];
        };

struct organism *makerandom();
int 		getinput(struct organism *);
int		getoutput(int, struct organism *);
void 		reproduce_food();
void 		print_blank(int, int);
void 		print_plant(int, int);
void 		print_org(int, int, int, int);
void 		print_pheromone(int, int, int);
void		print_world();
void		create_world();
void		move(struct organism *, int);
void 		reproduce_food();
struct organism *copy_values(struct organism *);
void		freeorg(struct organism *);
void		create_orgs();
void		spawn(struct organism *);
void		kill(struct organism *);
void		randomize();
void		action(struct organism *);
void		eat_orgs(struct organism *);
int		no_orgs(int,int);
int		count_orgs();
int		org_type(int, int, int);
void		intro();
void		stop_false_calls(struct organism *);
void 		menu();
void		show_orgs();
void		save_world();
void		load_world();
void		free_all_orgs();
struct organism *read_org(FILE *);
void		print_files(char *);
int		member(int *, int, int);
int		*count_species(int *);
void 		write_stats();
void		read_stats();
void		open_stats_file(int);
void		file_rename(char *, char *);
void		plain_world();
void		rock_world();
void		box_world();
void		split_world();
void		inner_world();
void		maze_world();
void		diamond_world();
void		wipe_world();
int		CheckExit();
void		get_release();
char		*get_file_name();
void		print_title(int, int);
void		show_colour_table();
void		show_inputs();
void		show_bug_details(struct organism *, int);

/********************************/
/* DODGY GLOBAL VARIABLES	*/
/********************************/
int		world[ISIZE][JSIZE];        
struct organism *root;
double		cycles;
int		numorgs;
double  	numspawned;
FILE		*sfp;		/* points to the stats file */
char		statfile[13];	/* name of stat file*/
int		going;		/* is a run going? Y/N */
