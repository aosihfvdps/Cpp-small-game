#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define	STOP	0
#define	MOVE	1

using namespace std;

void HideCursor();

void HideCursor(){
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}


class Robot{
private:
	char skin;
	int x;
	int y;
	int chargingX;
	int chargingY;
	int power;
	int targetX;
	int targetY;
public:
	Robot(char s){
		skin = s;
	}
	void SetXY(int a, int b){
		x = a;
		y = b;
		ShowXY();
	}
	void ShowXY(){
		cout<<"x = "<<x<<endl;
		cout<<"y = "<<y<<endl;
	}
	void SetChargingXY(int a, int b){
		chargingX = a;
		chargingY = b;
		ShowChargingXY();
	}
	void ShowChargingXY(){
		cout<<"chargingX = "<<chargingX<<endl;
		cout<<"chargingY = "<<chargingY<<endl;
	}
	void SetPower(int p){
		power = p;
		ShowPower();
	}
	void ShowPower(){
		cout<<"power = "<<power<<endl;
	}
	void SetTargetXY(int a, int b){
		targetX = a;
		targetY = b;
		ShowTargetXY();
	}
	void ShowTargetXY(){
		cout<<"targetX = "<<targetX<<endl;
		cout<<"targetY = "<<targetY<<endl;
	}
	void gotoxy(int x, int y){
    	COORD pos = {x,y};
    	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    	SetConsoleCursorPosition(hOut, pos);
	}
	void ShowRobot(){
		gotoxy(x,y);
		cout<<"R";
	}
	int MoveToTargetXY(){
		if((x!=targetX)&&(y!=targetY)){
			gotoxy(x,y);
			cout<<" ";
			if(x<targetX)
				x++;
			else
				if(x>targetX)
					x--;

			if(y<targetY)
				y++;
			else
				if(y>targetY)
					y--;
		}
		gotoxy(x,y);
		cout<<skin;

		//_sleep(200);

		//return MoveToTargetXY();
	}
};

int main(){
	HideCursor();

	Robot robot1('R'), robot2('B'), robot3('C');

	robot1.SetXY(0,0);
	robot1.SetChargingXY(10,10);
	robot1.SetPower(100);
	robot1.SetTargetXY(20,20);

	robot2.SetXY(50,30);
	robot2.SetChargingXY(10,10);
	robot2.SetPower(40);
	robot2.SetTargetXY(15,15);

	robot3.SetXY(30,10);
	robot3.SetTargetXY(80,30);

	(void)getch();
	system("cls");

	while(1){
		robot1.MoveToTargetXY();
		robot2.MoveToTargetXY();
		robot3.MoveToTargetXY();
		_sleep(150);
	}

	return 0;
}
