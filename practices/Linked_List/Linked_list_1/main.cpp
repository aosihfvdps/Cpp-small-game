#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define WIDTH 30
#define HEIGHT 20

using namespace std;

void gotoxy(int,int);
void gotoxy(int x,int y){
	HANDLE hConsoleOutput;
    COORD Cursor_Pos={x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput,Cursor_Pos);
}

class Node
{
	public:
	    static int Number_of_Node;
		int x;
		int y;
		int timer;
		Node *next = NULL;

	Node()
	{
	    Number_of_Node++;
		x=rand()%WIDTH;
		y=rand()%HEIGHT;
		timer=3;
		Print();
	}

	void Print(){
		gotoxy(x,y);
		cout<<timer;
	}

	~Node()
	{
	    //cout << "Number_of_Node: "<<Number_of_Node<<endl;
		Number_of_Node--;
		gotoxy(x, y);
	    cout << " ";
	    if(Number_of_Node == 0)
            exit(1);
	}

};
int Node::Number_of_Node=0;

class LinkedList{
	private:
		Node *p = NULL;

	public:
		LinkedList(){
			p=NULL;
		}
		void Insert(Node *newNode)
		{
			if(p==NULL)
            {
				p = newNode;
				p->next = p;
			}
			else
			{
				newNode->next = p->next;
				p->next = newNode;
			}
			AroundList();
		}

		void AroundList()
		{
			Node *q;
			q=p;
			if(p == NULL) //At the beggining, p is pointing to nothing, so if dont have this evaluation, it will have mistake.( nothing to "goto")
                return;

			do{
				q->Print();
				q=q->next;
			}while(q!=p);
		}

		void Minus()
		{
		    Node *q;
			q=p;
			if(p == NULL)
                return;

			do{
                q->timer--;
                if((q->timer)<=0)
                {
                    Node *DD;
                    DD = q;
                    q=q->next;
                    Delete(DD, DD);
                }

				q->Print();
				q=q->next;
			}while(q!=p);
		}

		void Plus()
		{
		    Node *q;
			q=p;
			if(p == NULL)
                return;

			do{
                if(q->timer == 9)
                    goto L;
                q->timer++;
                L:{}
				q->Print();
				q=q->next;
			}while(q!=p);
		}

		void Delete(Node *a, Node *b)
		{
		    for(int i=1; i<Node::Number_of_Node; i++)
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

    void Action(LinkedList *List = NULL){
        List -> AroundList(); //Go to the train head and go around
        Node *newNode = NULL;
        switch(PressedKey()){
            case 'A':
            case 'a':
                newNode = new Node;
                List->Insert(newNode);
                break;
            case '-':
                List->Minus();
                break;
            case '+':
                List->Plus();
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
        List -> AroundList();
*/


	return 0;
}
