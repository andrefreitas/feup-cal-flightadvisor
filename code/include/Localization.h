#ifndef LOCALIZATION_H_
#define LOCALIZATION_H_

#include "math.h"
#include <vector>
#include <iostream>
using namespace std;

//! Class Localization
/*! This classe defines a position in earth by latitude and longitude
*/
class Localization{
	//! The latitude relative to Equator
	long double latitude;
	//! The longitude relative to Greenwich
	long double longitude;
public:
	// Get methods
	//! Returns the latitude
	long double getLatitude(){return latitude;};
	//! Returns the longitude
	long double getLongitude(){return longitude;};
	//! Empty constructor
	Localization(){};
	//!Constructor
	Localization(long double la, long double lo):latitude(la),longitude(lo){
	};
	//! Convert degrees to rads
	static long double toRads(long double x){
			return (x/180.0)*acos(-1);
		}
	//! Calculate the distance between 2 positions with Haversine formula
	/*!
	 \param a first localization
	 \param b second localization
	 \return the distance between a and b in kilometers
	 */
	static double distance(const Localization &a, const Localization &b){
		long double rTerra=6371.0;
		long double dLat= toRads(a.latitude-b.latitude);
		long double dLon= toRads(a.longitude-b.longitude);
		long double lat1=toRads(a.latitude);
		long double lat2=toRads(b.latitude);
		long double a1=sin(dLat/2.0) * sin(dLat/2.0) + sin(dLon/2.0) * sin(dLon/2.0) * cos(lat1) * cos(lat2);
		long double c=2.0 * atan2(sqrt(a1), sqrt(1-a1));
		return c*rTerra;
	}
	//! Returns a reference to the object nearest to target. Must define .getLocalization()!!
	/*!
	 \param t the target object
	 \param objects the objects relative to the target
	 */
	template<class target,class obj>
	static obj *nearest( target &t, vector<obj> &objects){
		obj *nearest=&objects[0];
		for (int unsigned i=0; i<objects.size(); i++)
			if (distance(t.getLocalization(),objects[i].getLocalization())< distance(t.getLocalization(),nearest->getLocalization()))
				nearest=&objects[i];
		return nearest;
	}
	//! Convert degree to radians
	/*!
	 \param x the degree value
	 */
};

#endif /* LOCALIZATION_H_ */
