#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include"Queue.h"


using namespace std;


class MaxFlow
{

private:
	string input_all;
	string input_instruction;
	string input_int;
	//int converted_int;

	int node1;
	int node2;
	int weight;

	int num_vertex ;
	int num_edge ;

	pair<bool, int>** original_edge_weight;
	pair<bool, int>** residul;


	
public:
	void read_input();
	void input_process();
	void addEdge(int node1, int node2, int weight);


	void fold_fulkerson();
	bool bfs(int* pre);



};




void MaxFlow::read_input()
{
	//build matrix
	stringstream convertor;

	getline(cin,input_int);
	convertor << input_int;
	convertor >> num_vertex;

	original_edge_weight = new pair<bool,int>* [num_vertex];
	for (int i = 0; i < num_vertex; i++)
	{
		original_edge_weight[i] = new pair<bool, int>[num_vertex];
		for (int j = 0; j < num_vertex; j++)
		{
			original_edge_weight[i][j].first = false;
			original_edge_weight[i][j].second = 0;
		}
	}


	while (getline(cin, input_all))
	{
		input_process();
	}


	fold_fulkerson();
}



void MaxFlow::input_process()		
{
	
	stringstream x(input_all);
	stringstream convertor, convertor1, convertor2;
	
	//addEdge

		getline(x, input_int, ' ');
		convertor << input_int;
		convertor >> node1;

		getline(x, input_int, ' ');
		convertor1 << input_int;
		convertor1 >> node2;

		getline(x, input_int, ' ');
		convertor2 << input_int;
		convertor2 >> weight;
	

		addEdge(node1, node2, weight);

}
	






void MaxFlow::addEdge(int node1, int node2, int weight)					//h--
{
		if (original_edge_weight[node1][node2].first == false)
		{
			original_edge_weight[node1][node2].first = true;
			original_edge_weight[node1][node2].second = weight;
			num_edge++;
		}
		else
		{
			original_edge_weight[node1][node2].second = weight;
		}
}


void MaxFlow::fold_fulkerson() 
{
	//intitial
	residul= new pair<bool, int>*[num_vertex];
	for (int i = 0; i < num_vertex; i++)
	{
		residul[i]= new pair<bool, int>[num_vertex];
		for (int j = 0; j < num_vertex; j++)
		{
			residul[i][j] = original_edge_weight[i][j];
		}
	}

	int maxflow = 0;
	int* pre = new int[num_vertex];


	/*
	//test
	for (int i = 0; i < num_vertex; i++)
	{
		for (int j = 0; j < num_vertex; j++)
		{
			cout << original_edge_weight[i][j].second << "  ";
		}
	}
	cout << endl;
	//test
	for (int i = 0; i < num_vertex; i++)
	{
		for (int j = 0; j < num_vertex; j++)
		{
			cout << residul[i][j].second << "  ";
		}
	}
	*/

	//find argument path
	while (bfs(pre))
	{
		//find min cap
		int min_cap=INT_MAX;

		for (int i = num_vertex-1; pre[i]!=-1 ; i=pre[i])
		{
			if (residul[pre[i]][i].first && residul[pre[i]][i].second!=0 && residul[pre[i]][i].second<min_cap)
			{
				min_cap = residul[pre[i]][i].second;
			}
		}

		//updata max flow + residual
		maxflow = maxflow + min_cap;
		for (int i = num_vertex-1; i!=0 ; i=pre[i])
		{
			int temp = pre[i];
			residul[temp][i].second -= min_cap;
			residul[i][temp].second += min_cap;
		}		
	}

	//output
	for (int i = 0; i < num_vertex; i++)
	{
		for (int j = 0; j < num_vertex; j++)
		{
			if (residul[i][j].first)
			{
				cout << "<" << i << "," << j << ">	" << (original_edge_weight[i][j].second-residul[i][j].second) << "	" << original_edge_weight[i][j].second << endl;
			}
		}
	}
	cout << "total:  " << maxflow;

}


bool MaxFlow::bfs(int* pre)		//start=0  , terminl=num_vertex-1
{
	int* visited=new int[num_vertex];

	//initialize visited
	for (int i = 0; i < num_vertex; i++) {
		visited[i] = 0;     
		pre[i] = -1;
	}

	Queue<int> queue;
	

	queue.enqueue(0);
	visited[0] = 1;
	while (!queue.isEmpty()) {
		int has_visited = queue.peek();
		for (int j = 0; j < num_vertex; j++) {
			if (residul[has_visited][j].first && residul[has_visited][j].second != 0 && visited[j] == 0)
			{
				queue.enqueue(j);
				visited[j] = 1;
				pre[j] = has_visited;
			}
		}
		int trash=queue.dequeue();
	}
	return (visited[num_vertex-1] == 1);  

}


