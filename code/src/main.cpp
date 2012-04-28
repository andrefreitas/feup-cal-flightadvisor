#include "LoadData.h"
#include "testAirport.h"
#include "testWaypoint.h"
#include "Airport.h"
#include "Waypoint.h"
#include "FlightAdvisor.h"
using namespace std;

int main(int argc, char *argv[])
{       

	FlightAdvisor a("data/network.csv","data/airports.csv","data/waypoints.csv");
	//a.run();
    return 0;
    
}

