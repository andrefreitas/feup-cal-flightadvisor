#ifndef WAYPOINT_H_
#define WAYPOINT_H_

#include <string>
#include "Localization.h"
using namespace std;

//! Class Waypoint
/*!
 * A waypoint is a determinaded spot in a route that a plane must pass,
 * between an airport A and B. Note that the source and destination airports
 * are waypoints, so the airport is a sub-class of waypoint.
 */
class Waypoint {
protected:

	//! The identification name of the waypoint
	string id;
	//! Country name
	string country;
	//! The latitude and longitude of the waypoint
	Localization localization;

public:
	//! Constructor
	/*!
	 \param id the identification
	 \param country the country name
	 \param loc the the gps localization
	 */
	Waypoint(string id, string country, Localization loc);

	//! Constructor
	/*!
	 \param id the identification
	 \param country the country name
	 \param lat the latitude
	 \param lon the longitude
	 */
	Waypoint(string id, string country,long double lat, long double lon);

	//! Empty constructor
	Waypoint(){};

	//! Get the identification
	string getID();
	//! Get the country
	string getCountry();
	//! Get the localization
	Localization getLocalization();

	//! Set the identification
	void setID(string id);
	//! Set the country
	void setCountry(string country);
	//! Set the localization with explicit values
	void setLocalization(long double lat, long double lon);
	//! Set the localization
	void setLocalization(Localization loc);

	//! Return if is an airport
	virtual bool isAirport();

	//! Set data by vector of strings
	virtual void setByStrings(vector<string> data);

	//Virtual Functions for sub-class airport
	virtual string getName(){
		return "this is a Waypoint";
	}
	virtual string getIATA(){
		return "this is a Waypoint";
	}
	virtual string getICAO(){
		return "this is a Waypoint";
	}
	virtual void setName(string name){}
	virtual void setIATA(string iata){}
	virtual void setICAO(string icao){}


};

//! Invalid Strings size exception class
class InvalidStringsSizeException {
public:
	InvalidStringsSizeException(){};
};
//! Operator << overloading
ostream& operator<<(ostream& os,  Waypoint& a);
#endif
