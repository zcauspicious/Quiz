#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <windows.h>

//define the boundary of the area
#define areaX 20
#define areaY 20
using namespace std;

//declare an array to record if the positiion is free
int coll[areaX][areaY]={0};

//design the model of rover
struct Rover
{
	int x, y;
	char dir;
	string comm;
};

Rover rover1;
Rover rover2;

//the init function
void roverInit(Rover &rover,int id);
//the move function
void roverMove(Rover &rover,int id);
//two threads
DWORD WINAPI FunRover1(LPVOID lpParameter);
DWORD WINAPI FunRover2(LPVOID lpParameter);

int main()
{
	//init rover1
	cout<<"Rover1:"<<endl;
	roverInit(rover1,1);
	//init rover2
	cout<<"Rover2:"<<endl;
	roverInit(rover2,2);
	//threads for rover1 and rover2
	HANDLE hThread_1 = CreateThread(NULL,0,FunRover1,NULL,0,NULL);
	HANDLE hThread_2 = CreateThread(NULL,0,FunRover2,NULL,0,NULL);
	CloseHandle(hThread_1);
	CloseHandle(hThread_2);
	
	system("pause");
	return 0;
}

DWORD WINAPI FunRover1(LPVOID lpParameter)
{
	//rover1 starts to move
	roverMove(rover1,1);
	return 0;
}

DWORD WINAPI FunRover2(LPVOID lpParameter)
{
	//rover2 starts to move
	roverMove(rover2,2);
	return 0;
}

void roverInit(Rover &rover,int id)
{
	//record the position
	int x, y;
	//record the direction
	char dir;
	//record the moving command
	string comm;

	cout<<"Please enter the initial location."<<endl;
	cout<<"X(0<=X<="<<areaX<<"):"<<endl;
	cin>>x;

	//rover can't be out of the area
	while(x < 0 || x > areaX)
	{
		cout<<"Illegal X! Please enter again."<<endl;
		cin>>x;
	}

	cout<<"Y(0<=Y<="<<areaY<<"):"<<endl;
	cin>>y;
	while(y < 0 || y > areaY)
	{
		cout<<"Illegal Y! Please enter again."<<endl;
		cin>>y;
	}

	//the letter of direction can't be others
	cout<<"Please enter the direction(N S E W):"<<endl;
	cin>>dir;
	while(dir != 'N'&&dir != 'n'&&dir != 'S'&&dir != 's'&&dir != 'E'&&dir != 'e'&&dir != 'W'&&dir != 'w')
	{
		cout<<"Illegal direction! Please enter again."<<endl;
		cin>>dir;
	}

	//the letter of moving command can't be others
	cout<<"Please enter the command(consists of m l r b):"<<endl;
	cin>>comm;
	string::iterator iter = comm.begin();
	for(; iter != comm.end(); iter++)
	{
		while(*iter!='M'&&*iter!='m'&&*iter!='L'&&*iter!='l'&&*iter!='R'&&*iter!='r'&&*iter!='B'&&*iter!='b')
		{
			cout<<"Illegal command! Please enter again"<<endl;
			cin>>comm;
		}
	}

	rover.x = x;
	rover.y = y;
	rover.dir = dir;
	rover.comm = comm;
	coll[x][y] = 1;
}

void roverMove(Rover &rover,int id)
{
	int x = rover.x;
	int y = rover.y;
	char dir = rover.dir;
	string comm = rover.comm;

	string::iterator iter = comm.begin();
	for(; iter != comm.end(); iter++)
	{
		if(*iter=='M'||*iter=='m')
		{
			if(dir=='N'||dir=='n')
			{
				if((y+1) > areaY)
				{
					cout<<"DEAD"<<endl;
					return;
				}
				while(coll[x][y+1] == 1)
				{
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
				if((y+1) <= areaY && coll[x][y+1]==0)
				{
					coll[x][y] = 0;
					++y;
					coll[x][y] = 1;
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
			}
			else if(dir=='S'||dir=='s')
			{
				if((y-1) < 0)
				{
					cout<<"DEAD"<<endl;
					return;
				}
				while(coll[x][y-1] == 1)
				{
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
				if((y-1) >= 0 && coll[x][y-1]==0)
				{
					coll[x][y] = 0;
					--y;
					coll[x][y] = 1;
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
			}
			else if(dir=='E'||dir=='e')
			{
				if((x+1) > areaX)
				{
					cout<<"DEAD"<<endl;
					return;
				}
				while(coll[x+1][y] == 1)
				{
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
				if((x+1) <= areaX && coll[x+1][y]==0)
				{
					coll[x][y] = 0;
					++x;
					coll[x][y] = 1;
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
			}
			else if(dir=='W'||dir=='w')
			{
				if((x-1) < 0)
				{
					cout<<"DEAD"<<endl;
					return;
				}
				while(coll[x-1][y] == 1)
				{
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
				if((x-1) >= 0 && coll[x-1][y]==0)
				{
					coll[x][y] = 0;
					--x;
					coll[x][y] = 1;
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
			}
		}	
		else if(*iter=='B'||*iter=='b')
		{
			if(dir=='N'||dir=='n')
			{
				if((y-1) < 0)
				{
					cout<<"DEAD"<<endl;
					return;
				}
				while(coll[x][y-1] == 1)
				{
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
				if((y-1) >= 0 && coll[x][y-1]==0)
				{
					coll[x][y] = 0;
					--y;
					coll[x][y] = 1;
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
			}
			else if(dir=='S'||dir=='s')
			{
				if((y+1) > areaY)
				{
					cout<<"DEAD"<<endl;
					return;
				}
				while(coll[x][y+1] == 1)
				{
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
				if((y+1) <= areaY && coll[x][y+1]==0)
				{
					coll[x][y] = 0;
					++y;
					coll[x][y] = 1;
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
			}
			else if(dir=='E'||dir=='e')
			{
				if((x-1) < 0)
				{
					cout<<"DEAD"<<endl;
					return;
				}
				while(coll[x-1][y] == 1)
				{
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
				if((x-1) >= 0 && coll[x-1][y]==0)
				{
					coll[x][y] = 0;
					--x;
					coll[x][y] = 1;
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
			}
			else if(dir=='W'||dir=='w')
			{
				if((x+1) > areaX)
				{
					cout<<"DEAD"<<endl;
					return;
				}
				while(coll[x+1][y] == 1)
				{
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
				if((x+1) <= areaX && coll[x+1][y]==0)
				{
					coll[x][y] = 0;
					++x;
					coll[x][y] = 1;
					cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
				}
			}
		}

		else if(*iter=='L'||*iter=='l')
		{
			if(dir=='N'||dir=='n')
			{
				dir = 'W';
				cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
			}
			else if(dir=='S'||dir=='s')
			{
				dir = 'E';
				cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
			}
			else if(dir=='E'||dir=='e')
			{
				dir = 'N';
				cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
			}
			else if(dir=='W'||dir=='w')
			{
				dir = 'S';
				cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
			}
		}

		else if(*iter=='R'||*iter=='r')
		{
			if(dir=='N'||dir=='n')
			{
				dir = 'E';
				cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
			}
			else if(dir=='S'||dir=='s')
			{
				dir = 'W';
				cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
			}
			else if(dir=='E'||dir=='e')
			{
				dir = 'S';
				cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
			}
			else if(dir=='W'||dir=='w')
			{
				dir = 'N';
				cout<<"Rover"<<id<<"("<<x<<","<<y<<")"<<dir<<endl;
			}
		}
	}
}