//
//  GraphOperation.h
//  test csv
//
//  Created by Olivier Alves on 31/03/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef test_csv_GraphOperation_h
#define test_csv_GraphOperation_h

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>

#include "FileOperation.h"
#include "Graph.h"

#include <iostream>
#include "GraphOperation.h"

class GraphOperation {
    
    
public:
    template <class T>
    static Graph<T> createGraph(){
        
        vector< vector<string> > network =FileOperation::loadFile("/Users/Sirae/Documents/network.csv");
        
        vector< vector<string> > airports =FileOperation::loadFile("/Users/Sirae/Documents/airports.csv");
        
        vector< vector<string> > waypoint =FileOperation::loadFile("/Users/Sirae/Documents/waypoints.csv");
        
        
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
};


#endif
