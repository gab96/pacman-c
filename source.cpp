/*
21/02/2017 Da sistemare checkwall
*/
#include <iostream>
#include <conio2.h>
#include <fstream>
#include <windows.h>
#include <algorithm>


using namespace std;

// Costants : 
#define ROWS 56
#define COL 122
#define DOWN 80
#define UP 72
#define LEFT 75
#define RIGHT 77
#define COND tmp2==WALL_VER||tmp2==WALL_HOR||tmp2==CORNER_UPPERLEFT||tmp2==CORNER_UPPERRIGHT||tmp2==CORNER_BOTTOMLEFT||tmp2==CORNER_BOTTOMRIGHT

// Blocks costants : 
	// Walls and others
	#define WALL_VER  'h'
	#define WALL_HOR 'b'
	#define CORNER_UPPERLEFT 'm'
	#define CORNER_UPPERRIGHT 'k'
	#define CORNER_BOTTOMLEFT 'j'
	#define CORNER_BOTTOMRIGHT 'l'
	#define POINT 'o'
// Pacman
	#define pac1 "ooooo"
	#define pac2 "ooooo"
	#define pac3 "ooooo"

const char block_list[6]={WALL_VER,WALL_HOR,CORNER_UPPERLEFT,CORNER_UPPERRIGHT,CORNER_BOTTOMLEFT,CORNER_BOTTOMRIGHT};

// Functions : 
void upload_map(); 
void print_map();
void update_matrix();
char replace_char(char elem);
void spawn_pac(bool);
void play();

// Pac Movements : 
bool check_wall(bool);
void move_pac();
void move_ghost();


// Variables : 
string map[ROWS]; 
int xpac=59,ypac=41; // Cordinate pac
int pac_dir=0;
bool powerup=false;
int temp_dir;

int main()
{
	system("pause>nul");
	textattr(0x0c);
	upload_map();
	print_map();
	spawn_pac(true);
	play();
	

 return 0;
}

void upload_map()
{
	ifstream in("map.txt");
	for(int i=0; i<ROWS; i++)
		getline(in,map[i]);
	in.close();
}

void print_map()
{
	for(int i=0; i<ROWS; i++)
	{
		for(int j=0; j<COL; j++)
		{
			cout<<replace_char(map[i][j]);
		}
		cout<<endl;
	}
}

char replace_char(char elem)
{
	switch(elem)
	{
		case WALL_HOR : 			return 205;
		case WALL_VER : 			return 186;
		case CORNER_UPPERLEFT : 	return 201;
		case CORNER_BOTTOMLEFT : 	return 200;
		case CORNER_BOTTOMRIGHT : 	return 188;
		case CORNER_UPPERRIGHT :	return 187;
		case POINT :				return 254;
		default : 					return ' ';
	}
}

void spawn_pac(bool check)
{
	if(check)
		xpac=59, ypac=41;
	gotoxy(xpac,ypac);
	cout<<pac1;
	
	ypac++;
	gotoxy(xpac,ypac);
	cout<<pac2;
	
	
	ypac++;
	gotoxy(xpac,ypac);
	cout<<pac3;
	
	ypac-=2;
	
}

void play()
{
	
	for(int cycles=0; ;cycles++)
	{
		if(pac_dir!=0)
			switch(pac_dir)
			{
				case UP:
				case DOWN: Sleep(100);break;
				case LEFT:
				case RIGHT: Sleep(50);break;
			}
		if(kbhit())
		{
			fflush(stdin);
			temp_dir=getch();
			fflush(stdin);
			temp_dir=getch();
			fflush(stdin);
			if(pac_dir==0 || check_wall(true))
				pac_dir=temp_dir;
		 	if(pac_dir!=0)
		}
		//if(!cycles&1)
		//{
			//if(kbhit())
				 
			move_pac();
			//move_ghost();
		//}
		if(powerup && cycles&1)
		{
			move_pac();
		}
	}
}

void move_pac()
{
	//gotoxy(ypac, xpac);
	if(pac_dir!=0){
		textattr(0x00);
		spawn_pac(false);
		if(check_wall(pac_dir))
			switch(pac_dir)
			{
				case UP : ypac--; break; // Abbiamo invertito
				case DOWN : ypac++; break;
				case LEFT : xpac--; break;
				case RIGHT : xpac++; break;
			}
			
		/*else
			pac_dir=0;*/
			
		textattr(0xEE);
			spawn_pac(false);
	}
}

bool check_wall(bool dir)
{
	/* Se viene passato true, il controllo viene fatto su pac_dir
	   altrimenti il controllo viene fatto su temp_dir, scambiandoli.*/
	   
	int tmp2_dir;
	string map_tmp;
	if(!dir)
	{
		tmp2_dir=pac_dir;
		pac_dir=temp_dir;
		temp_dir=tmp2_dir;
	}
	
	switch(pac_dir)
	{
		case LEFT : 
			for(int i=0; i<3; i++)
			{
				char tmp2=map[ypac-1+i][xpac-2];
				//if(find(block_list,block_list+6,map[ypac+i][xpac-1])!=(block_list+6))
				if(COND)
				{
					pac_dir=0;
					if(!dir)
					{
						tmp2_dir=temp_dir;
						temp_dir=pac_dir;
						pac_dir=tmp2_dir;	
					}
					
					return false;
				}
			}
			break;
		case RIGHT : 
			for(int i=0; i<3; i++)
			{
				char tmp2=map[ypac-1+i][xpac+4]; // Prove per check wall
				//if(find(block_list,block_list+6,map_tmp[xpac+5])!=(block_list+6))
				if(COND)
				{
					pac_dir=0;
					if(!dir)
					{
						tmp2_dir=temp_dir;
						temp_dir=pac_dir;
						pac_dir=tmp2_dir;
					}
					
					return false;
				}
			}
			break;
		case UP : 
			for(int i=0; i<5; i++)
			{
				char tmp2=map[ypac-2][xpac-1+i];
				//if(find(block_list,block_list+6,map[ypac-1][xpac+i])!=(block_list+6))
				if(COND)
				{
					pac_dir=0;
					if(!dir)
					{
						tmp2_dir=temp_dir;
						temp_dir=pac_dir;
						pac_dir=tmp2_dir;
					}
					return false;
				}
			}
			break;
		case DOWN : 
			for(int i=0; i<5; i++)
			{
				char tmp2=map[ypac+2][xpac-1+i];
				if(COND)
				{
					pac_dir=0;
					if(!dir)
					{
						tmp2_dir=temp_dir;
						temp_dir=pac_dir;
						pac_dir=tmp2_dir;
					}
					return false;
				}	
			}
			break;
		default: 
			if(!dir)
			{
				tmp2_dir=temp_dir;
				temp_dir=pac_dir;
				pac_dir=tmp2_dir;
			}
			return false;
	}
	if(!dir)
		{
			tmp2_dir=temp_dir;
			temp_dir=pac_dir;
			pac_dir=tmp2_dir;
		}
	return true;
}
