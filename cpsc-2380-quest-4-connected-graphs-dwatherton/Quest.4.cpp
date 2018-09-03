#include"Graph.h"

int menu(int choice);
Graph createGraph();

int main()
{
	int choice = 0;

	do {
		system("cls");
		choice = menu(choice);

		switch (choice)
		{
			case 1:
			{
				system("cls");
				Graph graph = createGraph();
				graph.isStronglyConnected() ? cout << endl << "This Graph is strongly connected!" << endl << endl : cout << endl << "This Graph is not strongly connected!" << endl << endl;
				system("pause");
				break;
			}
			case 2:
			{
				system("cls");
				Graph graph = createGraph();
				graph.isWeaklyConnected() ? cout << endl << "This Graph is weakly connected!" << endl << endl : cout << endl << "This Graph is not weakly connected!" << endl << endl;
				system("pause");
				break;
			}
			case 3:
			{
				system("cls");
				Graph graph = createGraph();
				cout << endl << "The number of vertices in the weakly connected sub-graph with the largest number of vertices is: " << graph.largestWeaklyConnectedSubGraph() << "!" << endl << endl;
				system("pause");
				break;
			}
			case 4:
			{
				system("exit");
				break;
			}
			default:
			{
				cout << endl << "Error: Please enter a number 1 - 4... " << endl << endl;
				system("pause");
				break;
			}
		}

	}while (choice != 4);

	cout << endl << "Thank you for using the directed graph program!" << endl << endl;
	system("pause");
	return 0;
}

int menu(int choice)
{
	cout << "\t\t\t  Welcome to the directed graph program! (Quest 4)" << endl << endl;
	cout << "\t\t\t  1. Check if a graph is strongly connected " << endl;
	cout << "\t\t\t  2. Check if a graph is weakly connected " << endl;
	cout << "\t\t\t  3. Find the largest weakly connected sub-graph " << endl;
	cout << "\t\t\t  4. Quit " << endl << endl;
	cout << "Enter your choice here => ";
	cin >> choice;
	cin.ignore();
	return choice;
}

Graph createGraph()
{
	int numNodes = 0, numEdges = 0, vertex = 0, adjacentVertex = 0;

	cout << "Please create the graph to check: " << endl << endl;

	cout << "Please enter the number of nodes here => ";
	cin >> numNodes;

	Graph graph(numNodes);

	cout << "Please enter the number of edges here => ";
	cin >> numEdges;

	for (int i = 0; i < numEdges; i++)
	{
		cout << endl << "Enter the vertex here => ";
		cin >> vertex;

		cout << "Enter the adjacent vertex here => ";
		cin >> adjacentVertex;

		graph.addEdge(vertex, adjacentVertex);
	}

	return graph;
}