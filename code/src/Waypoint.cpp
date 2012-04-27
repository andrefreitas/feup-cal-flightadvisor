#include "Waypoint.h"
#include <iostream>
#include <stdlib.h>
Waypoint::Waypoint(string country, string name, string id, Localization loc){
	this->id=id;
	this->name=name;
	this->country=country;
	this->localization=loc;
}
Waypoint::Waypoint(string country, string name, string id,long double lat, long double lon){
	this->name=name;
	this->id=id;
	this->country=country;
	this->localization=Localization(lat, lon);

}

string Waypoint::getID(){
	return id;
}

string Waypoint::getName(){
	return name;
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

void Waypoint::setName(string name){
	this->name=name;
}

void Waypoint::setLocalization(long double lat, long double lon){
	this->localization=Localization(lat, lon);
}

void Waypoint::setLocalization(Localization loc){
	this->localization=loc;
}

void Waypoint::setByStrings(vector<string> data){
	if (data.size()!=5) throw InvalidStringsSizeException();
	this->country=data[0];
	this->name=data[1];
	this->id=data[2];
	this->localization=Localization(atof(data[3].c_str()),atof(data[4].c_str()));


}

ostream& operator<<(ostream& os,  Waypoint& a){
	os << a.getCountry()  << " " << a.getName()  << " " << a.getID() << " " << a.getLocalization().getLatitude() << " " << a.getLocalization().getLongitude();
	return os;
}
