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
	//! The human friendly name of the airport
	string name;
	//! The code assigned by International Air Transport Association (IATA)
	string IATA;
	//! The code assigned by International Civil Aviation Organization(ICAO)
	string ICAO;

public:
	//! Constructor
	/*!
	 \param name the know name of the airport
	 \param IATA the IATA code
	 \param ICAO the ICAO code
	 \param localization the gps localization
	 */
	Airport(string name,string country, string IATA, string ICAO, Localization localization);
	//! Constructor
	/*!
	 \param name the know name of the airport
	 \param IATA the IATA code
	 \param ICAO the ICAO code
	 \param localization the gps localization
	 */
	Airport(string name,string country, string IATA, string ICAO, long double lat,
			long double lon);
	//! Empty constructor
	Airport(){};

	//! Get the name
	string getName();
	//! Get the IATA
	string getIATA();
	//! Get theICAO
	string getICAO();

	//! Set the name
	void setName(string name);
	//! Set the IATA
	void setIATA(string IATA);
	//! Set the ICAO
	void setICAO(string ICAO);
	//! Set data by vector of strings
	void setByStrings(vector<string> data);

	//! Evaluates if is an airport
	bool isAirport();


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
