Bugs
====

 * Kazan Glenn
 * kazan@kazan.co.uk
 * written Summer 1995

Introduction
------------

This is a old program written in 1994/1995. It is interesting
to see what could be done with very low specification machines!
My original text follows.

Description
-----------

This program simulates an environment with a  population
of  'bugs' within it.   The bugs are not static entities but
go through changes in  response  to the environment and also
other bug species that may be present.   One species can  go
through drastic alteration and produce further species, when
the situation is right, somewhat akin to adaptive radiation.
Population  fluxes  will  be  observed as bugs interact with
their  food  supply.    The user can interact to some degree
with this process by observing graphs of population,  number
of species and also lineage of the species present.   Saving
and recalling runs is also  possible,   although it is up to
the user to manage the number of  files  they  have  stored.
See  file  conventions.    Interactions  can  be carried out
either through the keyboard or using the mouse.

Specifications
--------------

Bugs was written using the Zortech C++ v2.1 package on a
486 sx25 machine under MS-DOS with  only 4mb of RAM.   It is
intended to run on almost anything,  although  it  might  be
rather  slow  on  lower  specification machines.   It is not
intended for use under windows.    It is not recommended for
use with a black and white monitor as it relies  heavily  on
colours  for   representational   purposes.     Use  of  low
resolution graphics for the main window is for two  reasons.
First it allows the graphics to be faster, and fast graphics
was  one  of the goals of this program.   Second,  I did not
have access to a  high  resolution  graphics mode that could
give me the number of colours required. 


File Conventions
----------------

Little needs to be said except that it is  worth  noting
that  a  given saved run is actually two files.   Theses two
files  are  both  binaries,   one  contains  the information
regarding the 'bugs' and the state of the world,  the  other
contains  all the run information such as population.   When
loaded this file is constantly open and written to.   If you
delete one you  must  delete  the  other  to avoid potential
problems.   *.WOR files are the world files,  *.STT are  the
statistics and graphing files.

The interface to the file management system as it stands
is  still  crude.   No  provision  has  been  made  for very
large  numbers  of  files.    It is up to the user to manage
their saved runs from  the DOS environment.   Later versions
will contain a rewrite of this interface. 

When working from within  the  program only the run name
shared between both file types is given.  You do not have to
deal  with  the  separate  files.    Do  not  add  file name
extensions.   The name 'TMP' is reserved.   Do not save  any
runs under this name.

The Software and its Use
------------------------

**Intro**
	
The   program   starts   with  an  introduction  screen.
Pressing any key will move you on to the primary menu system
with three options; starting a new run,  loading a saved run
or exiting.   Do not attemt  to  load a run unless there are
runs present on your disk.

**Main**

This is the  screen  displaying  the  run  in  progress.
While  in  this  screen  the mouse driver is deactivated for
speed. Pressing any key will return you to the main menu.

**Menu**

The main menu expands once a run is started to allow you
to save,  view the networks or view the population trends as
autoscaling graphs.

**Statistics information**
	
As stated the  graphs  displaying  population trends are
autoscaling.   As yet there is no way to zoom in to  view  a
small  period  of time in a long run.   Future versions will
have this modification.   Samples  stored in the *.STT files
are recorded every 100 cycles.   A cycle is defined as being
the movement of all existing bugs once. 

**Viewing networks**
	
The networks are displayed as  a  graph.    Pictographic
representation  would  not have been very clear owing to the
large number of connections and the specific nature of these
connections.    The  colour  of  the  square  representing a
connection indicates the action.   A colour coding chart  is
displayed next to the graph.   The number in black over this
colour indicates the state to which the connection goes, and
therefor  the  state  from  which  the  next  action will be
derived.


**Saving and loading a Run**

To save or load a run go  to the main menu and press the
appropriate button with the mouse or key letter from the key
board.   Simply enter the name you have chosen, a maximum of
eight characters long, with no extensions, and press return.
After you will be returned to the main menu.


Bug Architecture
----------------

**The Basics**
	
The 'bugs'  of  this  program  are  actually  relatively
simple  finite state machines.   A finite state machine is a
relatively old  concept  derived  from  cybernetics  and the
desire to  explain  and  model  homeostatic  systems.    The
principle  points  to  be made start with the fact that they
are serial in action, unlike a neural network which operates
in  parallel  (within  a   given   layer  and  dependent  on
architecture).  At any given point they are in a given state
or  cell.    This  cell  receives   the   input   from   the
ennvironment,  whatever it may be, and produces to things in
consequence.  The first is an output signal, an action.  The
second  is  a  state  or cell change.   This is a simplistic
explanation and of course  there  are many ways to represent
these  structures  and  many  variations,    such   as   the
probabilistic  networks  used in speech recognition known as
hidden Markov models.   The inputs and active outputs can be
viewed as  alphabets.    In  the  simplest  cases these both
contain two possibilites.   In other words they  are  binary
either  producing  1's or 0's.   However there are no limits
and no need  for  the  two  sets  to  contain the same sized
alphabets. 
        
**Bug Network Specifications**

The alpahabet of the bug nets here are different.  There
are seven possibilities in the input alphabet:  food,  wall,
nothing, same species of bug, different species of bug, same
pheromone  or   different   pheromone.     There   are   ten
possibilites in the output alphabet: move ahead,  move left,
move  right,  these three again but also leaving a pheromone
unit behind,  turning left  but  staying  in the same place,
turning right, remaining still and finally reproducing.

Bugs reproduce under two conditions.   First, they reach
their maximum  energy  levels  from  food  consumption,   as
indicated  on  the  right  hand side of the energy indicator
while viewing nets.   Secondly,  akin to a cancer gene, they
can have the instruction to reproduce within their networks.
This latter case can produce dramatic population explosions,
but is a rare gene to aquire through mutation.   The maximum
energy of a bug is  as  prone  to mutation as the net during
the process of reproduction.

**The Environment**

**Food Units**
	
Food units have their own rules  governing  growth  rate
and pattern.  Principally they spread from covered areas but
there  is  also  a  degree  of  random  reseeding.   This is
necessary to ensure a  continued 'plant' population.   These
plants are the dark greeny blue symbols on the main window.

**Walls**
    
Walls are the shaded grey blocks.   Bugs  can  not  move
through or over these objects. They must move around them.

**Pheromones**
    
Pheromones  are  the coloured dots on the display.   The
colour of the dot  is  an  indication  of  the species it is
derived from.   Any given bug determines whether a pheromone
unit comes from the same species as itself or  from  another
species. This information is then fed into the network.

**Bugs**
    
These  are  the  fast  moving  things running around the
screen!   Colour is an indication of species.  Bugs will eat
other species if they land on the same square,  but will not
eat their own kind.   The pheromone colour they leave (if at
all) is the same as their central pixel colour.

**Alternative Environmental Situations**                                             
    
There are  several  possible  internal  wall  formats to
chose from.  These vary in complexity and therefor hardness.
The harder ones are more likely  to  result  in  extinction.
The  best  advice  here  is  experiment  and observe.   If a
seeding fails first time try  again.    No two runs are ever
the same, even in the same environment
    

Reproduction and Change
-----------------------

When bugs  reproduce  they  are  subject  to  mutations.
Small  mutations  of  instruction or redirection of the next
cell or maximum  energy  are  contained  within one species.
Large changes such as the addition or  removal  of  a  state
result  in  the production of a new species.   Thus,  within
this simulation,  there  is  intraspecific and interspecific
competition.   This,  coupled  with  the  'bottle  necking',
'adaptive  radiations'  and  environmental  demands create a
plausible if simple model of the process of evolution.

This is a simple and  brief explanation of the software.
For further information you can contact me  at  the  address
given  at  the top of this file or at the exit window of the
program.   Thank you for  trying  this program and I hope it
provided some amusement. Feedback is welcome. 

Kazan Glenn.