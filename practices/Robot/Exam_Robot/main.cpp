#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <iomanip>

#define WIDTH 80
#define HEIGHT 15

using namespace std;

void gotoxy(int, int);
void HideCursor();
class Trash;
class SweeperRobot;
//void SweeperRobot::OccupyCapacity(int);



void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void gotoxy(int x, int y)
{
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}


class Robot{
private:
	char Skin;
	int X;
	int Y;
	int ChargingX;
	int ChargingY;
	int Power;
	int Max_power;
	int TargetX;
	int TargetY;
	Trash *Helper;
	int Judge_if_Change_Target;
	SweeperRobot *SWRB;
	int Make_sure_only_once;
	int temporaryX;
	int temporaryY;
	int Go_to_Charger_Because_of_no_Capacity;
	int If_Empty_Trash;
	int If_Charge;

public:
    Robot()
    {
        Skin = 'A';
        SetLocation(0, 0);
        SetChargingLocation(0, 0);
        SetPower(500);
        SetMaxPower(500);
        SetTargetLocation(0, 0);
        Judge_if_Change_Target = 1;
        Make_sure_only_once = 0;
        Go_to_Charger_Because_of_no_Capacity = 0;
        If_Empty_Trash = 0;
        If_Charge = 0;
    }


	Robot(char s, int a, int b, int CA=0, int CB=0)
	{
		Skin = s;
		SetLocation(a, b);
		SetChargingLocation(CA, CB);
        SetPower(500);
        SetMaxPower(500);
        SetTargetLocation(0, 0);
        Judge_if_Change_Target = 1;
        Make_sure_only_once = 0;
        Go_to_Charger_Because_of_no_Capacity = 0;
        If_Empty_Trash = 0;
        If_Charge = 0;
	}


	void SetLocation(int a, int b)
	{
		X = a;
		Y = b;
	}
	void SetChargingLocation(int a, int b)
	{
		ChargingX = a;
		ChargingY = b;
	}
	void SetPower(int p)
	{
		Power = p;
	}
	void SetMaxPower(int mp)
	{
		Max_power = mp;
	}
	void SetTargetLocation(int a, int b)
	{
		TargetX = a;
		TargetY = b;
	}

	void Status()
	{
	    if(Skin == 'A')
            gotoxy(0, 31);
        else
            gotoxy(0, 16);

	    cout<<Skin<<": "<<endl;
	    cout<<"Location = ("<<X<< ", "<<Y<<")    "<<endl;
		cout<<"Charging Location = ("<<ChargingX<< ", "<<ChargingY<<")     "<<endl;
		cout<<"Power = "<<fixed<< setprecision(1)<< (float)Power/(float)Max_power*100<<"% "<<endl;
		//printf("Max Power = %d\n", Max_power);
        cout<<"Target Location = ("<<TargetX<< ", "<<TargetY<<")      "<<endl;
        //cout<<"Judge_if_Change_Target = "<<Judge_if_Change_Target<<endl;
        //cout<<"If_Charge = "<<If_Charge<<endl;
        //cout<<"If_Empty_Trash = "<<If_Empty_Trash<<endl;
	}

	void GetSweeperRobot(SweeperRobot *swp)
	{
	    SWRB = swp;
	}
	void OccupyCap();
	void Print_State_from_Child();
	void Empty_Cap();


	int MoveToTargetXY()
	{
	    if((((float)Power/(float)Max_power)>=0.1)&&(Go_to_Charger_Because_of_no_Capacity==0))
        {
            PrintCharger();
            if((X!=TargetX)||(Y!=TargetY))
            {
                gotoxy(X,Y);
                cout<<" ";
                if(X<TargetX)
                {
                    X++;
                    Power-=5;
                    Print_State_from_Child();
                }
                else
                {
                    if(X>TargetX)
                    {
                        X--;
                        Power-=5;
                        Print_State_from_Child();
                    }
                }

                if(Y<TargetY)
                {
                    Y++;
                    Power-=5;
                    Print_State_from_Child();

                }
                else
                {
                    if(Y>TargetY)
                    {
                        Y--;
                        Power-=5;
                        Print_State_from_Child();
                    }
                }
            }

            gotoxy(X,Y);
            cout<<Skin;

            if((X==TargetX)&&(Y==TargetY))
            {
                temporaryX = X;
                temporaryY = Y;
                OccupyCap();
                Print_State_from_Child();
                Judge_if_Change_Target = 1;
            }
            else
                Judge_if_Change_Target = 0;

            if((temporaryX == X)&&(temporaryY == Y))
            {
            }
            else
            {
                Make_sure_only_once = 0;
            }

        }

        else
            Go_to_Charger();
	}

	void Go_to_Charger()
	{
	    if((((float)Power/(float)Max_power)<=0.1))
            If_Charge = 1;


	    Judge_if_Change_Target = 0;
	    PrintCharger();
		if((X!=ChargingX)||(Y!=ChargingY))
        {
			gotoxy(X,Y);
			cout<<" ";
			if(X<ChargingX)
            {
                X++;
                Print_State_from_Child();
            }

			else
            {
                if(X>ChargingX)
                {
                    X--;
                    Print_State_from_Child();
                }
            }

			if(Y<ChargingY)
            {
                Y++;
                Print_State_from_Child();
            }
			else
            {
                if(Y>ChargingY)
				{
                    Y--;
                    Print_State_from_Child();
                }
            }

		}

		gotoxy(X,Y);
		cout<<Skin;
		if((X==ChargingX)&&(Y==ChargingY))
        {
            //Power = Max_power;
            if(If_Charge == 1)
            {
                Power = Max_power;
                If_Charge = 0;
            }
            //Empty_Cap();
            if(If_Empty_Trash == 1)
            {
                Empty_Cap();
                If_Empty_Trash = 0;
            }


            Go_to_Charger_Because_of_no_Capacity = 0; //////////////////////////////////////////////////////////////
            Judge_if_Change_Target = 1;
            Print_State_from_Child();
            _sleep(1000);
        }
	}

	void PrintCharger()
	{
	    gotoxy(ChargingX, ChargingY);
	    cout<<"C";
	}

	int GetX()
    {
        return X;
    }

    int GetY()
    {
        return Y;
    }

    int GetPower()
    {
        return Power;
    }

    int GetMax_power()
    {
        return Max_power;
    }

    int GetJudge_if_Change_Target()
    {
        return Judge_if_Change_Target;
    }
};




class SweeperRobot: public Robot
{
private:
    int Capacity;
    int MaxCapacity;
public:
    SweeperRobot():Robot()
    {
        SetCapacity(0);
        SetMaxCapacity(500);
        Status();
    }

    SweeperRobot(char s, int a, int b, int ca, int cb, int n):Robot(s, a, b, ca, cb)
    {
        SetCapacity(80);
        SetMaxCapacity(n);
        Status();
    }

    void SetCapacity(int c)
    {
        Capacity = c;
    }

    void OccupyCapacity(int ic)
    {
        Capacity = Capacity + ic;
    }

    int GetCapacity()
    {
        return Capacity;
    }

    int GetMaxCapacity()
    {
        return MaxCapacity;
    }

    void SetMaxCapacity(int mc)
    {
        MaxCapacity = mc;
    }
    Status()
    {
        Robot::Status();
        cout<<"Occupied Capacity = "<<fixed<< setprecision(1)<< ((float)Capacity/(float)MaxCapacity)*100<<"%            "<<endl;
    }
};

void Robot::OccupyCap()
{
    if(Make_sure_only_once == 0)
    {
        SWRB -> OccupyCapacity(5);
        Make_sure_only_once = 1;

        //gotoxy(0, 29);
        //cout<<"((double)(SWRB -> GetCapacity()) / (double)(SWRB ->GetMaxCapacity()) = "<<(double)(SWRB -> GetCapacity()) / (double)(SWRB ->GetMaxCapacity())<<endl;
        //printf("((float)(SWRB -> GetCapacity()) / (float)(SWRB ->GetMaxCapacity()) = %f", (float)(SWRB -> GetCapacity()) / (float)(SWRB ->GetMaxCapacity()));

        if(((double)(SWRB -> GetCapacity()) / (double)(SWRB ->GetMaxCapacity())>=0.95))
        {
            gotoxy(0, 30);
            //printf("((float)(SWRB -> GetCapacity()) / (float)(SWRB ->GetMaxCapacity()) = %f", (float)(SWRB -> GetCapacity()) / (float)(SWRB ->GetMaxCapacity()));
            //cout<<"If_Empty_Trash = "<<If_Empty_Trash<<endl;
            If_Empty_Trash = 1;
            //cout<<"If_Empty_Trash = "<<If_Empty_Trash<<endl;
            Go_to_Charger_Because_of_no_Capacity = 1;
        }
    }
    else
    {

    }
}

void Robot::Empty_Cap()
{
    SWRB -> SetCapacity(0);
}

void Robot::Print_State_from_Child()
{
    SWRB -> Status();
}

class Trash
{
private:
    int X;
    int Y;
    Trash *NEW_TRASH;
    clock_t start;
    clock_t finish;

public:
    Trash(Robot &rb)
    {
        X=rand()%WIDTH;
		Y=rand()%HEIGHT;
		start = clock();
        finish = clock();
        gotoxy(X, Y);
        cout << "T";
        if((double)rb.GetPower()/(double)rb.GetMax_power()<=0.1)
        {

        }
        else
        {
            if(rb.GetJudge_if_Change_Target()==0)
            {

            }
            else
            {
                rb.SetTargetLocation(X, Y);
            }
        }
    }

    void Countdown(Robot &rb)
	{
	    finish = clock();
	    if((finish - start)>=1000)
        {
            NEW_TRASH = new Trash(rb);
            start = clock();
        }
	}

    void Judge_if_Delete_trash(SweeperRobot &Sweeper)
    {
        if((Sweeper.GetX()==X)&&(Sweeper.GetY()==Y))
            delete this;
        else
        {

        }
    }

    ~Trash()
    {
        gotoxy(X, Y);
        cout << " ";
    }

    int GetX()
    {
        return X;
    }

    int GetY()
    {
        return Y;
    }
};

int main(){
	HideCursor();
    srand(time(NULL));

	SweeperRobot robot2('R', 0, 14, 0, 14, 100);
	robot2.GetSweeperRobot(&robot2);
	Trash TG(robot2);

	(void)getch();
	//system("cls");

	while(1)
    {
        TG.Countdown(robot2);
		robot2.MoveToTargetXY();
		_sleep(5);
		//(void)getch();
	}

	return 0;
}
