//
//  openFileException.h
//  test csv
//
//  Created by Olivier Alves on 31/03/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef test_csv_openFileException_h
#define test_csv_openFileException_h

#include <iostream>
#include <string.h>

using namespace std;

class openFileException {
    string message;
    
public:
    openFileException(string errorMessage){
        message = errorMessage;
    }
    
    string getMessage(){
        return message;
    }
};;

#endif
