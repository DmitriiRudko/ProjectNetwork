#pragma once
#include "Graph.h"
#include "Event.h"

class NetworkGraph :
	public Graph<Event>
{
public:
	NetworkGraph() {};
	string getRootEvent();  // возвращает начальное событие
	string getLastEvent();  // возвращает конечное событие
	void countEventParameters();  //подсчитывает раннее и позддее время событий
	float getEarliestTime(string eventName);  // возвращает раннее время наступления события
	float getLatestTime(string eventName);  // возвращает позднее время наступления события
	float fullTimeReserve(string from, string to);  // полный резерв работы
	float independentTimeReserve(string from, string to);  // независимый резерв работы
	void findCriticalWays(vector<vector<string>>* criticalWays);  // ищет критические пути

private:
	friend float Event::recountEarliestTime(NetworkGraph* owner);  // доверяем этим методам доступ к функциям получения вершин
	friend float Event::recountLatestTime(NetworkGraph* owner);
};
