#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH	80
#define HEIGHT	20

#define DEAD_END -1
#define SPACE	0
#define WALL	1
#define NoItem	2
#define FASTER	3
#define SLOWER	4
#define REMOVE	5
#define TRANFROM 6
#define HEAL 7

#define BUFF_GENRATEION_TIME 10
#define MONSTER_GENRATEION_TIME 20
#define WALLEXISTENCETIME	4.5
#define DAMAGE 10

#define PEOPLE	16
#define MONSTER	13

using namespace std;

void gotoxy(short x, short y){
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}
void HideCursor(){
	CONSOLE_CURSOR_INFO cursor_info ={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}

class Map{
private:
	int x;
	int y;
	int thickX, thickY;
	static int map[WIDTH][HEIGHT];
public:
	Map(){
		int n=rand()%10+7;
		int times=0;
		while(n>times){
			x=rand()%WIDTH;
			y=rand()%HEIGHT;
			thickX = rand()%7+1;
			thickY = rand()%3+1;
			for(int i=0;i<thickX;i++){
				for(int j=0;j<thickY;j++){
					gotoxy(i+x,j+y);
					map[x+i][y+j] = WALL;
				}
			}
			times++;
		}
		for(int i=0; i<=WIDTH-1; i++){
			map[i][0] = WALL;
			map[i][HEIGHT-1] = WALL;
		}
		for(int i=0; i<=HEIGHT; i++){
			map[0][i] = WALL;
			map[WIDTH-1][i] = WALL;
		}
	}
	void Print(){
		for(int i=0;i<WIDTH;i++){
			for(int j=0;j<HEIGHT;j++){
				if(map[i][j] == WALL){
					gotoxy(i,j);
					cout<<"*";
				}
			}
		}
	}

	static int GetMap(int i,int j){
		return map[i][j];
	}
	static void SetItem(int i,int j,int ItemNumber){
		map[i][j]=ItemNumber;
	}
};
int Map::map[WIDTH][HEIGHT]={{SPACE}};

class Item{
protected:
	int x, y;
	int ItemNumber;
	clock_t start;
	clock_t finish;
public:
	Item(){}
	void Produce(){
		finish=clock();
		double duration=(double)(finish - start) / CLOCKS_PER_SEC;
		if(duration >= BUFF_GENRATEION_TIME){
			do{
				x=rand()%(WIDTH-1);
				y=rand()%(HEIGHT-1);
			}while(Map::GetMap(x,y)!=SPACE);
			ItemNumber = rand()%2;
			//gotoxy(0, HEIGHT);
			//cout<<"ItemNumber = "<<ItemNumber<<endl;
			if(ItemNumber == 0)
            {
                Map::SetItem(x,y,FASTER);
                gotoxy(x, y);
                cout<<"F";
            }
            else if(ItemNumber == 1)
            {
                Map::SetItem(x,y,REMOVE);
                gotoxy(x, y);
                cout<<"B";
            }
			start = clock();
		}
	}

};


class Node{
public:
	Node *next;
public:
	virtual void Print()=0;
	virtual void Action()=0;
	virtual int GetItem()=0;
	virtual int GetNodeNumber()=0;
	virtual int GetX()=0;
	virtual int GetY()=0;
	virtual ~Node(){}
	int NodeNumber;
};

class People:public Node{
private:
	short x, y;
	clock_t start;
	clock_t finish;
	int ItemNumber;
	int hp;
	int point;
	int Getitem=0;
	int NodeNumber=PEOPLE;
	int Buff_F=0;
	int check_F_only_once=0;
	bool IF_hurt;
public:
	People(){
		hp = 100;
		point = 0;
		ItemNumber = NoItem;
	    do{
			x=rand()%(WIDTH-1)+1;
			y=rand()%(HEIGHT-1)+1;
		}while(Map::GetMap(x,y)!=SPACE);
	}
	~People(){
		system("cls");
        cout<<" ******   ***    *   *    ******"<<endl;
        cout<<"*******  *****  *** ***  *******"<<endl;
        cout<<"**      *** *** *** ***  **"<<endl;
        cout<<"**      **   ** *******  **"<<endl;
        cout<<"** **** **   ** *******  ******"<<endl;
        cout<<"**  *** **   ** ** * **  ******"<<endl;
        cout<<"**   ** ******* **   **  **"<<endl;
        cout<<"**   ** *** *** **   **  **"<<endl;
        cout<<"******* **   ** **   **  *******"<<endl;
        cout<<" *****  **   ** **   **   ******"<<endl;
        cout<<""<<endl;
        cout<<" *****  **   **  ******   *****"<<endl;
        cout<<"******* **   ** *******  *******"<<endl;
        cout<<"**   ** **   ** **       **   **"<<endl;
        cout<<"**   ** **   ** **       **   **"<<endl;
        cout<<"**   ** **   ** ******   **   **"<<endl;
        cout<<"**   ** **   ** ******   *******"<<endl;
        cout<<"**   ** **   ** **       ******"<<endl;
        cout<<"**   ** *** *** **       ** **"<<endl;
        cout<<"*******  *****  *******  **  **"<<endl;
        cout<<" *****    ***    ******  **   **"<<endl;
	}
	int GetX(){
		return x;
	}
	int GetY(){
		return y;
	}
	int GetItemNumber(){
		return ItemNumber;
	}
	int GetNodeNumber(){
		return NodeNumber;
	}
	int GetHP(){
		return hp;
	}
	void Print(){
		gotoxy(x,y);
		cout<<"P";
	}
	char presskey(){
		if(kbhit()){
			return getch();
		}
		else{
            return -1;
		}
	}
	int GetItem(){
		double duration;
		finish=clock();
		duration=(double)(finish - start) / CLOCKS_PER_SEC;
		if(Map::GetMap(x, y)==FASTER){
			start=clock();
			ItemNumber=FASTER;
			Map::SetItem(x, y, SPACE);
			return ItemNumber;
		}
		else if(Map::GetMap(x,y)==HEAL){
			ItemNumber = HEAL;
			Map::SetItem(x,y,SPACE);
			return ItemNumber;
		}
		else if(Map::GetMap(x, y)==SLOWER){
			start=clock();
			ItemNumber=SLOWER;
			Map::SetItem(x, y, SPACE);
			return ItemNumber;
		}
		else if(Map::GetMap(x, y)==REMOVE){
			ItemNumber=REMOVE;
			Map::SetItem(x, y, SPACE);
			return ItemNumber;
		}
		else if(Map::GetMap(x,y)==TRANFROM){
			start = clock();
			Map::SetItem(x,y,TRANFROM);
			return TRANFROM;
		}
		if(duration<=5&&duration>=0)
			return ItemNumber;
		else{
			ItemNumber=NoItem;
			return NoItem;
		}
	}
	void Action(){
		int g;
		g = GetItem();
		switch(g){
			case FASTER:
				Buff_F = 1;
				break;
			case HEAL:
				 Buff_F = 0;
				 FullHp();
				 break;
			case TRANFROM:
				ItemNumber = TRANFROM;
				break;
			default:
				Buff_F = 0;
				break;
		}
	    gotoxy(x,y);
	    cout<<"P";
		switch(presskey())
		{
			case 72:
		    case 'W':
			case 'w':
				if(Map::GetMap(x,y-1) != WALL)     //if the player's above is not a Wall, go up. If is, break.
                {
                    gotoxy(x,y);
                    cout<<" ";
                    y--;
                   	if(Map::GetMap(x,y) == DEAD_END)
				    	Map::SetItem(x,y,SPACE);
                }
                if(Buff_F)                          //If buff_f is 1, move one more time.
                {
                    if(Map::GetMap(x,y-1) != WALL)
                    {
                        gotoxy(x,y);
                        cout<<" ";
                        y--;
                        if(Map::GetMap(x,y) == DEAD_END)
				    		Map::SetItem(x,y,SPACE);
				    	g = GetItem();
                    }
                }
                IF_hurt = 0;
			    break;
			case 75:
            case 'A':
			case 'a':
				if(Map::GetMap(x-1,y) != WALL)
                {
                    gotoxy(x,y);
                    cout<<" ";
                    x--;
                    if(Map::GetMap(x,y) == DEAD_END)
				    	Map::SetItem(x,y,SPACE);
                }
                if(Buff_F)                          //If buff_f is 1, move one more time.
                {
                    if(Map::GetMap(x-1,y) != WALL)
                    {
                        gotoxy(x,y);
                        cout<<" ";
                        x--;
                        if(Map::GetMap(x,y) == DEAD_END)
				    		Map::SetItem(x,y,SPACE);
				    	g = GetItem();
                    }
                }
                IF_hurt = 0;
			    break;
			case 80 :
            case 'S':
			case 's':
				if(Map::GetMap(x,y+1) != WALL)
                {
                    gotoxy(x,y);
                    cout<<" ";
                    y++;
                    if(Map::GetMap(x,y) == DEAD_END)
				    	Map::SetItem(x,y,SPACE);
                }
                if(Buff_F)                          //If buff_f is 1, move one more time.
                {
                    if(Map::GetMap(x,y+1) != WALL)
                    {
                        gotoxy(x,y);
                        cout<<" ";
                        y++;
                        if(Map::GetMap(x,y) == DEAD_END)
				    		Map::SetItem(x,y,SPACE);
				    	g = GetItem();
                    }
                }
                IF_hurt = 0;
			    break;
			case 77:
            case 'D':
			case 'd':
				if(Map::GetMap(x+1,y) != WALL)
                {
                    gotoxy(x,y);
                    cout<<" ";
                    x++;
                    if(Map::GetMap(x,y) == DEAD_END)
				    	Map::SetItem(x,y,SPACE);
                }
                if(Buff_F)                          //If buff_f is 1, move one more time.
                {
                    if(Map::GetMap(x+1,y) != WALL)
                    {
                        gotoxy(x,y);
                        cout<<" ";
                        x++;
                        if(Map::GetMap(x,y) == DEAD_END)
				    		Map::SetItem(x,y,SPACE);
				    	g = GetItem();
                    }
                }
                IF_hurt = 0;
			    break;
			case 'l':
			case 'L':
				FullHp(99999);
				break;
            default:
                break;
		}

		gotoxy(0,HEIGHT+1);
		cout<<"HP:"<<hp<<"      "<<endl;
		cout<<"SCORE:"<<point<<"      "<<endl;
		cout<<"BUFF:"<<ItemNumber<<"      "<<endl;

	}
	void FullHp(){
		hp = 100;
	}
	void FullHp(int HP){
		hp = HP;
	}
	bool Get_IF_hurt()
    {
        return IF_hurt;
    }
    void Change_IF_hurt(bool i)
    {
        IF_hurt = i;
    }
	void GetDamage(int x){
		hp = hp - x;
	}
	void GetPoint(){
		point = point + 10;
	}
	void GetPoint(int sec){
		point += sec;
	}
};

class Monster:public Node{
protected:
    People *player;
	short x, y;
	short detectX, detectY;
	short targetX, targetY;
	short nextTargetX = -1, nextTargetY = -1;
	short originalX, originalY;
	short priorityX = 0 ,priorityY = 0;
	clock_t start;
	clock_t finish;
	clock_t damage_start;
	clock_t damage_finish;
	float MovingTime = 1;
	float time = 1;
	int NodeNumber = MONSTER;
	double damage_duration;
public:
	Monster(People *newplayer){
		do{
			x=rand()%(WIDTH-1)+1;
			y=rand()%(HEIGHT-1)+1;
		}while(Map::GetMap(x,y)!=SPACE);
		start=clock();
		player=newplayer;
		detectX = x;
		detectY = y;
		originalX = x;
		originalY = y;
	}
	~Monster(){
		player->GetPoint();
		gotoxy(x,y);
		cout<<" ";
	}
	int GetX(){
		return x;
	}
	int GetY(){
		return y;
	}
	int GetNodeNumber(){
		return NodeNumber;
	}
	void Print(){
		gotoxy(x,y);
		cout<<"M";
	}
	int GetItem(){
		if(Map::GetMap(x,y)==FASTER){
			gotoxy(x,y);
			cout<<"F";
		}
		else if(Map::GetMap(x,y)==SLOWER){
			gotoxy(x,y);
			cout<<"S";
		}
		else if(Map::GetMap(x,y)==REMOVE){
			gotoxy(x,y);
			cout<<"B";
		}
		else if(Map::GetMap(x,y)==TRANFROM){
			gotoxy(x,y);
			cout<<"T";
		}
		else if(Map::GetMap(x,y)==HEAL){
			gotoxy(x,y);
			cout<<"H";
		}

		return 0;
	}
	void MonsterSlower(){
		if(player->GetItemNumber()==SLOWER)
			MovingTime = time*2;
		else
			MovingTime = time;
	}
	void ActionX(){
		if(x>targetX&&Map::GetMap(x-1,y)!=WALL&&Map::GetMap(x-1,y)!=DEAD_END){
			gotoxy(x,y);
			cout<<" ";
			GetItem();
			x--;
			Print();
		}else if(x<targetX&&Map::GetMap(x+1,y)!=WALL&&Map::GetMap(x+1,y)!=DEAD_END){
			gotoxy(x,y);
			cout<<" ";
			GetItem();
			x++;
			Print();
		}
	}
	void ActionY(){
		if(y>targetY&&Map::GetMap(x,y-1)!=WALL&&Map::GetMap(x,y-1)!=DEAD_END){
			gotoxy(x,y);
			cout<<" ";
			GetItem();
			y--;
			Print();
		}else if(y<targetY&&Map::GetMap(x,y+1)!=WALL&&Map::GetMap(x,y+1)!=DEAD_END){
			gotoxy(x,y);
			cout<<" ";
			GetItem();
			y++;
			Print();
		}
	}
	virtual	void Action(){
		int canMoveX = 1, canMoveY = 1;
		int to_bottom=0, to_top=0, to_right=0, to_left=0;
		finish=clock();
		damage_finish = clock();
		double duration=(double)(finish - start) / CLOCKS_PER_SEC;
		damage_duration=(double)(damage_finish - damage_start) / CLOCKS_PER_SEC;

		//gotoxy(0, HEIGHT);
		//cout<<"damage_duration = "<<damage_duration<<endl;


		if(x==player->GetX()&&y==player->GetY()&&player->GetItemNumber()!=TRANFROM&&player->Get_IF_hurt()==0){
            player->GetDamage(10);
            damage_start = clock();
            //IF_hurt = 1;
            player->Change_IF_hurt(1);
        }

        else if(x==player->GetX()&&y==player->GetY()&&player->GetItemNumber()!=TRANFROM&&damage_duration>0.8&&player->Get_IF_hurt()==1){
            player->GetDamage(10);
            damage_start = clock();
        }

		MonsterSlower();           //Tell monster action how many step

		targetX = player->GetX();
		targetY = player->GetY();
		if(nextTargetX==x||canMoveX==0||targetX==x)
			nextTargetX = -1;
		if(nextTargetY==y||canMoveY==0||targetY==y)
			nextTargetY = -1;
		if(duration>=MovingTime){
			targetX = player->GetX();
			targetY = player->GetY();
			start=clock();
			if(x>targetX)
				detectX = x-1;
			else if(x<targetX)
				detectX = x+1;

			if(y>targetY)
				detectY = y-1;
			else if(y<targetY)
				detectY = y+1;

			if(Map::GetMap(detectX,y)==WALL||Map::GetMap(detectX,y)==DEAD_END)
				canMoveX = 0;
			if(Map::GetMap(x,detectY)==WALL||Map::GetMap(x,detectY)==DEAD_END)
				canMoveY = 0;
			if(nextTargetX==x||canMoveX==0||targetX==x)
				nextTargetX=-1;
			if(nextTargetY==y||canMoveY==0||targetY==y)
				nextTargetY=-1;

			if(player->GetItemNumber()==TRANFROM){
				if(x>player->GetX()&&Map::GetMap(x+1,y)!=WALL){
					gotoxy(x,y);
					cout<<" ";
					GetItem();
					x++;
				}
				else if(x<player->GetX()&&Map::GetMap(x-1,y)!=WALL){
					gotoxy(x,y);
					cout<<" ";
					GetItem();
					x--;
				}
				if(y>player->GetY()&&Map::GetMap(x,y+1)!=WALL){
					gotoxy(x,y);
					cout<<" ";
					GetItem();
					y++;
				}
				else if(y<player->GetY()&&Map::GetMap(x,y-1)!=WALL){
					gotoxy(x,y);
					cout<<" ";
					GetItem();
					y--;
				}
			}
			else{
				if(nextTargetX==-1&&nextTargetY==-1){
					if(canMoveX&&canMoveY){
						if(priorityX==0 && priorityY==0){
							ActionX();
							ActionY();
						}else if(priorityX==1){
							ActionX();
							priorityX=0;
						}else if(priorityY==1){
							ActionY();
							priorityY=0;
						}
					}
					else{
						int upMove = 1, downMove = 1;
						int rightMove = 1, leftMove = 1;
						for(to_bottom=1;to_bottom<HEIGHT;to_bottom++){
							if(Map::GetMap(x,y+to_bottom)==WALL||Map::GetMap(x,y+to_bottom)==DEAD_END){
								downMove=0;
								to_bottom=100;
								break;
							}
							if(Map::GetMap(detectX,y+to_bottom)!=WALL&&Map::GetMap(detectX,y+to_bottom)!=DEAD_END){
								break;
							}
						}
						for(to_top=1;to_top<HEIGHT;to_top++){
							if(Map::GetMap(x,y-to_top)==WALL||Map::GetMap(x,y-to_top)==DEAD_END){
								upMove=0;
								to_top=100;
								break;
							}
							if(Map::GetMap(detectX,y-to_top)!=WALL&&Map::GetMap(detectX,y-to_top)!=DEAD_END){
								break;
							}
						}

						for(to_right=1;to_right<WIDTH;to_right++){
							if(Map::GetMap(x+to_right,y)==WALL||Map::GetMap(x+to_right,y)==DEAD_END){
								rightMove=0;
								to_right=100;
								break;
							}
							if(Map::GetMap(x+to_right,detectY)!=WALL&&Map::GetMap(x+to_right,detectY)!=DEAD_END){
								break;
							}
						}
						for(to_left=1;to_left<WIDTH;to_left++){
							if(Map::GetMap(x-to_left,y)==WALL||Map::GetMap(x-to_left,y)==DEAD_END){
								leftMove=0;
								to_left=100;
								break;
							}
							if(Map::GetMap(x-to_left,detectY)!=WALL&&Map::GetMap(x-to_left,detectY)!=DEAD_END){
								break;
							}
						}
						if(((!canMoveX&&!upMove&&!downMove)||(!canMoveY&&!rightMove&&!leftMove))&&(player->GetX()!=x||player->GetY()!=y)){
							if(Map::GetMap(x+1,y)!=WALL&&Map::GetMap(x+1,y)!=DEAD_END){
								targetX = x+1;
								ActionX();
							}else if(Map::GetMap(x-1,y)!=WALL&&Map::GetMap(x-1,y)!=DEAD_END){
								targetX = x-1;
								ActionX();
							}else if(Map::GetMap(x,y+1)!=WALL&&Map::GetMap(x,y+1)!=DEAD_END){
								targetY = y+1;
								ActionY();
							}else if(Map::GetMap(x,y-1)!=WALL&&Map::GetMap(x,y-1)!=DEAD_END){
								targetY = y-1;
								ActionY();
							}
							Map::SetItem(originalX,originalY,DEAD_END);
						}
						if(canMoveX==0){
							if(abs(targetY-(y+to_bottom))>abs(targetY-(y-to_top))&&upMove){
								targetY = y-to_top;
								int i;
								if(x<targetX){
									for(i=1;i<=abs(targetX-x);i++){
										if(Map::GetMap(x+i,targetY)==WALL||Map::GetMap(x+i,targetY)==DEAD_END)
											break;
									}
									nextTargetX = x+i-1;
								}
								else if(x>targetX){
									for(i=-1;i<=abs(targetX-x);i--){
										if(Map::GetMap(x+i,targetY)==WALL||Map::GetMap(x+i,targetY)==DEAD_END)
											break;
									}
									nextTargetX = x+i+1;
								}else
									nextTargetX = -1;
							}
							else if(abs(targetY-(y+to_bottom))<abs(targetY-(y-to_top))&&downMove){
								targetY = y+to_bottom;
								int i;
								if(x<targetX){
									for(i=1;i<=abs(targetX-x);i++){
										if(Map::GetMap(x+i,targetY)==WALL||Map::GetMap(x+i,targetY)==DEAD_END)
											break;
									}
									nextTargetX = x+i-1;
								}
								else if(x>targetX){
									for(i=-1;i<=abs(targetX-x);i--){
										if(Map::GetMap(x+i,targetY)==WALL||Map::GetMap(x+i,targetY)==DEAD_END)
											break;
									}
									nextTargetX = x+i+1;
								}else
									nextTargetX = -1;
							}
							else{
								if(targetX>x){
									for(int n=1;n<abs(targetX-x);n++){
										if(Map::GetMap(x+n,y+to_bottom)==WALL||downMove==0){
											targetY = y-to_top;
											break;
										}
										else if(Map::GetMap(x+n,y-to_top)==WALL||upMove==0){
											targetY = y+to_bottom;
											break;
										}else targetY = y+to_bottom;
									}
								}else if(targetX<x){
									for(int n=1;abs(n)<abs(targetX-x);n--){
										if(Map::GetMap(x+n,y+to_bottom)==WALL||downMove==0){
											targetY = y-to_top;
											break;
										}
										else if(Map::GetMap(x+n,y-to_top)==WALL||upMove==0){
											targetY = y+to_bottom;
											break;
										}else targetY = y+to_bottom;
									}
								}
							}
							if(upMove || downMove){
								ActionY();
								priorityX=1;
							}
						}
						if(canMoveY==0){
							if(abs(targetX-(x+to_right))>abs(targetX-(x-to_left))&&leftMove){
								targetX = x-to_left;
								int i;
								if(targetY>y){
									for(i=1;i<=abs(targetY-y);i++){
										if(Map::GetMap(targetX,y+i)==WALL||Map::GetMap(targetX,y+i)==DEAD_END)
											break;
									}
									nextTargetY = y+i-1;
								}else if(targetY<y){
									for(i=-1;i<=abs(targetY-y);i--){
										if(Map::GetMap(targetX,y+i)==WALL||Map::GetMap(targetX,y+i)==DEAD_END)
											break;
									}
									nextTargetY = y+i+1;
								}else
									nextTargetY = -1;
							}

							else if(abs(targetX-(x+to_right))<abs(targetX-(x-to_left))&&rightMove){
								targetX = x+to_right;
								int i;
								if(targetY>y){
									for(i=1;i<=abs(targetY-y);i++){
										if(Map::GetMap(targetX,y+i)==WALL||Map::GetMap(targetX,y+i)==DEAD_END)
											break;
									}
									nextTargetY = y+i-1;
								}else if(targetY<y){
									for(i=-1;i<=abs(targetY-y);i--){
										if(Map::GetMap(targetX,y+i)==WALL||Map::GetMap(targetX,y+i)==DEAD_END)
											break;
									}
									nextTargetY = y+i+1;
								}else
									nextTargetY = -1;
							}
							else{
								if(targetY>y){
									for(int n=1;n<abs(targetY-y);n++){
										if(Map::GetMap(x+to_right,y+n)==WALL||rightMove==0){
											targetX = x-to_left;
											break;
										}
										if(Map::GetMap(x-to_left,y+n)==WALL||leftMove==0){
											targetX = x+to_right;
											break;
										}else targetX = x+to_right;
									}
								}else if(targetY<y){
									for(int n=1;abs(n)<abs(targetY-y);n--){
										if(Map::GetMap(x+to_right,y+n)==WALL||rightMove==0){
											targetX = x-to_left;
											break;
										}
										else if(Map::GetMap(x-to_left,y+n)==WALL||leftMove==0){
											targetX = x+to_right;
											break;
										}else targetX = x+to_right;
									}
								}
							}
							if(rightMove || leftMove){
								ActionX();
								priorityY=1;
							}
						}
					}

				}else{
					if(nextTargetX!=-1){
						targetX = nextTargetX;
						ActionX();
					}
					if(nextTargetY!=-1){
						targetY = nextTargetY;
						ActionY();
					}
				}
				originalX = x;
				originalY = y;
	            /*if(x==player->GetX()&&y==player->GetY()&&player->GetItemNumber()!=TRANFROM){
	                player->GetDamage(DAMAGE);
	            }*/
			}
		}
		Print();
	}

};

class FireBall
{
private:
    short x;
    short y;
    clock_t Fire_start;
	clock_t Fire_finish;
    double duration;
public:
    FireBall(int born_x, int born_y)
    {
        x=born_x;
        y=born_y;
        Fire_start = clock();
        gotoxy(x, y);
        cout<<"F";
    }

    void Fire_UP()
    {
        Fire_finish = clock();
        duration=(double)(Fire_finish - Fire_start) / CLOCKS_PER_SEC;
        if(duration>0.1)
        {
            Fire_start = clock();
            gotoxy(x, y);
            cout<<" ";
            y--;
            Map::SetItem(x, y, SPACE);
            gotoxy(x,y);
            cout<<"F";
        }
    }

    void Fire_DOWN()
    {
        Fire_finish = clock();
        duration=(double)(Fire_finish - Fire_start) / CLOCKS_PER_SEC;

        if(duration>0.1)
        {
            Fire_start = clock();
            gotoxy(x, y);
            cout<<" ";
            y++;
            Map::SetItem(x, y, SPACE);
            gotoxy(x,y);
            cout<<"F";
        }
    }

    void Fire_LEFT()
    {
        Fire_finish = clock();
        duration=(double)(Fire_finish - Fire_start) / CLOCKS_PER_SEC;
        if(duration>0.1)
        {
            Fire_start = clock();
            gotoxy(x, y);
            cout<<" ";
            x--;
            Map::SetItem(x, y, SPACE);
            gotoxy(x,y);
            cout<<"F";
        }
    }

    void Fire_RIGHT()
    {
        Fire_finish = clock();
        duration=(double)(Fire_finish - Fire_start) / CLOCKS_PER_SEC;

        if(duration>0.1)
        {
            Fire_start = clock();
            gotoxy(x, y);
            cout<<" ";
            x++;
            Map::SetItem(x, y, SPACE);
            gotoxy(x,y);
            cout<<"F";
        }
    }

    short GetX()
    {
        return x;
    }

    short GetY()
    {
        return y;
    }


    ~FireBall()
    {
        gotoxy(x,y);
		cout<<" ";
    }
};

class FireBall_Monster: public Monster
{
    FireBall *fire;
    bool IF_run_fireball;
    char direction;
public:
    FireBall_Monster(People *newplayer):Monster(newplayer)
    {
        fire = NULL;
        IF_run_fireball=0;
    }

    ~FireBall_Monster()
    {
        delete fire;
        IF_run_fireball=0;
    }


    void Action(){
		if(IF_run_fireball == 0)//if there's no fireball to run, then new a fireball
        {
            if(x==player->GetX() && player->GetItemNumber()!=TRANFROM)
            {
                if(y>player->GetY())    //Monster's below player
                {
                    fire = new FireBall(x, y);
                    direction = 'U';
                    IF_run_fireball=1;
                }

                else if(y<player->GetY())
                {
                    fire = new FireBall(x, y);
                    direction = 'D';
                    IF_run_fireball=1;
                }
            }

            if(y==player->GetY() && player->GetItemNumber()!=TRANFROM)
            {
                if(x>player->GetX())    //Monster's on the right side of the player
                {
                    fire = new FireBall(x, y);
                    direction = 'L';
                    IF_run_fireball=1;
                }
                else if(x<player->GetX())
                {
                    fire = new FireBall(x, y);
                    direction = 'R';
                    IF_run_fireball=1;
                }
            }
        }

        if(IF_run_fireball)
        {
            switch(direction)
            {
            case 'U':

                if(Map::GetMap(fire->GetX(), fire->GetY()-1) == WALL)
                {
                    delete fire;
                    fire = NULL;
                    IF_run_fireball = 0;
                    break;
                }
                fire->Fire_UP();
                break;

            case 'D':

                if(Map::GetMap(fire->GetX(), fire->GetY()+1) == WALL)
                {
                    delete fire;
                    fire = NULL;
                    IF_run_fireball = 0;
                    break;
                }
                fire->Fire_DOWN();
                break;

            case 'L':

                if(Map::GetMap((fire->GetX()-1), (fire->GetY())) == WALL)
                {
                    delete fire;
                    fire = NULL;
                    IF_run_fireball = 0;
                    break;
                }

                fire->Fire_LEFT();
                break;



            case 'R':

                if(Map::GetMap(fire->GetX()+1, fire->GetY()) == WALL)
                {
                    delete fire;
                    fire = NULL;
                    IF_run_fireball = 0;
                    break;
                }
                fire->Fire_RIGHT();
                break;

            default: break;
            }


            if(fire)
            {
                if((fire->GetX()==player->GetX())&&(fire->GetY()==player->GetY()))
                {
                    player->GetDamage(20);
                    delete fire;
                    fire = NULL;
                    IF_run_fireball = 0;
                }

            }
        }
        Monster::Action();
	}
};


class Linkedlist_Node{
private:
    People *player;
	Node *p;
public:
	Linkedlist_Node(People *newplayer){
		p=NULL;
		player=newplayer;
	}
	void Insert(Node *newnode){
		if(p==NULL){
			p = newnode;
			p->next = p;
		}else{
			newnode->next = p->next;
			p->next = newnode;
		}
	}
	void PrintList(){
		Node *n = p;
		player->Print();
		do{
			n->Print();
			n = n->next;
		}while(n != p);
	}
	void ActionList(){
		Node *n = p;
		do{
			n->Action();
			n = n->next;
		}while(n != p);
	}
	void DeleteMonster()
    {
        p = player;
        Node *n = p;
        if(player->GetItemNumber()==REMOVE){
            do{
                if(n->next->GetNodeNumber()==MONSTER){
                    DeleteList(n,n->next);
                }
                n = n->next;
            }while(n != p);

            if(n->next->GetNodeNumber()==MONSTER){
                DeleteList(n,n->next);
            }
        }
    }
	void ItemTranform(){
		Node *n = p;
		do{
			if(player->GetItemNumber()==TRANFROM){
				if(n->next->GetNodeNumber()==MONSTER && n->next->GetX()==player->GetX() && n->next->GetY()==player->GetY()){
					DeleteList(n,n->next);
				}
			}
			n = n->next;
		}while(n != p);
	}
	void PlayerDie(){
		Node *n = p;
		do{
			if(n->next->GetNodeNumber()==PEOPLE && player->GetHP()<=0)
				DeleteList(n,n->next);
			n = n->next;
		}while(n!=p);
	}
	void DeleteList(Node *a,Node *b){
		p=a;
		p->next = a->next->next;
		delete b;
	}
};

class UI{
private:
	People *player;
	clock_t start;
	clock_t finish;
	double time = 0;
public:
	UI(People *newplayer){
		start = clock();
		player = newplayer;
	}
	void Action(Linkedlist_Node *listnode){
		Node *newMonster;

		double duration;
		finish=clock();
		duration=(double)(finish - start) / CLOCKS_PER_SEC;
		if(duration>=MONSTER_GENRATEION_TIME){
			newMonster = new FireBall_Monster(player);  //the FireBall monster
            listnode->Insert(newMonster);
            start=clock();
		}
		listnode->ActionList();
		listnode->DeleteMonster();
		listnode->ItemTranform();
		listnode->PlayerDie();
	}
};




int main(){
	srand(time(NULL));
	HideCursor();
	cout<<"Rule:"<<endl;
	cout<<"First: The player will get 10 damage when being touched by the monsters"<<endl;
	cout<<"Second: The effect of each item lasts for 5 seconds, except B and H and R"<<endl;
	cout<<"Third: The player can get 10 points by killing a monster"<<endl;
	cout<<"Fourth: The game will end as long as the player's HP reaches zero"<<endl;
	cout<<"\n"<<endl;
	cout<<"Start the game by pressing any key"<<endl;
	(void)getch();
	system("cls");
	Map *map = new Map;
	People *p = new People;
	Linkedlist_Node *listnode= new Linkedlist_Node(p);
	FireBall_Monster *m = new FireBall_Monster(p);
	UI *u = new UI(p);
	Item *item = new Item;

	listnode->Insert(p);
	listnode->Insert(m);

	map->Print();
	listnode->PrintList();

	while(1){
		item->Produce();
		u->Action(listnode);
	}
}
