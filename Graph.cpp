#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>

#define infinity 0x3f3f3f3f

#include "Graph.h"

using namespace std;

Graph::Graph(){}

int Graph::addVertex()
{
	int newv = getNumVertices();
	vertices.insert(newv);
	return newv;
}

void Graph::addEdge(directedEdge newEdge, int weight)
{
	bool check1, check2;

	check1 = vertices.find(newEdge.first) != vertices.end();
	check2 = vertices.find(newEdge.second) != vertices.end();

	if(check1 == 1 && check2 == 1)
	{
		edges.insert(make_pair(newEdge.first, newEdge.second));
		weights[make_pair(newEdge.first, newEdge.second)] = weight;
	}
}

int Graph::getNumVertices()
{
	int size;
	size = vertices.size();
	return size;
}

int Graph::getWeight(directedEdge edge)
{
	int w;
	w = weights[make_pair(edge.first, edge.second)];
	return w;
}

bool Graph::isEdge(directedEdge newEdge)
{
	bool check;
	check = edges.find(newEdge) != edges.end();
	return check;
}

void Graph::print()
{
	typedef set<int>::iterator iterator;
	iterator i;

	typedef set<directedEdge>::iterator iteratorj;
	iteratorj j;

	for(i = vertices.begin(); i != vertices.end(); i++)
	{
		cout << *i << ": ";
		
		for(j = edges.begin(); j != edges.end(); j++)
		{
			if(*i == (*j).first)
			{
				cout << (*j).second << " ";
				cout << "(" << weights[make_pair((*j).first, (*j).second)] << ")";
				cout << " ";
			}
		}

		cout << endl;
	}
}

void Graph::generateGraph(string fileName)
{
	ifstream file;
	string s;
	istringstream iss(s);

	string line;
	int n = 0, v, i = 0;

	directedEdge ne;

	file.open(fileName);

	if(file.is_open())
	{
		for(n = 1; getline(file, line); n++)
		{
			i = 0;
			istringstream iss(line);


			//add vertices and edges

			if(n == 1) //first vertex
			{
				while(iss >> s && i < 2)
				{
					i++
					if(i == 1)
					{
						v = stoi(s);
						for(int n = 0; n < v; n++) //until the last vertex
						{
							addVertex();
						}
					}
				}
			}

			else //creates edges after vertices are made
			{
				while(iss >> s)
				{
					i++;

					if(i == 1)
					{
						ne.first = stoi(s); //generates first edge
					}
					else if(i == 2)
					{
						ne.second = stoi(s); //generates second edge
					}
					else
					{
						int nw;
						nw = stoi(s):
						addEdge(ne, nw); //generates edges
					}
				}
			}
		}
	}
}

void Graph::modifiedDijkstra(int source)
{
	//initialize vectors, map, set with types in graph.h
	vector<int> d, tempd, sptcurrentv;
    map<int, int>::iterator it;
    set<int> sptSet;

	int currentv, min;

	//creating typed iterators
    typedef set<int>::iterator iterator;
	iterator it;
	typedef set<directedEdge>::iterator iteratorj;
	iteratorj j;

	//vectors get vertices
	sptcurrentv.assign(getNumVertices(), 0);
	tempd.assign(getNumVertices(), infinity);
	d.assign(getNumVertices(), infinity);

	d[source] = 0; //distance from any source to vertex is 0
	tempd[source] = 0; //same prospect as above

	//Djikstra
	//find minimum path for all vertices
	while(!tempd.empty())
	{
		min = *min_element(begin(tempd), end(tempd)); //create min specifications

		for(int i = 0; i < d.size(); i++)
		{
			if(min == d[i]) //sweet n simple
			{
				currentv = i;
			}
		}

		bool end = sptSet.find(currentv) != sptSet.end(); //check to make sure you're not at the end of the set

		for(it = edges.begin(); it != edges.end(); it++) //go through all edges
		{
			if(currentv == (*it).first && end == 0) //if not at end of set
			{ 
				if(d[(*it).second] > (d[currentv] + weights[make_pair((*it).first), (*it).second])) //if dist[v] > dist[u] + weight(u,v)
				{
					sptcurrentv[(*it).second] =  sptcurrentv[(*it).second] + 1; //update distance
				}
			}
		}

		sptSet.insert(currentv); //inserts new weight
		tempd.erase(remove(tempd.begin(), tempd.end(), min), tempd.end());
	}

	//printtttt
	cout << endl;
	cout << "shortest paths from node " << source << ":" << endl;
	for (int i=0; i < getNumVertices(); i++)
	{
		if(i != source)
		{
			cout << "distance to vertex " << i << " is " << d[i] << " ";
			cout << "and there are " << sptcurrentv[i] << " shortest paths" << endl;
		}
	}


    //basic Djikstra for reference, pulled from geeksforgeeks. unused in actual code.


    /* // Prints shortest paths from src to all other vertices 
void Graph::shortestPath(int src) 
{ 
    // Create a set to store vertices that are being 
    // prerocessed 
    set< pair<int, int> > setds; 
  
    // Create a vector for distances and initialize all 
    // distances as infinite (INF) 
    vector<int> dist(V, INF); 
  
    // Insert source itself in Set and initialize its 
    // distance as 0. 
    setds.insert(make_pair(0, src)); 
    dist[src] = 0; 
  
    Looping till all shortest distance are finalized 
       then setds will become empty
    while (!setds.empty()) 
    { 
        // The first vertex in Set is the minimum distance 
        // vertex, extract it from set. 
        pair<int, int> tmp = *(setds.begin()); 
        setds.erase(setds.begin()); 
  
        // vertex label is stored in second of pair (it 
        // has to be done this way to keep the vertices 
        // sorted distance (distance must be first item 
        // in pair) 
        int u = tmp.second; 
  
        // 'i' is used to get all adjacent vertices of a vertex 
        list< pair<int, int> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
            // Get vertex label and weight of current adjacent 
            // of u. 
            int v = (*i).first; 
            int weight = (*i).second; 
  
            //  If there is shorter path to v through u. 
            if (dist[v] > dist[u] + weight) 
            { 
                	If distance of v is not INF then it must be in 
                    our set, so removing it and inserting again 
                    with updated less distance.   
                    Note : We extract only those vertices from Set 
                    for which distance is finalized. So for them,  
                    we would never reach here.
                if (dist[v] != INF) 
                    setds.erase(setds.find(make_pair(dist[v], v))); 
  
                // Updating distance of v 
                dist[v] = dist[u] + weight; 
                setds.insert(make_pair(dist[v], v)); 
            } 
        } 
    } 
  
    // Print shortest distances stored in dist[] 
    printf("Vertex   Distance from Source\n"); 
    for (int i = 0; i < V; ++i) 
        printf("%d \t\t %d\n", i, dist[i]); 
    */
  
} 