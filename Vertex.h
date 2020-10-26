#pragma once
#include <string>
using namespace std;

/*вершина графа
фактически содержит поле имени иметоды доступа к нему*/
class Vertex
{
public:
	Vertex(string newName) : vertexName(newName) {};

	string name() {
		return this->vertexName;
	}

	string name(string newName) {
		this->vertexName = newName;
	}

private:
	string vertexName;
};