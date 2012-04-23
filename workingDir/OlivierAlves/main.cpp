//
//  main.cpp
//  test csv
//
//  Created by Olivier Alves on 31/03/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "GraphOperation.h"

using namespace std;

int main(int argc, char *argv[])
{       
    Graph<string> t1 = GraphOperation::createGraph<string>();
    vector<Vertex<string> *> vertexSet = t1.getVertexSet();

    
    for (int i = 0; i < vertexSet.size();i++)
    {
        cout << vertexSet[i]->getInfo() << "\n ------- \n";
    }
    return 0;
    
}

