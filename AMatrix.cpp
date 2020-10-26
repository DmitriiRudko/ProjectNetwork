#include "AMatrix.h"

template<typename V>
void AMatrix<V>::addVertex(string name) {  // добавляет вершину
	vertices->push_back(V(name));
	for (vector<vector<float>>::iterator i = matrix.begin(); i != matrix.end(); i++)  // добавляем столбец в матрице смежности
		i->push_back(NAN);  // так как работа может быть нулевой, я использую в ачестве дефолтного веса бесконечность
	order++;
	matrix.push_back(vector<float>(order, NAN));  // добавляем новую строку
}

template<typename V>
void AMatrix<V>::addEdge(string from, string to, float weight) {  // добавляет ребро
	int fromIndex = distance(vertices->begin(), find_if(vertices->begin(), vertices->end(),  // ищем индекс первой вершины
		[from](V vtx) {return vtx.name() == from; }));
	int toIndex = distance(vertices->begin(), find_if(vertices->begin(), vertices->end(),  // индекс второй
		[to](V vtx) {return vtx.name() == to; }));
	matrix[fromIndex][toIndex] = weight;
}

template<typename V>
float AMatrix<V>::getWeight(string from, string to) {  // то же самое что и выше, только вес не корректируется а возвращается
	int fromIndex = distance(vertices->begin(), find_if(vertices->begin(), vertices->end(),
		[from](V vtx) {return vtx.name() == from; }));
	int toIndex = distance(vertices->begin(), find_if(vertices->begin(), vertices->end(),  
		[to](V vtx) {return vtx.name() == to; }));
	return matrix[fromIndex][toIndex];
}

template<typename V>
int AMatrix<V>::getNextVertices(string vertexName, vector<string>* emptyVector) {  // заполняет пустой вектор именами следующих вершин
	int vertexIndex = distance(vertices->begin(), find_if(vertices->begin(), vertices->end(),
		[vertexName](V vtx) {return vtx.name() == vertexName; }));

	for (int i = 0; i < vertices->size(); i++)
		if (matrix[vertexIndex][i] == matrix[vertexIndex][i])  // пользуемся свойством NAN != NAN
			emptyVector->push_back(vertices->at(i).name());	
	return emptyVector->size();
}

template<typename V>
int AMatrix<V>::getLastVertices(string vertexName, vector<string>* emptyVector) {
	int vertexIndex = distance(vertices->begin(), find_if(vertices->begin(), vertices->end(),
		[vertexName](V vtx) {return vtx.name() == vertexName; }));

	for (int i = 0; i < vertices->size(); i++)
		if (matrix[i][vertexIndex] == matrix[i][vertexIndex])  // пользуемся свойством NAN != NAN
			emptyVector->push_back(vertices->at(i).name());
	return emptyVector->size();
}

template<typename V>
void AMatrix<V>::eraseVertex(string vertexName) {
	typename vector<V>::iterator vertexIt = find_if(vertices->begin(), vertices->end(),
		[vertexName](V vtx) {return vtx.name() == vertexName; });
	int vertexIndex = distance(vertices->begin(), vertexIt);
	for (vector<vector<float>>::iterator i = matrix.begin(); i != matrix.end(); i++)
		i->erase(i->begin() + vertexIndex);
	matrix.erase(matrix.begin() + vertexIndex);
	vertices->erase(vertexIt);
	order--;
}

template<typename V>
void AMatrix<V>::removeEdge(string from, string to) {
	int fromIndex = distance(vertices->begin(), find_if(vertices->begin(), vertices->end(),
		[from](V vtx) {return vtx.name() == from; }));
	int toIndex = distance(vertices->begin(), find_if(vertices->begin(), vertices->end(),
		[to](V vtx) {return vtx.name() == to; }));
	matrix[fromIndex][toIndex] = NAN;
}
