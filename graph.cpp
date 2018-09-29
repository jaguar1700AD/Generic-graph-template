#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef struct _head
{
	vector <int> adjacent;
}head;

template <class T> class Graph
{
	vector <head> vertex;
	vector <T> mapping;  // Contains the mapping from vertex indices to their actual values

	int return_index(T x); // Returns the index corresponding to vertex x
	bool edge(int srcI, int destI); // Is there an edge between vertices with indices srcI and destI ?
	void DFS_visit(int uI, vector <int> &visited, vector <T> &dfs);

public:

	void add_edge(T src, T dest, bool directed);
	void delete_edge(T src, T dest, bool directed);
	void print();

	vector <T> BFS(T origin);
	vector <T> DFS();
};

template <class T> int Graph<T>::return_index(T x)
{
	for(int i = 0; i < mapping.size(); i++)
	{
		if (mapping[i] == x)
			return i;
	}

	return -1;
}

template <class T> bool Graph<T>::edge(int srcI, int destI)
{
	for(int i = 0; i < vertex[srcI].adjacent.size(); i++)
	{
		if (vertex[srcI].adjacent[i] == destI)
			return true;
	}
	return false;
}

template <class T> void Graph<T>::add_edge(T src, T dest, bool directed)
{
	int srcI = return_index(src); int destI = return_index(dest);
	
	if (srcI == -1)
	{
 		vertex.push_back(*(new head));
		srcI = vertex.size() - 1;
		mapping.push_back(src);
	}

	if (destI == -1)
	{
		vertex.push_back(*(new head));
		destI = vertex.size() - 1;
		mapping.push_back(dest);
	}

	if (!edge(srcI, destI))
		vertex[srcI].adjacent.push_back(destI);


	if (directed == false && !edge(destI, srcI))
		vertex[destI].adjacent.push_back(srcI);
}

template <class T> void Graph<T>::delete_edge(T src, T dest, bool directed)
{
	int srcI = return_index(src); int destI = return_index(dest); 
	if (srcI == -1 || destI == -1)
		return;

	for(int i = 0; i < vertex[srcI].adjacent.size(); i++)
	{
		if (vertex[srcI].adjacent[i] == destI)
			vertex[srcI].adjacent.erase(vertex[srcI].adjacent.begin() + i, vertex[srcI].adjacent.begin() + i + 1);
	}

	if (directed == true)
		return;

	for(int i = 0; i < vertex[destI].adjacent.size(); i++)
	{
		if (vertex[destI].adjacent[i] == srcI)
			vertex[destI].adjacent.erase(vertex[destI].adjacent.begin() + i, vertex[destI].adjacent.begin() + i + 1);
	}

}

template <class T> void Graph<T>::print()
{
	cout << endl;

	for (int i = 0; i < vertex.size(); i++)
	{
		cout << mapping[i] << " -> ";

		for(int j = 0; j < vertex[i].adjacent.size(); j++)
			cout << mapping[vertex[i].adjacent[j]] << " ";
		cout << endl;
	}

	cout << endl;
}

template <class T> vector <T> Graph<T>::BFS(T origin)
{
	int originI = return_index(origin);
	vector <T> bfs; 
	queue <int> Q; Q.push(originI);
	vector <bool> visited(vertex.size(), false); visited[originI] = true;

	while(!Q.empty())
	{
		int uI = Q.front(); Q.pop();
		bfs.push_back(mapping[uI]);

		for(int i = 0; i < vertex[uI].adjacent.size(); i++)
		{
			int vI = vertex[uI].adjacent[i]; 
			if (visited[vI] == false)
			{
				Q.push(vI); visited[vI] = true;
			}
		}
	}

	return bfs;
}

template <class T> vector <T> Graph<T>::DFS()
{
	vector <int> visited(vertex.size(), false);
	vector <T> dfs;

	for(int i = 0; i < vertex.size(); i++)
	{
		if (visited[i] == false)
			DFS_visit(i, visited, dfs);
	}

	return dfs;
}

template <class T> void Graph<T>::DFS_visit(int uI, vector <int> &visited, vector <T> &dfs)
{
		dfs.push_back(mapping[uI]);
		visited[uI] = true;

		for(int i = 0; i < vertex[uI].adjacent.size(); i++)
		{
			int vI = vertex[uI].adjacent[i];
			if (visited[vI] == false)
			{
				DFS_visit(vI, visited, dfs);
			}
		}
}


int main()
{
	Graph <char> g1;

	g1.add_edge('b','a',true);
	g1.add_edge('a','c',true);
	g1.add_edge('a','d',true);
	g1.add_edge('e','d',true);
	g1.add_edge('e','f',true);
	g1.add_edge('c','f',true);
	g1.add_edge('c','g',true);
	g1.add_edge('f','g',true);

	g1.print();

	cout << endl;
	vector <char> dfs = g1.DFS();
	for(int i = 0; i < dfs.size(); i++)
		cout << dfs[i] << " ";
	cout << endl;
}