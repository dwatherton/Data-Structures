#include"Graph.h"

// Please note: I borrowed code for the constructor, addEdge and DFSRecursive functions from the code examples on GitHub! Citation: https://github.com/CPSC-2380-UALR/CPSC.2380.Code.Examples/tree/master/Level.8.2.Graph.Depth.First.Search

Graph::Graph(int vertices)
{
	this->numVertices = vertices;
	adjacents = new list<int>[numVertices];
}

void Graph::addEdge(int vertex, int adjacentVertex)
{
	adjacents[vertex].push_back(adjacentVertex);
	// Commented out because we need a DIRECTED graph
	// adjacents[adjacentVertex].push_back(vertex);
}

void Graph::DFSRecursive(int vertex, bool visited[])
{
	visited[vertex] = true;

	for (auto adjVertex : adjacents[vertex])
	{
		if (!visited[adjVertex])
		{
			DFSRecursive(adjVertex, visited);
		}
	}
}

// Function that returns reverse (or transpose) of a graph. Citation: https://www.geeksforgeeks.org/connectivity-in-a-directed-graph/ This citation includes the idea behind the isStronglyConnected() function!
Graph Graph::getTranspose()
{
	Graph g(numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		// Recur for all the vertices adjacent to this vertex
		list<int>::iterator j;
		for (j = adjacents[i].begin(); j != adjacents[i].end(); ++j)
		{
			// Reverse the direction of graph (add this vertex to the adjacent vertices list)
			g.adjacents[*j].push_back(i);
		}
	}
	return g;
}

bool Graph::isStronglyConnected()
{
	// Mark all vertices as not visited
	bool* visited = new bool[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
		visited[i] = false;
	}

	DFSRecursive(0, visited);

	// Check if we visited every vertex in DFS
	for (int i = 0; i < numVertices; i++)
	{
		if (visited[i] == false)
		{
			return false;
		}
	}

	// I got the idea to transpose and run another DFS on GeeksForGeeks.org
	Graph g = getTranspose();

	for (int i = 0; i < numVertices; i++)
	{
		visited[i] = false;
	}

	g.DFSRecursive(0, visited);

	for (int i = 0; i < numVertices; i++)
	{
		if (visited[i] == false)
		{
			return false;
		}
	}

	// If we visited every vertex in both directions, return true
	return true;
}

bool Graph::isWeaklyConnected()
{
	// Create new graph to make undirected graph
	Graph g(numVertices);

	// Turn the digraph into an undirected graph
	for (int i = 0; i < numVertices; i++)
	{
		for (auto adjVertex : adjacents[i])
		{
			g.adjacents[i].push_back(adjVertex);
			g.adjacents[adjVertex].push_back(i);
		}
	}

	// Check if the graph isStronglyConnected now
	return g.isStronglyConnected();
}

int Graph::largestWeaklyConnectedSubGraph()
{
	if (isWeaklyConnected())
	{
		return numVertices;
	}

	int currentLargest = 1;

	// Mark each vertex as unvisited
	bool *visited = new bool[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
		visited[i] = false;
	}
	
	for (int i = 0; i < numVertices; i++)
	{
		int nodesVisited = 0;
		// Do a DFS
		DFSRecursive(0, visited);
		for (int j = 0; j < numVertices; j++)
		{
			if (visited[j])
			{
				// Add up the number of visited vertices
				nodesVisited++;
			}
		}
		if (nodesVisited > currentLargest)
		{
			// Found a larger sub-graph, update currentLargest
			currentLargest = nodesVisited;
		}
	}
	return currentLargest;
}