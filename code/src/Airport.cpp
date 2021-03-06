#include "Airport.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
Airport::Airport(string country,string name,string IATA, string ICAO,
		Localization localization):Waypoint(country, name,ICAO,localization) {

	if(IATA.size()!=3) throw new InvalidIATAException();
	this->IATA = IATA;

	if(ICAO.size()!=4) throw new InvalidICAOException();
	this->ICAO = ICAO;

	this->country=country;
}

Airport::Airport(string country,string name, string IATA, string ICAO, long double lat,
		long double lon):Waypoint(country, name,ICAO,lat, lon) {
	this->IATA = IATA;
	this->ICAO = ICAO;

}


string Airport::getIATA(){
	return IATA;
}

string Airport::getICAO(){
	return ICAO;
}


void Airport::setIATA(string IATA){
	if(IATA.size()!=3) throw  InvalidIATAException();
	this->IATA=IATA;
}

void Airport::setICAO(string ICAO){
	if(ICAO.size()!=4) throw InvalidICAOException();
	this->ICAO=ICAO;
	// the id of the waypoint is the ICAO
	this->id=ICAO;
}

bool Airport::isAirport(){
	return true;
}

void Airport::setByStrings(vector<string> data){
	if (data.size()!=6) throw InvalidStringsSizeException();
	this->country=data[0];
	this->name=data[1];
	if(data[2].size()!=3) throw  InvalidIATAException();
	this->IATA=data[2];
	if(data[3].size()!=4) throw InvalidICAOException();
	this->ICAO=data[3];
	this->id=ICAO;
	this->localization=Localization(atof(data[4].c_str()),atof(data[5].c_str()));

}


ostream& operator<<(ostream& os,  Airport& a){
	os << a.getCountry() << " " << a.getName()<< " " << a.getIATA() << " " << a.getICAO() <<  " " << a.getLocalization().getLatitude() << " " << a.getLocalization().getLongitude();
	return os;
}
