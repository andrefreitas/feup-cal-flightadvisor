#include "Waypoint.h"
#include <iostream>
#include <stdlib.h>
Waypoint::Waypoint(string id,string country,  Localization loc){
	this->id=id;
	this->country=country;
	this->localization=loc;
}
Waypoint::Waypoint(string id,string country,  long double lat, long double lon){
	this->id=id;
	this->country=country;
	this->localization=Localization(lat, lon);

}

string Waypoint::getID(){
	return id;
}

string Waypoint::getCountry(){
	return country;
}
Localization Waypoint::getLocalization(){
	return localization;
}

bool Waypoint::isAirport(){
	return false;
}

void Waypoint::setID(string id){
	this->id=id;
}

void Waypoint::setCountry(string country){
	this->country=country;
}

void Waypoint::setLocalization(long double lat, long double lon){
	this->localization=Localization(lat, lon);
}

void Waypoint::setLocalization(Localization loc){
	this->localization=loc;
}

void Waypoint::setByStrings(vector<string> data){
	if (data.size()!=4) throw InvalidStringsSizeException();
	this->id=data[0];
	this->country=data[1];
	this->localization=Localization(atof(data[2].c_str()),atof(data[3].c_str()));


}

ostream& operator<<(ostream& os,  Waypoint& a){
	os << a.getID()  << " " << a.getCountry() << " " << a.getLocalization().getLatitude() << " " << a.getLocalization().getLatitude();
	return os;
}
