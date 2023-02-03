/**
 * *FUNCIÓN
 * @param A:puntero hacia Arreglo
 * @param NA:número de celdas necesarias del Arreglo 
 * @param dataStrings5:Lista que contiene las entradas para una de los nombres sorteados anteriormente
 * Función para empezar a llenar la estructura total empezando por el nivel Arreglo
 * Se crean las celdas de Arreglo necesarias llenando cada uno con un dato de tipo Character definido en el archivo character.cpp
 */
void PopulateArray(DS<int>* A, int NA, LinkedList dataStrings5) {
    /**
     * *BLOQUE
     * Extraer los elementos unicos de las armas contenidas en la lista sorteada por nombre dataStrings5
     * Crear múltiples listas sorteadas por arma y guardarlas en un arreglo de listas sortedLists5
     */
    LinkedList unique5;
    unique5 = dataStrings5.uniqueElements(5);
    LinkedList sortedLists5[unique5.length()];
    dataStrings5.sort(sortedLists5, unique5, 5);

    string arr[5];
    Character* C;

    /**
     * *ITERACIÓN
     * Se hacen NA iteraciones
     * En cada iteración se extraen los elementos contenidos en la lista sortedLists5 de la iteración y se guardan en el arreglo arr
     * Se guarda cada elemento del arreglo arr en un objeto de tipo Character
     * Se inserta el objeto de tipo Character en una nueva celda del arreglo
     */
    for (int i = 0; i < NA; i++) {
        // Extracción de elementos separados
        sortedLists5[i].extractWords(arr);

        C = new Character;
        C->id = i + 1;
        C->era = arr[0];
        C->realm = arr[1];
        C->race = arr[2];
        C->name = arr[3];
        C->weapon = arr[4];

        SDDS<int>::insert(A,i,(int)C);
    }
}