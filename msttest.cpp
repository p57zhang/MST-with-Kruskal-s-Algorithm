#include <iostream>
#include <string>
#include "graph.h"
#include "Exception.h"

using namespace std;

int main()
{

    string command;
    string args;
    int arg1;
    int arg2;
    double arg3;
    int pos;
    double **mainMatrix;
    string string;

    weightedGraph *test;
    

    while(!cin.eof())
    {

        


        cin >> command;
        

        if(command == "n")
        {
            
            try
            {
                cin >> arg1;
                test = new weightedGraph(arg1);
                cout << "success" << endl;
            }
            catch(illegal_argument)
            {
                cout << "failure" << endl;
                abort();
            }
            
            

        }

        if(command == "i")
        {

            try
            {
                cin >> args;

                //extracting the params in the case there are 3
                for(int i = 0; i < 3; i++)
                {
                    //finding the position of the ;
                    pos = args.find(";");
                    
                    if(i == 0)
                    {
                        arg1 = stoi(args.substr(0, pos));
                    }
                    else if(i == 1)
                    {
                        arg2 = stoi(args.substr(0, pos));
                    }
                    else if(i == 2)
                    {
                        arg3 = stod(args.substr(0, pos));
                    }

                    //erasing the previous substring so we can find the postions of the next ;
                    args.erase(0, pos + 1);

                }

                test -> insertEdge(arg1, arg2, arg3);
                cout << "success" << endl;

            }
            catch(illegal_argument)
            {
                cout << "failure" << endl;
            }
            


        }

        if(command == "d")
        {
            try
            {

                cin >> args;

                //extracting the params in this case there are 2
                for(int i = 0; i < 2; i++)
                {
                    //finding the position of the ;
                    pos = args.find(";");
                    
                    if(i == 0)
                    {
                        arg1 = stoi(args.substr(0, pos));
                    }
                    else if(i == 1)
                    {
                        arg2 = stoi(args.substr(0, pos));
                    }
                    
                    //erasing the previous substring so we can find the postions of the next ;
                    args.erase(0, pos + 1);

                }

                mainMatrix = test -> getMatrix();

                test -> deleteEdge(arg1, arg2);
                
            }
            catch(illegal_argument)
            {
                cout << "failure" << endl;
            }
            
        }

        if(command == "degree")
        {
            try
            {
                cin >> arg1;
                cout << "degree of " + to_string(arg1) + " is " + to_string(test ->nodeDegree(arg1)) << endl;
            }
            catch(illegal_argument)
            {
                cout << "failure" << endl;
            }


        }

        if(command == "edge_count")
        {
            
            cout << "edge count is " + to_string(test -> getNumEdges()) << endl;
        }

        if(command == "clear")
        {
            test -> clearEdges();
            cout << "success" << endl;
        }

        if(command == "mst")
        {
            
            //accounts for the cases that the number of edges is not sufficient for being a connect graph and when the node number is only 1
            if(test -> getNumEdges() >= test -> getNumNodes() - 1 && test -> getNumNodes() !=  1)
            {
                cout << "mst " + to_string(test -> kruskal()) << endl;
            }
            else
            {
                cout << "not connected" << endl;
            }
            

            
        }

       

    }


}