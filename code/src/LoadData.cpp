#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <iostream>

#include "LoadData.h"
#include "Graph.h"
#include "Localization.h"

vector< vector<string> > LoadData::loadFile(string nameFile){
     vector< vector<string> > fileFinalInformation;
     
     vector<string> fileRawInfo;
     string const nomFichier(nameFile);
     
     ifstream monFlux(nomFichier.c_str());
     
     string ligne;
     
     if(monFlux)    
     {
         while(getline(monFlux, ligne))    
         {
             fileRawInfo.push_back(ligne);
         }
     }
     else
     {
         throw new openFileException(); 
     }
    
     

     for(int unsigned i = 0; i < fileRawInfo.size();i++){
         vector<string> tempStringVector;
         int separa;
         do{
             separa = fileRawInfo[i].find(";");
             tempStringVector.push_back(fileRawInfo[i].substr(0,separa));
             fileRawInfo[i].erase(0,separa+1);
         }while(separa != (int)string::npos);
         fileFinalInformation.push_back(tempStringVector);
     }
     
     return fileFinalInformation;
     
}

Graph<string> LoadData::createGraph(string networkFileName,string airportsFileName, string waypointsFileName){
        
        vector< vector<string> > network =LoadData::loadFile(networkFileName);
        vector< vector<string> > airports =LoadData::loadFile(airportsFileName);
        vector< vector<string> > waypoint =LoadData::loadFile(waypointsFileName);
        
        
        Graph<string> networkGraph;
        
        vector<Vertex<string>* > waypoints;
        
        //create airport vertex
        for (int unsigned i = 0; i < airports.size(); i++)
        {
            string icao = airports[i][3];
            networkGraph.addVertex(icao);
        }
        
        //create waypoint vertex
        for (int unsigned i = 0; i < waypoint.size(); i++)
        {
            string id = waypoint[i][2];
            networkGraph.addVertex(id);
        }
        
        vector<Vertex<string> *> test = networkGraph.getVertexSet();

       for (int unsigned i = 0; i < network.size(); i++)
        {
            for (int unsigned j = 1; j < network[i].size()-1; j++)
            {
                string previous = network[i][j];
                string next = network[i][j+1];
                Waypoint prev=getWayPointbyID(previous);
                Waypoint nex=getWayPointbyID(next);
                long double distance=Localization::distance(prev.getLocalization(),nex.getLocalization());
                //cout << prev << " => " << nex << ": distance= " <<distance << endl;
                networkGraph.addEdge(previous, next, distance);
                networkGraph.addEdge(next,previous,  distance);

            }
        }
        return networkGraph;
    }

vector<Waypoint> LoadData::waypoints=vector<Waypoint>();

vector<Airport> LoadData::airports= vector<Airport>();

vector<Waypoint> LoadData::loadWaypoints(string nameFile){
	// (1) fetch the waypoint vector of lines
	vector< vector<string> > waypoint =LoadData::loadFile(nameFile);

	// (2) add to the vector
	waypoints.clear();
	for (int unsigned i=0; i<waypoint.size(); i++){
		Waypoint *p;
		p=new Waypoint();
		try{
			p->setByStrings(waypoint[i]);
		}
		catch(InvalidStringsSizeException &e){
			cout << nameFile << ", line " << i+1 << ": invalid waypoint!\n";
		}

		LoadData::waypoints.push_back(*p);
	}
	return waypoints;
}

vector<Airport> LoadData::loadAirports(string nameFile){
	// (1) fetch the waypoint vector of lines
	vector< vector<string> > airport =LoadData::loadFile(nameFile);

	// (2) add to the vector
	airports.clear();
	for (int unsigned i=0; i<airport.size(); i++){
		Airport *p;
		p=new Airport();
		try{
			p->setByStrings(airport[i]);
		}
		catch(InvalidStringsSizeException &a){
			cout << nameFile << ", line " <<  i+1  << ": invalid airport!";
				}
		LoadData::airports.push_back(*p);
	}
	return airports;
}

Waypoint LoadData::getWayPointbyID(string id){
	for(int unsigned i=0; i<waypoints.size(); i++)
		if (waypoints[i].getID()==id) return waypoints[i];
	for(int unsigned i=0; i<airports.size(); i++)
			if (airports[i].getID()==id) return airports[i];

	return Waypoint();
}
