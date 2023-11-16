// Translating to Java (using interface)
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class Print_class
{
public:
    void Print()
    {
        for(;;)
            cout<<"printprintprintprintprintprint"<<endl;
    }
};

class test
{
    Print_class *p;
public:
    void Call_Print()
    {
        p = new Print_class;
        p->Print();
    }
    void Clean()
    {
        system("cls");
    }
};

int main(){
    test ttt;
    ttt.Call_Print();
    ttt.Clean();
    return 0;
}
