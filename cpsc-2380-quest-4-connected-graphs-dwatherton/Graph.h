#pragma once
#include<iostream>
#include<list>
using namespace std;

// Please note: I borrowed code for the Graph class from the code examples provided on GitHub! Citation: https://github.com/CPSC-2380-UALR/CPSC.2380.Code.Examples/tree/master/Level.8.2.Graph.Depth.First.Search

class Graph
{
	private:
		int numVertices;
		list<int>* adjacents;
		void DFSRecursive(int vertex, bool visited[]);

	public:
		Graph(int vertices);
		void addEdge(int vertex, int adjacentVertex);

		// Added utility function for isStronglyConnected()
		Graph getTranspose();

		// Added functions for Quest 4
		bool isStronglyConnected();
		bool isWeaklyConnected();
		int largestWeaklyConnectedSubGraph();
};