/**
 * *FUNCIÓN
 * @param G:puntero hacia grafo
 * @param dataFile:archivo .csv que contiene los dataSets
 * Función para empezar a llenar la estructura total empezando por el nivel Grafo
 * Se crean los nodos de Grafo necesarios llenando cada uno con sus estructuras internas
 */
void PopulateGraph(DS<int>* G, ifstream& dataFile) {
    /**
     * *BLOQUE
     * Leer línea por línea los dataSets y guardarlas en una lista dataStrings1
     * Cerrar el archivo dataFile
     */
    string line;
    LinkedList dataStrings1;
    getline (dataFile, line);
    while (getline(dataFile, line)) {
        dataStrings1.insert(line);
    }
    dataFile.close();

    /**
     * *BLOQUE
     * Extraer los elementos unicos de las eras contenidas en el archivo y guardarlos en la lista unique1
     * Crear múltiples listas sorteadas por eras y guardarlas en un arreglo de listas sortedLists1
     * Contar la cantidad de elementos unicos de unique1, es decir la cantidad de nodos de grafo necesarios y guardar el resultado en NG 
     */
    LinkedList unique1;
    unique1 = dataStrings1.uniqueElements(1);
    LinkedList sortedLists1[unique1.length()];
    dataStrings1.sort(sortedLists1, unique1, 1);
    int NG = unique1.length();

    // Crear puntero hacia un Árbol
    DS<int>* T;

    /**
     * *ITERACIÓN
     * Se hacen NG iteraciones
     * En cada iteración se crea un Árbol binario de búsqueda y se guarda como entero (dirección de memoria) en un nuevo nodo del Grafo
     * Índices de cada nodo incrementados de 1 a NG
     * Llamada de función para llenar el Árbol recién creado
     */
    for(int i = 1; i <= NG; i++){
        SDDS<int>::create(&T, BINARY_SEARCH_TREE);
        SDDS<int>::insert(G, i, (int)T);
        
        PopulateTree(T, sortedLists1[i-1]);
    }
    
    int CG, count, j;
    DS<int>* L;


    /**
     * *ITERACIÓN
     * Se hacen NG iteraciones
     * El objetivo de esta iteración es crear las conexiones entre los nodos de Grafo insertados previamente
     * Se crea una lista enlazada simple L donde se guardan enteros aleatorios correspondientes a los nodos existentes
     * Se utiliza la función para definir conexiones del Grafo a partir de la lista generada
     */
    for (int i = 1; i <= NG; ++i)
    {
        SDDS<int>::create(&L,SINGLE_LINKED_LIST);

        // Cantidad de conexiones para el nodo de la iteración actual
        CG = rand()%(NG - 1) + 1;
        // Arreglo para guardar las conexiones posibles en la iteración actual
        int connections[NG - 1];
        // Contador
        count = 0;

        // Se guardan los enteros correspondientes a las conexiones posibles en la iteración y se guardan en el arreglo connections
        for (j = 1; j <= NG; ++j)
        {
            if (i != j) {
                connections[count] = j;
                count++;
            }
        }

        // Se mezcla el arreglo connections
        random_shuffle(&connections[0], &connections[NG - 1]);

        // Se guarda el arreglo mezclado en la lista L
        for (j = 0; j < NG - 1; ++j)
        {
            if (j < CG) 
                SDDS<int>::insert(L,connections[j]);
        } 

        // Se crean las conexiones a partir de la lista L
        SDDS<int>::define_connections(G,i,L);
        // Se destruye la lista L
        SDDS<int>::destroy(L);
    }

    delete L;
}