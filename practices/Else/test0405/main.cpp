#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH	100
#define HEIGHT	25

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
	short x;
	short y;
	int thickX, thickY;
	static int map[WIDTH][HEIGHT];
public:
	Map(){
		int n=rand()%10+7;
		int times=0;
		while(n>times){
			x=rand()%WIDTH;
			y=rand()%HEIGHT;
			thickX = rand()%10+1;
			thickY = rand()%8+1;
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
	short x, y;
	int ItemNumber;
	clock_t start;
	clock_t finish;
public:
	Item(){}
	void Produce(){
		finish=clock();
		double duration=(double)(finish - start) / CLOCKS_PER_SEC;
		if(duration>=2){
			do{
				x=rand()%(WIDTH-1);
				y=rand()%(HEIGHT-1);
			}while(Map::GetMap(x,y)!=SPACE);
			ItemNumber = rand()%4+4;
			Map::SetItem(x,y,ItemNumber);
			Print();
			start = clock();
		}
	}
	void Print(){
		gotoxy(x,y);
		switch(ItemNumber){
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
	virtual int GetLifeID()=0;
	virtual void DIE()=0;
	virtual int GetX()=0;
	virtual int GetY()=0;
	virtual ~Node(){};
	int NodeNumber;
	int LifeID;
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
		hp = 100;
		point = 0;
		ItemNumber = NoItem;
	    do{
			x=rand()%(WIDTH-1)+1;
			y=rand()%(HEIGHT-1)+1;
		}while(Map::GetMap(x,y)!=SPACE);
	}

	People(bool i){
		hp = 100;
		point = 0;
		ItemNumber = NoItem;
	    x=10;
		y=10;

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
            //gotoxy(0, HEIGHT+7);
            //cout<<"\n\n\nHP = "<<hp<<endl;
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
	int GetLifeID(){
		return LifeID;
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
			return NULL;
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
                }
                if(Buff_F)                          //If buff_f is 1, move one more time.
                {
                    if(Map::GetMap(x,y-1) != WALL)
                    {
                        gotoxy(x,y);
                        cout<<" ";
                        y--;
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
                }
                if(Buff_F)                          //If buff_f is 1, move one more time.
                {
                    if(Map::GetMap(x-1,y) != WALL)
                    {
                        gotoxy(x,y);
                        cout<<" ";
                        x--;
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
                }
                if(Buff_F)                          //If buff_f is 1, move one more time.
                {
                    if(Map::GetMap(x,y+1) != WALL)
                    {
                        gotoxy(x,y);
                        cout<<" ";
                        y++;
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
                }
                if(Buff_F)                          //If buff_f is 1, move one more time.
                {
                    if(Map::GetMap(x+1,y) != WALL)
                    {
                        gotoxy(x,y);
                        cout<<" ";
                        x++;
                    }
                }
                IF_hurt = 0;
                //GetBUFF();
			    break;
		}
        gotoxy(0,HEIGHT+2);
        cout<<"HP:"<<hp<<"      "<<endl;
        cout<<"SCORE:"<<point<<"      "<<endl;
        cout<<"BUFF:"<<ItemNumber<<"      "<<endl;
        cout<<"IF_hurt: "<<IF_hurt<<"      "<<endl;
    }

    bool Get_IF_hurt()
    {
        return IF_hurt;
    }
    void Change_IF_hurt(bool i)
    {
        IF_hurt = i;
    }

	void FullHp(){
		hp = 100;
	}
	void GetDamage(int x){
		hp = hp - x;
	}
	void GetPoint(){
		point = point + 10;
	}
	void DIE(){
		LifeID = 0;
	}
};

class Monster:public Node{
protected:
    People *player;
	short x;
	short y;
	clock_t start;
	clock_t finish;
	clock_t damage_start;
	clock_t damage_finish;
	int MovingTime=1;
	int NodeNumber=MONSTER;
	double damage_duration;
public:
    Monster()
    {

    }
	Monster(People *ppp){
		do{
			x=rand()%(WIDTH-1)+1;
			y=rand()%(HEIGHT-1)+1;
		}while(Map::GetMap(x,y)!=SPACE);
		start=clock();
		player=ppp;
	}
	Monster(bool i, People *ppp){
		x=15;
        y=15;
		start=clock();
		player=ppp;
	}

	~Monster(){
		player->GetPoint();
		gotoxy(x,y);
		cout<<" ";
	}
	int GetLifeID(){
		return LifeID;
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
	virtual void Print(){
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
	}
	void MonsterSlower(){
		if(player->GetItemNumber()==SLOWER)
			MovingTime=2;
		else
			MovingTime=1;
	}
	virtual void Action(){
		double duration;
		finish=clock();
		damage_finish = clock();
		duration=(double)(finish - start) / CLOCKS_PER_SEC;
		damage_duration=(double)(damage_finish - damage_start) / CLOCKS_PER_SEC;


		if(x==player->GetX()&&y==player->GetY()&&player->GetItemNumber()!=TRANFROM&&damage_duration>0.1&&player->Get_IF_hurt()==0){
            player->GetDamage(DAMAGE);
            damage_start = clock();
            //IF_hurt = 1;
            player->Change_IF_hurt(1);
        }

        else if(x==player->GetX()&&y==player->GetY()&&player->GetItemNumber()!=TRANFROM&&damage_duration>0.8&&player->Get_IF_hurt()==1){
            player->GetDamage(DAMAGE);
            damage_start = clock();
        }

		MonsterSlower();           //Tell monster action how many step
		if(duration>=MovingTime){
			start=clock();
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
				if(x==player->GetX()&&y==player->GetY()){
					player->GetDamage(DAMAGE);
				}
				if(x==player->GetX()&&y==player->GetY()&&player->GetItemNumber()==TRANFROM){
					DIE();
				}

			}

			else{
				if(x>player->GetX()&&Map::GetMap(x-1,y)==SPACE){
					gotoxy(x,y);
					cout<<" ";
					GetItem();
					x--;
				}
				else if(x<player->GetX()&&Map::GetMap(x+1,y)==SPACE){
					gotoxy(x,y);
					cout<<" ";
					GetItem();
					x++;
				}
                if(y>player->GetY()&&Map::GetMap(x,y-1)==SPACE){
                    gotoxy(x,y);
                    cout<<" ";
                    GetItem();
                    y--;
                }
                else if(y<player->GetY()&&Map::GetMap(x,y+1)==SPACE){
                    gotoxy(x,y);
                    cout<<" ";
                    GetItem();
                    y++;
                }
			}
		}
		gotoxy(x,y);
		cout<<"M";
	}
	void DIE(){
		LifeID = 0;
	}

};

class Pretender:public Monster{
private:
	int actative_num;
public:
	Pretender(People* ppp):Monster(ppp){
		player = ppp;
		actative_num = 0;
	}
	void Print(){
		if(actative_num==0){
			gotoxy(x,y);
			cout<<"H";
		}
		else{
			gotoxy(x,y);
			cout<<"M";
		}
	}

	void Action(){
		if(player->GetX()==x&&player->GetY()==y){
			actative_num = 1;
		}

		if(actative_num ==1){
            Monster::Action();
		}
		else{
			gotoxy(x,y);
			cout<<"H";
		}
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

public:
    FireBall(int born_x, int born_y)
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
    }

    void Fire_UP(People *player)
    {
        //duration = Fire_finish - Fire_start;
        //run_time++;

        Fire_finish = clock();
        if(x==player->GetX() && y==player->GetY())  //Player die immediately
        {
            player->GetDamage(210);
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
            player->GetDamage(210);
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
            player->GetDamage(210);
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
            player->GetDamage(210);
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
		//gotoxy(0, HEIGHT+15);
		//cout<<"--------------------------------------------------------------"<<endl;
        able_to_recast = 1;
    }
};
//bool FireBall::able_to_recast = 0;


class FireBall_Monster: public Monster
{
    FireBall *fire;
    bool IF_run_fireball;
    char direction;
public:
    FireBall_Monster(People *ppp, bool i):Monster(i, ppp)
    {
        //player=ppp;
        IF_run_fireball=0;
    }

    FireBall_Monster(People *ppp):Monster(ppp)
    {
        //player=ppp;
        IF_run_fireball=0;
    }
    void Print()
    {
        gotoxy(x, y);
        cout<<"M";
    }

    void Action(){
		double duration;
		finish=clock();
		damage_finish=clock();
		duration=(double)(finish - start) / CLOCKS_PER_SEC;
        damage_duration=(double)(damage_finish - damage_start) / CLOCKS_PER_SEC;
/*
		gotoxy(0,HEIGHT+11);
		cout<<"FireBall::Return_able_to_recast = "<<FireBall::Return_able_to_recast<<endl;
        cout<<"IF_run_fireball = "<<IF_run_fireball<<endl;
*/
        bool Only_once;
        Only_once = 0;
/*
        gotoxy(0, HEIGHT+15);
        cout<<"damage_duration = "<<damage_duration<<"           "<<endl;
        cout<<"Player X = "<<player->GetX()<<"           "<<endl;
        cout<<"Player Y = "<<player->GetY()<<"           "<<endl;
        cout<<"Player Get_IF_hurt = "<<player->Get_IF_hurt()<<"           "<<endl;
*/

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
            }
            //fire->Fire_UP(player);
            IF_run_fireball = !(fire->Return_able_to_recast());
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
                    fire = new FireBall(x, y);
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
                    fire = new FireBall(x, y);
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
                    fire = new FireBall(x, y);
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
                    fire = new FireBall(x, y);
                    direction = 'R';
                    IF_run_fireball=1;
                }
                if(Only_once == 1)
                {                }
                else
                    fire->Fire_RIGHT(player);
            }
        }


        if(x==player->GetX()&&y==player->GetY()&&player->GetItemNumber()!=TRANFROM&&damage_duration>0.1&&player->Get_IF_hurt()==0){
            //gotoxy(0, HEIGHT+15);
            //cout<<"--------------------------------------------------------------"<<endl;
            player->GetDamage(DAMAGE);
            damage_start = clock();
            //IF_hurt = 1;
            player->Change_IF_hurt(1);
        }

        else if(x==player->GetX()&&y==player->GetY()&&player->GetItemNumber()!=TRANFROM&&damage_duration>0.8&&player->Get_IF_hurt()==1){
            player->GetDamage(DAMAGE);
            damage_start = clock();
        }

		MonsterSlower();           //Tell monster action how many step
		if(duration>=MovingTime){
			start=clock();
			if(player->GetItemNumber()==TRANFROM)
            {
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
				if(x==player->GetX()&&y==player->GetY()){
					player->GetDamage(DAMAGE);
				}
				if(x==player->GetX()&&y==player->GetY()&&player->GetItemNumber()==TRANFROM){
					DIE();
				}
			}

			else
			{
				if(x>player->GetX()&&Map::GetMap(x-1,y)==SPACE){
					gotoxy(x,y);
					cout<<" ";
					GetItem();
					x--;
				}
				else if(x<player->GetX()&&Map::GetMap(x+1,y)==SPACE){
					gotoxy(x,y);
					cout<<" ";
					GetItem();
					x++;
				}
                if(y>player->GetY()&&Map::GetMap(x,y-1)==SPACE){
                    gotoxy(x,y);
                    cout<<" ";
                    GetItem();
                    y--;
                }
                else if(y<player->GetY()&&Map::GetMap(x,y+1)==SPACE){
                    gotoxy(x,y);
                    cout<<" ";
                    GetItem();
                    y++;
                }


                if(x==player->GetX()&&y==player->GetY()&&player->GetItemNumber()!=TRANFROM){
                    player->GetDamage(DAMAGE);
                }
			}
		}
		gotoxy(x,y);
		cout<<"M";
	}
};

class Linkedlist_Node{
private:
    People *player;
	Node *p;
public:
	Linkedlist_Node(People *ppp){
		p=NULL;
		player=ppp;
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
	void DeleteMonster(){
		Node *n = p;
		if(player->GetItemNumber()==REMOVE){
			do{
				if(n->next->GetNodeNumber()==MONSTER){
					DeleteList(n,n->next);
				}
			n = n->next;
			}while(n != p);
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
		/*Node *d = b;
		a ->next = a->next->next;*/
		delete b;
	}

};

class UI{
private:
	short x;
	short y;
	People *player;
	clock_t start;
	clock_t finish;
    FireBall *Fmonster;



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
		if(duration>=5){
            int i;
            i = rand()%3;
            //i = 2;    //For testing
            switch(i){
            case 0:
                newMonster = new Monster(player);  //the normal one
                listnode->Insert(newMonster);
                start = clock();
                break;

            case 1:
                newMonster = new Pretender(player);  // the pretender monster
                listnode->Insert(newMonster);
                Node *Second_Monster;
                Second_Monster = new Monster(player);
                listnode->Insert(Second_Monster);
                start = clock();
                break;

            case 2:
                newMonster = new FireBall_Monster(player);  // the FireBall monster
                listnode->Insert(newMonster);
                start = clock();
                break;
            }
		}
		//if()
		listnode->ActionList();
		listnode->DeleteMonster();
		listnode->ItemTranform();
		listnode->PlayerDie();
	}
};

int main(){
	srand(time(NULL));
	HideCursor();
	Map *map = new Map;
	People *p = new People();
	Linkedlist_Node *listnode= new Linkedlist_Node(p);
	Monster *m = new Monster(p);
	UI *u = new UI(p);

	Item *item = new Item;
	listnode->Insert(m);
	listnode->Insert(p);


    //FireBall_Monster *mp = new FireBall_Monster(p, 1);
    //FireBall_Monster *mp1 = new FireBall_Monster(p);
    //mp->Print();

	map->Print();
	listnode->PrintList();

	while(1){
		item->Produce();
		u->Action(listnode);
		//mp->Action();
		//mp1->Action();
	}
}
