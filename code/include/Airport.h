#ifndef AIRPORT_H_
#define AIRPORT_H_

#include <string>
#include "Localization.h"
#include "Waypoint.h"
using namespace std;

//! Class Airport
/*! This class defines an Airport with it's basic information
 */
class Airport: public Waypoint {
protected:
	//! The code assigned by International Air Transport Association (IATA)
	string IATA;
	//! The code assigned by International Civil Aviation Organization(ICAO)
	string ICAO;

public:
	//! Constructor
	/*!
	 \param country the country name
	 \param name the know name of the airport
	 \param IATA the IATA code
	 \param ICAO the ICAO code
	 \param localization the gps localization
	 */
	Airport(string country,string name, string IATA, string ICAO, Localization localization);
	//! Constructor
	/*!
	 \param country the country name
	 \param name the know name of the airport
	 \param IATA the IATA code
	 \param ICAO the ICAO code
	 \param localization the gps localization
	 */
	Airport(string country,string name, string IATA, string ICAO, long double lat,
			long double lon);
	//! Empty constructor
	Airport(){};

	//! Get the IATA
	string getIATA();
	//! Get theICAO
	string getICAO();

	//! Set the IATA
	void setIATA(string IATA);
	//! Set the ICAO
	void setICAO(string ICAO);
	//! Set data by vector of strings
	void setByStrings(vector<string> data);

	//! Evaluates if is an airport
	bool isAirport();
	virtual ~Airport(){};

};
//! Invalid IATA exception class
class InvalidIATAException {
public:
	InvalidIATAException(){};
};

//! Invalid ICAO exception class
class InvalidICAOException {
public:
	InvalidICAOException(){};
};

//! Airport Operator << overloading
ostream& operator<<(ostream& os,  Airport& a);

#endif
