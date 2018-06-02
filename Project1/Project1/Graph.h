#pragma once

#include "Flags.h"
#include "List.h"
#include "Timer.h"
//#include "Structs.h"
//#include "Functions.h"

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>      // std::setw
#include <sstream>		// std::istringstream
#include <ctime>

extern std::string getWord(std::string *);

class Graph
{
public:
	Graph(int numberOfNodes, int density, int type);

	Graph(std::string description, int type);

	Graph(int type);

	~Graph();

	int readFormFile(std::string patch, int graphIsDirected = UNDIRECTED_GRAPH);
	
	void primsAlgorithmUsingIncydenceMatrix(std::string *&minTree, int startNode  = 0);

	void primsAlgorithmUsingListOfSuccessors(std::string *&minTree, int startNode = 0);

	int dijkstrasAlgorithmIncydenceMatrix(int startNode = 0, int endNode = 0);

	int dijkstrasAlgorithmListOfSuccessors(int startNode = 0, int endNode = 0);

public: //will be "private" in the future
	
	void createIncidenceMatrix(int numberOfEdges, int numberOfNodes);
	
	void resetIncidenceMatrix();
	
	void showIncidenceMatrix();
	
	static const void showIncidenceMatrix(int** incidenceMatrix, int numberOfNodes, int numberOfEdges);

	void createWeightMatrix(int numberOfEdges);
	
	void showWeightMatrix();

	void createListOfSuccessors(int numberOfNodes);
	
	void showListOfSuccessors();
	
	static const void showListOfSuccessors(List<int> ** listOfSuccessors, int numberOfNodes, int numberOfEdges);

	int getWeight(int first, int second);

private:
	int **incidenceMatrix;

	int *weightOfEdge;

	List<int> **listOfSuccessors;

	int numberOfEdges;

	int numberOfNodes;

	int type;

	bool empty;

	void Graph::addEdge(int firstNode, int secondNode, int edgeNumber, int weight);
};

