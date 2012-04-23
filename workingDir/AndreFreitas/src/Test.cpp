#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"

#include "testAirport.h"
#include "testWaypoint.h"

int main() {
	testAirport::runSuite();
	testWaypoint::runSuite();
	return 0;
}

