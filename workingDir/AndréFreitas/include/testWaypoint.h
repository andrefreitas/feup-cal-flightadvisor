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
		Waypoint a("point1", loc);
		Waypoint b("point2", -3.234322, 1.445);
		Waypoint c;
		c.setID("point3");
		c.setLocalization(-2.2332, 1.3232);
		Waypoint d;
		d.setLocalization(Localization(-4.2222, 3.445));

		// Test all the get methods
		ASSERT_EQUAL(a.getID(), "point1");
		ASSERT_EQUAL_DELTA(-3.2222, a.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(1.445, a.getLocalization().getLongitude(), 0.01);

		ASSERT_EQUAL(b.getID(), "point2");
		ASSERT_EQUAL_DELTA(-3.234322, b.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(1.445, b.getLocalization().getLongitude(), 0.01);

		ASSERT_EQUAL(c.getID(), "point3");
		ASSERT_EQUAL_DELTA(-2.2332, c.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(1.3232, c.getLocalization().getLongitude(), 0.01);

		ASSERT_EQUAL_DELTA(-4.2222, d.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(3.445, d.getLocalization().getLongitude(), 0.01);

	}

	static void runSuite() {
		cute::suite s;
		s.push_back(CUTE(testData));
		cute::ide_listener lis;
		cute::makeRunner(lis)(s, "Test Waypoint");
	}
};

#endif
