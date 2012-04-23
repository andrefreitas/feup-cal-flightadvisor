//
//  FileOperation.cpp
//  test csv
//
//  Created by Olivier Alves on 31/03/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "FileOperation.h"
#include <string.h>

 vector< vector<string> > FileOperation::loadFile(string nameFile){
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
         throw new openFileException("Error opening file: " + nameFile); 
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
