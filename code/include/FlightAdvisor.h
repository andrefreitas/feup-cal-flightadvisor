#ifndef FLIGHTADVISOR_H_
#define FLIGHTADVISOR_H_

#include "Graph.h"
#include "Waypoint.h"
#include "Airport.h"
#include "LoadData.h"
#include <string.h>
#include <vector>
#include "graphviewer.h"
//! A class for describing a program that chooses the best routes according the source and destination airport.
/*! The network of flight paths is represented as a graph and the decisions are made upon graphs algorithms.
 * Remember that an waypoint is a place in a map that a plane must pass. That waypoint can be an airport or not.
 */
class FlightAdvisor{

	Graph<string> network; //!< The graph network of waypoints
	vector<Airport> airports; //!< The vector of airports
	vector<Waypoint> waypoints; //!< The vector of waypoints (that are not airports)

	string source;	//!< The source airport choosen by the user
	string destination; //!< The destination airport choosen by the user
	int userOption; //!< The option choosen by the user
	vector<vector<string> > routesCalculated; //!< The vector of routes between arbitrary airports

	string networkFileName; //!< The name of the network .csv file
	string airportsFileName; //!< The name of the airports .csv file
	string waypointsFileName; //!< The name of the waypoints .csv file
	GraphViewer *gv ; //!< Pointer to a GraphViewer Window object

	//! Loads all the data
	void loadData();
	//! Prints the wellcome message
	void welcomeMessage();
	//! Receives the user option
	void askOption();
	//! Calculate the routes based on the option and airports given by the user
	void calculateRoutes();
	//! Print the calculated routes in the Standard Output and in the Graphviewer API
	void printRoutes();
	//! Check if the airport ID exists
	/*!
	 * \param ID the airport ID
	 * \return true if valid
	 */
	bool checkAirportID(string ID);

	//! Returns the best route between the source and destination airport
	/*!
	\param source the source airport
	\param destination the destination airport
	*/
	vector<string> getBestRoute(string source, string destination);

	//! Returns the best routes between the source to all others airports
	/*!
		\param source the source airport
		*/
	vector<vector<string> > getBestRoutes(string source);

	//! Returns all the best routes between all airports
	vector<vector<string> > getAllRoutes();

	//! Resets the GraphViewer aspect by removing the red vertexs after presenting a path
	void resetGVAspect();
public:
	//! Constructor
	/*!
		\param networkFileName The name of the network .csv file
		\param airportsFileName The name of the airports .csv file
		\param waypointsFileName The name of the waypoints .csv file
		*/
	FlightAdvisor(string networkFileName,string airportsFileName, string waypointsFileName);

	//! Run the FlightAdvisor in interactive mode (STDOUTPUT)
	void run();

	//! Shows the network in a window with a map
	void showGraphNetwork();

	//! Run the FlightAdvisor in the arg mode. ex: flightadvisor LPPT LPPR
	void runArgsMode(int argc,char *argv[]);
};
//! A class for handling filenames that doesn't exist
class InvalidFileNameException{
	string fileName;
public:
	InvalidFileNameException(string fileName):fileName(fileName){};
	string getFileName(){ return fileName; };
};
#endif /* FLIGHTADVISOR_H_ */
