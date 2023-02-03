/**
 * *CLASE
 * Clase de tipo lista enlazada simple para el manejo especializado de cadenas de caracteres
 * Clase implementada especificamente para el tratado de datos provenientes del archivo .csv de dataSets
 * Implementada visto que la librería contenida en el código de clase no parecía compatible con strings de c++ 
 */

// Nodo de lista enlazada simple con datos de tipo string
struct SNode { 
    string data; 
    int pos;
    SNode *next;
};

class LinkedList
{
private:
    // Cabecera de la lista
    SNode* head;
    // Cantidad de elementos insertados en la lista
    int len; 

public:
    // Constructor
    LinkedList()
    {
        head = NULL;
        len = 0;
    }

    // Retornar longitud de la lista
    int length() {
        return len;
    }

    // Verificar si la lista está vacía
    bool isEmpty() {
        if (head == NULL)
            return true;
    }

    // Insertar un nuevo elemento al final de la lista
    void insert(string val)
    {
        SNode* new_node = new SNode;
        new_node->data = val;
        new_node->pos = len;
        new_node->next = NULL;

        if (head == NULL)
            head = new_node;
        else
        {
            new_node->next = head;
            head = new_node;
        }
        len++;
    }

    // Verificar si la lista contiene un nodo que contenga el string val
    bool search(string val)
    {
        SNode* temp = head;
        while(temp != NULL)
        {
            if (temp->data == val)
                return true;
            temp = temp->next;
        }
        return false;
    }

    // Eliminar elemento de la lista
    void remove(string val)
    {
        if (head->data == val)
        {
            delete head;
            head = head->next;
            return;
        }

        if (head->next == NULL)
        {
            if (head->data == val)
            {
                delete head;
                head = NULL;
                return;
            }
            cout << "Value not found!" << endl;
            return;
        }

        SNode* temp = head;
        while(temp->next!= NULL)
        {
            if (temp->next->data == val)
            {
                SNode* temp_ptr = temp->next->next;
                delete temp->next;
                temp->next = temp_ptr;
                return;
            }
            temp = temp->next;
        }

        cout << "Value not found" << endl;
    }

    // Imprimir la lista en la consola
    void display()
    {
        SNode* temp = head;
        while(temp != NULL)
        {
            cout << temp->data << endl;
            temp = temp->next;
        }
        cout << endl;
    }

    // Extraer el elemento de la lista posicionado en la posición pos
    string extract(int pos) {
        SNode* temp = head;
        for (int i = 0; i < pos; ++i)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    /**
     * *MÉTODO
     * @param arr:arreglo de strings
     * Este método solo utiliza la cabecera de la lista, es decir que espera ser utilizado con una lista con un solo elemento
     * Método para separar 5 substrings separados por una coma dentro del string contenido en la cabecera de la lista y guardarlos en el arreglo arr
     * El arreglo es retornado por referencia
     */
    void extractWords(string* arr) {
        stringstream ss(head->data);
        for (int i = 0; i < 5; ++i)
        {
            getline(ss, arr[i], ',');
        }
    }

    /**
     * *MÉTODO
     * @param level:entero que representa el nivel de la estructura del que se busca extraer los elementos unicos
     * Método que recorre la lista y busca los elementos unicos contenidos en el nivel especificado por level y los guarda en una lista
     * Niveles: (0 Eras) (1 Reinos) (2 Razas) (3 Nombres) (4 Armas)
     * @return lista que contiene los elementos unicos
     */
    LinkedList uniqueElements(int level) {
        LinkedList newList;
        SNode* temp = head;
        string arr[5];
        while(temp != NULL)
        {
            // uso de stringstream
            stringstream ss(temp->data);
            for (int i = 0; i < 5; ++i)
            {
                // guardar cada elemento separado por una coma en una celda del arreglo arr
                getline(ss, arr[i], ',');
            }
            // si la lista newList no contiene el elemento extraido especifico del nivel, insertarlo
            if (!newList.search(arr[level - 1]))
                newList.insert(arr[level - 1]);
            temp = temp->next;
        }
        return newList;
    }

    /**
     * *MÉTODO
     * @param lists:arreglo de listas sorteadas
     * @param UE:lista de elementos unicos
     * @param level:entero que representa el nivel de la estructura del que se busca extraer los elementos unicos
     * Método para crear diferentes listas sorteadas, es decir que cada una ha sido separada según un el nivel especificado
     * Niveles: (0 Eras) (1 Reinos) (2 Razas) (3 Nombres) (4 Armas)
     * Retorna un arreglo con las listas sorteadas por referencia
     */
    void sort(LinkedList* lists, LinkedList UE, int level) {
        int size = UE.length();
        SNode* temp = head;
        string arr[5];
        while(temp != NULL)
        {
            stringstream ss(temp->data);
            for (int i = 0; i < 5; ++i)
            {
                getline(ss, arr[i], ',');
            }
            for (int i = 0; i < size; ++i)
            {
                if (UE.extract(i) == arr[level - 1])
                    lists[i].insert(temp->data);
            }
            temp = temp->next;
        }
    }
};