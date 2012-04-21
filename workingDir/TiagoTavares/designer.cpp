#include "designer.h"

std::string Designer::defautFile = "airports.txt";

Designer::Designer(int x, int y, string path, vector<Nodes>n1, vector<Edges>e1) {
	//Accepts minimum 600x600 MAX->1000, 700
	graph = new GraphViewer(x, y, false);

	if(path!="")
		graph->setBackground(path);

	graph->createWindow(x, y);

	nodes=n1;
	edges=e1;
	loadNodes();
	loadEdges();
	draw();
}

bool Designer::addNode(int id, int x, int y, string title, string color) {
	Nodes node;
	node.id=id;
	node.x=x;
	node.y=y;
	if(title == "") {
		stringstream ss;
		ss << node.id;
		node.title=ss.str();
	}else{
		node.title=title;
	}

	if(color != "")
		node.color=color;

	nodes.push_back(node);

	graph->addNode(nodes[nodes.size()-1].id, nodes[nodes.size()-1].x, nodes[nodes.size()-1].y);
	graph->setVertexLabel(nodes[nodes.size()-1].id, nodes[nodes.size()-1].title);
	if(nodes[nodes.size()-1].color != "")
		graph->setVertexColor(nodes[nodes.size()-1].id, nodes[nodes.size()-1].color);

	return true;
}

void Designer::loadNodes() {
	for(unsigned i=0; i<nodes.size(); i++) {
		graph->addNode(nodes[i].id, nodes[i].x, nodes[i].y);
		graph->setVertexLabel(nodes[i].id, nodes[i].title);
		if(nodes[i].color != "")
			graph->setVertexColor(nodes[i].id, nodes[i].color);
	}
}

void Designer::loadEdges() {
	for(unsigned i=0; i<edges.size(); i++) {
		graph->addEdge(edges[i].id, edges[i].node1, edges[i].node2, EdgeType::UNDIRECTED);
		if(edges[i].color != "")
			graph->setEdgeColor(edges[i].id, edges[i].color);
	}
}

void Designer::draw() {
	graph->rearrange();
}

void Designer::clean() {
	for(unsigned i=0; edges.size(); i++) {
		graph->removeEdge(edges[i].id);
	}

	for(unsigned i=0; nodes.size(); i++) {
		graph->removeEdge(nodes[i].id);
	}
}
