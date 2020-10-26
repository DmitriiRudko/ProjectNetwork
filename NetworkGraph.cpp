#include "NetworkGraph.h"
#include "Graph.cpp"
#include <queue>


string NetworkGraph::getRootEvent() {
	vector<string> eventNames = vector<string>();
	getVertices(&eventNames);
	for (vector<string>::iterator i = eventNames.begin(); i != eventNames.end(); i++)
		if (!getLastVertices(*i, &vector<string>()))
			return *i;
	throw exception("Graph has no root");
}

string NetworkGraph::getLastEvent() {
	vector<string> eventNames = vector<string>();
	getVertices(&eventNames);
	for (vector<string>::iterator i = eventNames.begin(); i != eventNames.end(); i++)
		if (!getNextVertices(*i, &vector<string>()))
			return *i;
	throw exception("Graph has no top");
}

void NetworkGraph::countEventParameters() {
	queue<string> bfsQueue = queue<string>();
	bfsQueue.push(getRootEvent());
	while (!bfsQueue.empty())
	{
		string current = bfsQueue.front();
		bfsQueue.pop();
		getRealVertices(current)->recountEarliestTime(this);
		vector<string> eventNames = vector<string>();
		getNextVertices(current, &eventNames);
		for (vector<string>::iterator i = eventNames.begin(); i != eventNames.end(); i++)
			bfsQueue.push(*i);
	}
	bfsQueue.push(getLastEvent());
	while (!bfsQueue.empty())
	{
		string current = bfsQueue.front();
		bfsQueue.pop();
		getRealVertices(current)->recountLatestTime(this);
		vector<string> eventNames = vector<string>();
		getLastVertices(current, &eventNames);
		for (vector<string>::iterator i = eventNames.begin(); i != eventNames.end(); i++)
			bfsQueue.push(*i);
	}

}

float NetworkGraph::getEarliestTime(string eventName) {
	return getRealVertices(eventName)->getEarliestTime();
}

float NetworkGraph::getLatestTime(string eventName) {
	return 	getRealVertices(eventName)->getLatestTime();
}

float NetworkGraph::fullTimeReserve(string from, string to) {
	return getLatestTime(to) - getEarliestTime(from) - getWeight(from, to);
}

float NetworkGraph::independentTimeReserve(string from, string to) {
	return getEarliestTime(to) - getLatestTime(from) - getWeight(from, to);
}

void NetworkGraph::findCriticalWays(vector<vector<string>>* criticalWays) {
	queue<vector<string>> ways = queue<vector<string>>();
	ways.push(vector<string>());
	ways.front().push_back(getRootEvent());
	string topEvent = getLastEvent();
	while (!ways.empty()) {
		vector<string> currentWay = ways.front();
		ways.pop();
		string lastEvent = currentWay.back();
		if (lastEvent == topEvent)
			criticalWays->push_back(currentWay);
		else {
			vector<string> nextEvents = vector<string>();
			getNextVertices(lastEvent, &nextEvents);
			for (vector<string>::iterator i = nextEvents.begin(); i != nextEvents.end(); i++)
				if (!fullTimeReserve(lastEvent, *i))
				{
					vector<string> newWay = vector<string>(currentWay);
					newWay.push_back(*i);
					ways.push(newWay);
				}
		}
	}
}