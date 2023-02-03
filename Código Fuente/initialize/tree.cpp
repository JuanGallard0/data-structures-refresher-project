/**
 * *FUNCIÓN
 * @param T:puntero hacia Árbol
 * @param dataStrings2:Lista que contiene las entradas para una de las eras sorteadas anteriormente
 * Función para empezar a llenar la estructura total empezando por el nivel Árbol
 * Se crean los nodos de Árbol necesarios llenando cada uno con sus estructuras internas
 */
void PopulateTree(DS<int>* T, LinkedList dataStrings2) {
    /**
     * *BLOQUE
     * Extraer los elementos unicos de los reinos contenidos en la lista sorteada por eras dataStrings2 
     * Crear múltiples listas sorteadas por reinos y guardarlas en un arreglo de listas sortedLists2
     * Contar la cantidad de elementos unicos de unique2, es decir la cantidad de nodos de Árbol necesarios y guardar el resultado en NT 
     */
    LinkedList unique2;
    unique2 = dataStrings2.uniqueElements(2);
    LinkedList sortedLists2[unique2.length()];
    dataStrings2.sort(sortedLists2, unique2, 2);
    int NT = unique2.length();

    // Crear puntero hacia Lista Doble
    DS<int>* DL;
    bool id = IDENTIFIABLE;

    /**
     * *ITERACIÓN
     * Se hacen NT iteraciones
     * En cada iteración se crea una Lista Doble y se guarda como entero (dirección de memoria) en un nuevo nodo del Árbol
     * Índices de cada nodo incrementados de 1 a NT
     * Llamada de función para llenar la Lista Doble recién creada
     */
    for (int i = 1; i <= NT; i++) {
        SDDS<int>::create(&DL,DOUBLE_LINKED_LIST);
        SDDS<int>::insert(T, i, (int)DL, id);

        PopulateDoubleList(DL, sortedLists2[i-1]);
    }
    
}