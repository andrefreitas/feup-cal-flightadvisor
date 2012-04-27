#include "LoadData.h"
#include "testAirport.h"
#include "testWaypoint.h"
#include "Airport.h"
#include "Waypoint.h"
using namespace std;

int main(int argc, char *argv[])
{       
	testAirport::runSuite();
    testWaypoint::runSuite();

	vector<Waypoint> waypoints=LoadData::loadWaypoints("data/waypoints.csv");
	vector<Airport> airports=LoadData::loadAirports("data/airports.csv");
	LoadData::createGraph();
	for (int unsigned i=0; i<waypoints.size(); i++){
		cout << waypoints[i] << endl;
	}

	for (int unsigned i=0; i<airports.size(); i++){
			cout << airports[i] << endl;
		}
    return 0;
    
}

