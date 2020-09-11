#include <iostream>
#include "Exception.h"

using namespace std;


//Node 
class Node
{

    //Should just convert this class into a Struct
    private:
        
    public:
        
        int vertexNumber;

        //Pointer to the parent of the vertex to check if the vertex has been grouped or not
        //parent will always point the the head of the each set
        Node *parent;
        
        //Pointers to the next node
        Node *next;
        
        //constructors for the Node class
        Node(int a)
        {
            vertexNumber = a;

            //setting null.
            next = nullptr;

            //we will create the node then set the parent pointer to itself once the node is created
            //cant set it right now!!!!!!!!!!!!!!
            parent = nullptr;
        }

};


class linkedList
{

    //Should just convert this class into a Struct
    private:

    public:

        Node *head;
        Node *tail;

        linkedList(int a)
        {
            Node *node = new Node(a);

            head = node;
            tail = node;
        }

        ~linkedList()
        {
            delete  head;
        }


};