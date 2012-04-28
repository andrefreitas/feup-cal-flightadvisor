#ifndef LoadData_h
#define LoadData_h

#include <string.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Graph.h"

using namespace std;
/**
 * LoadData - A class for loading graph flight routes data from CSV files.
 */
class LoadData {
public:
    /**
     * Create a graph from the files data
     * @return a graph of strings
     */
    static Graph<string> createGraph();
     /**
     * Reads a CSV file and returns a vector of lines. Each line is a vector of strings.
     * @param nameFile the file name
     * @return a vector of string vectors
     */
    static vector< vector<string> > loadFile(string nameFile);
};

/**
 * openFileException - A class for handling file openning exceptions
 */
class openFileException {
public:
    openFileException(){};

};

#endif
