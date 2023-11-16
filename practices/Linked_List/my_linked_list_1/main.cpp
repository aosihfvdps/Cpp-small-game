#include <iostream>

using namespace std;

class Demo {
    //static int C;
    int A;
    int B;

public:

    char str[1000];
    static int C;
    Demo(int a =55, int b = 22) {
        //cout << "constructor.." << endl;
        A = a;
        B = b;
        cout << "Before: C = " << C << endl;
    }

    int do_something() {
        return A + B;
    }

    void Setting()
    {
        cout << "After: C = " << C << endl;
    }

    int GetA()
    {
        return A;
    }

    void enterA(int a)
    {
        A += a;
    }
};


//Demo test;
/*
void F1(Demo *pb)
{
    pb = new Demo;
    cout << "Size of pb: " << sizeof(*pb) << endl;
}
*/
int main() {
    //Demo d(25, 22);

    //::C = 5;
    //std::cout << d.do_something() << std::endl;

    //d.C++;
    //d.Setting();

    Demo pa;
    //F1(pa);
    cout << pa.GetA() << endl;

    pa.enterA(1000);

    cout << pa.GetA() << endl;





    return 0;
}

int Demo::C = 5;
