#pragma once
#include "Graph.h"
#include "AMatrix.cpp"

template<typename T>
void Graph<T>::addVertex(string vertexName) {
	adMatrix.addVertex(vertexName);
}

template<typename T>
void Graph<T>::addEdge(string from, string to, float weight) {
	adMatrix.addEdge(from, to, weight);
}

template<typename T>
void Graph<T>::getVertices(vector<string>* emptyVector) {
	for (typename vector<T>::iterator i = vertices.begin(); i != vertices.end(); i++)
		emptyVector->push_back(i->name());
}

template<typename T>
int Graph<T>::getNextVertices(string eventName, vector<string>* emptyVector) {
	return adMatrix.getNextVertices(eventName, emptyVector);
}

template<typename T>
int Graph<T>::getLastVertices(string eventName, vector<string>* emptyVector) {
	return adMatrix.getLastVertices(eventName, emptyVector);
}

template<typename T>
float Graph<T>::getWeight(string from, string to) {
	return adMatrix.getWeight(from, to);
}

template<typename T>
void Graph<T>::eraseVertex(string vertexName) {
	adMatrix.eraseVertex(vertexName);
}

template<typename T>
void Graph<T>::eraseEdge(string from, string to) {
	adMatrix.removeEdge(from, to);
}

template<typename T>
void Graph<T>::getRealVertices(vector<string>* names, vector<T*>* realVertices) {
	for (vector<string>::iterator i = names->begin(); i != names->end(); i++) {
		auto& soughtVertex = *find_if(vertices.begin(), vertices.end(),
			[i](T currentVertex) {return currentVertex.name() == *i; });
		realVertices->push_back(&soughtVertex);
	}
}

template<typename T>
T* Graph<T>::getRealVertices(string name) {
	auto& soughtVertex = *find_if(vertices.begin(), vertices.end(),
		[name](T currentVertex) {return currentVertex.name() == name; });
	return &soughtVertex;
}
