#include <iostream>
#include<time.h>
#include<string>

using namespace std;

class Player;
class NPC;
class Monster;

class Object
{
protected:
    string NAME;
    int HP;
    int ATK;
    float Hit_Rate;

public:
    Object(string name, int hp, int atk, float rate)
    {
        NAME = name;
        HP = hp;
        ATK = atk;
        Hit_Rate=rate;
    }

    int Hit()
    {
        int n=rand()%100;
        //cout<<"n = "<<n<<endl;
        if(n>Hit_Rate)
            return 0;
        else
            return 1;
    }

    void state()
    {
        cout<<NAME<<"'s HP = "<<HP<<endl;
    }
    /********************************************/
    void attack(Object *obj)
    {
        if(Hit())
            obj->under_attack(ATK);
        else
            cout<<NAME<<" missed..."<<endl;
    }
    /********************************************/
    void under_attack(int damage)
    {
        HP = HP - damage;
        state();
        /*
        if(HP<=0)
        {
            cout<<NAME<<" Died......."<<endl;
            delete this;

            //exit(1);
        }*/
    }
};
class Player: public Object
{
    int EXP=0;
    int LEVEL=0;
public:
    Player():Object("John", 500, 60, 80)
    {

    }

    void Kill()
    {
        EXP += 10;
        if(EXP==100)
        {
            if((LEVEL%3)==0)
                Levelup(50, 10);

            else
                Levelup(50);
        }
    }

    void Levelup(int hp, int atk)
    {
        LEVEL++;
        EXP = 0;
        HP += hp;
        ATK += atk;
    }

    void Levelup(int hp)
    {
        LEVEL++;
        EXP = 0;
        HP += hp;
    }

    void CHECK()
    {
        cout<<"EXP: "<<EXP<<endl;
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }

};

class NPC: public Object
{
public:
    NPC():Object("Farmer", 600, 20, 60)
    {

    }
};

class Monster: public Object
{
public:
    Monster():Object("Vampire", 1000, 10, 50)
    {

    }

    ~Monster()
    {

    }

    int GetHP()
    {
        return HP;
    }
};

int main(){
    srand(time(NULL));

	Player *John=new Player;
	NPC *Farmer=new NPC;
	Monster *Vampire=new Monster;

	cout<<Vampire -> GetHP()<<endl;

	while(1)
    {
        cout<<"John is attacking the vampire"<<endl;
        John->attack(Vampire);
        cout<<"The farmer is attacking the vampire"<<endl;
        Farmer->attack(Vampire);

        if((Vampire -> GetHP())<=0)
        {
            cout<<"Vampir Died..."<<endl;
            delete Vampire;
            John->Kill();
            break;
        }

        cout<<"The vampire is attacking John"<<endl;
        Vampire->attack(John);
        cout<<"The vampire is attacking the farmer"<<endl;
        Vampire->attack(Farmer);

    }

    cout<<"\n\nJohn's state:"<<endl;

    John -> CHECK();



	return 0;
}
