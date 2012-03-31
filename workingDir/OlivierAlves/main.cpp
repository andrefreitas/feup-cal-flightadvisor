//
//  main.cpp
//  test csv
//
//  Created by Olivier Alves on 31/03/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "FileOperation.h"

using namespace std;

int main(int argc, char *argv[])
{       
     vector< vector<string> > test =FileOperation::loadFile("/Users/Sirae/Documents/airports.csv");
    
    for (int i = 0; i < test.size(); i++)
    {
        for (int j = 0; j < test[i].size(); j++)
        {
            cout << test[i][j] << "   ";
        }
        cout << "\n";
    }
   
    return 0;
    
}

