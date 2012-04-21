#include "designer.h"


int main() {
	int width = 600, height=600;
	string background = "background.jpg";
	vector<Nodes> n1;
	vector<Edges> e1;
	Nodes tempNode;
	Edges tempEdge;
	tempNode.id=0;
	tempNode.x=50;
	tempNode.y=50;
	tempNode.title = "First";
	tempNode.color = "white";
	n1.push_back(tempNode);
	tempNode.id=1;
	tempNode.x=200;
	tempNode.y=200;
	tempNode.title = "Second";
	tempNode.color = "gray";
	n1.push_back(tempNode);

	tempEdge.id=0;
	tempEdge.node1=1;
	tempEdge.node2=0;
	tempEdge.color = "white";
	e1.push_back(tempEdge);
	tempEdge.id=1;
	tempEdge.node1=0;
	tempEdge.node2=1;
	tempEdge.color = "gray";
	e1.push_back(tempEdge);

	Designer* designer = new Designer(width, height, "", n1, e1);


	getchar();
	return 0;
}
