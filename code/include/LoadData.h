#ifndef LoadData_h
#define LoadData_h

#include <string.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Graph.h"
#include "Waypoint.h"
#include "Airport.h"
#include <sstream>

using namespace std;
//!
/*! LoadData - A class for loading graph flight routes data from CSV files.
 * It needs a waypoint, airport and network in .csv format. This class is
 * delivered with mostly static methods because is a functional class.
 */
class LoadData {
private:
	static vector<Waypoint> waypoints; //!< The vector of airports
	static vector<Airport> airports; //!< The vector of waypoints (that are not airports)
public:
	//!
	/*! Create a graph from the files data
	 \return a graph of strings
	 */
	static Graph<string> createGraph(string networkFileName,
			string airportsFileName, string waypointsFileName);

	//!
	/*! Reads a CSV file and returns a vector of lines. Each line is a vector of strings.
	 * \param nameFile the file name
	 * \return a vector of string vectors
	 */
	static vector<vector<string> > loadFile(string nameFile);

	//!
	/*! Loads all the waypoints
	 * \param nameFile the file name
	 * \return a vector of Waypoints
	 */
	static vector<Waypoint> loadWaypoints(string nameFile);
	//!
	/*! Loads all the airports
	 * \param nameFile the file name
	 * \return a vector of Waypoints
	 */
	static vector<Airport> loadAirports(string nameFile);

	//!
	/*!
	 * Get the waypoint (including airports) by the id. Remember that if a waypoint is an airport, then the id is the ICAO (i.e. LPPT)
	 * \param id the id
	 * \return an waypoint if exists
	 */
	static Waypoint getWayPointbyID(string id);

};

//!
/*! openFileException - A class for handling file opening exceptions
 */
class openFileException {
public:
	openFileException() {
	}
	;

};
//!
/*! notConnectedGraphException - A class that is thrown when a not connected graph is created
 */
class notConnectedGraphException {
	string waypoint;
public:
	notConnectedGraphException(string waypoint) {
		this->waypoint = waypoint;
	}
	string getWaypointWithoutEdges() {
		return waypoint;
	}
};
//!
/*! InvalidEdgeException - A class that is thrown when an invalid edge is created
 */
class InvalidEdgeException{
	string source;
	string destination;
public:
	InvalidEdgeException(string source, string destination):source(source),destination(destination){};
	string getEdge(){
		stringstream ss;
		ss << source << " => " << destination << endl;
		return ss.str();
	}
};
#endif
