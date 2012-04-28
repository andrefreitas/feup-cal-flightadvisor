#include "FlightAdvisor.h"
#include "Graph.h"
#include <stdlib.h>
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
	} while (input.size() != (unsigned int) 1 || (int)validOptions.find(input[0]) ==-1);
	userOption = atoi(input.c_str());

}

void FlightAdvisor::calculateRoutes(){
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
	Graph<string> tempGraph;
	network.clone(tempGraph);
	tempGraph.Dijkstra(source);
}

bool FlightAdvisor::checkAirportID(string ID) {
	for (int unsigned i = 0; i < airports.size(); i++)
		if (airports[i].getID() == ID)
			return true;
	return false;
}

