#pragma once
#include "Vertex.h"

/*событие, унаследованное от вершины*/
class NetworkGraph;
class Event :
	public Vertex
{
public:
	Event(string newName) : Vertex(newName), earliestTime(0), latestTime(0) {};  
	float recountEarliestTime(NetworkGraph* owner);  // подсчитывает раннее время, owner - граф которому принадлежит событие
	float recountLatestTime(NetworkGraph* owner);  // то же самое, только поздее время
	float getEarliestTime();  // получение раннего и позднего времени
	float getLatestTime();

private:
	float earliestTime;
	float latestTime;
};

