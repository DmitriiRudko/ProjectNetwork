#pragma once
#include <array>
#include "AMatrix.h"


/*сам граф*/
template <class T>
class Graph
{
public:  // все те же методы, что и у матриы смежности
	Graph() : vertices(vector<T>()), adMatrix(AMatrix<T>(&vertices)) {};
	void addVertex(string vertexName);
	void addEdge(string from, string to, float weight);
	void eraseVertex(string vertexName);
	void eraseEdge(string from, string to);
	void getVertices(vector<string>* emptyVector);
	float getWeight(string from, string to);
	int getNextVertices(string eventName, vector<string>* emptyVector);
	int getLastVertices(string eventName, vector<string>* emptyVector);

protected:
	void getRealVertices(vector<string>* names, vector<T*>* realVertices);  // позволяет получить реальные образы вершин из коллекции vertices
	T* getRealVertices(string name);

private:
	AMatrix<T> adMatrix;  // матрица смежности
	vector<T> vertices;  // коллекция вершин
};

