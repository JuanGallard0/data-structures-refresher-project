/**
 * *FUNCIÓN
 * @param M:puntero hacia Matriz
 * @param NM:número de celdas necesarias de la Matriz
 * @param f:número de filas necesarias
 * @param c:número de columnas necesarias
 * @param dataStrings4:Lista que contiene las entradas para una de la razas sorteadas anteriormente
 * Función para empezar a llenar la estructura total empezando por el nivel Matriz
 * Se crean las celdas de Matriz necesarios llenando cada uno con un Arreglo
 * Se llenan las celdas vacías con un entero -1 como placeholder
 */
void PopulateMatrix(DS<int>* M, int NM, int f, int c, LinkedList dataStrings4) {
    /**
     * *BLOQUE
     * Extraer los elementos unicos de los nombres contenidos en la lista sorteada por razas dataStrings4 
     * Crear múltiples listas sorteadas por nombre y guardarlas en un arreglo de listas sortedLists4
     */
    LinkedList unique4;
    unique4 = dataStrings4.uniqueElements(4);
    LinkedList sortedLists4[unique4.length()];
    dataStrings4.sort(sortedLists4, unique4, 4);

    int NA;
    // Crear puntero hacia Arreglo
    DS<int>* A;

    /**
     * *ITERACIÓN
     * Se hacen NL iteraciones
     * En cada iteración se crea un Arreglo y se guarda como entero (dirección de memoria) en una nueva celda de la Matriz
     * Llamada de función para llenar el Arreglo recién creado
     */
    for (int i = 0; i < NM; i++){
        // Es necesario definir la cantidad de elementos del Arreglo antes de poder crearlo ya que es una estructura estática
        unique4 = sortedLists4[i].uniqueElements(5);
        // Cantidad de celdas necesarias NA
        NA = unique4.length();

	    SDDS<int>::create(&A,NA,ARRAY);
        SDDS<int>::insert(M,i/c,i%c,(int)A);

        PopulateArray(A, NA, sortedLists4[i]);
    } 

    // Se llenan las celdas vacías con -1
    for (int i = NM; i < f * c; ++i)
    {
        SDDS<int>::insert(M,i/c,i%c,-1);
    }
}