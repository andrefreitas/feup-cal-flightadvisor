#include "Waypoint.h"
#include <iostream>

Waypoint::Waypoint(string id, Localization loc){
	this->id=id;
	this->localization=loc;
}
Waypoint::Waypoint(string id, long double lat, long double lon){
	this->id=id;
	this->localization=Localization(lat, lon);

}

string Waypoint::getID(){
	return id;
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
void Waypoint::setLocalization(long double lat, long double lon){
	this->localization=Localization(lat, lon);
}

void Waypoint::setLocalization(Localization loc){
	this->localization=loc;
}
