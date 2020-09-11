#include <iostream>
#include "Node.h"
#include "Exception.h"

using namespace std;

//use a parent to rememeber the adjacency between to vertexs

//disjoin sets is also know as union find 
class disjointSets
{

    //Should just convert this class into a Struct
    private:


    public:
        vector<linkedList*> vectorOfLL;

        //constructor creates a vector with size x
        disjointSets(int x)
        {
            //assigns the vector with size x and all the indexes have nullpointers
            vectorOfLL.assign(x, nullptr);
        }

        //Makeset function takes the vertex value and makes a linkedlist of that vertex       
        void makeSet(int x)
        {
            //Each new linkedlist will initialize a new node with value x. Also the head and tail pointer of the linkedlist will point to that new node
            vectorOfLL[x] = new linkedList(x);

            //we also set the parent value of each of the newly created node to the head of the linkedlist/itself
            vectorOfLL[x] -> head -> parent = vectorOfLL[x] -> head;
        }

        //findset returns the parent pointer of each vertex to check cycles and when do use union etc
        int findSet(int x)
        {
            int parent = vectorOfLL[x] -> head -> vertexNumber;
            
            return parent; 
        }
        
        //union function
        void unionSet(int x, int y)
        {
            //make set x's tail the current head of set y
            vectorOfLL[x] -> tail -> next = vectorOfLL[y] -> head;

            //make set x's tail equal the tail of set y
            vectorOfLL[x] -> tail = vectorOfLL[y] -> tail;
            
            //make set y's head equal set x's head
            vectorOfLL[y] -> head = vectorOfLL[x] -> head;

            
            
            //Linkedlist iterator
            Node *iterator = vectorOfLL[x] -> head;

            //updating all the linkedlist pointers to ensure that each node has the correct parent
            while(iterator != nullptr)
            {
                vectorOfLL[iterator -> vertexNumber] = vectorOfLL[x];
                //cout << iterator -> vertexNumber << endl;
                iterator = iterator -> next;
            }
            

        }

};




