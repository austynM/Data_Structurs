#include "digraphMatrix.h"

using namespace std;
//Driver: Austyn
//Reads the input file and creates an adjacency matrix
DigraphMatrix::DigraphMatrix(const string& text)
{
	int m;

	ifstream in(text);
	if (!in.is_open())
	{
		cout << "Failed to open file\n";
	}

	in >> n >> m;
	in.ignore();

	A = new bool* [n];
	for (int i = 0; i < n; i++)
	{
		A[i] = new bool[n];
		for (int j = 0; j < n; j++)
			A[i][j] = 0;
	}

	for (int i = 0; i < m; i++)
	{
		int u, v;
		in >> u >> v;
		A[u][v] = 1;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << A[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}
//Driver: Braden
//Creates a vector containing the out neighbors, for DFS pass 1
vector<int> DigraphMatrix::getOutNeighbors(const int& v)
{
	vector<int> neighbors;

	for (int u = 0; u < n; u++)
	{
		if (A[v][u] == 1)
		{
			neighbors.push_back(u);
		}
	}

	return neighbors;
}
//Driver: Braden
//Creates a vector with the in neighbors, the reverse of our previous vector, for DFS pass 2
vector<int> DigraphMatrix::getInNeighbors(const int& v)
{
	vector<int> neighbors;

	for (int u = 0; u < n; u++)
	{
		if (A[u][v] == 1)
		{
			neighbors.push_back(u);
		}
	}

	return neighbors;
}
//Driver: Austyn
//Navigates through the digraph discovering and exploring vertices, adding them to a stack as they are explored
void DigraphMatrix::rDFS1(const int& v, map<int, mark_t>& marks)
{
	marks[v] = DISCOVERED;

	for (int C : getOutNeighbors(v))
		if (marks.at(C) == UNDISCOVERED)
			rDFS1(C, marks);

	marks[v] = EXPLORED;
	verts.push(v);
}
//Driver: Braden
//Navigates backwards through the digraph using the stack to determine which vertex to process and then adding a compID to each vertex
void DigraphMatrix::rDFS2(const int& v, map<int, mark_t>& marks, vector<int>& SCC)
{
	marks[v] = DISCOVERED;

	for (int C : getInNeighbors(v))
		if (marks.at(C) == UNDISCOVERED)
			rDFS2(C, marks, SCC);

	marks[v] = EXPLORED;
	SCC[v] = compID;
}
//Driver: Austyn
//Runs the DFS functions, sends the vertices in the stack to DFS2, and determines which compID to assign in DFS2
vector<int> DigraphMatrix::stronglyConnectedComponents()
{
	vector<int> SCC(n, -1);
	map<int, mark_t> marks;


	for (int i = 0; i < n; i++)
		marks[i] = UNDISCOVERED;

	for (int i = 0; i < n; i++)
	{
		if (marks[i] == UNDISCOVERED)
			rDFS1(i, marks);
	}

	for (int i = 0; i < n; i++)
		marks[i] = UNDISCOVERED;

	while (!verts.empty())
	{
		if (marks[verts.top()] == UNDISCOVERED)
		{
			rDFS2(verts.top(), marks, SCC);
			compID++;
		}

		verts.pop();
	}



	return SCC;
}