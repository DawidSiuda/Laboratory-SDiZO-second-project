#include "Core.h"

void mainProgram()
{
	bool mainProgram = true;

	while (mainProgram == true)
	{
		show_main_menu();

		int comand;

		cin >> comand;

		switch (comand)
		{
		case 0:
			mainProgram = false;
			break;
		case 1:
			dijkstraAlgorithmProgram();
			break;
		case 2: 
			primAlgorithmProgram();
			break;
		}

		#ifdef CLEAN_SCREEN
		system("cls");
		#endif // CLEAN_SCREEN
	}

	return;
}

void dijkstraAlgorithmProgram() 
{
	bool mainProgram = true;

	std::string message;

	Graph *graph = nullptr;
	
	while (mainProgram == true)
	{
		#ifdef CLEAN_SCREEN
		system("cls");
		#endif // CLEAN_SCREEN

		if (message.empty() != true)
		{
			std::cout << "================ KOMUNIKATY ================" << std::endl;
			std::cout << message << std::endl;
			std::cout << "============================================" << std::endl;

			message.clear();
		}

		show_menu_dijkstra();

		int comand;

		cin >> comand;

		switch (comand)
		{
			case 0:
			{
				#ifdef CLEAN_SCREEN
				system("cls");
				#endif // CLEAN_SCREEN

				mainProgram = false;
				break;
			}
			case 1:
			{

				int var;
				int numberOfNodes;

				#ifdef CLEAN_SCREEN
				system("cls");
				#endif // CLEAN_SCREEN

				if (graph != nullptr)
				{
					message += "Poprzeni graf zostal usuniety z pamieci.\n\n";

					delete graph;

					graph = nullptr; 
				}

				std::cout << "Podaj liczbe wezlow: ";

				std::cin >> numberOfNodes;

				std::cout << "Podaj gêstosc grafu (%): ";

				std::cin >> var;

				if (numberOfNodes < 2)
				{
					message += "Podano zbyt mala liczbe wezlow w grafie.\n\n";
					break;
				}

				graph = new Graph(numberOfNodes, var, DIRECTED_GRAPH);

				break;
			}
			case 2:
			{
				std::string path;

				#ifdef CLEAN_SCREEN
				system("cls");
				#endif // CLEAN_SCREEN

				std::cout << "Podaj sciezke do pliku z grafem: " << std::endl;

				std::cin >> path;

				if (graph != nullptr)
				{
					message += "Poprzeni graf zostal usuniety z pamieci.\n\n";

					//
					// According to standard, compilator doesn't have to set pointer
					// to nullptr after deleting object, so I have to do it manualy
					// all what I can say is "wtf?"
					//

					delete graph;

					graph = nullptr; 
				}

				graph = new Graph(DIRECTED_GRAPH);

				if (graph->readFormFile(path, DIRECTED_GRAPH) == -1)
				{
					message += "Nie udalo sie wczytac grafu,\n"
						"prawdopodobnie jest to spowodowanie\n"
						"niepoprawna sciezka do pliku lub niepoprawna\n"
						"zawartosc.\n\n";

					delete graph;

					graph = nullptr; 
				}

				break;
			}
			case 3:
			{
				#ifdef CLEAN_SCREEN
				system("cls");
				#endif // CLEAN_SCREEN

				if (graph == nullptr)
				{
					message += "Graf nie istnieje\n\n";

					break;
				}

				std::cout << endl;
				std::cout << "==================================================\n";
				std::cout << "MACIERZ INCYDENCJI\n";
				std::cout << "==================================================\n\n";

				graph->showIncidenceMatrix();

				std::cout << endl;
				std::cout << "==================================================\n";
				std::cout << "LISTA SASIEDZTWA\n";
				std::cout << "==================================================\n\n";

				graph->showListOfSuccessors();

				#ifdef CLEAN_SCREEN
				std::cout << "\n\n\n";
				system("pause");
				#endif // CLEAN_SCREEN

				break;
			}
			case 4:
			{
				#ifdef CLEAN_SCREEN
				system("cls");
				#endif // CLEAN_SCREEN

				int startNode;
				int endNode;
				int weigth;

				if (graph == nullptr)
				{
					message += "Graf nie istnieje\n\n";

					break;
				}

				std::cout << "Podawj wierzcholek startowy: " << std::endl;

				cin >> startNode;

				std::cout << "Podawj wierzcholek koncowy: " << std::endl;

				cin >> endNode;

				weigth = graph->dijkstrasAlgorithmIncydenceMatrix(startNode, endNode);
				
				if (weigth != -1)
				{
					message += " Waga najktrutszej sciezki z\n"
								" wierzcholka " + std::to_string(startNode) +
								" do wierzcholka " + std::to_string(endNode) + "\n"
								" wynosi: " + std::to_string(weigth) + "\n\n";
				}
				else
				{
					message += " Nie mozna wyznaczyc sciezki z\n"
								" wierzcholka " + std::to_string(startNode) +
								" do wierzcholka " + std::to_string(endNode) + "\n\n";
				}

				break;
			}
			case 5:
			{
				#ifdef CLEAN_SCREEN
				system("cls");
				#endif // CLEAN_SCREEN

				int startNode;
				int endNode;
				int weigth;

				if (graph == nullptr)
				{
					message += "Graf nie istnieje\n\n";

					break;
				}

				std::cout << "Podawj wierzcholek startowy: " << std::endl;

				cin >> startNode;

				std::cout << "Podawj wierzcholek koncowy: " << std::endl;

				cin >> endNode;

				weigth = graph->dijkstrasAlgorithmListOfSuccessors(startNode, endNode);

				if (weigth != -1)
				{
					message += " Waga najktrutszej sciezki z\n"
						" wierzcholka " + std::to_string(startNode) +
						" do wierzcholka " + std::to_string(endNode) + "\n"
						" wynosi: " + std::to_string(weigth) + "\n\n";
				}
				else
				{
					message += "  Nie mozna wyznaczyc sciezki z\n"
						" wierzcholka " + std::to_string(startNode) +
						" do wierzcholka " + std::to_string(endNode) + "\n\n";
				}
				break;
			}
		}
	}

	if (graph != nullptr)
	{
		delete graph;
	}
}

void primAlgorithmProgram()
{
	bool mainProgram = true;

	std::string message;

	Graph *graph   = nullptr;
	Graph *minTree = nullptr;

	while (mainProgram == true)
	{
		#ifdef CLEAN_SCREEN
		system("cls");
		#endif // CLEAN_SCREEN

		if (message.empty() != true)
		{
			std::cout << "================ KOMUNIKATY ================" << std::endl;
			std::cout << message << std::endl;
			std::cout << "============================================" << std::endl;

			message.clear();
		}

		show_menu_prim();

		int comand;

		cin >> comand;

		switch (comand)
		{
			case 0:
			{
				#ifdef CLEAN_SCREEN
				system("cls");
				#endif // CLEAN_SCREEN

				mainProgram = false;

				break;
			}
			case 1:
			{

				int var;
				int numberOfNodes;

				#ifdef CLEAN_SCREEN
				system("cls");
				#endif // CLEAN_SCREEN

				if (graph != nullptr)
				{
					message += "Poprzeni graf zostal usuniety z pamieci.\n\n";

					delete graph;

					graph = nullptr; 

					if (minTree != nullptr)
					{
						message += "Poprzednie drzewo minimalne grafu zostalo usuniete z pamieci.\n\n";

						delete minTree;

						minTree = nullptr;
					}
				}

				std::cout << "Podaj liczbe wezlow: ";

				std::cin >> numberOfNodes;

				std::cout << "Podaj gêstosc grafu (%): ";

				std::cin >> var;

				if (numberOfNodes < 2)
				{
					message += "Podano zbyt mala liczbe wezlow w grafie.\n\n";
					break;
				}

				graph = new Graph(numberOfNodes, var, UNDIRECTED_GRAPH);

				break;
			}
			case 2:
			{
				std::string path;

				#ifdef CLEAN_SCREEN
				system("cls");
				#endif // CLEAN_SCREEN

				std::cout << "Podaj sciezke do pliku z grafem: " << std::endl;

				std::cin >> path;

				if (graph != nullptr)
				{
					message += "Poprzeni graf zostal usuniety z pamieci.\n\n";

					//
					// According to standard, compilator doesn't have to set pointer
					// to nullptr after deleting object, so I have to do it manualy
					// all what I can say is "wtf?"
					//

					delete graph;

					graph = nullptr; 

					if (minTree != nullptr)
					{
						message += "Poprzednie drzewo minimalne grafu zostalo usuniete z pamieci.\n\n";

						delete minTree;

						minTree = nullptr;
					}
				}

				graph = new Graph(UNDIRECTED_GRAPH);

				if (graph->readFormFile(path, UNDIRECTED_GRAPH) == -1)
				{
					message += "Nie udalo sie wczytac grafu,\n"
						"prawdopodobnie jest to spowodowanie\n"
						"niepoprawna sciezka do pliku lub niepoprawna\n"
						"zawartosc.\n\n";

					delete graph;

					graph = nullptr; 
				}

				break;
			}
			case 3:
			{
				#ifdef CLEAN_SCREEN
				system("cls");
				#endif // CLEAN_SCREEN

				if (graph == nullptr)
				{
					message += "Graf nie istnieje\n\n";

					break;
				}

				std::cout << endl;
				std::cout << "==================================================\n";
				std::cout << "MACIERZ INCYDENCJI\n";
				std::cout << "==================================================\n\n";

				graph->showIncidenceMatrix();

				std::cout << endl;
				std::cout << "==================================================\n";
				std::cout << "LISTA SASIEDZTWA\n";
				std::cout << "==================================================\n\n";

				graph->showListOfSuccessors();

				#ifdef CLEAN_SCREEN
				std::cout << "\n\n\n";
				system("pause");
				#endif // CLEAN_SCREEN

				break;
			}
			case 4:
			{
				#ifdef CLEAN_SCREEN
				system("cls");
				#endif // CLEAN_SCREEN

				std::string *sourceOfTree = nullptr;

				int startNode;

				if (graph == nullptr)
				{
					message += "Graf nie istnieje\n\n";

					break;
				}

				std::cout << "Podawj wierzcholek startowy: " << std::endl;

				cin >> startNode;

				graph->primsAlgorithmUsingIncydenceMatrix(sourceOfTree, startNode);

				if (minTree != nullptr)
				{
					message += "Poprzednie drzewo minimalne grafu zostalo usuniete z pamieci.\n\n";

					delete minTree;

					minTree = nullptr;
				}

				minTree = new Graph(*sourceOfTree, UNDIRECTED_GRAPH);

				break;
			}
			case 5:
			{
				#ifdef CLEAN_SCREEN
				system("cls");
				#endif // CLEAN_SCREEN

				std::string *sourceOfTree = nullptr;

				int startNode;

				if (graph == nullptr)
				{
					message += "Graf nie istnieje\n\n";

					break;
				}

				std::cout << "Podawj wierzcholek startowy: " << std::endl;

				cin >> startNode;

				if (minTree != nullptr)
				{
					message += "Poprzednie drzewo minimalne grafu zostalo usuniete z pamieci.\n\n";

					delete minTree;

					minTree = nullptr;
				}

				graph->primsAlgorithmUsingListOfSuccessors(sourceOfTree, UNDIRECTED_GRAPH);

				break;
			}
			case 6:
			{
				#ifdef CLEAN_SCREEN
				system("cls");
				#endif // CLEAN_SCREEN

				if (minTree == nullptr)
				{
					message += "Drzewo minimalne nie istnieje\n\n";

					break;
				}

				std::cout << endl;
				std::cout << "==================================================\n";
				std::cout << "MACIERZ INCYDENCJI\n";
				std::cout << "==================================================\n\n";

				minTree->showIncidenceMatrix();

				std::cout << endl;
				std::cout << "==================================================\n";
				std::cout << "LISTA SASIEDZTWA\n";
				std::cout << "==================================================\n\n";

				minTree->showListOfSuccessors();

				#ifdef CLEAN_SCREEN
				std::cout << "\n\n\n";
				system("pause");
				#endif // CLEAN_SCREEN

				break;
			}
		}
	}

	if (graph != nullptr)
	{
		delete graph;
	}

	if (minTree != nullptr)
	{
		delete minTree;
	}
}

void show_main_menu()
{
	std::cout << "================================" << std::endl;
	std::cout << "WYBIERZ ALGORYTM" << std::endl;
	std::cout << "================================" << std::endl;
	std::cout << "1) Algorytm Djikstry" << std::endl;
	std::cout << "2) Algorytm Prima" << std::endl;
	std::cout << std::endl;
	std::cout << "0) Exit" << std::endl << std::endl;
}

void show_menu_dijkstra()
{
	std::cout << "================================" << std::endl;
	std::cout << "ALGORYTM DIJKSTRY" << std::endl;
	std::cout << "================================" << std::endl;
	std::cout << "1) Stworz Graf skierowany" << std::endl;
	std::cout << "2) Wczytaj graf z pliku" << std::endl;
	std::cout << "3) pokaz graf" << std::endl;
	std::cout << "4) Wykonaj algorytm djikstry (macierz incydencji)" << std::endl;
	std::cout << "5) Wykonaj algorytm djikstry (lista sasiedztwa)" << std::endl;
	std::cout << std::endl;
	std::cout << "0) Exit" << std::endl << std::endl;
}

void show_menu_prim()
{
	std::cout << "================================" << std::endl;
	std::cout << "ALGORYTM PRIMA" << std::endl;
	std::cout << "================================" << std::endl;
	std::cout << "1) Stworz Graf nieslierowany" << std::endl;
	std::cout << "2) Wczytaj graf z pliku" << std::endl;
	std::cout << "3) pokaz graf" << std::endl;
	std::cout << "4) Wykonaj algorytm prima (macierz incydencji)" << std::endl;
	std::cout << "5) Wykonaj algorytm prima (lista sasiedztwa)" << std::endl;
	std::cout << "6) Pokaz drzewo minimalne" << std::endl;
	std::cout << std::endl;
	std::cout << "0) Exit" << std::endl << std::endl;
}
