/**
 * *FUNCIÓN
 * @param DL:puntero hacia Lista Doble
 * @param dataStrings3:Lista que contiene las entradas para uno de los reinos sorteadas anteriormente
 * Función para empezar a llenar la estructura total empezando por el nivel Lista Doble
 * Se crean los nodos de Lista Doble necesarios llenando cada uno con sus estructuras internas
 */
void PopulateDoubleList(DS<int>* DL, LinkedList dataStrings3) {
    /**
     * *BLOQUE
     * Extraer los elementos unicos de las razas contenidos en la lista sorteada por reinos dataStrings3 
     * Crear múltiples listas sorteadas por razas y guardarlas en un arreglo de listas sortedLists3
     * Contar la cantidad de elementos unicos de unique3, es decir la cantidad de nodos de Listas Dobles necesarias y guardar el resultado en NL 
     */
    LinkedList unique3;
    unique3 = dataStrings3.uniqueElements(3);
    LinkedList sortedLists3[unique3.length()];
    dataStrings3.sort(sortedLists3, unique3, 3);
    int NL = unique3.length();

	int f, c, NM;
    // Crear puntero hacia Lista Doble
    DS<int>* M;
    bool id = IDENTIFIABLE;

    /**
     * *ITERACIÓN
     * Se hacen NL iteraciones
     * En cada iteración se crea una Matriz y se guarda como entero (dirección de memoria) en un nuevo nodo de la Lista Doble
     * Índices de cada nodo incrementados de 1 a NL
     * Llamada de función para llenar la matriz recién creada
     */
    for (int i = 1; i <= NL; i++){
        // Es necesario definir la cantidad de elementos de la matriz antes de poder crearla ya que es una estructura estática
        unique3 = sortedLists3[i-1].uniqueElements(4);
        // Cantidad de celdas necesarias NM
        NM = unique3.length();
        // Se calcula el tamaño de una matriz cuadrada de tamaño suficiente para guardar NM celdas
        f = ceil(sqrt(NM));
        c = f;

	    SDDS<int>::create(&M,f,c,MATRIX);
        SDDS<int>::insert(DL, i, (int)M, id);

        PopulateMatrix(M, NM, f, c, sortedLists3[i-1]);
    }
}