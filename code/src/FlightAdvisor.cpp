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
	try {
		network = LoadData::createGraph(networkFileName, airportsFileName,
				waypointsFileName);
	} catch (notConnectedGraphException &e) {
		cout << "The network is not connected! The waypoint "
				<< e.getWaypointWithoutEdges() << " don't have edges!" << endl;
		exit(1);
	}
}
void FlightAdvisor::run() {
	welcomeMessage();
	printNetwork();
	do {
		askOption();
		calculateRoutes();
		printRoutes();
		;
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
	if ((userOption == 2) | (userOption==1)) {
		do {
			cout << "Source: ";
			getline(cin, source);
		} while (!checkAirportID(source));
	}
	if (userOption == 1) {
		do {
			cout << "Destination: ";
			getline(cin, destination);
		} while (!checkAirportID(destination));
	}

}

void FlightAdvisor::calculateRoutes() {
	routesCalculated.clear();
	if (userOption == 1)
		routesCalculated.push_back(getBestRoute(source, destination));
	else if (userOption == 2)
		routesCalculated = getBestRoutes(source);
	else{
		routesCalculated = getAllRoutes();
	}

}

void FlightAdvisor::printRoutes() {
	cout << "\nBest Path";
	if (routesCalculated.size() > 1)
		cout << "s";
	cout << ":\n";
	for (int unsigned i = 0; i < routesCalculated.size(); i++) {

		for (int unsigned j = 0; j < routesCalculated[i].size(); j++) {
			cout << routesCalculated[i][j];
			if (j != (routesCalculated[i].size() - 1))
				cout << " -> ";
		}
		cout << "\n\n";
	}

}

vector<string> FlightAdvisor::getBestRoute(string source, string destination) {
	// (1) use the dijkstra
	Graph<string> tempGraph;
	network.clone(tempGraph);
	if (tempGraph.havePathsWithSameSize(source, destination)) {
		if (userOption == 1)
			cout << "\nUsed best path by distance" << endl;
		tempGraph.Dijkstra(source);
	} else {
		tempGraph.unweightedShortestPath(source);
		if (userOption == 1)
			cout << "\nUsed best path by number of nodes" << endl;
	}

	// (2) build the path
	vector<string> path;
	Vertex<string> *p = tempGraph.getVertex(destination);
	while (p->getInfo() != source) {
		path.insert(path.begin(), p->getInfo());
		p = p->path;
	}
	path.insert(path.begin(), source);
	return path;
}
vector<vector<string> > FlightAdvisor::getBestRoutes(string source) {
	vector<vector<string> > routes;
	for (int unsigned i = 0; i < airports.size(); i++) {
		if (airports[i].getID() != source)
			routes.push_back(getBestRoute(source, airports[i].getID()));
	}
	return routes;

}

vector<vector<string> > FlightAdvisor::getAllRoutes() {
	vector<vector<string> > routes;
	for (int unsigned i = 0; i < airports.size(); i++) {
		vector<vector<string> > aux= getBestRoutes(airports[i].getID());
		for (int unsigned j=0; j<aux.size(); j++){
			routes.push_back(aux[j]);
		}

	}
	return routes;
}
bool FlightAdvisor::checkAirportID(string ID) {
	for (int unsigned i = 0; i < airports.size(); i++)
		if (airports[i].getID() == ID)
			return true;
	return false;
}

void FlightAdvisor::printNetwork() {
	// (1) Setup the Window
	int mapwidth = 1458;
	int mapheight = 947;
	GraphViewer *gv = new GraphViewer(mapwidth, mapheight, false);
	gv->setBackground("data/ibericMap.gif");
	gv->createWindow(mapwidth - 400, mapheight);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	// (2) Get the network of waypoints
	vector<Vertex<string>*> routes = network.getVertexSet();

	// (3) Get the lowest x and y for adjusting the graph in the map
	double lowestX = 10000000000000;
	double lowestY = 10000000000000;
	for (int unsigned i = 0; i < routes.size(); i++) {
		long double lon =
				LoadData::getWayPointbyID(routes[i]->getInfo()).getLocalization().getLongitude();
		long double lat =
				LoadData::getWayPointbyID(routes[i]->getInfo()).getLocalization().getLatitude();
		double x = (180 + lon) * (mapwidth / 360.0);
		double y = (90 - lat) * (mapheight / 180.0);
		if (x < lowestX)
			lowestX = x;
		if (y < lowestY)
			lowestY = y;
	}

	//cout << "x:" << lowestX << "y: " << lowestY << endl;
	double fixedLowestXforEuropeMap = 692.003;
	double fixedLowestYforEuropeMap = 207.481;
	// (4) Create the nodes
	for (int unsigned i = 0; i < routes.size(); i++) {
		// Calculate x and y axis position
		long double lon =
				LoadData::getWayPointbyID(routes[i]->getInfo()).getLocalization().getLongitude();
		long double lat =
				LoadData::getWayPointbyID(routes[i]->getInfo()).getLocalization().getLatitude();
		double x = (180 + lon) * (mapwidth / 360.0) - fixedLowestXforEuropeMap;
		x = 11 * x + 130;
		double y = (90 - lat) * (mapheight / 180.0) - fixedLowestYforEuropeMap;
		y = 11 * y + 95;
		// Create the node
		gv->addNode(i, x, y);
		gv->setVertexLabel(i, routes[i]->getInfo());
		routes[i]->gvNodeID = i;
	}

	// (5) Create the edges
	int unsigned edgeCounter = 0;
	for (int unsigned i = 0; i < routes.size(); i++) {
		for (int unsigned j = 0; j < routes[i]->adj.size(); j++) {
			gv->addEdge(edgeCounter++, routes[i]->gvNodeID,
					routes[i]->adj[j].getDest()->gvNodeID,
					EdgeType::UNDIRECTED);
			stringstream ss;
			ss << routes[i]->adj[j].getWeight() << " km" << endl;
			gv->setEdgeLabel(edgeCounter - 1, ss.str());
		}
	}

}
