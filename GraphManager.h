#pragma once
#include <fstream>
#include <tuple>
#include <vector>
#include <iostream>
#include <iomanip>
#include "NetworkGraph.h"
using namespace std;

/*То, что заставляет этот код работать*/
class GraphManager
{
public:
	GraphManager(string nameOfInputFile, NetworkGraph* processedNetworkGraph) :  // достает весь текст из файла и запихивает в textConverted
		textConverted(vector<tuple<string, string, float>>()), networkGraph(processedNetworkGraph),
		eventCodes(vector<string>()) {
		ifstream fin = ifstream(nameOfInputFile);
		while (!fin.eof())
		{
			vector<tuple<string, string, float>> currentString;
			string from;
			fin >> from;
			string to;
			fin >> to;
			float weight;
			fin >> weight;
			textConverted.push_back(make_tuple(from, to, weight));
		}
		fin.close();
	}
	
	void alhorithmStuff() {  // ход работы программы
		initializeComponents();
		displayAllWork();
		networkGraph->countEventParameters();
		displayEventParameters();
		displayWorkParameters();
		displayCriticalWays();
	}

private:
	NetworkGraph* networkGraph;  // ссылка на обрабатываемый граф
	vector<tuple<string, string, float>> textConverted;  // типизированный текст из файла
	vector<string> eventCodes;  // коды всех событий
	void retriveEventCodes();  // извлекает коды событий из текста
	void initializeComponents();  // добавление в граф вершин и ребер
	void displayAllWork();  // дисплеи
	void displayEventParameters();
	void displayWorkParameters();
	void displayCriticalWays();
};

