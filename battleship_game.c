#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <dos.h>
#include<math.h>
#define MAXGRIDSIZE 15
#define SEA '.'
#define PSHIP 'P'
#define CSHIP 'C'
#define BOMB '*'
#define SUNKENSHIP 'v'
unsigned char grid[MAXGRIDSIZE][MAXGRIDSIZE];
int f;
unsigned char m;
unsigned char newgrid[MAXGRIDSIZE][MAXGRIDSIZE];
int fleet(){
  int fleetSize;
  printf("\n---------------------------------------\nEnter fleet size : \n---------------------------------------\n");
  scanf("%d", &fleetSize);
  if (fleetSize>(pow(MAXGRIDSIZE,2))/2){
    printf("\n---------------------------------------\nFleet is too large, please enter a smaller fleet size.\n---------------------------------------\n");
    fleet();
  }
  else{
    f=fleetSize;
  }
}
void printGrid(){
  int x, y;
  printf("\n");
  for(y=0; y<MAXGRIDSIZE; y++){
    printf("%2d", y);
      for(x=0; x<MAXGRIDSIZE; x++){
        printf("%3c", grid[y][x]);
  }
  printf("\n");
}
  printf("%2c", ' ');
  for(x=0; x<MAXGRIDSIZE; x++){
    printf("%3d", x);
  }
    printf("\n");
}
void initGrid(){
  int x, y;
  for(y=0; y<MAXGRIDSIZE; y++){
    for(x=0; x<MAXGRIDSIZE; x++){
      grid[y][x] = SEA;
      newgrid[y][x] = SEA;
    }
  }
}
void hiddenGrid(){
  int x, y;
  printf("\n");
    for(y=0; y<MAXGRIDSIZE; y++){
      printf("%2d", y);
      for(x=0; x<MAXGRIDSIZE; x++){
        printf("%3c", newgrid[y][x]);
    }
    printf("\n");
  }
  printf("%2c", ' ');
  for(x=0; x<MAXGRIDSIZE; x++){
    printf("%3d", x);
  }
  printf("\n");
}
void placePShip(){
  int x,y;
  printf("\n---------------------------------------\nEnter Ship's x-coordinates :\n---------------------------------------\n");
  scanf("%d", &x);
  printf("\n---------------------------------------\nEnter Ship's y-coordinates :\n---------------------------------------\n");
  scanf("%d",&y);
  if(x<MAXGRIDSIZE&&y<MAXGRIDSIZE){
    if (grid[y][x] == SEA){
      grid[y][x] = PSHIP;
      newgrid[y][x]=PSHIP;
  }
    else {
      printf("\n---------------------------------------\nShip cannot be placed here\n---------------------------------------\n");
    placePShip();
  }
}
 else{
  printf("\n----------------------------------------------------------\nInvalid X,Y Coordinates,Please Input Another Pair.\n----------------------------------------------------------\n");
  placePShip();
  }
}
void placePShips(){
  int i;
  for(i=0;i<f;i++){
    placePShip();
    printGrid();
  }
}
int placeCShip(){ //This portion of the code takes a very long time to find places for all of the ships without clashing with player-placed ships
  int x,y,j; //This is due to the "sleep()"usage, which I have put in in order to change the value of the rand()
  srand(time(NULL));
  while(j<f){
    x=rand()%MAXGRIDSIZE;
    sleep(1);
    y=rand()%MAXGRIDSIZE;
    j++;
    if (grid[y][x] == SEA){
      grid[y][x] = CSHIP;
    }
    else {
      j--;
    }
  }
return 0;
}
void placeCShips(){
  printf("\n---------------------------------------\nPlacing Opponent Ships...\n---------------------------------------\n");
  placeCShip();
  printf("\n---------------------------------------\nOpponent's Ships Placed.\n---------------------------------------\n");
}
int hideGrid(){
  int i,j;
  for(i=0;i<MAXGRIDSIZE;i++){
    for(j=0;j<MAXGRIDSIZE;j++){
      if(grid[i][j]==CSHIP){
        newgrid[i][j]=SEA;
     }
    }
  }
}
void quit(){
  printf("\n--------------------------------------------------------\nThank you for playing Battleship!\n--------------------------------------------------------\n");
  printGrid();
  sleep(5);
  exit(0);
}
void restart(){
  printf("\n---------------------------------------\nRestarting...\n---------------------------------------\n");
  main();
}
void fire(){
  int x,y;
  printf("\n-----------------------------\nChoose where to fire.\n-----------------------------\n");
  printf("\n-----------------------------\nX-Coordinate :\n-----------------------------\n");
  scanf("%d",&x);
  printf("\n-----------------------------\nY-Coordinate :\n-----------------------------\n");
  scanf("%d",&y);
  if(x<MAXGRIDSIZE&&y<MAXGRIDSIZE)
    if(newgrid[y][x] !=PSHIP&&newgrid[y][x]!=BOMB&&newgrid[y][x]!=SUNKENSHIP){
      printf("\n-----------------------------\nShot fired...\n-----------------------------\n");
      if(grid[y][x]==CSHIP){
        printf("\n-----------------------------\nDirect hit!\n-----------------------------\n");
        grid[y][x]=SUNKENSHIP;
        newgrid[y][x]=SUNKENSHIP;
        hiddenGrid();
      }
      else{
        printf("\n-----------------------------\nShot missed!\n-----------------------------\n");
        newgrid[y][x]=BOMB;
        grid[y][x]=BOMB;
    }
  }
  else if(newgrid[y][x]==PSHIP){
    printf("\n-----------------------------\nYou cannot fire at your own ships.\n-----------------------------\n");
    fire();
  }
  else if(newgrid[y][x]==BOMB){
    printf("\n-----------------------------\nYou cannot fire where you have fired before.\n-----------------------------\n");
    fire();
  }
  else{
    printf("\n-----------------------------\nYou cannot fire here.\n-----------------------------\n");
    fire();
  }
else{
  printf("\n----------------------------------------------------------\nInvalid X,Y Coordinates, Please Input Another Pair.\n----------------------------------------------------------\n");
  fire();
  }
}
void compfire(){
  int x,y;
  srand(time(NULL));
  x=rand()%MAXGRIDSIZE;
  sleep(1);
  y=rand()%MAXGRIDSIZE;
  if(grid[y][x]!=CSHIP&&grid[y][x]!=BOMB&&grid[y][x]!=SUNKENSHIP){
    printf("\n-----------------------------\nComputer is firing...\n-----------------------------\n");
     if(grid[y][x]==PSHIP){
      printf("\n-----------------------------\nOne of your ships has been sunk! Direct hit!\n-----------------------------\n");
      grid[y][x]=SUNKENSHIP;
      newgrid[y][x]=SUNKENSHIP;
      }
      else{
        printf("\n-----------------------------\nComputer missed!\n-----------------------------\n");
        grid[y][x]=BOMB;
        newgrid[y][x]=BOMB;
    }
  }
 else{
  compfire();
  }
}
void choose_options(){
  char n;
  int i;
  printf("\n--------------------------------------------------------\nPress F to fire at a point of your choosing.\nPress P to print the grid without revealing opponent's remaining fleet.\nPress S to print the status of the game.\nPress Q to end the game and show opponent ship locations.\nPress R to restart the game.\n--------------------------------------------------------\n");
  scanf(" %c",&n);
  m=n;
}
void options(){
  int i,j,c=0,p=0,s=0,o=0;
  choose_options();
  if(m=='F'|m=='f'){
    fire();
    compfire();
    victory_check();
  }
  else if(m=='P'|m=='p'){
      hiddenGrid();
      options();
  }
  else if(m=='S'|m=='s'){
    for(i=0;i<MAXGRIDSIZE;i++){
      for(j=0;j<MAXGRIDSIZE;j++){
        if(grid[i][j]==CSHIP){
          c++;
  }
  else if(grid[i][j]==PSHIP){
     p++;
  }
  else if(grid[i][j]==BOMB){
     s++;
}
  else if(newgrid[i][j]==SEA){
    o++;
      }
    }
  }
  printf("\n--------------------------------------------------------\n%d Computer ships,%d Player ships,%d Shots fired,%d Options remaining.\n--------------------------------------------------------\n",c,p,s,o);
  options();
  }
   else if(m=='q'|m=='Q'){
    quit();
  }
   else if(m=='r'|m=='R'){
    restart();
  }
  else{
  printf("\n---------------------------------------\nSorry, that is not a valid option.\n---------------------------------------\n");
  options();
  }
}
int victory_check(){
  int i=0,j=0,c=0,p=0;
  for(i=0;i<MAXGRIDSIZE;i++){
    for(j=0;j<MAXGRIDSIZE;j++){
      if(grid[i][j]==CSHIP){
        c++;
    }
      else if(grid[i][j]==PSHIP){
         p++;
      }
    }
  }
    if(c==0){
    printf("\n------------------------------------------------------------------------------\nYou have won! Congratulations, all of your opponent's ships have been sunk!\n------------------------------------------------------------------------------\n");
    quit();
  }
    else if(p==0){
      printf("\n------------------------------------------------------------------------------\nYou have lost! All of your ships have been sunk!\n------------------------------------------------------------------------------\n");
      quit();
     }
    else{
      options();
    }
}
int main(){
  initGrid();
  printGrid();
  fleet();
  placePShips();
  placeCShips(); //Don't worry if this portion of the code takes a long time to run, the random generation method is time-intensive.
  options();
return 0;
}
