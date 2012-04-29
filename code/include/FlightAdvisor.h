#ifndef FLIGHTADVISOR_H_
#define FLIGHTADVISOR_H_

#include "Graph.h"
#include "Waypoint.h"
#include "Airport.h"
#include "LoadData.h"
#include <string.h>
#include <vector>
#include "graphviewer.h"
//! Class FlightAdvisor
/*! A class for describing a program that chooses the best routes according the source and destination airport.
 * The network of flight paths is represented as a graph and the decisions are made upon graphs algorithms.
 */
class FlightAdvisor{
	// Data
	Graph<string> network;
	vector<Airport> airports;
	vector<Waypoint> waypoints;

	// User Information
	string source;
	string destination;
	int userOption;
	vector<vector<string> > routesCalculated;

	// Files .csv with data
	string networkFileName;
	string airportsFileName;
	string waypointsFileName;

	// Main Functions
	void loadData();
	void welcomeMessage();
	void askOption();
	void calculateRoutes();
	void printRoutes();
	bool checkAirportID(string ID);

	// Routing functions
	vector<string> getBestRoute(string source, string destination);
	vector<vector<string> > getBestRoutes(string source);
	vector<vector<string> > getAllRoutes();

	// Graphviewer
	GraphViewer *gv ;
	void resetGVAspect();
public:
	FlightAdvisor(string networkFileName,string airportsFileName, string waypointsFileName);
	void run();
	void printNetwork();
	void runArgsMode(int argc,char *argv[]);
};


#endif /* FLIGHTADVISOR_H_ */
