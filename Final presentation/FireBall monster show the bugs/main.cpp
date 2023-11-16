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
		n=0;
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
/*
	void Delete_Print(){
		for(int i=0;i<WIDTH;i++){
			for(int j=0;j<HEIGHT;j++){
				if(map[i][j] == SPACE){
					gotoxy(i,j);
					cout<<" ";
				}
			}
		}
	}
*/
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
		if(duration>=4){
			do{
				x=rand()%(WIDTH-1);
				y=rand()%(HEIGHT-1);
			}while(Map::GetMap(x,y)!=SPACE);
			ItemNumber = rand()%5+3;
			ItemNumber = REMOVE;////////////////////////////////////////////////////////////////////////////////////////////////////////
			Map::SetItem(x,y,ItemNumber);
			Print();
			start = clock();
		}
	}
	void Print(){
		gotoxy(x,y);

		switch(ItemNumber){////////////////////////////////////////////////////////////////////////////////////////////////////////
			case FASTER:
				cout<<"F";
				break;
			case SLOWER:
				cout<<"S";
				break;
			case REMOVE:
				cout<<"R";
				break;
			case TRANFROM:
				cout<<"T";
				break;
			case HEAL:
				cout<<"H";
				break;
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
	virtual ~Node(){};
	int NodeNumber;
};

class People:public Node{
private:
	short x;
	short y;
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
		hp = 1000;
		point = 0;
		ItemNumber = NoItem;
	    do{
			x=rand()%(WIDTH-1)+1;
			y=rand()%(HEIGHT-1)+1;
		}while(Map::GetMap(x,y)!=SPACE);
	}
	People(bool i){
		hp = 2000;
		point = 0;
		ItemNumber = NoItem;
	    x=10;
        y=5;
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
		else if(Map::GetMap(x,y)==HEAL){    //HEAL
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
		int g=GetItem();
		switch(g){
			case FASTER:
				Buff_F=1;
				//GenerallyAction();
				break;
			case HEAL: //Heal
				 Buff_F=0;
				 FullHp();
				 break;
			case TRANFROM:
				ItemNumber = TRANFROM;
				break;
			default:
				//cout<<"Generally";
				//GenerallyAction();
				Buff_F=0;
				break;
		}

	//void GenerallyAction(){
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
                    }
                }
                //GetBUFF();
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
                    }
                }
                //GetBUFF();
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
                    }
                }
                //GetBUFF();
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
                    }
                }
                //GetBUFF();
                IF_hurt = 0;
			    break;
            case -1:
                break;
		}

		gotoxy(0,HEIGHT+5);
		cout<<"HP:"<<hp<<"      "<<endl;
		cout<<"SCORE:"<<point<<"      "<<endl;
		cout<<"BUFF:"<<ItemNumber<<"      "<<endl;

	}
	void FullHp(){
		hp = 100;
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
	int MovingTime=1;
	int NodeNumber=MONSTER;
	double damage_duration;
public:
	Monster(People *ppp){
		do{
			x=rand()%(WIDTH-1)+1;
			y=rand()%(HEIGHT-1)+1;
		}while(Map::GetMap(x,y)!=SPACE);
		start=clock();
		player=ppp;
		detectX = x;
		detectY = y;
		originalX = x;
		originalY = y;
	}


	Monster(bool i, People *ppp){
		x=2;
        y=5;
		start=clock();
		player=ppp;
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
			cout<<"R";
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
			MovingTime=2;
		else
			MovingTime=1;
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
		int xi=0, xj=0, yi=0, yj=0;
		finish=clock();
		damage_finish = clock();
		double duration=(double)(finish - start) / CLOCKS_PER_SEC;
		damage_duration=(double)(damage_finish - damage_start) / CLOCKS_PER_SEC;


		if(x==player->GetX()&&y==player->GetY()&&player->GetItemNumber()!=TRANFROM&&damage_duration>0.1&&player->Get_IF_hurt()==0){
            player->GetDamage(10);
            damage_start = clock();
            //IF_hurt = 1;
            player->Change_IF_hurt(1);
        }
/*
        else if(x==player->GetX()&&y==player->GetY()&&player->GetItemNumber()!=TRANFROM&&damage_duration>0.8&&player->Get_IF_hurt()==1){
            player->GetDamage(10);
            damage_start = clock();
        }*/
		MonsterSlower();           //Tell monster action how many step
		if(duration>=0.5/*MovingTime*/){
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
					else{//嚙???P?_
						int upMove = 1, downMove = 1;
						int rightMove = 1, leftMove = 1;
						for(xi=1;xi<HEIGHT;xi++){
							if(Map::GetMap(x,y+xi)==WALL||Map::GetMap(x,y+xi)==DEAD_END){
								downMove=0;
								xi=100;
								break;
							}
							if(Map::GetMap(detectX,y+xi)!=WALL&&Map::GetMap(detectX,y+xi)!=DEAD_END){
								break;
							}
						}
						for(xj=1;xj<HEIGHT;xj++){
							if(Map::GetMap(x,y-xj)==WALL||Map::GetMap(x,y-xj)==DEAD_END){
								upMove=0;
								xj=100;
								break;
							}
							if(Map::GetMap(detectX,y-xj)!=WALL&&Map::GetMap(detectX,y-xj)!=DEAD_END){
								break;
							}
						}

						for(yi=1;yi<WIDTH;yi++){
							if(Map::GetMap(x+yi,y)==WALL||Map::GetMap(x+yi,y)==DEAD_END){
								rightMove=0;
								yi=100;
								break;
							}
							if(Map::GetMap(x+yi,detectY)!=WALL&&Map::GetMap(x+yi,detectY)!=DEAD_END){
								break;
							}
						}
						for(yj=1;yj<WIDTH;yj++){
							if(Map::GetMap(x-yj,y)==WALL||Map::GetMap(x-yj,y)==DEAD_END){
								leftMove=0;
								yj=100;
								break;
							}
							if(Map::GetMap(x-yj,detectY)!=WALL&&Map::GetMap(x-yj,detectY)!=DEAD_END){
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
							if(abs(targetY-(y+xi))>abs(targetY-(y-xj))&&upMove){
								targetY = y-xj;
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
							else if(abs(targetY-(y+xi))<abs(targetY-(y-xj))&&downMove){
								targetY = y+xi;
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
							else if(abs(targetY-(y+xi))==abs(targetY-(y-xj))){
								if(targetX>x){
									for(int n=1;n<abs(targetX-x);n++){
										if(Map::GetMap(x+n,y+xi)==WALL||downMove==0){
											targetY = y-xj;
											break;
										}
										else if(Map::GetMap(x+n,y-xj)==WALL||upMove==0){
											targetY = y+xi;
											break;
										}else targetY = y+xi;
									}
								}else if(targetX<x){
									for(int n=1;abs(n)<abs(targetX-x);n--){
										if(Map::GetMap(x+n,y+xi)==WALL||downMove==0){
											targetY = y-xj;
											break;
										}
										else if(Map::GetMap(x+n,y-xj)==WALL||upMove==0){
											targetY = y+xi;
											break;
										}else targetY = y+xi;
									}
								}
							}
							if(upMove || downMove){
								ActionY();
								priorityX=1;
							}
						}
						if(canMoveY==0){
							if(abs(targetX-(x+yi))>abs(targetX-(x-yj))&&leftMove){
								targetX = x-yj;
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

							else if(abs(targetX-(x+yi))<abs(targetX-(x-yj))&&rightMove){
								targetX = x+yi;
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
							else if(abs(targetX-(x+yi))==abs(targetX-(x-yj))){
								if(targetY>y){
									for(int n=1;n<abs(targetY-y);n++){
										if(Map::GetMap(x+yi,y+n)==WALL||rightMove==0){
											targetX = x-yj;
											break;
										}
										if(Map::GetMap(x-yj,y+n)==WALL||leftMove==0){
											targetX = x+yi;
											break;
										}else targetX = x+yi;
									}
								}else if(targetY<y){
									for(int n=1;abs(n)<abs(targetY-y);n--){
										if(Map::GetMap(x+yi,y+n)==WALL||rightMove==0){
											targetX = x-yj;
											break;
										}
										else if(Map::GetMap(x-yj,y+n)==WALL||leftMove==0){
											targetX = x+yi;
											break;
										}else targetX = x+yi;
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
	            if(x==player->GetX()&&y==player->GetY()&&player->GetItemNumber()!=TRANFROM){
	                player->GetDamage(DAMAGE);
	            }
			}
		}
		Print();
	}
};

class FireBall//:public Monster
{
private:
    short x;
    short y;
    clock_t Fire_start;
	clock_t Fire_finish;
	//float duration;
    double duration;
    People *player;
    //static bool able_to_recast;
    bool able_to_recast;
	int run_time = 0;
	FireBall *for_deletion;

public:
    FireBall(int born_x, int born_y, FireBall *fff)
    {
        //player=ppp;
        x=born_x;
        y=born_y;

        //Fire_finish = clock();
        //X=x;
        //Y=y;
        Fire_start = clock();
        able_to_recast = 0;
        gotoxy(x, y);
        cout<<"F";
        for_deletion = fff;
    }

    void Fire_UP(People *player)
    {
        //duration = Fire_finish - Fire_start;
        //run_time++;

        Fire_finish = clock();
        if(x==player->GetX() && y==player->GetY())  //Player die immediately
        {
            player->GetDamage(20);
            delete this;
        }
        duration=(double)(Fire_finish - Fire_start) / CLOCKS_PER_SEC;

        if(duration>0.1)
        {
            Fire_start = clock();
            gotoxy(x, y);
            cout<<" ";
            if(Map::GetMap(x, y-1) == WALL)
                delete this;

            else
            {
                gotoxy(x, y);
                cout<<" ";
                y--;
                Map::SetItem(x, y, SPACE);
                gotoxy(x,y);
                cout<<"F";
            }
        }
    }

    void Fire_DOWN(People *player)
    {
        //duration = Fire_finish - Fire_start;
        //run_time++;

        Fire_finish = clock();
        if(x==player->GetX() && y==player->GetY())  //Player die immediately
        {
            player->GetDamage(20);
            delete this;
        }
        duration=(double)(Fire_finish - Fire_start) / CLOCKS_PER_SEC;

        if(duration>0.1)
        {
            Fire_start = clock();
            gotoxy(x, y);
            cout<<" ";
            if(Map::GetMap(x, y+1) == WALL)
                delete this;

            else
            {
                gotoxy(x, y);
                cout<<" ";
                y++;
                Map::SetItem(x, y, SPACE);
                gotoxy(x,y);
                cout<<"F";
            }
        }
    }

    void Fire_LEFT(People *player)
    {
        //duration = Fire_finish - Fire_start;
        //run_time++;

        Fire_finish = clock();
        if(x==player->GetX() && y==player->GetY())  //Player die immediately
        {
            player->GetDamage(20);
            delete this;
        }
        duration=(double)(Fire_finish - Fire_start) / CLOCKS_PER_SEC;

        if(duration>0.1)
        {
            Fire_start = clock();
            gotoxy(x, y);
            cout<<" ";
            if(Map::GetMap(x-1, y) == WALL)
                delete this;

            else
            {
                gotoxy(x, y);
                cout<<" ";
                x--;
                Map::SetItem(x, y, SPACE);
                gotoxy(x,y);
                cout<<"F";
            }
        }
    }

    void Fire_RIGHT(People *player)
    {
        //duration = Fire_finish - Fire_start;
        //run_time++;

        Fire_finish = clock();
        if(x==player->GetX() && y==player->GetY())  //Player die immediately
        {
            player->GetDamage(20);
            delete this;
        }
        duration=(double)(Fire_finish - Fire_start) / CLOCKS_PER_SEC;

        if(duration>0.1)
        {
            Fire_start = clock();
            gotoxy(x, y);
            cout<<" ";
            if(Map::GetMap(x+1, y) == WALL)
                delete this;

            else
            {
                gotoxy(x, y);
                cout<<" ";
                x++;
                Map::SetItem(x, y, SPACE);
                gotoxy(x,y);
                cout<<"F";
            }
        }
    }

    /*static*/ bool Return_able_to_recast()
    {
        return able_to_recast;
    }

    ~FireBall()
    {
        gotoxy(x,y);
		cout<<" ";
		gotoxy(0, HEIGHT+15);
		cout<<"for_deletion = "<<for_deletion<<endl;
        able_to_recast = 1;
        for_deletion = NULL;
        cout<<"for_deletion = "<<for_deletion<<endl;
    }
};
//bool FireBall::able_to_recast = 0;


class FireBall_Monster: public Monster
{
    FireBall *fire;
    bool IF_run_fireball;
    char direction;
public:
    FireBall_Monster(People *ppp):Monster(ppp)
    {
        //player=ppp;
        fire = NULL;
        IF_run_fireball=0;
    }
    FireBall_Monster(bool i, People *ppp):Monster(i, ppp)
    {
        fire = NULL;
        IF_run_fireball=0;
    }

    ~FireBall_Monster()
    {
        //player=ppp;
        delete fire;
        IF_run_fireball=0;
    }




    void Action(){
        bool Only_once;
        Only_once = 0;
		if(IF_run_fireball)
        {
            switch(direction)
            {
            case 'U':
                fire->Fire_UP(player);
                break;

            case 'D':
                fire->Fire_DOWN(player);
                break;

            case 'R':
                fire->Fire_RIGHT(player);
                break;

            case 'L':
                fire->Fire_LEFT(player);
                break;
            default: break;
            }
            //fire->Fire_UP(player);
            if(fire)
            {
                gotoxy(0, HEIGHT+18);
                cout<<"fire = "<<fire<<endl;
                IF_run_fireball = !(fire->Return_able_to_recast());


            }
            else
            {
                gotoxy(0, HEIGHT+17);
                cout<<"fire = "<<fire<<endl;
                gotoxy(0, HEIGHT+17);
                cout<<"                                             "<<fire<<endl;


            }

            //gotoxy(0, HEIGHT+15);
            //cout<<"IF_run_fireball = "<<IF_run_fireball<<"           "<<endl;
            Only_once = 1;
        }


		if(x==player->GetX()&&player->GetItemNumber()!=TRANFROM)
        {
            if(y>player->GetY())    //Monster's below player
            {
                if(IF_run_fireball == 0)
                {
                    fire = new FireBall(x, y, fire);
                    direction = 'U';
                    IF_run_fireball=1;
                }
                if(Only_once == 1)
                {                }
                else
                    fire->Fire_UP(player);
            }
            else if(y<player->GetY())
            {
                if(IF_run_fireball == 0)
                {
                    fire = new FireBall(x, y, fire);
                    direction = 'D';
                    IF_run_fireball=1;
                }
                if(Only_once == 1)
                {                }
                else
                    fire->Fire_DOWN(player);
            }
        }

        if(y==player->GetY()&&player->GetItemNumber()!=TRANFROM)
        {
            if(x>player->GetX())    //Monster's on the right side of the player
            {
                if(IF_run_fireball == 0)
                {
                    fire = new FireBall(x, y, fire);
                    direction = 'L';
                    IF_run_fireball=1;
                }
                if(Only_once == 1)
                {                }
                else
                    fire->Fire_LEFT(player);
            }
            else if(x<player->GetX())
            {
                if(IF_run_fireball == 0)
                {
                    fire = new FireBall(x, y, fire);
                    direction = 'R';
                    IF_run_fireball=1;
                }
                if(Only_once == 1)
                {                }
                else
                    fire->Fire_RIGHT(player);
            }
        }
        Monster::Action();
	}
};

/*
class FireBall//:public Monster //NEW
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

    void Fire_UP(People *player)
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

    void Fire_DOWN(People *player)
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

    void Fire_LEFT(People *player)
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

    void Fire_RIGHT(People *player)
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


class FireBall_Monster: public Monster //NEW
{
    FireBall *fire;
    bool IF_run_fireball;
    char direction;
public:
    FireBall_Monster(People *ppp):Monster(ppp)
    {
        fire = NULL;
        IF_run_fireball=0;
    }

    FireBall_Monster(bool i, People *ppp):Monster(i, ppp)
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
		if(x==player->GetX() && player->GetItemNumber()!=TRANFROM)
        {
            if(y>player->GetY())    //Monster's below player
            {
                if(IF_run_fireball == 0)//if there's no fireball to run, then new a fireball
                {
                    fire = new FireBall(x, y);
                    direction = 'U';
                    IF_run_fireball=1;
                }
            }
            else if(y<player->GetY())
            {
                if(IF_run_fireball == 0)
                {
                    fire = new FireBall(x, y);
                    direction = 'D';
                    IF_run_fireball=1;
                }
            }
        }

        if(y==player->GetY() && player->GetItemNumber()!=TRANFROM)
        {
            if(x>player->GetX())    //Monster's on the right side of the player
            {
                if(IF_run_fireball == 0)
                {
                    fire = new FireBall(x, y);
                    direction = 'L';
                    IF_run_fireball=1;
                }
            }
            else if(x<player->GetX())
            {
                if(IF_run_fireball == 0)
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
                fire->Fire_UP(player);
                break;

            case 'D':

                if(Map::GetMap(fire->GetX(), fire->GetY()+1) == WALL)
                {
                    delete fire;
                    fire = NULL;
                    IF_run_fireball = 0;
                    break;
                }
                fire->Fire_DOWN(player);
                break;

            case 'L':
                if(Map::GetMap((fire->GetX()-1), (fire->GetY())) == WALL)
                {
                    delete fire;
                    fire = NULL;
                    IF_run_fireball = 0;
                    break;
                }

                fire->Fire_LEFT(player);
                break;



            case 'R':

                if(Map::GetMap(fire->GetX()+1, fire->GetY()) == WALL)
                {
                    delete fire;
                    fire = NULL;
                    IF_run_fireball = 0;
                    break;
                }
                fire->Fire_RIGHT(player);
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
*/

class Linkedlist_Node{
private:
    People *player;
	Node *p;
	//Map *map;
public:
	Linkedlist_Node(People *ppp){
		p=NULL;
		player=ppp;
		//map = m;
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
	//short x;
	//short y;
	People *player;
	clock_t start;
	clock_t finish;

public:
	UI(People *ppp){
		start=clock();
		player=ppp;
	}
	void Action(Linkedlist_Node *listnode){
		Node *newMonster;

		double duration;
		finish=clock();
		duration=(double)(finish - start) / CLOCKS_PER_SEC;
		if(duration>=20){
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
	/*cout<<"Rule:"<<endl;
	cout<<"First: The player will get 10 damage when being touched by the monsters"<<endl;
	cout<<"Second: The effect of each item lasts for 5 seconds, except B and H and R"<<endl;
	cout<<"Third: The player can get 10 points by killing a monster"<<endl;
	cout<<"Fourth: The game will end as long as the player's HP reaches zero"<<endl;
	//cout<<"Note: You will die immediately when being touched by the fireballs (symbol: f) "<<endl;
	cout<<"\n"<<endl;
	cout<<"Start the game by pressing any key"<<endl;
	(void)getch();*/
	system("cls");
	Map *map = new Map;
	People *p = new People(1);
	Linkedlist_Node *listnode= new Linkedlist_Node(p);
	FireBall_Monster *m = new FireBall_Monster(1, p);
//	Pretender *mp = new Pretender(p);
	UI *u = new UI(p);

	Item *item = new Item;
	listnode->Insert(p);
	listnode->Insert(m);
//  listnode->Insert(mp);



	map->Print();
	listnode->PrintList();

	while(1){
		item->Produce();
		u->Action(listnode);
	}
}
