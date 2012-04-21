#ifndef _DESIGNER_
#define _DESIGNER_

#include "graphviewer.h"
#include <vector>
#include <sstream>

using namespace std;

struct Nodes {
  int id;
  std::string title;
  int x;
  int y;
  string color;
} ;

struct Edges {
  int id;
  int node1;
  int node2;
  string color;
} ;

class Designer {
private:
	GraphViewer *graph;
	vector<Nodes> nodes;
	vector<Edges> edges;

	void loadNodes();
	void loadEdges();
 public:
  //Constructor
  Designer(int x, int y, string path, vector<Nodes>n1, vector<Edges>e1);
  bool addNode(int id, int x, int y, string title, string color);
  void draw();
  void clean();
};

#endif
