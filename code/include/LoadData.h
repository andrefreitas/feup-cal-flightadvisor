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

using namespace std;
/**
 * LoadData - A class for loading graph flight routes data from CSV files.
 */
class LoadData {
private:
	static vector<Waypoint> waypoints; // note that an waypoint can be an airport, but here is only the pure waypoints
	static vector<Airport> airports;
public:
    /**
     * Create a graph from the files data
     * @return a graph of strings
     */
    static Graph<string> createGraph(string networkFileName,string airportsFileName, string waypointsFileName);
     /**
     * Reads a CSV file and returns a vector of lines. Each line is a vector of strings.
     * @param nameFile the file name
     * @return a vector of string vectors
     */
    static vector< vector<string> > loadFile(string nameFile);
    /**
     * Loads all the waypoints
     */
    static vector<Waypoint> loadWaypoints(string nameFile);
    /**
     * Loads all the airports
     */
    static vector<Airport> loadAirports(string nameFile);
    /**
     * Get the waypoint (including airports) by the id. Remember that if a waypoint is an airport, then the id is the ICAO (i.e. LPPT)
     */
    static Waypoint getWayPointbyID(string id);

};

/**
 * openFileException - A class for handling file opening exceptions
 */
class openFileException {
public:
    openFileException(){};

};

#endif
