/*********************************************************************
* Filename:   Cpp_Dijkstra.Algorithm.cpp
* Author:     Javier Montenegro (javiermontenegro.github.io)
* Copyright:  @2019
* Details:    function to implement Dijkstra algorithm.
*********************************************************************/

#include <iostream>
#include <limits.h>
using namespace std;

class Graph
{
public:
    int vertexNum;
    int **edges;

    Graph(const int V)
    {
        this->edges = new int*[V];
        for (int i = 0; i < V; i++)
        {
            edges[i] = new int[V];
        }//End for

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                edges[i][j] = 0;
            }//End for
        }//End for

        this->vertexNum = V;
    }//End Graph

    void addEdge(int src, int dst, int weight)
    {
        this->edges[src][dst] = weight;
    }//End addEdge
};//End class Graph

int minDistance(int mdist[], bool vset[], int V)
{
    int minVal = INT_MAX, minInd = 0;
    for(int i=0; i<V; i++)
    {
        if(!vset[i] && (mdist[i] < minVal))
        {
            minVal = mdist[i];
            minInd = i;
        }//End if
    }//End for

    return minInd;
}//End minDistance

void print(int dist[], int V)
{
    cout<<"\nVertex  Distance"<<endl;
    for(int i = 0; i < V; i++)
    {
        if( dist[i] < INT_MAX)
            cout<<i<<"\t"<<dist[i]<<endl;
        else
            cout<<i<<"\tINF"<<endl;
    }//End for
}//End print 

void Dijkstra(Graph graph, int src)
{
    int V = graph.vertexNum;
    int mdist[V]; //Stores updated distances to vertex
    bool vset[V]; // vset[i] is true if the vertex i included
    // in the shortest path tree

    for(int i=0; i<V; i++)
    {
        mdist[i] = INT_MAX;
        vset[i] = false;
    }//End for

    mdist[src] = 0;

    for(int count = 0; count<V-1; count++)
    {
        int u = minDistance(mdist,vset,V);

        vset[u] = true;

        for(int v=0; v<V; v++)
        {
            if(!vset[v] && graph.edges[u][v] && mdist[u] + graph.edges[u][v] < mdist[v])
            {
                mdist[v] = mdist[u] + graph.edges[u][v];
            }//End if
        }//End for
    }//End for

    print(mdist, V);
}//End Dijkstra

int main()
{
    int V,E,gsrc;
    int src,dst,weight;
    cout<<"Enter number of vertices: ";
    cin>>V;
    cout<<"Enter number of edges: ";
    cin>>E;
    Graph G(V);
    for(int i=0; i<E; i++)
    {
        cout<<"\nEdge "<<i+1<<"\nEnter source: ";
        cin>>src;
        cout<<"Enter destination: ";
        cin>>dst;
        cout<<"Enter weight: ";
        cin>>weight;

        if (src >= 0 && src < V && dst >= 0 && dst < V)
        {
            G.addEdge(src, dst, weight);
        }
        else
        {
            cout << "source and/or destination out of bounds" << endl;
            i--;
            continue;
        }//End if
    }//End for

    cout<<"\nEnter source:";
    cin>>gsrc;
    Dijkstra(G,gsrc);

    return 0;
}//End main
