#ifndef TESTAIRPORT_H_
#define TESTAIRPORT_H_

#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Airport.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
//! A class for testing the class Airport
class testAirport {
public:
	static void testData() {
		Airport a("Portugal","Aeroporto Francisco Sá Carneiro", "OPO", "LPPO",
				Localization(-3.2222, 1.222));
		Airport b( "Portugal","Aeroporto da Portela", "LIS", "LPPT", -4.2222,
				6.222);
		Airport c;

		// Test airport A gets
		ASSERT_EQUAL(a.getName(), "Aeroporto Francisco Sá Carneiro");
		ASSERT_EQUAL(a.getCountry(), "Portugal");
		ASSERT_EQUAL(a.getIATA(), "OPO");
		ASSERT_EQUAL(a.getICAO(), "LPPO");
		ASSERT_EQUAL(a.getID(), "LPPO");
		ASSERT_EQUAL_DELTA(-3.2222, a.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(1.222, a.getLocalization().getLongitude(), 0.01);

		// Test airport B gets
		ASSERT_EQUAL(b.getName(), "Aeroporto da Portela");
		ASSERT_EQUAL(b.getCountry(), "Portugal");
		ASSERT_EQUAL(b.getIATA(), "LIS");
		ASSERT_EQUAL(b.getICAO(), "LPPT");
		ASSERT_EQUAL(b.getID(), "LPPT");
		ASSERT_EQUAL_DELTA(-4.2222, b.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(6.2222, b.getLocalization().getLongitude(), 0.01);

		// Test airport C gets
		c.setName("Aeroporto da Madeira");
		c.setCountry("Portugal");
		c.setIATA("FNC");
		c.setICAO("LPMA");
		c.setLocalization(-8.11212, 1.122221);
		ASSERT_EQUAL(c.getName(), "Aeroporto da Madeira");
		ASSERT_EQUAL(c.getCountry(), "Portugal");
		ASSERT_EQUAL(c.getIATA(), "FNC");
		ASSERT_EQUAL(c.getICAO(), "LPMA");
		ASSERT_EQUAL(c.getID(), "LPMA");
		ASSERT_EQUAL_DELTA(-8.11212, c.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(1.122221, c.getLocalization().getLongitude(), 0.01);
		c.setLocalization(Localization(16.1212, 43.122221));
		ASSERT_EQUAL_DELTA(16.1212, c.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(43.122221, c.getLocalization().getLongitude(), 0.01);

		// Test exceptions of invalid IATA and invalid ICAO
		ASSERT_THROWS(c.setIATA("DDDDDDDD"), InvalidIATAException);
		ASSERT_THROWS(c.setICAO("DDDDDDDD"), InvalidICAOException);

	}
	static void testDataWithStrings() {
		Airport a;
		vector<string> fileLine;
		fileLine.push_back("Portugal");
		fileLine.push_back("Aeroporto da Madeira");
		fileLine.push_back("FNC");
		fileLine.push_back("LPMA");
		fileLine.push_back("-8.11212");
		fileLine.push_back("1.122221");
		a.setByStrings(fileLine);

		// Test if setByStringsWorked
		ASSERT_EQUAL(a.getName(), "Aeroporto da Madeira");
		ASSERT_EQUAL(a.getCountry(), "Portugal");
		ASSERT_EQUAL(a.getIATA(), "FNC");
		ASSERT_EQUAL(a.getICAO(), "LPMA");
		ASSERT_EQUAL(a.getID(), "LPMA");
		ASSERT_EQUAL_DELTA(-8.11212, a.getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(1.122221, a.getLocalization().getLongitude(), 0.01);

		// Test invalid IATA exception

		vector<string> fileLine2;
		fileLine2.push_back("Portugal");
		fileLine2.push_back("Aeroporto da Madeira");
		fileLine2.push_back("FNCCCCCC"); // <- wrong IATA
		fileLine2.push_back("LPMA");
		fileLine2.push_back("-8.11212");
		fileLine2.push_back("1.122221");
		ASSERT_THROWS(a.setByStrings(fileLine2), InvalidIATAException);

		// Test invalid ICAO exception

		vector<string> fileLine3;
		fileLine3.push_back("Portugal");
		fileLine3.push_back("Aeroporto da Madeira");
		fileLine3.push_back("FNC");
		fileLine3.push_back("LPM"); // <- wrong ICAO
		fileLine3.push_back("-8.11212");
		fileLine3.push_back("1.122221");
		ASSERT_THROWS(a.setByStrings(fileLine3), InvalidICAOException);

		// Test invalid StringSize exception

		vector<string> fileLine4;
		fileLine4.push_back("Portugal");
		ASSERT_THROWS(a.setByStrings(fileLine4), InvalidStringsSizeException);

	}
	static void testOperators() {
		Airport a("Portugal","Aeroporto Francisco Sá Carneiro", "OPO", "LPPO",
				Localization(-3.2222, 1.222));
		ostringstream aux;
		aux << a;
		ASSERT_EQUAL(aux.str(),
				"Portugal Aeroporto Francisco Sá Carneiro OPO LPPO -3.2222 1.222");
	}

	static void testWaypointContext() {
		Waypoint *p = new Airport( "Portugal","Aeroporto Francisco Sá Carneiro",
				"OPO", "LPPO", Localization(-3.2222, 1.222));

		ASSERT_EQUAL(p->getName(), "Aeroporto Francisco Sá Carneiro");
		ASSERT_EQUAL(p->getCountry(), "Portugal");
		ASSERT_EQUAL(p->getIATA(), "OPO");
		ASSERT_EQUAL(p->getICAO(), "LPPO");
		ASSERT_EQUAL(p->getID(), "LPPO");
		ASSERT_EQUAL_DELTA(-3.2222, p->getLocalization().getLatitude(), 0.01);
		ASSERT_EQUAL_DELTA(1.222, p->getLocalization().getLongitude(), 0.01);
		ASSERT_EQUAL(p->isAirport(),true);


	}
	static void runSuite() {
		cute::suite s;
		s.push_back(CUTE(testData));
		s.push_back(CUTE(testDataWithStrings));
		s.push_back(CUTE(testOperators));
		s.push_back(CUTE(testWaypointContext));
		cute::ide_listener lis;
		cute::makeRunner(lis)(s, "Test Airport");
	}
};

#endif
