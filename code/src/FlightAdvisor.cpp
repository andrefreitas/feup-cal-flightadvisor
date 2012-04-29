#include "FlightAdvisor.h"
#include "Graph.h"
#include <stdlib.h>

#include <sstream>
#include <cctype>
string toString(char *s){
	stringstream ss;
	for(int unsigned i=0; *(s+i)!='\0';i++){
		ss << *(s+i );
	}
	return ss.str();
}
void toUpperString(string &s){
	for(int unsigned i=0; i<s.size();i++){
		s[i]=toupper(s[i]);
	}
}
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
			toUpperString(source);
		} while (!checkAirportID(source));
	}
	if (userOption == 1) {
		do {
			cout << "Destination: ";
			getline(cin, destination);
			toUpperString(destination);
		} while (!checkAirportID(destination));
	}
	if(userOption==0) exit(0);

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

	// Standard output
	for (int unsigned i = 0; i < routesCalculated.size(); i++) {

		for (int unsigned j = 0; j < routesCalculated[i].size(); j++) {
			cout << routesCalculated[i][j];
			if (j != (routesCalculated[i].size() - 1))
				cout << " ";
		}
		cout << "\n\n";
	}

	// GraphViewer
	if(userOption==1){
		resetGVAspect();
		int unsigned i;
		for (i=0; i<routesCalculated[0].size(); i++) gv->setVertexColor(network.getVertex(routesCalculated[0][i])->gvNodeID,"green");
		gv->setVertexColor(network.getVertex(routesCalculated[0][0])->gvNodeID,"red");
		gv->setVertexColor(network.getVertex(routesCalculated[0][i-1])->gvNodeID,"red");
		gv->rearrange();
	}

}

void FlightAdvisor::resetGVAspect(){
	vector<Vertex<string> *> vertexs=network.getVertexSet();
	for(int unsigned i=0; i<vertexs.size(); i++){
		gv->setVertexColor(vertexs[i]->gvNodeID,"blue");
	}


}

vector<string> FlightAdvisor::getBestRoute(string source, string destination) {
	// (1) choose the best algorithm
	Graph<string> tempGraph;
	network.clone(tempGraph);
	if (tempGraph.havePathsWithSameSize(source, destination)) {
		/*if (userOption == 1)
			cout << "\nUsed best path by distance" << endl; */
		tempGraph.Dijkstra(source);
	} else {
		tempGraph.unweightedShortestPath(source);
		/*if (userOption == 1)
			cout << "\nUsed best path by number of nodes" << endl; */
	};

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
	cout << "This is going to take a while, please wait...\n";
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
	gv = new GraphViewer(mapwidth, mapheight, false);
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
	// (4) Create the nodesroutesCalculated.push_back(getBestRoute(source, destination));
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
			// Retain information for further handling
			vector<int> pairNodeIDs;
			pairNodeIDs.push_back(edgeCounter+1);
			pairNodeIDs.push_back(routes[i]->gvNodeID);
			pairNodeIDs.push_back(routes[i]->adj[j].getDest()->gvNodeID);
			edgesIDs.push_back(pairNodeIDs);
			// Create the edge
			gv->addEdge(edgeCounter++, routes[i]->gvNodeID,
					routes[i]->adj[j].getDest()->gvNodeID,
					EdgeType::UNDIRECTED);
			stringstream ss;
			ss << routes[i]->adj[j].getWeight() << " km" << endl;
			gv->setEdgeLabel(edgeCounter - 1, ss.str());
		}
	}

}

int FlightAdvisor::getGVEdgeID(int node1ID, int node2ID){
	for (int unsigned i=0; i<edgesIDs.size(); i++){
		if(((edgesIDs[i][1]==node1ID) & (edgesIDs[i][2]==node2ID)) || ((edgesIDs[i][2]==node1ID) & (edgesIDs[i][1]==node2ID))) return edgesIDs[i][0];
	}
	return -1;
}

void FlightAdvisor::runArgsMode(int argc,char *argv[]){
	// Only source
	if(argc==2){
		userOption=2;
		source=toString(argv[1]);
		toUpperString(source);
		if(!checkAirportID(source)){
			cout << "Invalid source \"" << source <<"\"\n";
			exit(1);
		}
		routesCalculated = getBestRoutes(source);
	}
	// Source and Destination
	else if(argc==3){
		userOption=1;
		source=toString(argv[1]);
		toUpperString(source);
		if(!checkAirportID(source)){
			cout << "Invalid source \"" << source <<"\"\n";
			exit(1);
		}
		destination=toString(argv[2]);
		toUpperString(destination);
		if(!checkAirportID(destination)){
			cout << "Invalid destination\"" << destination <<"\"\n";
			exit(1);
		}
		routesCalculated.push_back(getBestRoute(source, destination));
	}
	printRoutes();

}
