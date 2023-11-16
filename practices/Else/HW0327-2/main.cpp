#include <iostream>

using namespace std;

class Object{
    protected:
        int dmg;
	public:
	    Object(){
            dmg = 0;
	    }
	    Object(int x){
            dmg = x;
	    }
		void Action(){
			cout<<"Do nothing......"<<endl;
		}
		void MoveTo(int x, int y){
            cout<<"Walking to location("<<x<<","<<y<<")"<<endl;
		}
		void Attack(int dmg){
            cout<<"Attack......."<<endl;
            cout<<"Damage: "<<dmg<<endl;
		}
};

class NPC: public Object{

};

class Player: public Object{
    private:
        int magicDmg;
    public:
        Player(){
            Object(10);
            magicDmg = 10;
            cout<<"dmg = "<<dmg<<endl;
            cout<<"magicDmg = "<<magicDmg<<endl;
        }
    	void Action(){
			MoveTo(10,20);
		}
		void Attack(){
            cout<<"Casting magic......"<<endl;
            Object::Attack(dmg+magicDmg);
		}
};

class Monster: public Object{
    public:
        Monster(){
            Object(20);
            cout<<"dmg = "<<dmg<<endl;
        }
    	void MoveTo(int x, int y){
            cout<<"Flying to location("<<x<<","<<y<<")"<<endl;
		}
		void Action(){
			MoveTo(10,20);
			Attack(dmg);
		}
};

class Building: public Object{
};

int main(){

	cout<<"NPC: "<<endl;
	NPC npc;
    npc.Action();

    cout<<"---------------------------"<<endl;
    cout<<"Player: "<<endl;
 	Player player;
    player.Action();

    cout<<"---------------------------"<<endl;
    cout<<"Monster: "<<endl;
	Monster monster;
    monster.Action();

    cout<<"---------------------------"<<endl;
    cout<<"Player: fight back...."<<endl;;
    player.Attack();

    cout<<"---------------------------"<<endl;
    cout<<"Building: "<<endl;;
    Building building;
    building.Action();


	return 0;
}
