//Going to implement the graph using adjancy matrix since we can store the weight of the edges in the adjaceny matrix 
//as explained in this video https://www.youtube.com/watch?v=HDUzBEG1GlA since it is easier to implement undirected weighted graphs this way

#include <iostream>
#include <vector>
#include "disjoint.h"
#include "Exception.h"

using namespace std;


class weightedGraph
{

    private: 
        //This will contain the number of nodes defined by the user with command "n"
        int numNodes = 0;
        //This is the pointer to the 2d array that will contrain the adjacency matrix
        double** matrix;
        int numEdges = 0;
        //This variable holds the minimum spanning tree's value
        double mst = 0;
        
    public:
    //Constructor will create the adjacency matrix and set all matrix values to 0  

        //constructor accepts the number of vertexes in the graph
        //If the input is <= 0 then we throw exception if > 0 we construct an ajacency matrix
        weightedGraph(int n)
        {

            if(n <= 0)
            {
                throw illegal_argument();
            }
            else if(n > 0)
            {
                this -> numNodes = n;
                this -> numEdges = 0;

                //creating the x component of the 2d array
                matrix = new double*[n];

                for(int i = 0; i < n; i++)
                {
                    //for each row we are creating a column length of numNodes (y component of 2d array)
                    matrix[i] = new double[n];

                    for(int j = 0; j < n; j++)
                    {
                        //populating the new matrix with 0s since no edges are connected.
                        matrix[i][j] = 0;
                    }
                }
            }
            
        }

        //Destructor will freeup the memory allocated when creating the matrix
        ~weightedGraph()
        {
            for (int i = 0; i < numNodes; i++)
            {
                delete[] matrix[i];
            }
            delete[] matrix;
        }



        //inserting between an edge with weight w between nodes u and v
        void insertEdge(int u, int v, double w)
        {
            //throws exception if u,v are negative or greater than the highest node or there is not any node
            //or u and v are the same
            //also throws an exception if w <= 0
            if(u < 0 || v < 0 || w <= 0 || u > numNodes -1 || v > numNodes -1 || numNodes == 0 || u == v)
            {
                throw illegal_argument();
            }
            else
            {
                //If there is no edges currently in the matrix at this location we increment numEdges
                //This if statement is used to prevent the case where we simply replace the weight of an existing edge
                if(matrix[u][v] == 0)
                {
                    numEdges++;
                }
                
                matrix[u][v] = w;
                matrix[v][u] = w;

            }

        
        }

        //deletes the edge between nodes u and v
        void deleteEdge(int u, int v)
        {
            //throws exception if u,v are negative or greater than the highest node or there is not any node
            //or u and v are the same
            if(u < 0 || v < 0 || u > numNodes -1 || v > numNodes -1 || numNodes == 0 || u == v)
            {
                throw illegal_argument();
            }
            else
            {

             
                if(matrix[u][v] > 0)
                {
                    //We complete this conditional if there is no edge to delete so we dont decerement the numEdges since we
                    //did not actually delete any edges
                    if(matrix[u][v] == 0)
                    {
                        return;
                    }

                    matrix[u][v] = 0;
                    matrix[v][u] = 0;

                    numEdges--;

                    cout << "success" << endl;
                }
                else
                {
                    cout << "failure" << endl;
                }
            }
            

        }

        //This function returns the degree of vertex u
        int nodeDegree(int n)
        {
            
            if(numNodes == 0 || n < 0 || n > numNodes - 1)
            {
                throw illegal_argument();
            }
            else
            {
                int degree = 0;

                //iterate through the columns of the row n to count++ the number of edges connected to the node
                for(int j = 0; j < numNodes; j++)
                {
                    
                    if(matrix[n][j] > 0)
                    {
                        degree++;
                    }
                }

                return degree;
            }

        }

        //THis function will clear all the edges from the graph
        void clearEdges()
        {

            this -> numEdges = 0;

            for(int i = 0; i < numNodes; i++)
            {
                for(int j = 0; j < numNodes; j++)
                {
                    //populating the new matrix with 0s since we are removing all edges
                    matrix[i][j] = 0;
                }
            }


        }    

        //This is for the vector triplets I that will be used in Kruskal
        struct Triplet
        {
            int x, y;
            double z;
        };

        vector<Triplet> unsortedVector;
        vector<Triplet> sortedVector;

        //This will sort the vector that will hold the paris of nodes and their weights
        void sortVector()
        {
            //This offset will be used to printout the bottom diagonal of adjancency matrix
            int offset = numNodes;
            //smallestEdge will store the current smallest for selection sorting
            double biggestEdge = 0;
            //This will keep track of the index to migrate from the unsorted to sorted vector
            int index;
            

            //This will sort the edges from the least value to the greatest value by sorting the edges and putting it into a vector
            for(int i = 0; i < numNodes; i++)
            {

                for(int j = 0; j < numNodes - offset; j++)
                {
                        
                        // //If the vector is empty just append doesnt matter order
                        //  if(sortedVector.empty() == true && matrix[i][j] > 0)
                        //  {
                        //     sortedVector.push_back({i, j, matrix[i][j]});
                        //  }

                        if(matrix[i][j] > 0)
                        {
                           unsortedVector.push_back({i, j, matrix[i][j]});
                        }
                        

                }
                //offset is used to iterate only the bottomw diagaonal of the adjacency matrix
                offset--;
  
            }



            //selection sort to sort the unsorted vector
            //picks the biggest edge and pushes into the end of the new sorted vector
            while(unsortedVector.size() > 0 )
            {
                for(int i = 0; i < unsortedVector.size(); i++)
                {
                    if(unsortedVector[i].z > biggestEdge)
                    {
                        biggestEdge = unsortedVector[i].z;
                        index = i;
                    }

                }
                //Reset biggest edge to 0
                //migrating the unsorted vector to the sorted vector and deleting the edge from the unsorted vector
                biggestEdge = 0;
                sortedVector.push_back({unsortedVector[index].x,unsortedVector[index].y, unsortedVector[index].z});
                unsortedVector.erase(unsortedVector.begin() + index);
            }


        }

        //This is wehre kruskals algorithm will goto
        double kruskal()
        {
            //resets the mst everytime incase we change the graph etc
            mst = 0;
            int setX;
            int setY;

            //creat a new disjoint object to use in kruskals algorithm
            disjointSets *eval = new disjointSets(numNodes);
            
            //Sorts the vector based on edge values between vertexes
            sortVector();

            //make a new set for each of the vertexes
            for(int i = 0; i < numNodes; i++)
            {
                eval -> makeSet(i);
            }

            //for each edge from least to greatest union the edges if no cycle occurs and add it to the mst value
            //iteration is done reverse since I sorted from greatest to least pepega
            for(int i = sortedVector.size() - 1; i >= 0; i--)
            {
                setX = sortedVector[i].x;
                setY = sortedVector[i].y;

                //If the parents of the two sets are not equal to one another then union them and add to the mst
                //If they are equal do nothing

                if(eval -> findSet(setX) != eval -> findSet(setY))
                {   
                    
                    //add to mst if the two sets are not equal
                    eval -> unionSet(setX, setY);
                    mst = mst + sortedVector[i].z;

                   
                }

                
            }

            return mst;
           
        }


        //This function returns the number of edges
        int getNumEdges()
        {
            return numEdges;
        }

        int getNumNodes()
        {
            return numNodes;
        }

        double** getMatrix()
        {
            return matrix;
        }
        


};


