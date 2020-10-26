#include "GraphManager.h"
#include "Graph.cpp"
#include <queue>


void GraphManager::retriveEventCodes() {
	for (vector<tuple<string, string, float>>::iterator i = textConverted.begin(); i != textConverted.end(); i++)
	{
		eventCodes.push_back(get<0>(*i));
		eventCodes.push_back(get<1>(*i));
	}
	sort(eventCodes.begin(), eventCodes.end());
	auto lastPtr = unique(eventCodes.begin(), eventCodes.end());
	eventCodes.erase(lastPtr, eventCodes.end());
}

void GraphManager::initializeComponents() {
	retriveEventCodes();
	for (vector<string>::iterator i = eventCodes.begin(); i != eventCodes.end(); i++)
		networkGraph->addVertex(*i);
	for (vector<tuple<string, string, float>>::iterator i = textConverted.begin(); i != textConverted.end(); i++)
		networkGraph->addEdge(get<0>(*i), get<1>(*i), get<2>(*i));
}

void GraphManager::displayAllWork() {
	for (vector<tuple<string, string, float>>::iterator i = textConverted.begin(); i != textConverted.end(); i++)
		cout << get<0>(*i) << "->" << get<1>(*i) << ": " <<
		networkGraph->getWeight(get<0>(*i), get<1>(*i)) << endl;
	cout << endl;
}

void GraphManager::displayEventParameters() {
	cout << "Событие    Ранний срок    Поздний срок    Резерв" << endl;
	for (vector<string>::iterator i = eventCodes.begin(); i != eventCodes.end(); i++)
	{
		cout << left << setw(7) << *i << "    ";
		cout << left << setw(11) << networkGraph->getEarliestTime(*i) << "    ";
		cout << left << setw(12) << networkGraph->getLatestTime(*i) << "    ";
		cout << left << networkGraph->getLatestTime(*i) - networkGraph->getEarliestTime(*i) << endl;
	}
	cout << endl;
}

void GraphManager::displayWorkParameters() {
	cout << "Работа           Продолжительность    Полный резерв    Независимый резерв" << endl;
	for (vector<tuple<string, string, float>>::iterator i = textConverted.begin(); i != textConverted.end(); i++)
	{
		string out = get<0>(*i) + "->" + get<1>(*i);
		cout << left << setw(13) << out << "    ";
		float result = networkGraph->getWeight(get<0>(*i), get<1>(*i));
		cout << left << setw(17) << result << "    ";
		result = networkGraph->fullTimeReserve(get<0>(*i), get<1>(*i));
		cout << left << setw(13) << result << "    ";
		result = networkGraph->independentTimeReserve(get<0>(*i), get<1>(*i));
		cout << result << endl;
	}
	cout << endl;
}

void GraphManager::displayCriticalWays() {
	cout << "Критические пути" << endl;
	vector<vector<string>> criticalWays = vector<vector<string>>();
	networkGraph->findCriticalWays(&criticalWays);
	for (vector<vector<string>>::iterator i = criticalWays.begin(); i != criticalWays.end(); i++)
	{
		for (vector<string>::iterator j = i->begin(); j != i->end(); j++)
			cout << *j << " -> ";
		cout << endl;
	}
}
