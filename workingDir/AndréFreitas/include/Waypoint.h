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
	//! The latitude and longitude of the waypoint
	Localization localization;

public:
	//! Constructor
	/*!
	 \param id the identification
	 \param loc the the gps localization
	 */
	Waypoint(string id, Localization loc);

	//! Constructor
	/*!
	 \param id the identification
	 \param lat the latitude
	 \param lon the longitude
	 */
	Waypoint(string id, long double lat, long double lon);

	//! Empty constructor
	Waypoint(){};

	//! Get the identification
	string getID();
	//! Get the localization
	Localization getLocalization();

	//! Set the identification
	void setID(string id);
	//! Set the localization with explicit values
	void setLocalization(long double lat, long double lon);
	//! Set the localization
	void setLocalization(Localization loc);

	//! Return if is an airport
	virtual bool isAirport();

	/* Virtual Functions for sub-class airport
	virtual string getName() const=0;
	virtual string getCountry() const=0;
	virtual string getIATA() const=0;
	virtual string getICAO() const=0;
	virtual void setName(string name) const=0 ;
	virtual void setCountry(string country) const=0;
	virtual void setIATA(string iata) const=0;
	virtual void setICAO(string icao) const=0 ; */


};

#endif
