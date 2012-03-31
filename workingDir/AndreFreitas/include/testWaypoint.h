#ifndef TESTWAYPOINT_H_
#define TESTWAYPOINT_H_

#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Waypoint.h"

class testWaypoint {
public:
	static void testData() {
		// Create the object with data in 4 ways
		Localization loc(-3.2222, 1.445);
		Waypoint a("point1","Portugal", loc);
		Waypoint b("point2","Portugal", -3.234322, 1.445);
		Waypoint c;
		c.setID("point3");
		c.setLocalization(-2.2332, 1.3232);
		c.setCountry("Portugal");
		Waypoint d;
		d.setLocalization(Localization(-4.2222, 3.445));

		// Test all the get methods
		ASSERT_EQUAL(a.getID(), "point1");
		ASSERT_EQUAL(a.getCountry(), "Portugal");
		ASSERT_EQUAL_DELTA(-3.2222, a.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(1.445, a.getLocalization().getLongitude(), 0.01);

		ASSERT_EQUAL(b.getID(), "point2");
		ASSERT_EQUAL(b.getCountry(), "Portugal");
		ASSERT_EQUAL_DELTA(-3.234322, b.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(1.445, b.getLocalization().getLongitude(), 0.01);

		ASSERT_EQUAL(c.getID(), "point3");
		ASSERT_EQUAL(c.getCountry(), "Portugal");
		ASSERT_EQUAL_DELTA(-2.2332, c.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(1.3232, c.getLocalization().getLongitude(), 0.01);

		ASSERT_EQUAL_DELTA(-4.2222, d.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(3.445, d.getLocalization().getLongitude(), 0.01);

	}

	static void testSetByStrings() {
		Waypoint a;
		vector<string> fileLine;
		fileLine.push_back("PT3");
		fileLine.push_back("Portugal");
		fileLine.push_back("-3.2222");
		fileLine.push_back("1.445");
		a.setByStrings(fileLine);

		// Test all the get methods
		ASSERT_EQUAL(a.getID(), "PT3");
		ASSERT_EQUAL(a.getCountry(), "Portugal");
		ASSERT_EQUAL_DELTA(-3.2222, a.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(1.445, a.getLocalization().getLongitude(), 0.01);

		// Test exceptions
		fileLine.push_back("invalid");
		ASSERT_THROWS(a.setByStrings(fileLine),InvalidStringsSizeException);

	}
	static void testOperators(){
		Waypoint a("point2", "Portugal",-3.234322, 1.445);
		ostringstream aux;
		aux << a;
		ASSERT_EQUAL(aux.str(),"point2 Portugal -3.23432 -3.23432");


	}

	static void testEvaluateWaypoint(){
			Waypoint a("point2", "Portugal",-3.234322, 1.445);
			ASSERT_EQUAL(a.isAirport(),false);
		}

	static void runSuite() {
		cute::suite s;
		s.push_back(CUTE(testData));
		s.push_back(CUTE(testSetByStrings));
		s.push_back(CUTE(testOperators));
		s.push_back(CUTE(testEvaluateWaypoint));
		cute::ide_listener lis;
		cute::makeRunner(lis)(s, "Test Waypoint");
	}
};

#endif
