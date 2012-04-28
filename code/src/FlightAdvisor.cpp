#include "FlightAdvisor.h"
#include "Graph.h"
#include <stdlib.h>
#include "graphviewer.h"
#include <sstream>
FlightAdvisor::FlightAdvisor(string networkFileName, string airportsFileName,
		string waypointsFileName) {
	// Save the file names
	this->networkFileName = networkFileName;
	this->airportsFileName = airportsFileName;
	this->waypointsFileName = waypointsFileName;
	// Load all the necessary data
	loadData();
}

void FlightAdvisor::loadData() {
	airports = LoadData::loadAirports(airportsFileName);
	waypoints = LoadData::loadWaypoints(waypointsFileName);
	network = LoadData::createGraph(networkFileName, airportsFileName,
			waypointsFileName);
	printNetwork();
}
void FlightAdvisor::run() {
	welcomeMessage();
	do {
		askOption();
		calculateRoutes();
		printRoutes();
	} while (userOption != 0);
}
void FlightAdvisor::welcomeMessage() {
	cout << ":: WELCOME TO FLIGHT ADVISOR ::\n";
	cout
			<< "This program can help you choosing the best flight route of a network\n"
			<< "of waypoints and airports, that are stored in the \"data\" folder.\n\n";
}
void FlightAdvisor::askOption() {
	cout << "Choose the best option for you:\n";
	cout << "1- Give source and destination airport\n";
	cout << "2- Give source airport and know all the routes\n";
	cout << "3- Know all the best routes\n";
	cout << "0- EXIT\n";

	// Get the option
	string input;
	string validOptions = "1230";
	do {
		cout << "> ";
		getline(cin, input);
	} while (input.size() != (unsigned int) 1
			|| (int) validOptions.find(input[0]) == -1);
	userOption = atoi(input.c_str());

}

void FlightAdvisor::calculateRoutes() {
	// Decide what to do
	switch (userOption) {
	case 1: {
		do {
			cout << "Source: ";
			getline(cin, source);
		} while (!checkAirportID(source));
		do {
			cout << "Destination: ";
			getline(cin, destination);
		} while (!checkAirportID(destination));
		routesCalculated.push_back(getBestRoute(source, destination));
	}
		break;
	}
}

void FlightAdvisor::printRoutes() {

}

vector<string> FlightAdvisor::getBestRoute(string source, string destination) {
	// (1) use the dijkstra
	Graph<string> tempGraph;
	network.clone(tempGraph);
	tempGraph.Dijkstra(source);

	// (2) build the path
	vector<string> path;
	Vertex<string> *p;
	vector<Vertex<string>*> vertexss = tempGraph.getVertexSet();

	for (int unsigned i = 0; i < vertexss.size(); i++) {
		cout << "[" << i << "] " << vertexss[i]->getInfo() << " " << vertexss[i]
				<< " size: " << vertexss[i]->adj.size() << "previous: ";
		cout << vertexss[i]->getPrevious() << endl;

	}
	cout << tempGraph.getVertexSet().size() << endl;
	return path;
}

bool FlightAdvisor::checkAirportID(string ID) {
	for (int unsigned i = 0; i < airports.size(); i++)
		if (airports[i].getID() == ID)
			return true;
	return false;
}

void FlightAdvisor::printNetwork() {
	int mapwidth=1458;
	int mapheight=947;
	GraphViewer *gv = new GraphViewer(mapwidth, mapheight, false);
	gv->setBackground("ibericMap.gif");
	gv->createWindow(mapwidth, mapheight);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");


	vector<Vertex<string>* > routes=network.getVertexSet();
	// get the lowest x
	double lowestX=10000000000000;
	double lowestY=10000000000000;
	for(int unsigned i=0; i<routes.size(); i++){
			long double lon= LoadData::getWayPointbyID(routes[i]->getInfo()).getLocalization().getLongitude();
			long double lat= LoadData::getWayPointbyID(routes[i]->getInfo()).getLocalization().getLatitude();
			double x = (180+lon) * (mapwidth / 360.0);
			double y = (90-lat) * (mapheight / 180.0);
			if(x<lowestX) lowestX=x;
			if(y<lowestY) lowestY=y;
	}
	cout << "LowestX: " << lowestX << endl;
	// Create the nodes
	for(int unsigned i=0; i<routes.size(); i++){
		long double lon= LoadData::getWayPointbyID(routes[i]->getInfo()).getLocalization().getLongitude();
		long double lat= LoadData::getWayPointbyID(routes[i]->getInfo()).getLocalization().getLatitude();
		double x = (180+lon) * (mapwidth / 360.0) -lowestX;
		x=11*x+130;
		double y = (90-lat) * (mapheight / 180.0)-lowestY;
		y=11*y+95;
		gv->addNode(i,x,y);
		gv->setVertexLabel(i, routes[i]->getInfo());
		routes[i]->gvNodeID=i;
	}

	// Create the edges
	int unsigned edgeCounter=0;
	for (int unsigned i=0; i<routes.size(); i++){
		for (int unsigned j=0; j<routes[i]->adj.size(); j++){
			gv->addEdge(edgeCounter++,routes[i]->gvNodeID, routes[i]->adj[j].getDest()->gvNodeID, EdgeType::UNDIRECTED);
			stringstream ss;
			ss << routes[i]->adj[j].getWeight() << " km" << endl;
			gv->setEdgeLabel(edgeCounter-1,ss.str());
		}
	}


	sleep(60);
	gv->rearrange();
}
