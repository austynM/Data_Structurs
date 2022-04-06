#ifndef __DIGRAPH_MATRIX_H
#define __DIGRAPH_MATRIX_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <map>
using namespace std;

enum mark_t { UNDISCOVERED, DISCOVERED, EXPLORED };

class DigraphMatrix
{
private:
  int n;
  int compID;
  bool** A;
  stack<int> verts;

public:
  //Reads in digraph from given file
  //Stores graph as an adjacency matrix
  DigraphMatrix(const string&);
  
  vector<int> getOutNeighbors(const int&);
  vector<int> getInNeighbors(const int& v);
  void rDFS1(const int&, map<int, mark_t>&);
  void rDFS2(const int&, map<int, mark_t>&, vector<int>&);

  //Returns number of vertices
  int getOrder() const { return n; }

  //Returns vector containing component ID for each vertex
  vector<int> stronglyConnectedComponents();



};

#endif