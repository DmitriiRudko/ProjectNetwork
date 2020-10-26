#include <iostream>
#include "NetworkGraph.h"
#include "Graph.cpp"
#include "GraphManager.h"


int main()
{
    std::cout << __cplusplus << std::endl;
    NetworkGraph graph = NetworkGraph();
    GraphManager("input.txt", &graph).alhorithmStuff();
}
