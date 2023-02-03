#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <sstream>
#include <regex>
#include <thread>
#include <math.h>

using namespace std;

#include "objects/character.cpp"
#include "headers/DSAlt/SLL.h"
#include "headers/SDDS.h"
#include "initialize/array.cpp"
#include "initialize/matrix.cpp"
#include "initialize/double_list.cpp"
#include "initialize/tree.cpp"
#include "initialize/graph.cpp"

template <typename T>
Data SDDS<T>::ref = Data();

int main(void){
    srand(time(NULL));

	/**
	 * *BLOQUE
	 * Abrir el archivo LOTR.csv que contiene los dataSets para llenar la estructura total
	 */
    ifstream dataFile;
    dataFile.open("data/LOTR.csv", ios::out);
    if (!dataFile.is_open()) {
        cout << "Could not open file." << endl;
        return 0;
    }

	// Creación de puntero hacia un Grafo
    DS<int> *G;
    SDDS<int>::create(&G, GRAPH);
    
	// Llamada de función para llenar la estructura total empezando por el nivel Grafo
	// Función definida en el archivo graph.cpp
	PopulateGraph(G, dataFile);

	/**
	 * *BLOQUE
	 * Menu principal del programa donde se llaman funciones para manipular la estructura total
	 * Funciones definidas en el archivo DSG.h
	 */
    int option = 0;
    do
	{
		cout << "                  MENU" << endl
		<< "1- Visualizar informacion almacenada" << endl
		<< "2- Agregar informacion al sistema" << endl 
		<< "3- Modificar informacion almacenada" << endl
		<< "4- Remover informacion del sistema" << endl
		<< "5- Salir" << endl 
		<< "SELECCION: ";
		cin >> option;
		cout << "<============================================================>" << endl;

		switch (option) {
			case 1:
                ((DSG<int>*)G)->navigate(0);
				break;
			case 2:
				((DSG<int>*)G)->addInfo();
				break;
			case 3:
				((DSG<int>*)G)->modifyInfo();
				break;
			case 4:
				((DSG<int>*)G)->removeInfo();
				break;
			case 5:
				((DSG<int>*)G)->removeAll();
				cout << "\nSe Limpio toda la Memoria " << endl;
				cout << "<============================================================>" << endl;
				cout << "Adios! " << endl;
				break;
			default:
				cout << "Esa opcion no existe " << endl;
				cout << "<============================================================>" << endl;
		}
	} while (option != 5);

    return 0;
}
