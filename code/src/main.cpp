#include "testAirport.h"
#include "testWaypoint.h"
#include "FlightAdvisor.h"
using namespace std;

int main(int argc, char *argv[])
{       
	// (1) Create an Flight advisor
	try{
		FlightAdvisor a("data/network.csv","data/airports.csv","data/waypoints.csv");
		if(argc==1) a.run();
		else a.runArgsMode(argc,argv);
	}
	catch (InvalidFileNameException &file){
		cout << "Invalid file name: " << file.getFileName() << endl;
	}

    return 0;
    
}
