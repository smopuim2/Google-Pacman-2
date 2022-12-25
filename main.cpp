#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct add{
	int x,y;
};

char gamemap[11][36]={
"===================================",
"=.................................=",
"=.=.#####.=======.#####.#.=.###.=.=",
"=...#.............#.....#.=.#.....=",
"===.#.###.###.###.#.###.#.=.###.===",
"   .#...#.# #.# #.#...#.#...#...   ",
"===.#####.###.###.#####.###.###.===",
"=.................................=",
"=.=======.======.===== =.========.=",
"=................=     =..........=",
"==================================="
};

struct add mon1,mon2,player;
int sc=0,peas=0;

void print(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	printf("\t  %d\n",sc);
	for(int i=0;i<11;i++){
		printf("\t");
		for(int j=0;j<35;j++){
			if((mon1.x==i && mon1.y==j) || (mon2.x==i && mon2.y==j)){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
				printf("*");
			}else if(player.x==i && player.y==j){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN);
				printf("@");
			}else if(gamemap[i][j]=='.'){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN);
				printf(".");
			}else if(gamemap[i][j]=='#'){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
				printf("#");
			}else if(gamemap[i][j]=='='){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
				printf("=");
			}else	printf(" ");
		}
		printf("\n");
	}
}

void init(int k){
	if(k==0) exit(0);
	srand(time(NULL));
	mon1.x=mon2.x=1;
	mon1.y=1;
	mon2.y=2;
	player.x=9;
	player.y=18;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	printf("Google-pacman 2\n\n     ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN);
	printf("@");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|FOREGROUND_BLUE);
	printf(" x %d\n",k);
	Sleep(800);
	system("cls");
}

void move(){
	static int face=4;
	if(GetAsyncKeyState(VK_UP) && gamemap[player.x-1][player.y]!='=' && gamemap[player.x-1][player.y]!='#') player.x--,face=0;
	else if(GetAsyncKeyState(VK_LEFT) && gamemap[player.x][player.y-1]!='=' && gamemap[player.x][player.y-1]!='#') player.y--,face=1;
	else if(GetAsyncKeyState(VK_DOWN) && gamemap[player.x+1][player.y]!='=' && gamemap[player.x+1][player.y]!='#') player.x++,face=2;
	else if(GetAsyncKeyState(VK_RIGHT) && gamemap[player.x][player.y+1]!='=' && gamemap[player.x][player.y+1]!='#') player.y++,face=3;

	else if(face==0 && gamemap[player.x-1][player.y]!='=' && gamemap[player.x-1][player.y]!='#') player.x--;
	else if(face==1 && gamemap[player.x][player.y-1]!='=' && gamemap[player.x][player.y-1]!='#') player.y--;
	else if(face==2 && gamemap[player.x+1][player.y]!='=' && gamemap[player.x+1][player.y]!='#') player.x++;
	else if(face==3 && gamemap[player.x][player.y+1]!='=' && gamemap[player.x][player.y+1]!='#') player.y++;
	
	if(player.y<0) player.y=34;
	if(player.y==35) player.y=0;
}

void AI(){
	if(!(rand()%3)) return;
	if(mon1.y>player.y && gamemap[mon1.x][mon1.y-1]!='=' && gamemap[mon1.x][mon1.y-1]!='#') mon1.y--;
	else if(mon1.y<player.y && gamemap[mon1.x][mon1.y+1]!='=' && gamemap[mon1.x][mon1.y+1]!='#') mon1.y++;
	else if(mon1.x>player.x && gamemap[mon1.x-1][mon1.y]!='=' && gamemap[mon1.x-1][mon1.y]!='#') mon1.x--;
	else if(mon1.x<player.x && gamemap[mon1.x+1][mon1.y]!='=' && gamemap[mon1.x+1][mon1.y]!='#') mon1.x++;
	if(mon1.y==-1) player.y=35; 
	else if(mon1.y==35) player.y=-1;
	
	if(mon2.x>player.x && gamemap[mon2.x-1][mon2.y]!='=' && gamemap[mon2.x-1][mon2.y]!='#') mon2.x--;
	else if(mon2.x<player.x && gamemap[mon2.x+1][mon2.y]!='=' && gamemap[mon2.x+1][mon2.y]!='#') mon2.x++;
	else if(mon2.y>player.y && gamemap[mon2.x][mon2.y-1]!='=' && gamemap[mon2.x][mon2.y-1]!='#') mon2.y--;
	else if(mon2.y<player.y && gamemap[mon2.x][mon2.y+1]!='=' && gamemap[mon2.x][mon2.y+1]!='#') mon2.y++;
	if(mon2.y==-1) player.y=35; 
	else if(mon2.y==35) player.y=-1;
}

int main(){
	int l=3;
	for(int i=0;i<11;i++) for(int j=0;j<35;j++) if(gamemap[i][j]=='.') peas++;
	init(l);
	while(peas!=sc){
		system("cls");
		if((mon1.x==player.x && mon1.y==player.y) || (mon2.x==player.x && mon2.y==player.y)) init(l-1),l--;
		if(gamemap[player.x][player.y]=='.') gamemap[player.x][player.y]=' ',sc++;
		if(GetAsyncKeyState(VK_ESCAPE)) return 0;
		move();
		AI();
		print();
		Sleep(300);
	}
	return 0;
}
