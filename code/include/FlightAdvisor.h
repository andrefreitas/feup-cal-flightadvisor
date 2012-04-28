#ifndef FLIGHTADVISOR_H_
#define FLIGHTADVISOR_H_

#include "Graph.h"
#include "Waypoint.h"
#include "Airport.h"
#include "LoadData.h"
#include <string.h>
#include <vector>
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
	Airport source;
	Airport destination;
	int userOption;

	// Files .csv with data
	string networkFileName;
	string airportsFileName;
	string waypointsFileName;

	// Main Functions
	void loadData();
	void welcomeMessage();
	void askOption();
	void printRoutes();
public:
	FlightAdvisor(string networkFileName,string airportsFileName, string waypointsFileName);
	void run();
};


#endif /* FLIGHTADVISOR_H_ */
