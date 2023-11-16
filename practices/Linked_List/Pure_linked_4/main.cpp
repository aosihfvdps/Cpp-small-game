#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define WIDTH 30
#define HEIGHT 20

using namespace std;

class LinkedList;

void gotoxy(int,int);
void gotoxy(int x,int y){
	HANDLE hConsoleOutput;
    COORD Cursor_Pos={x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput,Cursor_Pos);
}

class Node{
	public:
	    static int number;
		int x;
		int y;
		int timer;
		Node *next;
		clock_t start;
        clock_t finish;

	Node(){
	    number++;
		x=rand()%WIDTH;
		y=rand()%HEIGHT;
		timer=3;
		next = NULL;
		start = clock();
        finish = clock();
		Print();
	}

	void Print(){
		gotoxy(x,y);
		cout<<timer;
	}

	void Countdown()
	{
	    finish = clock();
	    if((finish - start)>=1000)
        {
            timer--;
            start = clock();
        }
	}



	~Node()
	{
	    number--;
	    gotoxy(x, y);
	    cout << " ";
	    if(number == 0)
            exit(1);
	}

};
int Node::number = 0;


class LinkedList{
	public:
        Node *p;

	public:
		LinkedList(){
			p=NULL;
		}
		void Insert(Node *newNode){
			if(p==NULL){
				p = newNode;
				p->next = p;
			}
			else{
				newNode->next = p->next;
				p->next = newNode;
			}
			PrintList();
		}

		void PrintList()
		{
			Node *q = NULL;
			q=p;
			if(p == NULL) //At the beginning, p is pointing to nothing, so if dont have this evaluation, it will have mistake.( nothing to "goto")
                return;
			do{

				q->Print();
                q->Countdown();

				if((q->timer)<=0)
                    Delete(q, q);

				q=q->next;

			}while(q!=p);
		}

		void Delete(Node *a, Node *b)
		{
		    for(int i=1; i<Node::number; i++)
            {
                b=b->next;
            }

            b->next = a->next;
            delete a;
		}
};


class UI{
public:
    char PressedKey(){
        if(kbhit())
            return getch();

        else
            return NULL;
    }

    void Action(LinkedList *List = NULL)
    {
        List -> PrintList(); //Go to the train head and go around
        Node *newNode = NULL;
        switch(PressedKey())
        {
            case 'A':
            case 'a':
                newNode = new Node;
                List->Insert(newNode);
                break;
        }
    }
};


int main(){
	srand(time(NULL));

	LinkedList *List = new LinkedList;

	UI ui;

	while(1){
		ui.Action(List);
	}

/*
    Node *newNode;

    newNode = new Node;
    List->Insert(newNode);

    Sleep(300);

    newNode = new Node;
    List->Insert(newNode);

    Sleep(300);

    newNode = new Node;
    List->Insert(newNode);


    for(;;)
        List -> PrintList();
*/

	return 0;
}
