#include "Graph.h"


Graph::Graph(int numberOfNodes, int density, int type)
{
	incidenceMatrix	 = nullptr;
	weightOfEdge	 = nullptr;
	listOfSuccessors = nullptr;

	if (type == UNDIRECTED_GRAPH || type == DIRECTED_GRAPH)
	{
		this->type = type;
	}
	else
	{
		#ifdef SHOW_ERROR
		std::cout << "ERROR: Can not recognize type of graph. Creating graph is going to DIRECTED "<< std::endl;
		#endif SHOW_ERROR

		this->type = DIRECTED_GRAPH;
	}

	srand(time(NULL));

	if (density < 10)
	{
		density = 10;
	}

	if (density > 100)
	{
		density = 100;
	}

	if (type == UNDIRECTED_GRAPH)
	{
		int max = ((numberOfNodes * (numberOfNodes - 1)) / 2);

		max = (int)(((float)max / 100.0) * (float)density);

		if (max < (numberOfNodes - 1))
		{
			max = numberOfNodes - 1;
		}

		numberOfEdges = max;

		this->numberOfNodes = numberOfNodes; 

		createIncidenceMatrix(numberOfEdges, numberOfNodes);

		createWeightMatrix(numberOfEdges);

		createListOfSuccessors(numberOfNodes);

		#ifdef SHOW_MESSAGES
		std::cout << "MESSAGE: Graph::Graph(int, int, int) Created graph with " << numberOfNodes << " nodes and " << numberOfEdges << " egdes" << std::endl;
		#endif //SHOW_MESSAGES

		int numberOfcreatedEdge = 0;

		//
		// create consistent graph
		//

		List<int> unvisitedNodes;

		List<int> visitedNodes;

		for (int i = 1; i < numberOfNodes; i++)
		{
			unvisitedNodes.push_front(i);
		}

		visitedNodes.push_front(0);

		while (numberOfcreatedEdge < (numberOfNodes - 1))
		{
			int firstNode = visitedNodes.get_value_at(rand() % visitedNodes.get_size());

			int secondNode = unvisitedNodes.get_value_at(rand() % unvisitedNodes.get_size());

			#ifdef SHOW_LOG_CREATE_GRPH
			std::cout << "First node " << firstNode << " second node " << secondNode << " SIZE: "<< unvisitedNodes.get_size() <<  std::endl;
			#endif //SHOW_LOG_CREATE_GRPH

					
			#ifdef SHOW_LOG_CREATE_GRPH
			std::cout << "Creating edge for nodes " << firstNode << " and " << secondNode << std::endl;
			#endif //SHOW_LOG_CREATE_GRPH

			int weight = rand() % 15 + 1 ;

			addEdge(firstNode, secondNode, numberOfcreatedEdge, weight);

			numberOfcreatedEdge++;

			unvisitedNodes.pop_value(secondNode);

			visitedNodes.push_front(secondNode);
		}

		//
		// creating other edges
		//

		while (numberOfcreatedEdge < numberOfEdges)
		{
			int firstNode = rand() % numberOfNodes;

			int secondNode  = rand() % numberOfNodes;

			#ifdef SHOW_LOG_CREATE_GRPH
			std::cout << "First node " << firstNode << " second node " << secondNode << std::endl;
			#endif //SHOW_LOG_CREATE_GRPH

			if (firstNode == secondNode)
			{
				continue;
			}

			if (listOfSuccessors[firstNode]->find(secondNode) == true)
			{
				continue;
			}

			#ifdef SHOW_LOG_CREATE_GRPH
			std::cout << "Creating edge for nodes " << firstNode << " and " << secondNode << std::endl;
			#endif //SHOW_LOG_CREATE_GRPH

			int weight = rand() % 15;

			addEdge(firstNode, secondNode, numberOfcreatedEdge, weight);

			numberOfcreatedEdge++;

			continue;
		}
	}
	else
	{
		int max = ((numberOfNodes * (numberOfNodes - 1)));

		max = (int)(((float)max / 100.0) * (float)density);

		if (max < (numberOfNodes - 1))
		{
			max = numberOfNodes - 1;
		}

		numberOfEdges = max;

		this->numberOfNodes = numberOfNodes; 

		createIncidenceMatrix(numberOfEdges, numberOfNodes);

		createWeightMatrix(numberOfEdges);

		createListOfSuccessors(numberOfNodes);

		#ifdef SHOW_MESSAGES
		std::cout << "MESSAGE: Graph::Graph(int, int, int) Created graph with " << numberOfNodes << " nodes and " << numberOfEdges << " egdes" << std::endl;
		#endif //SHOW_MESSAGES

		int numberOfcreatedEdge = 0;

		//
		// create consistent graph
		//

		List<int> unvisitedNodes;

		List<int> visitedNodes;

		for (int i = 1; i < numberOfNodes; i++)
		{
			unvisitedNodes.push_front(i);
		}

		visitedNodes.push_front(0);

		while (numberOfcreatedEdge < (numberOfNodes - 1))
		{
			int firstNode = visitedNodes.get_value_at(rand() % visitedNodes.get_size());

			int secondNode = unvisitedNodes.get_value_at(rand() % unvisitedNodes.get_size());

			#ifdef SHOW_LOG_CREATE_GRPH
			std::cout << "First node " << firstNode << " second node " << secondNode << " SIZE: "<< unvisitedNodes.get_size() <<  std::endl;
			#endif //SHOW_LOG_CREATE_GRPH

					
			#ifdef SHOW_LOG_CREATE_GRPH
			std::cout << "Creating edge for nodes " << firstNode << " and " << secondNode << std::endl;
			#endif //SHOW_LOG_CREATE_GRPH

			int weight = rand() % 15 + 1 ;

			addEdge(firstNode, secondNode, numberOfcreatedEdge, weight);

			numberOfcreatedEdge++;

			unvisitedNodes.pop_value(secondNode);

			visitedNodes.push_front(secondNode);
		}

		//
		// creating other edges
		//

		while (numberOfcreatedEdge < numberOfEdges)
		{
			int firstNode = rand() % numberOfNodes;

			int secondNode  = rand() % numberOfNodes;

			#ifdef SHOW_LOG_CREATE_GRPH
			std::cout << "First node " << firstNode << " second node " << secondNode << std::endl;
			#endif //SHOW_LOG_CREATE_GRPH

			if (firstNode == secondNode)
			{
				continue;
			}

			if (listOfSuccessors[firstNode]->find(secondNode) == true)
			{
				continue;
			}

			#ifdef SHOW_LOG_CREATE_GRPH
			std::cout << "Creating edge for nodes " << firstNode << " and " << secondNode << std::endl;
			#endif //SHOW_LOG_CREATE_GRPH

			int weight = rand() % 15;

			addEdge(firstNode, secondNode, numberOfcreatedEdge, weight);

			numberOfcreatedEdge++;

			continue;
		}
	}
}

Graph::Graph(std::string description, int type)
{
	numberOfEdges = 0;
	numberOfNodes = 0;

	incidenceMatrix	 = nullptr;
	weightOfEdge	 = nullptr;
	listOfSuccessors = nullptr;

	if (type == UNDIRECTED_GRAPH || type == DIRECTED_GRAPH)
	{
		this->type = type;
	}
	else
	{
		#ifdef SHOW_ERROR
		std::cout << "ERROR: Can not recognize type of graph. Ccreating graph is going to DIRECTED "<< std::endl;
		#endif SHOW_ERROR

		this->type = DIRECTED_GRAPH;
	}

	empty = true;

	std::string line;

	int edgeNumber = 0;

	bool first_value = true;

	try
	{
		std::istringstream istr(description);

		while (getline(istr, line)) 
		{	
			if (first_value == true)
			{
				#ifdef SHOW_LOG
				std::cout << "LOG: Value at frst line: " <<  line << std::endl;
				#endif // SHOW_LOG

				first_value = false;

				int numberEdges = 0;
				int numberNodes = 0;

				numberEdges = atoi(getWord(&line).c_str());
				numberNodes = atoi(getWord(&line).c_str());

				createIncidenceMatrix(numberEdges, numberNodes);

				createWeightMatrix(numberEdges);

				createListOfSuccessors(numberNodes);

				continue;
			}

			#ifdef SHOW_LOG
			std::cout << "LOG: " << line << std::endl;
			#endif // SHOW_LOG

			int firstNode	= atoi(getWord(&line).c_str());
			int secondNode	= atoi(getWord(&line).c_str());
			int weight		= atoi(getWord(&line).c_str());

			addEdge(firstNode, secondNode, edgeNumber, weight);

			edgeNumber++;
		}
	}
	catch (...) 
	{
		#ifdef SHOW_ERROR
		std::cout << "ERROR: Graph::Graph(string, int) can't push all values." << std::endl;
		#endif SHOW_ERROR
	}
}

Graph::Graph(int type)
{
	numberOfEdges = 0;
	numberOfNodes = 0;

	incidenceMatrix	 = nullptr;
	weightOfEdge	 = nullptr;
	listOfSuccessors = nullptr;

	if (type == UNDIRECTED_GRAPH || type == DIRECTED_GRAPH)
	{
		this->type = type;
	}
	else
	{
		#ifdef SHOW_ERROR
		std::cout << "ERROR: Can not recognize type of graph. Ccreating graph is going to DIRECTED "<< std::endl;
		#endif SHOW_ERROR

		this->type = DIRECTED_GRAPH;
	}

	empty = true;
}

Graph::~Graph()
{
	//
	// deleting incidenceMatrix
	//

	if (incidenceMatrix != nullptr)
	{
		for (int i = 0; i < numberOfNodes; i++)
		{
			delete[] incidenceMatrix[i];
		}

		delete[] incidenceMatrix;
	}

	//
	// deleting weightOfEdge
	//

	if (weightOfEdge != nullptr)
	{
		delete[] weightOfEdge;
	}

	//
	// deleting listOfSuccessors
	//

	if (listOfSuccessors != nullptr)
	{
		for (int i = 0; i < numberOfNodes; i++)
		{
			delete listOfSuccessors[i];
		}

		delete[] listOfSuccessors;
	}
}

void Graph::createIncidenceMatrix(int edgesNumber, int nodesNumber)
{
	numberOfNodes = nodesNumber;
	numberOfEdges = edgesNumber;

	incidenceMatrix = new int*[numberOfNodes];

	for (int i = 0; i < numberOfNodes; i++)
	{
		incidenceMatrix[i] = new int [numberOfEdges];
	}

	resetIncidenceMatrix();
}

void Graph::createWeightMatrix(int edgesNumber)
{
	weightOfEdge = new int[edgesNumber];
	
	for (int i = 0; i < edgesNumber; i++)
	{
		weightOfEdge[i] = 0;
	}
}

void Graph::showWeightMatrix()
{
	std::cout << "edge | weight" << std::endl;

	for (int i = 0; i < numberOfEdges; i++)
	{
		std::cout << std::setw(4) << i << " | " << weightOfEdge[i] << std::endl;
	}
}

void Graph::createListOfSuccessors(int numberOfNodes)
{
	listOfSuccessors = new List<int>*[numberOfNodes];

	for (int i = 0; i < numberOfNodes; i++)
	{
		listOfSuccessors[i] = new List<int>;
	}
}

void Graph::showListOfSuccessors()
{
	if (listOfSuccessors == nullptr)
	{
		return;
	}

	std::cout << "Node | List" << std::endl;
	std::cout << "------------------>" << std::endl;
	
	for (int i = 0; i < numberOfNodes; i++)
	{
		std::cout << std::setw(4) << i << " | ";
		
		for (int j = 0; j < listOfSuccessors[i]->get_size(); j++)
		{
			int node = listOfSuccessors[i]->get_value_at(j);
			int weight = getWeight(i, node);
			
			std::cout << node << "(" << weight << "), ";
		}

		std::cout << std::endl;
	}
}

const void Graph::showListOfSuccessors(List<int>** listOfSuccessors, int numberOfNodes, int numberOfEdges)
{
	if (listOfSuccessors == nullptr)
	{
		return;
	}

	std::cout << "Node | List" << std::endl;
	std::cout << "------------------>" << std::endl;

	for (int i = 0; i < numberOfNodes; i++)
	{
		std::cout << std::setw(4) << i << " | ";

		listOfSuccessors[i]->showHorizontally();

		std::cout << std::endl;
	}
}

int Graph::getWeight(int first, int second)
{
	
	if (type == DIRECTED_GRAPH)
	{
		for (int i = 0; i < numberOfEdges; i++)
		{
			if (incidenceMatrix[first][i] == 1)
			{
				for (int j = 0; j < numberOfEdges; j++)
				{
					if (incidenceMatrix[second][j] == -1 && j == i)
					{
						return weightOfEdge[j];
					}
				}
			}
		}
	}
	else if (type == UNDIRECTED_GRAPH)
	{
		for (int i = 0; i < numberOfEdges; i++)
		{
			if (incidenceMatrix[first][i] == 1)
			{
				for (int j = 0; j < numberOfEdges; j++)
				{
					if (incidenceMatrix[second][j] == 1 && j == i)
					{
						return weightOfEdge[j];
					}
				}
			}
		}
	}
	else
	{
		#ifdef SHOW_ERROR
		std::cout << "ERROR: getWeight(): Can not recognize type of graph." << std::endl;
		#endif // SHOW_ERROR
		return -1;
	}

	#ifdef SHOW_ERROR
	std::cout << "ERROR: getWeight(int, int): Can not fing weight of edge "
			  << first << " --> " << second << std::endl;
	#endif // SHOW_ERROR

	return -1;

}

void Graph::resetIncidenceMatrix()
{
	for (int i = 0; i < numberOfNodes; i++)
	{
		for (int j = 0; j < numberOfEdges; j++)
		{
			incidenceMatrix[i][j] = 0;
		}
	}
}

int Graph::readFormFile(std::string path, int graphIsDirected)
{
	std::string line;
	std::ifstream myfile(path);

	int edgeNumber = 0;

	bool first_value = true;

	if (myfile.is_open()) 
	{
		try
		{
			while (getline(myfile, line))
			{	
				if (first_value == true)
				{
					#ifdef SHOW_LOG
					std::cout << "LOG: Value at frst line: " <<  line << std::endl;
					#endif // SHOW_LOG

					first_value = false;

					int numberEdges = 0;
					int numberNodes = 0;

					numberEdges = atoi(getWord(&line).c_str());
					numberNodes = atoi(getWord(&line).c_str());

					createIncidenceMatrix(numberEdges, numberNodes);

					createWeightMatrix(numberEdges);

					createListOfSuccessors(numberNodes);

					continue;
				}

				#ifdef SHOW_LOG
				std::cout << "LOG: " << line << std::endl;
				#endif // SHOW_LOG

				int firstNode	= atoi(getWord(&line).c_str());
				int secondNode	= atoi(getWord(&line).c_str());
				int weight		= atoi(getWord(&line).c_str());

				addEdge(firstNode, secondNode, edgeNumber, weight);

				edgeNumber++;
			}
		}
		catch (...) 
		{
			#ifdef SHOW_ERROR
			std::cout << "ERROR: can't push all values " << path << std::endl << std::endl;
			#endif SHOW_ERROR

			myfile.close();

			return -1;
		}

		myfile.close();
	}
	else
	{
		#ifdef SHOW_ERROR
		std::cout << "ERROR: Unable to read data from file "<< path << std::endl << std::endl;
		#endif SHOW_ERROR

		return -1;
	}

	return 0;
}

void Graph::primsAlgorithmUsingIncydenceMatrix(std::string *&minTree, int startNode)
{
	#ifdef SHOW_LOG
	std::cout << "--> Graph::primsAlgorithmUsingIncydenceMatrix has been colled." << std::endl;
	#endif // SHOW_LOG

	if (type == DIRECTED_GRAPH)
	{
		#ifdef SHOW_MESSAGES
		std::cout << "MESSAGE: Graph::primsAlgorithmUsingIncydenceMatrix Can not create tree for directed graph." << std::endl;
		#endif //SHOW_MESSAGES

		return;
	}

	if (startNode >= numberOfNodes)
	{
		#ifdef SHOW_MESSAGES
		std::cout << "MESSAGE: Graph::primsAlgorithmUsingIncydenceMatrix Start node doesn't exist." << std::endl;
		#endif //SHOW_MESSAGES

		return;
	}

	
	//
	// variables
	//

	int endMainLoop = false;

	List<int> listOfUnvisitedNodes;

	List<int> listOfVisitedNodes;

	std::string outcome;

	outcome += std::to_string(numberOfNodes-1) + " " + std::to_string(numberOfNodes) + "\n";

	//
	// Set lists
	//

	for (int i = 0; i < numberOfNodes; i++)
	{
		if (i != startNode)
		{
			listOfUnvisitedNodes.push_back(i);
		}
	}

	listOfVisitedNodes.push_front(startNode);

	//
	// Broswing all neighbors
	//

	while (endMainLoop == false)
	{
		#ifdef SHOW_LOG_CREATE_MIN_TREE
		std::cout << "========== NEW LOOP ===============" << std::endl;
		#endif

		bool minIsSet = false;

		int min = 0;
		int selectedEdge;
		int selectedNode = -1;
		int secondNodeOfEdge;
		int tempSelectedNode = -1;

		for (int currentNode = 0; currentNode < numberOfNodes; currentNode++)
		{
			if (listOfVisitedNodes.find(currentNode) != true)
			{
				continue;
			}

			for (int currentEdge = 0; currentEdge < numberOfEdges; currentEdge++)
			{
				if (incidenceMatrix[currentNode][currentEdge] == 1)
				{
					//
					// Check if node has selected
					//

					for (int i = 0; i < numberOfNodes; i++)
					{
						if (incidenceMatrix[i][currentEdge] == 1 && i != currentNode)
						{
							tempSelectedNode = i;

							#ifdef SHOW_LOG_CREATE_MIN_TREE
							std::cout << "--> Chck egde: " <<currentEdge << " to node: " << tempSelectedNode << std::endl;
							#endif		

							break;
						}
					}

					if (listOfVisitedNodes.find(tempSelectedNode) == true)
					{
						#ifdef SHOW_LOG_CREATE_MIN_TREE
						std::cout << "--> Node: " << tempSelectedNode << " exist in list of visited nodes." << std::endl;
						#endif

						continue;
					}

					#ifdef SHOW_LOG_CREATE_MIN_TREE
					std::cout << "--> Old weight: " << min << " new weight(" << currentEdge << "): " << weightOfEdge[currentEdge] << std::endl;
					#endif

					if (minIsSet != true)
					{
						min = weightOfEdge[currentEdge];
						
						selectedEdge = currentEdge;

						selectedNode = tempSelectedNode;

						secondNodeOfEdge = currentNode;

						//
						// Find second node of edge
						//

						#ifdef SHOW_LOG_CREATE_MIN_TREE
						std::cout << "--> change current edge on : " << selectedEdge  << std::endl;
						#endif

						if (selectedNode == -1)
						{
							#ifdef SHOW_ERROR
							std::cout << "ERROR: primsAlgorithmUsingIncydenceMatrix(): Can't find edge." << std::endl;
							#endif // SHOW_ERROR

							return;
						}

						minIsSet = true;
					}
					else
					{
						if (min > weightOfEdge[currentEdge])
						{
							min = weightOfEdge[currentEdge];

							selectedEdge = currentEdge;

							selectedNode = tempSelectedNode;

							secondNodeOfEdge = currentNode;

							#ifdef SHOW_LOG_CREATE_MIN_TREE
							std::cout << "--> Change current edge on : " << selectedEdge  << std::endl;
							#endif
						}
					}
				}
			}
		}
		
		//
		// add node to listOfVisitedNodes and delete it from second list and add checking all selected nodes
		//

		#ifdef SHOW_LOG_CREATE_MIN_TREE
		std::cout << "SELECTED EDGE: " << selectedEdge << std::endl
				  << "WEIGHT: " << min << std::endl 
				  << "NODE: " << selectedNode << std::endl
			      << "SIZE: "<< listOfUnvisitedNodes.get_size() << std::endl;
		#endif
		
		outcome += std::to_string(selectedNode)  + " " + std::to_string(secondNodeOfEdge)  + " " +  std::to_string(min) + '\n';

		listOfVisitedNodes.push_front(selectedNode);

		listOfUnvisitedNodes.pop_value(selectedNode);

		if (listOfUnvisitedNodes.get_size() == 0)
		{
			endMainLoop = true;

			break;
		}
	}

	#ifdef SHOW_LOG_CREATE_MIN_TREE
	std::cout << "OUTCOME: " << std::endl;
	std::cout << outcome << std::endl;
	#endif

	minTree = new std::string(outcome);

	return;
}

void Graph::primsAlgorithmUsingListOfSuccessors(std::string *&minTree, int startNode)
{
	#ifdef SHOW_LOG
	std::cout << "--> Graph::primsAlgorithmUsingListOfSuccessors(" << startNode << ") has been colled." << std::endl;
	#endif // SHOW_LOG

	if (type == DIRECTED_GRAPH )
	{
		#ifdef SHOW_MESSAGES
		std::cout << "MESSAGE: Graph::primsAlgorithmUsingListOfSuccessors Can not create tree for directed graph." << std::endl;
		#endif //SHOW_MESSAGES

		return;
	}

	if (startNode >= numberOfNodes)
	{
		#ifdef SHOW_MESSAGES
		std::cout << "MESSAGE: Graph::primsAlgorithmUsingListOfSuccessors Start node doesn't exist." << std::endl;
		#endif //SHOW_MESSAGES

		return;
	}

	//
	// variables
	//

	int endMainLoop = false;

	List<int> listOfUnvisitedNodes;

	List<int> listOfVisitedNodes;

	std::string outcome;

	outcome += std::to_string(numberOfNodes-1) + " " + std::to_string(numberOfNodes) + "\n";

	//
	// Set lists
	//

	for (int i = 0; i < numberOfNodes; i++)
	{
		if (i != startNode)
		{
			listOfUnvisitedNodes.push_back(i);
		}
	}

	listOfVisitedNodes.push_front(startNode);

	while (endMainLoop == false)
	{
		#ifdef SHOW_LOG_CREATE_MIN_TREE
		std::cout << "========== NEW LOOP ===============" << std::endl;
		#endif

		bool minIsSet = false;

		int min				   = 0;
		int tempSelectedNode   = -1;
		int selectedNode       = -1;
		int secondSelectedNode = -1;
		int firstNode          = -1;

		for (int currentNode = 0; currentNode < listOfVisitedNodes.get_size(); currentNode++)
		{
			firstNode = listOfVisitedNodes.get_value_at(currentNode);

			for (int i = 0; i < listOfSuccessors[firstNode]->get_size(); i++)
			{
				tempSelectedNode = listOfSuccessors[firstNode]->get_value_at(i);

				if (listOfVisitedNodes.find(tempSelectedNode) == true)
				{
					continue;
				}

				if (minIsSet != true)
				{
					min = getWeight(firstNode, tempSelectedNode);

					selectedNode = tempSelectedNode;

					secondSelectedNode = firstNode;

					minIsSet = true;

					#ifdef SHOW_LOG_CREATE_MIN_TREE
					std::cout << "--> Change current edge on : " << firstNode 
							  << " --> " << selectedNode << std::endl;
					#endif

					continue;
				}
				
				if (min > getWeight(firstNode, tempSelectedNode))
				{
					selectedNode = tempSelectedNode;

					secondSelectedNode = firstNode;

					#ifdef SHOW_LOG_CREATE_MIN_TREE
					std::cout << "--> Change current edge on : " << firstNode 
							  << " --> " << selectedNode << std::endl;
					#endif

				}
				
			}
		}

		listOfUnvisitedNodes.pop_value(selectedNode);

		listOfVisitedNodes.push_front(selectedNode);

		#ifdef SHOW_LOG_CREATE_MIN_TREE
		std::cout << "SELECTED EDGE: " << secondSelectedNode << " --> " << selectedNode << std::endl
				  << "WEIGHT: " << min << std::endl 
				  << "NODE: " << selectedNode << std::endl
			      << "SIZE: "<< listOfUnvisitedNodes.get_size() << std::endl;
		#endif

		outcome += std::to_string(secondSelectedNode)  + " " + std::to_string(selectedNode)  + " " +  std::to_string(min) + '\n';


		if (listOfUnvisitedNodes.get_size() == 0)
		{
			endMainLoop = true;

			break;
		}
	}

	minTree = new std::string(outcome);
}

int Graph::dijkstrasAlgorithmIncydenceMatrix(int startNode, int endNode)
{
	#ifdef SHOW_LOG
	std::cout << "--> Graph::dijkstrasAlgorithmIncydenceMatrix(" << startNode << ") has been colled." << std::endl;
	#endif // SHOW_LOG

	if (type == UNDIRECTED_GRAPH )
	{
		#ifdef SHOW_MESSAGES
		std::cout << "MESSAGE: Graph::dijkstrasAlgorithmIncydenceMatrix Can not create tree for undirected graph." << std::endl;
		#endif //SHOW_MESSAGES

		return -1;
	}

	if (startNode >= numberOfNodes)
	{
		#ifdef SHOW_MESSAGES
		std::cout << "MESSAGE: Graph::dijkstrasAlgorithmIncydenceMatrix Start node doesn't exist." << std::endl;
		#endif //SHOW_MESSAGES

		return -1;
	}

	List<int> S;
	List<int> Q;

	int output = 0;

	//
	// Set lists
	//

	for (int i = 0; i < numberOfNodes; i++)
	{
		Q.push_back(i);
	}

	//
	// create table d(i) p(i) isSet(i)
	//

	int *d		 = new int[numberOfNodes];
	int *p		 = new int[numberOfNodes];
	int *isSet	 = new int[numberOfNodes];

	memset(d, 0, numberOfNodes * sizeof(int));
	memset(p, -1, numberOfNodes * sizeof(int));
	memset(isSet, 0, numberOfNodes * sizeof(int));

	isSet[startNode] = 1;

	bool endMainLoop = false;

	while (endMainLoop == false)
	{
		//
		// searching node with the lower value in set of node
		//
		
		int selectetRootNode = -1;

		bool selectetRootNodeIsSet = false;
		
		for (int i = 0; i < Q.get_size(); i++)
		{
			int tempSelectedNode = Q.get_value_at(i);

			if (isSet[tempSelectedNode] == 1 && selectetRootNodeIsSet == false)
			{
				selectetRootNode = tempSelectedNode;

				selectetRootNodeIsSet = true;

				continue;
			}

			if (isSet[tempSelectedNode] == 1 && selectetRootNodeIsSet == true)
			{
				if (d[selectetRootNode] > d[tempSelectedNode])
				{
					selectetRootNode = tempSelectedNode;
				}	
			}
		}

		if (selectetRootNode == -1)
		{
			return -1;
		}

		Q.pop_value(selectetRootNode);

		S.push_front(selectetRootNode);

		//
		// copy list of succesors of selected node
		//

		List<int> tempListOfSuccesors;

		int secondNode;

		for (int i = 0; i < numberOfEdges; i++)
		{
			if (incidenceMatrix[selectetRootNode][i] == 1)
			{
				for (int j = 0; j < numberOfNodes; j++)
				{
					if (incidenceMatrix[j][i] == -1 )
					{
						tempListOfSuccesors.push_front(j);
					}
				}
			}

		}

		#ifdef SHOW_LOG_DJIKSTRA_ALGORITHM
			std::cout << "list of succesors : ";

			tempListOfSuccesors.showHorizontally();

			std::cout << std::endl;
		#endif // SHOW_LOG_DJIKSTRA_ALGORITHM

		//
		// set new walue for nodes 
		//

		while(tempListOfSuccesors.get_size() != 0)
		{
			int procesedNode = tempListOfSuccesors.get_value_at(0);
			
			tempListOfSuccesors.pop_front();

			int weightOfEdge = getWeight(selectetRootNode, procesedNode);

			//
			// Check if node have used
			//

			if (isSet[procesedNode] == 0)
			{
				int newWeight = d[selectetRootNode] + weightOfEdge;

				isSet[procesedNode] = 1;

				d[procesedNode] = newWeight;

				p[procesedNode] = selectetRootNode;

			} else
			{
				//
				// check if selected node have less weight
				//

				int newWeight = d[selectetRootNode] + weightOfEdge;

				if (d[procesedNode] > newWeight)
				{
					d[procesedNode] = newWeight;

					p[procesedNode] = selectetRootNode;
				}
			}
		}

		//
		// Show details  
		//

		#ifdef SHOW_LOG_DJIKSTRA_ALGORITHM

			std::cout << "============= STATE ================" << std::endl;

			//
			// i:
			//

			std::cout << std::setw(7) << "i:" << " | ";

			for (int i = 0; i < numberOfNodes; i++)
			{
				std::cout << std::setw(4) << i;
			}

			std::cout << std::endl;

			//
			// -----------
			//

			std::cout << "----------";

			for (int i = 0; i < numberOfNodes; i++)
			{
				std::cout << std::setw(4) << "-----";
			}

			std::cout << std::endl;

			//
			// isSet:
			//

			std::cout << std::setw(7) << "isSet:" << " | ";

			for (int i = 0; i < numberOfNodes; i++)
			{
				std::cout << std::setw(4) << isSet[i];

			}

			std::cout << std::endl;

			//
			// d:
			//

			std::cout << std::setw(7) << "d:" << " | ";

			for (int i = 0; i < numberOfNodes; i++)
			{
				std::cout << std::setw(4) << d[i];

			}

			std::cout << std::endl;

			//
			// p:
			//

			std::cout << std::setw(7) << "p:" << " | ";

			for (int i = 0; i < numberOfNodes; i++)
			{
				std::cout << std::setw(4) << p[i];

			}

			std::cout << std::endl;

			std::cout << "====================================" << std::endl;
			std::cout << "Selected Node: " << selectetRootNode << std::endl;
			std::cout << "unvisited  Q: "; Q.showHorizontally(); std::cout << std::endl;
			std::cout << "  visited  S: "; S.showHorizontally(); std::cout << std::endl;
			std::cout << "====================================" << std::endl;

		#endif // SHOW_LOG_DJIKSTRA_ALGORITH

		if (Q.get_size() == 0)
		{
			endMainLoop = true;

			break;
		}
	}

	if (endNode >= numberOfNodes)
	{
		output = -1;
	}
	else
	{
		output = d[endNode];
	}

	delete d;
	delete p;
	delete isSet;

	return output;
}

int Graph::dijkstrasAlgorithmListOfSuccessors(int startNode, int endNode)
{
	#ifdef SHOW_LOG
	std::cout << "--> Graph::dijkstrasAlgorithmListOfSuccessors(" << startNode << ") has been colled." << std::endl;
	#endif // SHOW_LOG

	if (type == UNDIRECTED_GRAPH )
	{
		#ifdef SHOW_MESSAGES
		std::cout << "MESSAGE: Graph::dijkstrasAlgorithmListOfSuccessors Can not create tree for undirected graph." << std::endl;
		#endif //SHOW_MESSAGES

		return -1;
	}

	if (startNode >= numberOfNodes)
	{
		#ifdef SHOW_MESSAGES
		std::cout << "MESSAGE: Graph::dijkstrasAlgorithmListOfSuccessors Start node doesn't exist." << std::endl;
		#endif //SHOW_MESSAGES

		return -1;
	}

	List<int> S;
	List<int> Q;

	int output;

	//
	// Set lists
	//

	for (int i = 0; i < numberOfNodes; i++)
	{
		Q.push_back(i);
	}

	//
	// create table d(i) p(i) isSet(i)
	//

	int *d		 = new int[numberOfNodes];
	int *p		 = new int[numberOfNodes];
	int *isSet	 = new int[numberOfNodes];

	memset(d, 0, numberOfNodes * sizeof(int));
	memset(p, -1, numberOfNodes * sizeof(int));
	memset(isSet, 0, numberOfNodes * sizeof(int));

	isSet[startNode] = 1;

	bool endMainLoop = false;

	while (endMainLoop == false)
	{
		//
		// searching node with the lower value in set of node
		//
		
		int selectetRootNode = -1;

		bool selectetRootNodeIsSet = false;
		
		for (int i = 0; i < Q.get_size(); i++)
		{
			int tempSelectedNode = Q.get_value_at(i);

			if (isSet[tempSelectedNode] == 1 && selectetRootNodeIsSet == false)
			{
				selectetRootNode = tempSelectedNode;

				selectetRootNodeIsSet = true;

				continue;
			}

			if (isSet[tempSelectedNode] == 1 && selectetRootNodeIsSet == true)
			{
				if (d[selectetRootNode] > d[tempSelectedNode])
				{
					selectetRootNode = tempSelectedNode;
				}	
			}
		}

		if (selectetRootNode == -1)
		{
			return -1;
		}

		Q.pop_value(selectetRootNode);

		S.push_front(selectetRootNode);


		//
		// copy list of succesors of selected node
		//

		List<int> tempListOfSuccesors;

		for (int i = 0; i < listOfSuccessors[selectetRootNode]->get_size(); i++)
		{
			tempListOfSuccesors.push_front(listOfSuccessors[selectetRootNode]->get_value_at(i));
		}

		#ifdef SHOW_LOG_DJIKSTRA_ALGORITHM
			std::cout << "coped list of succesors: ";

			tempListOfSuccesors.showHorizontally();

			std::cout << std::endl;
		#endif // SHOW_LOG_DJIKSTRA_ALGORITHM

		//
		// set new walue for nodes 
		//

		while(tempListOfSuccesors.get_size() != 0)
		{
			int procesedNode = tempListOfSuccesors.get_value_at(0);
			
			tempListOfSuccesors.pop_front();

			int weightOfEdge = getWeight(selectetRootNode, procesedNode);

			//
			// Check if node have used
			//

			if (isSet[procesedNode] == 0)
			{
				int newWeight = d[selectetRootNode] + weightOfEdge;

				isSet[procesedNode] = 1;

				d[procesedNode] = newWeight;

				p[procesedNode] = selectetRootNode;

			} else
			{
				//
				// check if selected node have less weight
				//

				int newWeight = d[selectetRootNode] + weightOfEdge;

				if (d[procesedNode] > newWeight)
				{
					d[procesedNode] = newWeight;

					p[procesedNode] = selectetRootNode;
				}
			}
		}

		//
		// Show details  
		//

		#ifdef SHOW_LOG_DJIKSTRA_ALGORITHM

			std::cout << "============= STATE ================" << std::endl;

			//
			// i:
			//

			std::cout << std::setw(7) << "i:" << " | ";

			for (int i = 0; i < numberOfNodes; i++)
			{
				std::cout << std::setw(4) << i;
			}

			std::cout << std::endl;

			//
			// -----------
			//

			std::cout << "----------";

			for (int i = 0; i < numberOfNodes; i++)
			{
				std::cout << std::setw(4) << "-----";
			}

			std::cout << std::endl;

			//
			// isSet:
			//

			std::cout << std::setw(7) << "isSet:" << " | ";

			for (int i = 0; i < numberOfNodes; i++)
			{
				std::cout << std::setw(4) << isSet[i];

			}

			std::cout << std::endl;

			//
			// d:
			//

			std::cout << std::setw(7) << "d:" << " | ";

			for (int i = 0; i < numberOfNodes; i++)
			{
				std::cout << std::setw(4) << d[i];

			}

			std::cout << std::endl;

			//
			// p:
			//

			std::cout << std::setw(7) << "p:" << " | ";

			for (int i = 0; i < numberOfNodes; i++)
			{
				std::cout << std::setw(4) << p[i];

			}

			std::cout << std::endl;

			std::cout << "====================================" << std::endl;
			std::cout << "Selected Node: " << selectetRootNode << std::endl;
			std::cout << "unvisited  Q: "; Q.showHorizontally(); std::cout << std::endl;
			std::cout << "  visited  S: "; S.showHorizontally(); std::cout << std::endl;
			std::cout << "====================================" << std::endl;

		#endif // SHOW_LOG_DJIKSTRA_ALGORITH

		if (Q.get_size() == 0)
		{
			endMainLoop = true;

			break;
		}
	}

	if (endNode >= numberOfNodes)
	{
		output = -1;
	}
	else
	{
		output = d[endNode];
	}

	delete d;
	delete p;
	delete isSet;

	return output;
	

}

void Graph::showIncidenceMatrix()
{
	std::cout << "    ";
	for (int i = 0; i < numberOfEdges; i++)
	{
		std::cout << std::setw(4) << i;
	}

	std::cout << std::endl;

	for (int i = 0; i <= numberOfEdges; i++)
	{
		std::cout << "----";
	}

	std::cout << std::endl;

	for (int i = 0; i < numberOfNodes; i++)
	{
		std::cout << std::setw(3) << i << "|";

		for (int j = 0; j < numberOfEdges; j++)
		{
			std::cout << std::setw(4) << incidenceMatrix[i][j];
		}

		std::cout << std::endl;
	}
}

const void Graph::showIncidenceMatrix(int ** incidenceMatrix, int numberOfNodes, int numberOfEdges)
{
	std::cout << "    ";
	for (int i = 0; i < numberOfEdges; i++)
	{
		std::cout << std::setw(4) << i;
	}

	std::cout << std::endl;

	for (int i = 0; i <= numberOfEdges; i++)
	{
		std::cout << "----";
	}

	std::cout << std::endl;

	for (int i = 0; i < numberOfNodes; i++)
	{
		std::cout << std::setw(3) << i << "|";

		for (int j = 0; j < numberOfEdges; j++)
		{
			std::cout << std::setw(4) << incidenceMatrix[i][j];
		}

		std::cout << std::endl;
	}
}

void Graph::addEdge(int firstNode, int secondNode, int edgeNumber, int weight)
{
	if (firstNode >= numberOfNodes)
	{
		#ifdef SHOW_ERROR
		std::cout << "ERROR: Graph::addEdge have got wrong argument \n";
		#endif //SHOW_ERROR

		return;
	}

	if (secondNode >= numberOfNodes)
	{
		#ifdef SHOW_ERROR
		std::cout << "ERROR: Graph::addEdge have got wrong argument \n";
		#endif //SHOW_ERROR

		return;
	}

	if (edgeNumber >= numberOfEdges)
	{
		#ifdef SHOW_ERROR
		std::cout << "ERROR: Graph::addEdge have got wrong argument \n";
		#endif //SHOW_ERROR

		return;
	}

	if (listOfSuccessors == nullptr || incidenceMatrix == nullptr || weightOfEdge == nullptr)
	{
		#ifdef SHOW_ERROR
		std::cout << "ERROR: Graph::addEdge some structures does not exist \n";
		#endif //SHOW_ERROR

		return;
	}

	if (type == UNDIRECTED_GRAPH)
	{
		incidenceMatrix[firstNode][edgeNumber] = 1;

		incidenceMatrix[secondNode][edgeNumber] = 1;

		weightOfEdge[edgeNumber] = weight;

		listOfSuccessors[firstNode]->push_back(secondNode);

		listOfSuccessors[secondNode]->push_back(firstNode);
	}
	else
	{
		incidenceMatrix[firstNode][edgeNumber] = 1;

		incidenceMatrix[secondNode][edgeNumber] = -1;

		weightOfEdge[edgeNumber] = weight;

		listOfSuccessors[firstNode]->push_back(secondNode);
	}

}
