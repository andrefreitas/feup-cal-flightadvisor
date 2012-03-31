
#ifndef TESTAIRPORT_H_
#define TESTAIRPORT_H_

#include "cute.h"
#include "ide_listener.h"
#include "cute_runner.h"
#include "Airport.h"
#include <string>
#include <vector>
class testAirport{
public:
	static void testData() {
		Airport a("Aeroporto Francisco Sá Carneiro", "Portugal", "OPO", "LPPO",
				Localization(-3.2222, 1.222));
		Airport b("Aeroporto da Portela", "Portugal", "LIS", "LPPT", -4.2222,
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
		ASSERT_THROWS(c.setIATA("DDDDDDDD"),InvalidIATAException);
		ASSERT_THROWS(c.setICAO("DDDDDDDD"),InvalidICAOException);

	}


	static void runSuite() {
		cute::suite s;
		s.push_back(CUTE(testData));
		cute::ide_listener lis;
		cute::makeRunner(lis)(s, "Test Airport");
	}
};


#endif
