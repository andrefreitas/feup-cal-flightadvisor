//
//  FileOperation.h
//  test csv
//
//  Created by Olivier Alves on 31/03/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef test_csv_FileOperation_h
#define test_csv_FileOperation_h

#include <string.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <fstream>

#include "openFileException.h"

using namespace std;

//! Class FileOperation

/*!
 *
 */
class FileOperation {

public:
    static vector< vector<string> > loadFile(string nameFile);
    
    
};

#endif
