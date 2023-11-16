//1.

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
    Object(string name="John", int hp=500, int atk=60, float rate=80.0)
    {
        NAME = name;
        HP = hp;
        ATK = atk;
        Hit_Rate=rate;
    }

    int Hit()
    {
        int n=rand()%100;
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

        if(HP<=0)
        {
            cout<<NAME<<" Died......."<<endl;
            delete this;

            //exit(1);
        }
    }
};

class Player: public Object
{
    static int HP_record; //=500
    static int ATK_record; //=60
    static int EXP;
    static int LEVEL;
public:
    Player():Object("John", 500, 120, 80.0)
    {

    }

    void Kill()
    {
        EXP += 50;
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
        HP = HP_record; //recover HP
        HP += hp; //increase the maximum of the HP
        HP_record = HP; // update the data of the next time reborn HP

        ATK = ATK_record;
        ATK += atk;
        ATK_record = ATK;
    }

    void Levelup(int hp)
    {
        LEVEL++;
        EXP = 0;
        HP = HP_record;
        HP += hp;
        HP_record = HP;
    }

    void CHECK()
    {
        cout<<"LEVEL: "<<LEVEL<<endl;
        cout<<"EXP: "<<EXP<<endl;
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }

    int GetHP()
    {
        return HP;
    }
    int GetATK()
    {
        return ATK;
    }

    void Setting(int hp, int atk)
    {
        HP = hp;
        ATK = atk;
    }
};

int Player::ATK_record=60;
int Player::HP_record=500;
int Player::EXP=0;
int Player::LEVEL=0;



class NPC: public Object
{
public:
    NPC():Object("Farmer", 600, 20, 60.0)
    {

    }

    int GetHP()
    {
        return HP;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }
};

class Monster: public Object
{
public:
    Monster():Object("Vampire", 300, 100, 50.0)
    {

    }

    ~Monster()
    {

    }

    int GetHP()
    {
        return HP;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }
};

int main(){
    srand(time(NULL));

	Player *John=new Player;
	NPC *Farmer=new NPC;
	Monster *Vampire=new Monster;

	cout<<"John's state:"<<endl;
    John -> CHECK();
    cout<<"\n\n\n"<<endl;

    cout<<"Farmer's state:"<<endl;
    Farmer -> CHECK();
    cout<<"\n\n\n"<<endl;

    cout<<"Vampire's state:"<<endl;
    Vampire -> CHECK();
    cout<<"\n"<<endl;

	return 0;
}

/*************************************************************************/

//2.
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
    Object(string name="John", int hp=500, int atk=60, float rate=80.0)
    {
        NAME = name;
        HP = hp;
        ATK = atk;
        Hit_Rate=rate;
    }

    int Hit()
    {
        int n=rand()%100;
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

        if(HP<=0)
        {
            cout<<NAME<<" Died......."<<endl;
            delete this;

            //exit(1);
        }
    }
};

class Player: public Object
{
    static int HP_record; //=500
    static int ATK_record; //=60
    static int EXP;
    static int LEVEL;
public:
    Player():Object("John", 500, 120, 80.0)
    {

    }

    void Kill()
    {
        EXP += 50;
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
        HP = HP_record; //recover HP
        HP += hp; //increase the maximum of the HP
        HP_record = HP; // update the data of the next time reborn HP

        ATK = ATK_record;
        ATK += atk;
        ATK_record = ATK;
    }

    void Levelup(int hp)
    {
        LEVEL++;
        EXP = 0;
        HP = HP_record;
        HP += hp;
        HP_record = HP;
    }

    void CHECK()
    {
        cout<<"LEVEL: "<<LEVEL<<endl;
        cout<<"EXP: "<<EXP<<endl;
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }

    int GetHP()
    {
        return HP;
    }
    int GetATK()
    {
        return ATK;
    }

    void Setting(int hp, int atk)
    {
        HP = hp;
        ATK = atk;
    }
};

int Player::ATK_record=60;
int Player::HP_record=500;
int Player::EXP=0;
int Player::LEVEL=0;



class NPC: public Object
{
public:
    NPC():Object("Farmer", 600, 20, 60.0)
    {

    }

    int GetHP()
    {
        return HP;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }
};

class Monster: public Object
{
public:
    Monster():Object("Vampire", 300, 100, 50.0)
    {

    }

    ~Monster()
    {

    }

    int GetHP()
    {
        return HP;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }
};

int main(){
    srand(time(NULL));

	Player *John=new Player;
	NPC *Farmer=new NPC;
	Monster *Vampire=new Monster;
	cout<<"John's state:"<<endl;
    John -> CHECK();
    cout<<"\n\n\n"<<endl;
    int i=0;

	while(i<196)
    {
        i++;

        cout<<"John is attacking the vampire"<<endl;
        John->attack(Vampire);

        if((Vampire -> GetHP())<=0)
        {
            delete Vampire;
            John->Kill();
            break;
        }

        cout<<"The farmer is attacking the vampire"<<endl;
        Farmer->attack(Vampire);
        if((Vampire -> GetHP())<=0)
        {
            delete Vampire;
            John->Kill();
            break;
        }

        cout<<"The vampire is attacking John"<<endl;
        Vampire->attack(John);

        cout<<"The vampire is attacking the farmer"<<endl;
        Vampire->attack(Farmer);

    }

    cout<<"\n\n\nJohn's state:"<<endl;
    John -> CHECK();
    cout<<"\n\n\n"<<endl;



	return 0;
}
/*********************************************************************************/

//3.
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
    Object(string name="John", int hp=500, int atk=60, float rate=80.0)
    {
        NAME = name;
        HP = hp;
        ATK = atk;
        Hit_Rate=rate;
    }

    int Hit()
    {
        int n=rand()%100;
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

        if(HP<=0)
        {
            cout<<NAME<<" Died......."<<endl;
            delete this;

            //exit(1);
        }
    }
};

class Player: public Object
{
    static int HP_record; //=500
    static int ATK_record; //=60
    static int EXP;
    static int LEVEL;
public:
    Player():Object("John", 500, 120, 80.0)
    {

    }

    void Kill()
    {
        EXP += 50;
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
        HP = HP_record; //recover HP
        HP += hp; //increase the maximum of the HP
        HP_record = HP; // update the data of the next time reborn HP

        ATK = ATK_record;
        ATK += atk;
        ATK_record = ATK;
    }

    void Levelup(int hp)
    {
        LEVEL++;
        EXP = 0;
        HP = HP_record;
        HP += hp;
        HP_record = HP;
    }

    void CHECK()
    {
        cout<<"LEVEL: "<<LEVEL<<endl;
        cout<<"EXP: "<<EXP<<endl;
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }

    int GetHP()
    {
        return HP;
    }
    int GetATK()
    {
        return ATK;
    }

    void Setting(int hp, int atk)
    {
        HP = hp;
        ATK = atk;
    }
};

int Player::ATK_record=60;
int Player::HP_record=500;
int Player::EXP=0;
int Player::LEVEL=0;



class NPC: public Object
{
public:
    NPC():Object("Farmer", 600, 20, 60.0)
    {

    }

    int GetHP()
    {
        return HP;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }
};

class Monster: public Object
{
public:
    Monster():Object("Vampire", 300, 100, 50.0)
    {

    }

    ~Monster()
    {

    }

    int GetHP()
    {
        return HP;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }
};

int main(){
    srand(time(NULL));

	Player *John=new Player;
	NPC *Farmer=new NPC;
	Monster *Vampire=new Monster;
	cout<<"John's state:"<<endl;
    John -> CHECK();
    cout<<"\n\n\n"<<endl;
    int i=0;

	while(i<196)
    {
        i++;

        cout<<"John is attacking the vampire"<<endl;
        John->attack(Vampire);

        if((Vampire -> GetHP())<=0)
        {
            delete Vampire;
            John->Kill();
            break;
        }

        cout<<"The farmer is attacking the vampire"<<endl;
        Farmer->attack(Vampire);
        if((Vampire -> GetHP())<=0)
        {
            delete Vampire;
            John->Kill();
            break;
        }

        cout<<"The vampire is attacking John"<<endl;
        Vampire->attack(John);

        cout<<"The vampire is attacking the farmer"<<endl;
        Vampire->attack(Farmer);

    }

    cout<<"\n\n\nJohn's state:"<<endl;
    John -> CHECK();
    cout<<"\n\n\n"<<endl;



	return 0;
}
/*****************************************************************************/
//4.
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
    Object(string name="John", int hp=500, int atk=60, float rate=80.0)
    {
        NAME = name;
        HP = hp;
        ATK = atk;
        Hit_Rate=rate;
    }

    int Hit()
    {
        int n=rand()%100;
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

        if(HP<=0)
        {
            cout<<NAME<<" Died......."<<endl;
            delete this;

            //exit(1);
        }
    }
};

class Player: public Object
{
    static int HP_record; //=500
    static int ATK_record; //=60
    static int EXP;
    static int LEVEL;
public:
    Player():Object("John", 500, 120, 80.0)
    {

    }

    void Kill()
    {
        EXP += 50;
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
        HP = HP_record; //recover HP
        HP += hp; //increase the maximum of the HP
        HP_record = HP; // update the data of the next time reborn HP

        ATK = ATK_record;
        ATK += atk;
        ATK_record = ATK;
    }

    void Levelup(int hp)
    {
        LEVEL++;
        EXP = 0;
        HP = HP_record;
        HP += hp;
        HP_record = HP;
    }

    void CHECK()
    {
        cout<<"LEVEL: "<<LEVEL<<endl;
        cout<<"EXP: "<<EXP<<endl;
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }

    int GetHP()
    {
        return HP;
    }
    int GetATK()
    {
        return ATK;
    }

    void Setting(int hp, int atk)
    {
        HP = hp;
        ATK = atk;
    }
};

int Player::ATK_record=60;
int Player::HP_record=500;
int Player::EXP=0;
int Player::LEVEL=0;



class NPC: public Object
{
public:
    NPC():Object("Farmer", 600, 20, 60.0)
    {

    }

    int GetHP()
    {
        return HP;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }
};

class Monster: public Object
{
public:
    Monster():Object("Vampire", 300, 100, 50.0)
    {

    }

    ~Monster()
    {

    }

    int GetHP()
    {
        return HP;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }
};

int main(){
    srand(time(NULL));

	Player *John=new Player;
	NPC *Farmer=new NPC;
	Monster *Vampire=new Monster;
	cout<<"John's state:"<<endl;
    John -> CHECK();
    cout<<"\n\n\n"<<endl;
    int i=0;

	while(i<196)
    {
        i++;

        cout<<"John is attacking the vampire"<<endl;
        John->attack(Vampire);

        if((Vampire -> GetHP())<=0)
        {
            delete Vampire;
            John->Kill();
            break;
        }

        cout<<"The farmer is attacking the vampire"<<endl;
        Farmer->attack(Vampire);
        if((Vampire -> GetHP())<=0)
        {
            delete Vampire;
            John->Kill();
            break;
        }

        cout<<"The vampire is attacking John"<<endl;
        Vampire->attack(John);

        cout<<"The vampire is attacking the farmer"<<endl;
        Vampire->attack(Farmer);

    }

    cout<<"\n\n\nJohn's state:"<<endl;
    John -> CHECK();
    cout<<"\n\n\n"<<endl;



	return 0;
}
/****************************************************************************/
//5.
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
    Object(string name="John", int hp=500, int atk=60, float rate=80.0)
    {
        NAME = name;
        HP = hp;
        ATK = atk;
        Hit_Rate=rate;
    }

    int Hit()
    {
        int n=rand()%100;
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

        if(HP<=0)
        {
            cout<<NAME<<" Died......."<<endl;
            delete this;

            //exit(1);
        }
    }
};

class Player: public Object
{
    static int HP_record; //=500
    static int ATK_record; //=60
    static int EXP;
    static int LEVEL;
public:
    Player():Object("John", 500, 120, 80.0)
    {

    }

    void Kill()
    {
        EXP += 50;
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
        HP = HP_record; //recover HP
        HP += hp; //increase the maximum of the HP
        HP_record = HP; // update the data of the next time reborn HP

        ATK = ATK_record;
        ATK += atk;
        ATK_record = ATK;
    }

    void Levelup(int hp)
    {
        LEVEL++;
        EXP = 0;
        HP = HP_record;
        HP += hp;
        HP_record = HP;
    }

    void CHECK()
    {
        cout<<"LEVEL: "<<LEVEL<<endl;
        cout<<"EXP: "<<EXP<<endl;
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }

    int GetHP()
    {
        return HP;
    }
    int GetATK()
    {
        return ATK;
    }

    void Setting(int hp, int atk)
    {
        HP = hp;
        ATK = atk;
    }
};

int Player::ATK_record=60;
int Player::HP_record=500;
int Player::EXP=0;
int Player::LEVEL=0;



class NPC: public Object
{
public:
    NPC():Object("Farmer", 600, 20, 60.0)
    {

    }

    int GetHP()
    {
        return HP;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }
};

class Monster: public Object
{
public:
    Monster():Object("Vampire", 300, 100, 50.0)
    {

    }

    ~Monster()
    {

    }

    int GetHP()
    {
        return HP;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }
};

int main(){
    srand(time(NULL));

	Player *John=new Player;
	NPC *Farmer=new NPC;
	Monster *Vampire=new Monster;
	cout<<"John's state:"<<endl;
    John -> CHECK();
    cout<<"\n\n\n"<<endl;
    int i=0;

	while(i<196)
    {
        i++;

        cout<<"John is attacking the vampire"<<endl;
        John->attack(Vampire);

        if((Vampire -> GetHP())<=0)
        {
            delete Vampire;
            John->Kill();
            break;
        }

        cout<<"The farmer is attacking the vampire"<<endl;
        Farmer->attack(Vampire);
        if((Vampire -> GetHP())<=0)
        {
            delete Vampire;
            John->Kill();
            break;
        }

        cout<<"The vampire is attacking John"<<endl;
        Vampire->attack(John);

        cout<<"The vampire is attacking the farmer"<<endl;
        Vampire->attack(Farmer);

    }

    cout<<"\n\n\nJohn's state:"<<endl;
    John -> CHECK();
    cout<<"\n\n\n"<<endl;



	return 0;
}
/*************************************************/
//6.
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
    Object(string name="John", int hp=500, int atk=60, float rate=80.0)
    {
        NAME = name;
        HP = hp;
        ATK = atk;
        Hit_Rate=rate;
    }

    int Hit()
    {
        int n=rand()%100;
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
    static int HP_record; //=500
    static int ATK_record; //=60
    static int EXP;
    static int LEVEL;
public:
    Player():Object("John", 500, 60, 80.0)
    {

    }

    void Kill()
    {
        EXP += 50;
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
        HP = HP_record; //recover HP
        HP += hp; //increase the maximum of the HP
        HP_record = HP; // update the data of the next time reborn HP

        ATK = ATK_record;
        ATK += atk;
        ATK_record = ATK;
    }

    void Levelup(int hp)
    {
        LEVEL++;
        EXP = 0;
        HP = HP_record;
        HP += hp;
        HP_record = HP;
    }

    void CHECK()
    {
        cout<<"LEVEL: "<<LEVEL<<endl;
        cout<<"EXP: "<<EXP<<endl;
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }

    int GetHP()
    {
        return HP;
    }
    int GetATK()
    {
        return ATK;
    }

    void Setting(int hp, int atk)
    {
        HP = hp;
        ATK = atk;
    }
};

int Player::ATK_record=60;
int Player::HP_record=500;
int Player::EXP=0;
int Player::LEVEL=0;



class NPC: public Object
{
public:
    NPC():Object("Farmer", 600, 20, 60.0)
    {

    }

    int GetHP()
    {
        return HP;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }
};

class Monster: public Object
{
public:
    Monster():Object("Vampire", 700, 100, 50.0)
    {

    }

    ~Monster()
    {

    }

    int GetHP()
    {
        return HP;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }
};

int main(){
    srand(time(NULL));

	Player *John=new Player;
	NPC *Farmer=new NPC;
	Monster *Vampire=new Monster;
	cout<<"John's state:"<<endl;
    John -> CHECK();
    cout<<"\n\n\n"<<endl;

	//cout<<Vampire -> GetHP()<<endl;

	//int local_HP_record, local_ATK_record;

	int i=0, Number_of_Dead_of_John=0, Number_of_Dead_of_Mon=0, Number_of_Dead_of_Farmer=0;

	while(i<196)
    {
        i++;

        //local_HP_record = John->GetHP();
        //local_ATK_record = John->GetATK();

        //cout<<"\n\nlocal_HP_record: "<<local_HP_record<<endl;
        //cout<<"local_ATK_record: "<<local_ATK_record<<"\n\n"<<endl;

        cout<<"John is attacking the vampire"<<endl;
        John->attack(Vampire);


        if((Vampire -> GetHP())<=0)
        {
            Number_of_Dead_of_Mon++;
            delete Vampire;
            John->Kill();

            Vampire=new Monster();
            //cout<<"\n\Vampire's state:"<<endl;
            //Vampire -> CHECK();
            //cout<<"in main, Vampire's HP: "<<Vampire -> GetHP()<<endl;
        }

        cout<<"The farmer is attacking the vampire"<<endl;
        Farmer->attack(Vampire);

        if((Vampire -> GetHP())<=0)
        {
            Number_of_Dead_of_Mon++;
            delete Vampire;
            John->Kill();

            Vampire=new Monster();
            //cout<<"\n\Vampire's state:"<<endl;
            //Vampire -> CHECK();
            //cout<<"in main, Vampire's HP: "<<Vampire -> GetHP()<<endl;
        }

        cout<<"The vampire is attacking John"<<endl;
        Vampire->attack(John);

        if((John -> GetHP())<=0)
        {
            Number_of_Dead_of_John++;
            delete John;
            John=new Player();
            //John -> Setting(local_HP_record, local_ATK_record);//Keep the HP and ATK


            //cout<<"\n\nJohn's state:"<<endl;
            //John -> CHECK();
            //cout<<"in main, John's HP: "<<John -> GetHP()<<endl;
        }


        cout<<"The vampire is attacking the farmer"<<endl;
        Vampire->attack(Farmer);

        if((Farmer -> GetHP())<=0)
        {
            Number_of_Dead_of_Farmer++;
            delete Farmer;
            cout<<"Farmer Died..."<<endl;
            Farmer=new NPC();
            //cout<<"\n\Farmer's state:"<<endl;
            //Farmer -> CHECK();
            //cout<<"in main, Farmer's HP: "<<Farmer -> GetHP()<<endl;
        }

    }




    cout<<"\n\nNumber_of_Dead_of_John: "<<Number_of_Dead_of_John<<endl;
    cout<<"\n\Number_of_Dead_of_Farmer: "<<Number_of_Dead_of_Farmer<<endl;
    cout<<"\n\Number_of_Dead_of_Mon: "<<Number_of_Dead_of_Mon<<endl;

    cout<<"\n\nJohn's state:"<<endl;

    John -> CHECK();



	return 0;
}
/***********************************************************************/
//7.
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
    Object(string name="John", int hp=500, int atk=60, float rate=80.0)
    {
        NAME = name;
        HP = hp;
        ATK = atk;
        Hit_Rate=rate;
    }

    int Hit()
    {
        int n=rand()%100;
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
    }
};

class Player: public Object
{
    static int HP_record; //=500
    static int ATK_record; //=60
    static int EXP;
    static int LEVEL;
public:
    Player():Object("John", 700, 70, 80.0)
    {

    }

    void Kill()
    {
        EXP += 50;
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
        HP = HP_record; //recover HP
        HP += hp; //increase the maximum of the HP
        HP_record = HP; // update the data of the next time reborn HP

        ATK = ATK_record;
        ATK += atk;
        ATK_record = ATK;
    }

    void Levelup(int hp)
    {
        LEVEL++;
        EXP = 0;
        HP = HP_record;
        HP += hp;
        HP_record = HP;
    }

    void CHECK()
    {
        cout<<"LEVEL: "<<LEVEL<<endl;
        cout<<"EXP: "<<EXP<<endl;
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }

    int GetHP()
    {
        return HP;
    }
    int GetATK()
    {
        return ATK;
    }

    void Setting(int hp, int atk)
    {
        HP = hp;
        ATK = atk;
    }
};

int Player::ATK_record=60;
int Player::HP_record=500;
int Player::EXP=0;
int Player::LEVEL=0;



class NPC: public Object
{
public:
    NPC():Object("Farmer", 400, 80, 60.0)
    {

    }

    int GetHP()
    {
        return HP;
    }

    int GetATK()
    {
        return ATK;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }
};

class Monster: public Object
{
    static int HP_record;
    static int ATK_record;
public:
    Monster():Object("Vampire", HP_record, ATK_record, 50.0)
    {

    }

    ~Monster()
    {

    }

    int GetHP()
    {
        return HP;
    }

    void CHECK()
    {
        cout<<"HP: "<<HP<<endl;
        cout<<"ATK: "<<ATK<<endl;
    }

    void Mode()
    {
        if(HP>(HP_record/2))
        {
            return;
        }
        else
        {
            if(HP<=(HP_record/5))
            {
                if(ATK == ATK_record*3)
                    return;
                else
                {
                    ATK = ATK/2;
                    ATK = ATK*3;
                    return;
                }
            }

            else
            {
                if(HP<=(HP_record/2))
                {
                    if(ATK == ATK_record*2)
                        return;
                    else
                    {
                        ATK = ATK*2;
                        return;
                    }
                }
            }
        }
    }
};
int Monster::HP_record = 1000;
int Monster::ATK_record = 100;


int main(){
    srand(time(NULL));

	Player *John=new Player;
	NPC *Farmer=new NPC;
	Monster *Vampire=new Monster;
	cout<<"John's state:"<<endl;
    John -> CHECK();
    cout<<"\n\n\n"<<endl;

	int i=0, Number_of_Dead_of_John=0, Number_of_Dead_of_Mon=0, Number_of_Dead_of_Farmer=0;

	while(i<196)
    {
        i++;

        cout<<"John is attacking the vampire"<<endl;
        John->attack(Vampire);


        if((Vampire -> GetHP())<=0)
        {
            Number_of_Dead_of_Mon++;
            delete Vampire;
            John->Kill();

            Vampire=new Monster();
        }

        cout<<"Farmer is attacking the vampire"<<endl;
        Farmer->attack(Vampire);

        if((Vampire -> GetHP())<=0)
        {
            Number_of_Dead_of_Mon++;
            delete Vampire;
            John->Kill();

            Vampire=new Monster();
        }


        Vampire -> Mode();
        cout<<"\n\Vampire's state:"<<endl;
        Vampire -> CHECK();



        if((John -> GetATK())>=(Farmer -> GetATK()))
        {
            cout<<"Vampire is attacking John"<<endl;
            Vampire->attack(John);

            if((John -> GetHP())<=0)
            {
                Number_of_Dead_of_John++;
                delete John;
                John=new Player();
            }
        }

        else
        {
            cout<<"Vampire is attacking the farmer"<<endl;
            Vampire->attack(Farmer);

            if((Farmer -> GetHP())<=0)
            {
                Number_of_Dead_of_Farmer++;
                delete Farmer;
                cout<<"Farmer Died..."<<endl;
                Farmer=new NPC();
            }
        }
    }

    cout<<"\n\nNumber_of_Dead_of_John: "<<Number_of_Dead_of_John<<endl;
    cout<<"\n\Number_of_Dead_of_Farmer: "<<Number_of_Dead_of_Farmer<<endl;
    cout<<"\n\Number_of_Dead_of_Mon: "<<Number_of_Dead_of_Mon<<endl;

    cout<<"\n\nJohn's state:"<<endl;

    John -> CHECK();


	return 0;
}

