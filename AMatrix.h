#pragma once
#include <string>
#include <vector>
#include "Vertex.h"
#include <type_traits>
using namespace std;

/*Матрица смежности*/
template <class V>
class AMatrix
{
static_assert((is_base_of<Vertex, V>::value), "template parameter must be derived from Vertex class");
public:
	AMatrix(vector<V>* vertices_ptr) : matrix(vector<vector<float>>()), vertices(vertices_ptr), order(0) {};
	void addVertex(string name);  // добавление вершины
	void addEdge(string from, string to, float weight);  // добавление ребра
	float getWeight(string from, string to);  // получение веса
	int getNextVertices(string vertexName, vector<string>* emptyVector);  // получение вершин, исходящих из заданной
	int getLastVertices(string vertexName, vector<string>* emptyVector);  // получение вершин, входящих в заданную
	void eraseVertex(string name);  // удаление вершины
	void removeEdge(string from, string to);  // удаление ребра

protected:
	vector<V>* vertices;  // ссылка на коллекцию фактических объектов класса вершина

private:
	vector<vector<float>> matrix;  // матрица смежности
	int order;  // ее порядок
};
