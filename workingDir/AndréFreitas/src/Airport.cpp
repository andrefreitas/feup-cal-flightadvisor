#include "Airport.h"
Airport::Airport(string name,string country, string IATA, string ICAO,
		Localization localization):Waypoint(ICAO, localization) {
	this->name = name;

	if(IATA.size()!=3) throw new InvalidIATAException();
	this->IATA = IATA;

	if(ICAO.size()!=4) throw new InvalidICAOException();
	this->ICAO = ICAO;

	this->country=country;
}

Airport::Airport(string name,string country, string IATA, string ICAO, long double lat,
		long double lon):Waypoint(ICAO, lat, lon) {
	this->name = name;
	this->IATA = IATA;
	this->ICAO = ICAO;
	this->country=country;

}


string Airport::getName(){
	return name;
}

string Airport::getCountry(){
	return country;
}

string Airport::getIATA(){
	return IATA;
}

string Airport::getICAO(){
	return ICAO;
}


void Airport::setName(string name){
	this->name=name;
}

void Airport::setCountry(string country){
	this->country=country;
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
