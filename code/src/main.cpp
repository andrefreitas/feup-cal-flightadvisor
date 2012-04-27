#include "LoadData.h"
#include "testAirport.h"
#include "testWaypoint.h"

using namespace std;

int main(int argc, char *argv[])
{       
    //testAirport::runSuite();
    //testWaypoint::runSuite();

    Graph<string> t1 = LoadData::createGraph();
    vector<Vertex<string> *> vertexSet = t1.getVertexSet();



    for (int unsigned i = 0; i < vertexSet.size();i++)
    {
        cout << vertexSet[i]->getInfo() << "\n ------- \n";
    }
    return 0;
    
}

