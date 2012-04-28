#include "testAirport.h"
#include "testWaypoint.h"
#include "FlightAdvisor.h"
using namespace std;

int main(int argc, char *argv[])
{       
	FlightAdvisor a("data/network.csv","data/airports.csv","data/waypoints.csv");
	//a.run();
	a.printNetwork();
    return 0;
    
}
