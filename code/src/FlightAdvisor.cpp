#include "FlightAdvisor.h"
#include "Graph.h"
#include <stdlib.h>
#include <sstream>
#include <cctype>

// Some auxiliar functions
string toString(char *s) {
	stringstream ss;
	for (int unsigned i = 0; *(s + i) != '\0'; i++) {
		ss << *(s + i);
	}
	return ss.str();
}
void toUpperString(string &s) {
	for (int unsigned i = 0; i < s.size(); i++) {
		s[i] = toupper(s[i]);
	}
}
bool fileExists(string filename)
{
  ifstream ifile(filename.c_str());
  return ifile;
}
// Methods definition
FlightAdvisor::FlightAdvisor(string networkFileName, string airportsFileName,
		string waypointsFileName) {
	// Save the file names
	if (!fileExists(networkFileName)) throw InvalidFileNameException(networkFileName);
	this->networkFileName = networkFileName;
	if (!fileExists(airportsFileName)) throw InvalidFileNameException( airportsFileName);
	this->airportsFileName = airportsFileName;
	if (!fileExists(waypointsFileName)) throw InvalidFileNameException(waypointsFileName);
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
	catch(InvalidEdgeException &e){
		cout << "The network have an invalid edge: " << e.getEdge() << endl;
		exit(1);
	}
}
void FlightAdvisor::run() {
	welcomeMessage();
	showGraphNetwork();
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
	// (1) Show the menu
	cout << "Choose the best option for you:\n";
	cout << "1- Give source and destination airport\n";
	cout << "2- Give source airport and know all the routes\n";
	cout << "3- Know all the best routes\n";
	cout << "0- EXIT\n";

	// (2) Get the option
	string input;
	string validOptions = "1230";
	do {
		cout << "> ";
		getline(cin, input);
	} while (input.size() != (unsigned int) 1
			|| (int) validOptions.find(input[0]) == -1);
	userOption = atoi(input.c_str());

	// (3) Handle that option
	if ((userOption == 2) | (userOption == 1)) {
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
	// Exit
	if (userOption == 0)
		exit(0);

}

void FlightAdvisor::calculateRoutes() {
	// (1) Clear previous routes
	routesCalculated.clear();
	// (2) Select the right function
	if (userOption == 1)
		routesCalculated.push_back(getBestRoute(source, destination));
	else if (userOption == 2)
		routesCalculated = getBestRoutes(source);
	else
		routesCalculated = getAllRoutes();

}

void FlightAdvisor::printRoutes() {
	// (1) Standard output
	for (int unsigned i = 0; i < routesCalculated.size(); i++){
		for (int unsigned j = 0; j < routesCalculated[i].size(); j++)
			cout << routesCalculated[i][j] << " ";
		cout << endl;
	}
	cout << "\n\n";

	// (2) Update the graphViewer (only if source and destination is given
	if (userOption == 1) {
		resetGVAspect();
		int unsigned i;
		// Put all the nodes in the path green
		for (i = 0; i < routesCalculated[0].size(); i++)
			gv->setVertexColor(
					network.getVertex(routesCalculated[0][i])->gvNodeID,
					"green");
		// Put the source airport red
		gv->setVertexColor(network.getVertex(routesCalculated[0][0])->gvNodeID,
				"red");
		// Put the destination airport red
		gv->setVertexColor(
				network.getVertex(routesCalculated[0][i - 1])->gvNodeID, "red");
		gv->rearrange();
	}

}

void FlightAdvisor::resetGVAspect() {
	vector<Vertex<string> *> vertexs = network.getVertexSet();
	for (int unsigned i = 0; i < vertexs.size(); i++)
		gv->setVertexColor(vertexs[i]->gvNodeID, "blue");

}

vector<string> FlightAdvisor::getBestRoute(string source, string destination) {
	// (1) Create a cloned temporary Graph
	Graph<string> tempGraph;
	network.clone(tempGraph);

	// (2) Choose the best algorithm to find the shortest path
	// Description: If the source and destination airport have more than one best path (unweighted) choose Dijkstra
	if (tempGraph.havePathsWithSameSize(source, destination))
		tempGraph.Dijkstra(source);
	else
		tempGraph.unweightedShortestPath(source);

	// (2) Retrieve the path
	vector<string> path;
	Vertex<string> *p = tempGraph.getVertex(destination);
	while (p->getInfo() != source) {
		path.insert(path.begin(), p->getInfo());
		p = p->path;
	}
	path.insert(path.begin(), source);

	// (3) Return the path
	return path;
}
vector<vector<string> > FlightAdvisor::getBestRoutes(string source) {
	vector<vector<string> > routes;
	for (int unsigned i = 0; i < airports.size(); i++)
		if (airports[i].getID() != source)
			routes.push_back(getBestRoute(source, airports[i].getID()));

	return routes;

}

vector<vector<string> > FlightAdvisor::getAllRoutes() {
	cout << "This is going to take a while, please wait...\n";
	vector<vector<string> > routes;
	for (int unsigned i = 0; i < airports.size(); i++) {
		vector<vector<string> > aux = getBestRoutes(airports[i].getID());
		for (int unsigned j = 0; j < aux.size(); j++)
			routes.push_back(aux[j]);
	}
	return routes;
}
bool FlightAdvisor::checkAirportID(string ID) {
	for (int unsigned i = 0; i < airports.size(); i++)
		if (airports[i].getID() == ID)
			return true;
	return false;
}

void FlightAdvisor::showGraphNetwork() {
	// (1) Setup the Window
	int mapwidth = 1458;
	int mapheight = 947;
	gv = new GraphViewer(mapwidth, mapheight, false);
	gv->setBackground("data/ibericMapFA.gif");
	gv->createWindow(mapwidth - 400, mapheight);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	// (2) Get the network of waypoints
	vector<Vertex<string>*> routes = network.getVertexSet();

	// (3) Get the lowest x and y for adjusting the graph in the map
	// Uncomment if you will change the map image
	/*double lowestX = 10000000000000;
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
	} */

	// calculated values used the previous code
	double fixedLowestXforEuropeMap = 692.003;
	double fixedLowestYforEuropeMap = 207.481;

	// (4) Create the nodes in the graph
	for (int unsigned i = 0; i < routes.size(); i++) {
		// Calculate x and y axis position
		long double lon =
				LoadData::getWayPointbyID(routes[i]->getInfo()).getLocalization().getLongitude();
		long double lat =
				LoadData::getWayPointbyID(routes[i]->getInfo()).getLocalization().getLatitude();
		double x = (180 + lon) * (mapwidth / 360.0) - fixedLowestXforEuropeMap;
		x = 11 * x + 130; // adjustments
		double y = (90 - lat) * (mapheight / 180.0) - fixedLowestYforEuropeMap;
		y = 11 * y + 95; // adjustments
		// Create the node
		gv->addNode(i, x, y);
		gv->setVertexLabel(i, routes[i]->getInfo());
		routes[i]->gvNodeID = i;
	}

	// (5) Create the edges
	int unsigned edgeCounter = 0;
	for (int unsigned i = 0; i < routes.size(); i++) {
		for (int unsigned j = 0; j < routes[i]->adj.size(); j++) {
			// Create the edge
			gv->addEdge(edgeCounter++, routes[i]->gvNodeID,
					routes[i]->adj[j].getDest()->gvNodeID,
					EdgeType::UNDIRECTED);
			// Ad the label of distance
			stringstream ss;
			ss << routes[i]->adj[j].getWeight() << " km" << endl;
			gv->setEdgeLabel(edgeCounter - 1, ss.str());
		}
	}

}

void FlightAdvisor::runArgsMode(int argc, char *argv[]) {

	// (1) Show the network int the graph viewer
	showGraphNetwork();

	// (2) Only source airport
	if (argc == 2) {
		// (a) Retrieve the source name
		userOption = 2;
		source = toString(argv[1]);
		toUpperString(source);
		if (!checkAirportID(source)) {
			cout << "Invalid source \"" << source << "\"\n";
			exit(1);
		}
		// (b) Calculate the routes
		routesCalculated = getBestRoutes(source);
	}
	// (3) Source and Destination Airport
	else if (argc == 3) {
		// (a) Retrieve the source name
		userOption = 1;
		source = toString(argv[1]);
		toUpperString(source);
		if (!checkAirportID(source)) {
			cout << "Invalid source \"" << source << "\"\n";
			exit(1);
		}
		// (b) Retrieve the destination name
		destination = toString(argv[2]);
		toUpperString(destination);
		if (!checkAirportID(destination)) {
			cout << "Invalid destination\"" << destination << "\"\n";
			exit(1);
		}

		// (c) Calculate the route
		routesCalculated.push_back(getBestRoute(source, destination));
	}

	// (4) print the routes
	printRoutes();
	sleep(30); // need to wait

}
