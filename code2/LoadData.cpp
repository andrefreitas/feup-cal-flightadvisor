#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <iostream>

#include "LoadData.h"
#include "Graph.h"

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
    
     

     for(int i = 0; i < fileRawInfo.size();i++){
         vector<string> tempStringVector;
         int separa;
         do{
             separa = fileRawInfo[i].find(";");
             tempStringVector.push_back(fileRawInfo[i].substr(0,separa));
             fileRawInfo[i].erase(0,separa+1);
         }while(separa != string::npos);
         fileFinalInformation.push_back(tempStringVector);
     }
     
     return fileFinalInformation;
     
}

Graph<string> LoadData::createGraph(){
        
        vector< vector<string> > network =LoadData::loadFile("data/network.csv");
        vector< vector<string> > airports =LoadData::loadFile("data/airports.csv");
        vector< vector<string> > waypoint =LoadData::loadFile("data/waypoints.csv");
        
        
        Graph<string> networkGraph;
        
        vector<Vertex<string>* > waypoints;
        
        //create airport vertex
        for (int i = 0; i < airports.size(); i++)
        {
            string icao = airports[i][2];
            networkGraph.addVertex(icao);
        }
        
        //create waypoint vertex
        for (int i = 0; i < waypoint.size(); i++)
        {
            string id = waypoint[i][2];
            networkGraph.addVertex(id);
        }
        
        vector<Vertex<string> *> test = networkGraph.getVertexSet();
        
        for (int i = 0; i < network.size(); i++)
        {
            for (int j = 1; j < network[i].size()-1; j++)
            {
                string previous = network[i][j];
                string next = network[i][j+1];
                
                networkGraph.addEdge(previous, next, 100);
            }
        }
        
        return networkGraph;
    }