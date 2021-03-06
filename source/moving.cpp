#include <iostream>						//libraries
#include <cstdlib>						//if you understand that,you can understand that
#include <conio.h>						//get the keyboard value
#include <fstream>						//read the map file
#include <cmath>						//abs() function
#include <ctime>						//random
using namespace std;

const int xview = 2,yview = 1,XPOS = 12,YPOS = 6,FULL = 20;
int mpos[25][80];

int main()
{
	string map[25],imap[25],pmap[25];											//map:game map;imap:background map;pmap:front map
	int coin = 0,kill = 0,level = 1,lives = 5,wk = 1,wp = 1,power = FULL;		//if you do not understand that,you can not understand that
	int x,y,counter1 = 0;														//init the position
	string weapon = "Fist";
	srand(time(NULL));
	
	while(true)
	{
		int mlives = -1;
		x = XPOS;y = YPOS;
		system("setmap");
		ifstream fin("map1.txt");			//file pointer
		for(int i=0;i<25;i++)				//this loop read the map file
		{
			getline(fin,map[i]);			//put a line in the array:map
			pmap[i] = imap[i] = map[i];		//put a line in the arrays:imap,pmap
			//cout<<map[i]<<endl;			//help us check the map
		}
		for(int i=0;i<25;i++)
		{
			for(int j=0;j<80;j++)
			{
				if(pmap[i][j] != '*')
					pmap[i][j] = '.';
			}
		}	
		//for(int i=0;i<25;i++)
		//	cout<<pmap[i]<<endl;
		int posc = 0;
		for(int i=0;i<25;i++)
		{
			for(int j=0;j<80;j++)
			{
				if(map[i][j] == 'M')
					mpos[i][j] = rand() % 5 + level*3;
			}
		}
		system("cls");
		cout<<"Load successful!"<<endl<<"Press W,A,S or D key to enter the game.";
		
		while(true)
		{
			map[y][x] = imap[y][x];			//clear the place before moving
			int tempx = x,tempy = y;		//memorize the place
			for(int i=y-yview;i<=y+yview;i++)
			{
				for(int j=x-xview;j<=x+xview;j++)
				{
					if(pmap[i][j] != '*')
						pmap[i][j] = '.';
				}
			}
			char c;
			switch(getch())					//control the player
			{								//move
				case 'w':
					if(map[y-1][x] != '*')
						y--;
					else
						continue;
					break;
				case 's':
					if(map[y+1][x] != '*')
						y++;
					else
						continue;
					break;
				case 'a':
					if(map[y][x-1] != '*')
						x--;
					else
						continue;
					break;
				case 'd':
					if(map[y][x+1] != '*')
						x++;
					else
						continue;
					break;
				case 'k':					//kill the monster
					if(power>=wp)
					{
						power -= wp;
						for(int i=y-1;i<=y+1;i++)
						{
							for(int j=x-1;j<=x+1;j++)
							{
								if(abs(y-i) == abs(x-j))
									continue;
								if(map[i][j] == 'M')
								{
									mpos[i][j] -= wk;
									mlives = mpos[i][j];
									if(mpos[i][j] <= 0)
									{
										map[i][j] = ' ';
										kill++;
										coin++;
									}
								}
							}
						}
					}
					else
						continue;
					break;
				case 'h':					//help menu
					system("cls");
					cout<<"===============Help Menu==============="<<endl;
					cout<<"Control:"<<endl;
					cout<<"Move:W,A,S,D;"<<endl;
					cout<<"Kill Monsters:K;"<<endl;
					cout<<"Shop:T"<<endl;
					cout<<"Symbol:"<<endl;
					cout<<"@:Xenia(Yourself);"<<endl;
					cout<<"M:Monster(You need to kill them);"<<endl;
					cout<<"C:Coin(Collect them to increase your coins);"<<endl;
					cout<<"H:Heart(Collect them to ncrease your lives);"<<endl;
					cout<<"O:Out(The end of the level);"<<endl;
					cout<<"======================================="<<endl<<endl<<endl;
					getch();
					break;
				case 't':
					system("cls");
					cout<<"===============Shop Menu==============="<<endl;
					cout<<"Press number keys to shop."<<endl;
					cout<<"1 Heart\t\t3 coins"<<endl;
					cout<<"2 Stick\t\t10 coins"<<endl;
					cout<<"3 Energy Drink\t5 coins"<<endl;
					/*add other things here*/
					c = getch();
					switch(c)
					{
						case '1':
							if(coin >= 3)
							{
								coin -= 3;
								lives++;
							}
							break;
						case '2':
							if(coin >= 10)
							{
								coin -= 10;
								weapon = "Stick";
								wk = 3;
								wp = 2;
							}
						case '3':
							if(coin >= 5)
							{
								coin -= 5;
								power += 50;
							}
					}
					break;
				default:
					continue;
			}
			
			if(map[y][x] != ' ')
			{
				if(map[y][x] == 'C')		//collect coins
				{
					coin++;
					imap[y][x] = ' ';
				}
				else if(map[y][x] == 'H')	//collect hearts
				{
					lives++;
					imap[y][x] = ' ';
				}
				else if(map[y][x] == 'O')	//win the game
				{
					system("cls");
					cout<<"You win."<<endl;
					cout<<"Press any key to enter the next level."<<endl;
					getch();
					break;
				}
				else{
					if(map[y][x] == 'M')	//meet the monster
						lives--;
					x = tempx;				//(go back to the place we met)
					y = tempy;
				}
			}
			
			map[y][x] = '@';				//change the game map after moving
			
			for(int i=0;i<25;i++)
			{
				for(int j=0;j<80;j++)
				{
					if(map[i][j] == 'M')
					{
						if(mpos[i][j] <= 0)
						{
							mpos[i][j] = 0;
							map[i][j] = ' ';
						}
					}
				}
			}
			
			//monsters' move
			for(int i=0;i<25;i++)
			{
				for(int j=0;j<80;j++)
				{
					if(map[i][j] == 'M')
					{
						int temp = rand() % 10;
						switch(temp)
						{
							case 0:
								if(map[i+1][j] != '*' && map[i+1][j] != '@' && map[i+1][j] != 'M')
								{
									mpos[i+1][j] = mpos[i][j];
									mpos[i][j] = 0;
									if(imap[i][j] == 'M')
										map[i][j] = ' ';
									else
										map[i][j] = imap[i][j];
									map[i+1][j] = 'M';
									break;
								}
							case 1:
								if(map[i-1][j] != '*' && map[i-1][j] != '@' && map[i-1][j] != 'M')
								{
									mpos[i-1][j] = mpos[i][j];
									mpos[i][j] = 0;
									if(imap[i][j] == 'M')
										map[i][j] = ' ';
									else
										map[i][j] = imap[i][j];
									map[i-1][j] = 'M';
									break;
								}
							case 2:
								if(map[i][j+1] != '*' && map[i][j+1] != '@' && map[i][j+1] != 'M')
								{
									mpos[i][j+1] = mpos[i][j];
									mpos[i][j] = 0;
									if(imap[i][j] == 'M')
										map[i][j] = ' ';
									else
										map[i][j] = imap[i][j];
									map[i][j+1] = 'M';
									break;
								}
							case 3:
								if(map[i][j-1] != '*' && map[i][j-1] != '@' && map[i][j-1] != 'M')
								{
									mpos[i][j-1] = mpos[i][j];
									mpos[i][j] = 0;
									if(imap[i][j] == 'M')
										map[i][j] = ' ';
									else
										map[i][j] = imap[i][j];
									map[i][j-1] = 'M';
									break;
								}
						}
					}
				}
			}
			
			for(int i=y-yview;i<=y+yview;i++)
			{
				for(int j=x-xview;j<=x+xview;j++)
				{
					if(pmap[i][j] == '.')
						pmap[i][j] = map[i][j];
				}
			}
			system("cls");					//if you can not understand that,you will never understand that
			if(lives <= 0)					//die
			{
				cout<<"You died at level "<<level<<'.'<<endl;
				cout<<"You finally realize that you can never get out of here."<<endl;
				getch();
				return 0;
			}
											//print status
			cout<<"x:"<<x<<" y:"<<y<<"\tlives:"<<lives<<" energy:"<<power<<"\tweapon:"<<weapon<<" coin:"<<coin<<" kill:"<<kill<<" monster's lives:"<<mlives<<" level:"<<level<<endl;
			for(int i=0;i<25;i++)			//print the map
				cout<<pmap[i]<<endl;
			/*{
				for(int j=0;j<80;j++)
				{
					if(mpos[i][j] > 0)
						cout<<mpos[i][j];
					else
						cout<<' ';
				}
				cout<<endl;
			}*/
			if(counter1 >= 5 && power < FULL)
			{
				power++;
				counter1 -= 5;
			}
			counter1++;
		}
		level++;							//(start this up a second time)
	}
}