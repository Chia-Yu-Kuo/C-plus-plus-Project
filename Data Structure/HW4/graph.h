#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include"Stack.h"


using namespace std;


class Graph
{

private:
	string input_all;
	string input_instruction;
	string input_int;
	//int converted_int;

	int node1;
	int node2;
	int weight;

	int num_vertex = 0;
	int num_edge = 0;
	bool vertex[101] = { false };
	pair<bool,int> edge_weight[101][101] ;   // row: outdegree  / column:indegree
	bool edge_transpose[101][101];




public:
	Graph();
	void read_input();
	void input_process();


	bool is_empty();
	void first_dfs(int start,bool visited[],Stack &stack);
	void second_dfs(int start, bool visited[]);

	void addVertex(int node1);	
	void deleteVertex(int node1);
	void addEdge(int node1, int node2, int weight);
	void deleteEdge(int node1,int node2);
	void Dijkstra(int node1,int node2);
	void connectedComponents();
	void BellmanFord(int node1, int node2);			



};

Graph::Graph()			
{
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			edge_weight[i][j].first = false;
			edge_weight[i][j].second = INT_MAX;
		}
	}
}


void Graph::read_input()
{
	/*
	ifstream  ifile;
	ifile.open("input4.txt");
	if (false == ifile.is_open())
	{
		cerr << "open file error" << endl;
	}
	

	while (getline(ifile, input_all))
	{
		//getline(ifile, input_all);
		input_process();
	}

	ifile.close();
	*/
	while (getline(cin, input_all))
	{
		//getline(ifile, input_all);
		input_process();
	}
}



void Graph::input_process()
{
	stringstream x(input_all);
	stringstream convertor,convertor1,convertor2;
	getline(x, input_instruction, ' ');



	if (input_instruction == "addVertex")
	{
		getline(x, input_int, ' ');
		convertor << input_int;
		convertor >> node1;



		addVertex(node1);

	}
	else if (input_instruction == "deleteVertex")
	{
		getline(x, input_int, ' ');
		convertor << input_int;
		convertor >> node1;

		deleteVertex(node1);	
	}
	else if (input_instruction == "addEdge")
	{
		getline(x, input_int, ' ');
		convertor << input_int;
		convertor >> node1;

		getline(x, input_int, ' ');
		convertor1 << input_int;
		convertor1 >> node2;

		getline(x, input_int, ' ');
		convertor2 << input_int;
		convertor2 >> weight;


		addEdge(node1, node2,weight);

	}
	else if (input_instruction == "deleteEdge")
	{
		getline(x, input_int, ' ');
		convertor << input_int;
		convertor >> node1;

		getline(x, input_int, ' ');
		convertor1 << input_int;
		convertor1 >> node2;

		deleteEdge(node1, node2);

	}
	else if (input_instruction == "Dijkstra")
	{
		getline(x, input_int, ' ');
		convertor << input_int;
		convertor >> node1;

		getline(x, input_int, ' ');
		convertor1 << input_int;
		convertor1 >> node2;

		Dijkstra(node1,node2);

	}
	else if (input_instruction == "connectedComponents")
	{
		connectedComponents();
	}
	else if (input_instruction == "BellmanFord")
	{
		getline(x, input_int, ' ');
		convertor << input_int;
		convertor >> node1;

		getline(x, input_int, ' ');
		convertor1 << input_int;
		convertor1 >> node2;

	

		BellmanFord(node1,node2);

	}
	else
	{
		cout << "Wrong Instruction" << endl;
	}


}


bool Graph::is_empty()
{
	for (int i = 0; i < 101; i++)
	{
		if (vertex[i]==true)
		{
			return false;
		}
	}
	return true;
}





void Graph::addVertex(int node1)		//char[0]  int -48
{
	if (node1 < 0 || node1>100)
	{
		cout << "add an invalid vertex" << endl;
	}
	else
	{
		if (vertex[node1]==true)
		{
			cout << "vertex " << node1 << " is already in G" << endl;
		}
		else
		{
			vertex[node1] = true;
			num_vertex++;
		}
	}
}

void Graph::deleteVertex(int node1)
{
	if (node1 < 0 || node1>100)
	{
		cout << "delete an invalid vertex" << endl;
	}
	else
	{
		if (vertex[node1] == false)
		{
			cout << "vertex " << node1 << " isn't in G" << endl;
		}
		else
		{
			vertex[node1] = false;
			num_vertex--;

			for (int i = 0; i < 101; i++)	//²MÃä
			{
				edge_weight[node1][i].first = false;		//outdegree
				edge_weight[i][node1].first = false;
				edge_weight[node1][i].second = INT_MAX;		//outdegree
				edge_weight[node1][i].first = INT_MAX;		//outdegree
			}
		}
	}
}


void Graph::addEdge(int node1, int node2 , int weight)					//h--
{
	if (vertex[node1] == false || vertex[node2] == false)
	{
		cout << "add an invalid edge" << endl;
	}
	else
	{
		if (edge_weight[node1][node2].first==false)
		{
			edge_weight[node1][node2].first = true;
			edge_weight[node1][node2].second = weight;
			num_edge++;
		}
		else
		{
			edge_weight[node1][node2].second = weight;
		}
		
	}
}


void Graph::deleteEdge(int node1, int node2)
{
	if (vertex[node1] == false || vertex[node2] == false)
	{
		cout << "delete an invalid edge" << endl;
	}
	else
	{
		if (edge_weight[node1][node2].first == false)		
		{
			cout << "fail to delete edge < " << node1 << " , " << node2 << " >" << endl;
		}
		else		// revise weight
		{
			edge_weight[node1][node2].first = false;
			edge_weight[node1][node2].second = INT_MAX;
			num_edge--;
		}
	}

}

void Graph::Dijkstra(int node1,int node2)
{
	if (vertex[node1] ==false || vertex[node2]==false)
	{
		cout << "an invalid vertex"<<endl;
		return;
	}
	
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)		//has negtive
		{
			if (edge_weight[i][j].first==true && edge_weight[i][j].second<0)
			{
				cout << "G contains a negative edge." << endl;
				return;
			}

		}
	}
	
	
	//intitialize
	bool can_sel[101];
	int distance[101];
	int current_vertex =node1;
	int min = INT_MAX;
	int last_move[101] = {0};
	//Queue<int> current_vertex_path;
	//Queue<int> shortest_path;


	for (int i = 0; i < 101; i++)
	{
		can_sel[i] = vertex[i];
		distance[i] = edge_weight[node1][i].second;
		if (edge_weight[node1][i].first)
		{
			last_move[i] = node1;			//root
		}
	}
	can_sel[node1] = false;
	//current_vertex_path.enqueue(node1);


	for (int i = 0; i < num_vertex - 2; i++)			//repeat (count-2)
	{
		//find min
		min = INT_MAX;
		for (int i = 0; i < 101; i++)
		{
			if (can_sel[i] == true && distance[i] < min)
			{
				min = distance[i];
				current_vertex = i;
			}
		}
		can_sel[current_vertex] = false;
		//current_vertex_path.enqueue(current_vertex);


		for (int i = 0; i < 101; i++)
		{
			if (edge_weight[current_vertex][i].first && min+edge_weight[current_vertex][i].second<distance[i])
			{
				/*
				if (i==node2)	//find current shortest path
				{
					//shortest_path = current_vertex_path;
				}
				*/
				distance[i] = min + edge_weight[current_vertex][i].second;
				last_move[i] = current_vertex;
			}
		}
	}

	//shortest_path.enqueue(node2);


	//////////////////////output//////////////

	if (distance[node2]==INT_MAX)
	{
		cout << "Disjkstra: no solution for " << node1 << " -> " << node2 << endl;
		
	}
	else
	{
		/*
		int queue_size = shortest_path.size();
		for (int i = 0; i < queue_size-1; i++)
		{
			cout << shortest_path.dequeue() << "->";
		}
		cout << shortest_path.dequeue() << "  total: " << distance[node2] << endl;
		*/

		//push to stack   (reverse)
		Stack reverse_path;

		for ( int i= node2; i !=node1; i=last_move[i])
		{
			reverse_path.push(i);
		}
		reverse_path.push(node1);


		int size = reverse_path.get_size();
		for (int i = 0; i < size-1 ; i++)
		{
			cout << reverse_path.pop() << "->";
		}
		cout << reverse_path.pop() << "  total: " << distance[node2] << endl;

	}


}


void Graph::BellmanFord(int node1, int node2)  // -1 :wrong data   0 :is not in bst  1:have data
{

	if (vertex[node1] == false || vertex[node2] == false)
	{
		cout << "an invalid vertex" << endl;
		return;
	}

	
	//intitialize
	bool can_sel[101];
	int distance[101];
	int min = INT_MAX;
	int last_move[101] = {0};

	for (int i = 0; i < 101; i++)
	{
		can_sel[i] = vertex[i];
		distance[i] = edge_weight[node1][i].second;
		if (edge_weight[node1][i].first)
		{
			last_move[i] = node1;			//root
		}
	}
	can_sel[node1] = false;
	distance[node1] = 0;


	for (int i = 0; i < num_vertex-1; i++)		//one vertex at most v-1 edge
	{
		for (int j = 0; j < 101; j++)			//source
		{
			for (int k = 0; k < 101; k++)		//dest
			{
				if (edge_weight[j][k].first)	
				{
					if (distance[j] !=INT_MAX &&distance[j]+edge_weight[j][k].second < distance[k])
					{
						distance[k] = distance[j] + edge_weight[j][k].second;
						last_move[k] = j;

					}
				}
			}
		}
	}


	//////////////////////output//////////////

	//chech cycle
	for (int j = 0; j < 101; j++)			//source
	{
		for (int k = 0; k < 101; k++)		//dest
		{
			if (edge_weight[j][k].first)
			{
				if (distance[j] != INT_MAX && distance[j] + edge_weight[j][k].second < distance[k])
				{
					cout << "G contains a cycle of negative length" << endl;
					return;
				}
			}
		}
	}

	if (distance[node2] == INT_MAX)
	{
		cout << "BellmanFord: no solution for " << node1 << " -> " << node2 << endl;
		return;
	}


	//push to stack   (reverse)
	Stack reverse_path;

	for (int i = node2; i != node1; i = last_move[i])
	{
		reverse_path.push(i);
	}
	reverse_path.push(node1);


	int size = reverse_path.get_size();
	for (int i = 0; i < size - 1; i++)
	{
		cout << reverse_path.pop() << "->";
	}
	cout << reverse_path.pop() << "  total: " << distance[node2] << endl;

}


void Graph::first_dfs(int start,bool visited[],Stack &stack)
{
	visited[start] = true;
	for (int i = 0; i < 101; i++)
	{
		if (edge_weight[start][i].first)
		{
			if (!visited[i])
			{
				first_dfs(i, visited,stack);
			}
		}

	}
	stack.push(start);

}

void Graph::second_dfs(int start, bool visited[])
{
	visited[start] = true;
	for (int i = 0; i < 101; i++)
	{
		if (edge_transpose[start][i])
		{
			if (!visited[i])
			{
				second_dfs(i, visited);
			}
		}

	}

}

void Graph::connectedComponents()			//level order
{
	bool *visited = new bool[101];
	int count=0;
	Stack stack;
	

	//first dfs

	for (int i = 0; i < 101; i++)
	{
		visited[i] = true;
		if (vertex[i] == true)
		{
			visited[i] = false;
		}
	}

	for (int i = 0; i < 101; i++) 
	{
		if (visited[i] == false)
			first_dfs(i, visited,stack);
	}


	//transpose
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			edge_transpose[j][i] = edge_weight[i][j].first;
		}
	}

	//second dfs
	for (int i = 0; i < 101; i++)
	{
		visited[i] = true;
		if (vertex[i] == true)
		{
			visited[i] = false;
		}
	}


	while (stack.isEmpty() == false) 
	{
		int index = stack.get_top_value();
		stack.pop();

		if (visited[index] == false) 
		{
			second_dfs(index, visited);
			count++;
		}
	}

	cout <<"connectedComponents: " << count << endl;
}


