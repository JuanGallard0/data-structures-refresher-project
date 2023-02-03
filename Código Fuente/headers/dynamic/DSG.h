template <typename T>
class DSG: public dynamicDS<T>,public measurable,public positionable<T> {
    private:
        NodeG<T>* G;

        void* createNode() override {
            return malloc(sizeof(NodeG<T>));
        }
    public:
        category getCategory() override {
            return GRAPH;
        }
        void destroy() override {
            NodeG<T>* temp;
            NodeSL<NodeG<T>*>* L;
            NodeSL<NodeG<T>*>* tempL;
            while(G != NULL){
                temp = G;
                L = temp->connections;
                while(L != NULL){
                    tempL = L;
                    L = L->next;
                    free(tempL);
                }
                G = G->next;
                free(temp);
            }
        }
        bool search(T value) override {
            bool ans = false;
            NodeG<T>* Gcopy = G;
            while(Gcopy != NULL){
                if(Gcopy->data == value){
                    ans = true;
                    break;
                }
                Gcopy = Gcopy->next;
            }
            return ans;
        }
        int count(T value) override {
            int cont = 0;
            NodeG<T>* Gcopy = G;
            while(Gcopy != NULL){
                if(Gcopy->data == value) cont++;
                Gcopy = Gcopy->next;
            }
            return cont;
        }
        void show(bool verbose) override {
            if(G == NULL){
                cout << "El grafo está vacío.\n";
                return;
            }
            NodeG<T>* Gcopy = G;
            NodeSL<NodeG<T>*>* L;
            if(verbose)
                while(Gcopy != NULL){
                    cout << "Nodo #" << Gcopy->id << ":\n\tDatos: " << Gcopy->data << "\n\tConexiones:\n";
                    L = Gcopy->connections;
                    int index = 1;
                    while(L != NULL){
                        cout << "\tConexión #" << index << " corresponde al Nodo #" << L->data->id << "\n";
                        index++;
                        L = L->next;
                    }
                    Gcopy = Gcopy->next;
                }
            else{
                while(Gcopy != NULL){
                    cout << "( " << Gcopy->id << " , " << Gcopy->data << " , [ ";
                    L = Gcopy->connections;
                    while(L != NULL){
                        cout << L->data->id << "->";
                        L = L->next;
                    }
                    cout << "NULL ] )" << " -> ";
                    Gcopy = Gcopy->next;
                }
                cout << "NULL\n";
            }
        }

        /**
         * *MÉTODO
         * @param Nid:id del nodo actual del Grafo
         * Método para navegar dentro del nodo especificado por Nid del Grafo
         */
        void navigate(int Nid) {
            if(G == NULL){
                cout << "El grafo está vacío.\n";
                return;
            }

            NodeG<T>* Gcopy = G;
            while (Gcopy->id != 1) {
                Gcopy = Gcopy->next;
            }

            NodeSL<NodeG<T>*>* L;
            int option, id;
            bool connectionExists;

            do {
                option = 0, id = -1;
                connectionExists = false;

                cout << "GRAFO G:" << endl 
                << "Nodo {" << Gcopy->id << "} " << endl
                << "Conexiones: ";

                L = Gcopy->connections;
                while(L != NULL){
                    cout << "{" << L->data->id << "} ";
                    L = L->next;
                }
                L = Gcopy->connections;
                
                cout << endl;
                cout << "                  MENU" << endl
                << "1- Moverse a uno de los nodos conectados al sistema actual" << endl
                << "2- Explorar el contenido del nodo actual" << endl 
                << "3- Regresar a la etapa anterior " << endl
                << "SELECCION: ";
                cin >> option;
                
                switch (option) {
                    case 1:
                        cout << "Moverse a: ";
                        cin >> id;

                        while(L != NULL){
                            if (L->data->id == id)
                            {
                                Gcopy = L->data;
                                connectionExists = true;
                            }
                            L = L->next;
                        }
                        if (!connectionExists)
                            cout << "Conexion ingresada no existe" << endl;
                            cout << "<============================================================>" << endl;
                        break;
                    case 2:
                        cout << "<============================================================>" << endl;
                        ((DST<int>*)Gcopy->data)->navigate(Gcopy->id);
                        break;
                    case 3:
                        cout << "<============================================================>" << endl;
                        break;
                    default:
                        cout << "Esa opcion no existe" << endl;
                        cout << "<============================================================>" << endl;
                } 
            } while(option != 3);
        }

        Node<T>* getRoot(){
            return G;
        }
        void create() override {
            G = NULL;
        }
        
        int extension() override {
            int cont = 0;
            NodeG<T>* Gcopy = G;
            while(Gcopy != NULL){
                cont++;
                Gcopy = Gcopy->next;
            }
            //Se puede añadir contar el número de aristas
            return cont;
        }

        void insert(int id, T value) override {
            //La posición en el listado principal no es relevante.
            //Por simplicidad se inserta al inicio.
            NodeG<T>* temp = (NodeG<T>*) createNode();
            temp->entry = false;
            temp->id = id;
            temp->data = value;
            temp->connections = NULL;
            if(G == NULL){
                temp->entry = true;
                temp->next = NULL;
            }else temp->next = G;
            G = temp;
        }

        T extract(int id) override {
            NodeG<T>* Gcopy = G;
            while(Gcopy != NULL){
                if(Gcopy->id == id) break;
                Gcopy = Gcopy->next;
            }
            return Gcopy->data;
        }

        /**
         * @brief Funcion invocada para agregar informacion en la estructura completa, dependiendo del ID
         * Proporcionado por el usuario la funcion sobreescribira un unico personaje especifico o todos los elementos
         * Debajo de un nivel.
         * 
         */
        void addInfo() {
		    string chain = "";
            string subChain = "";
		    int ID = 0;
            cout << "    AGREGAR INFORMACION" << endl
            << "Introduzca la cadena de ID: ";
            cin >> chain;

            //Regular Expression que comprueba si el formato introducido es invalido
            if (!regex_match(chain, regex("([0-9]{2}|N{2}){6}"))) {
                cout << "Formato de cadena invalido." << endl;
                return;
            }

            /**Regular Expression que comprueba si la cadena cumple con ID de Grafo seguido de N's
            * Si el formato se cumple, la funcion sobre escribe toda la estructura debajo del Nodo indicado por el Usuario
            */
            if(regex_match(chain, regex("^[0-9]{2}N{10}$"))) {
                //TODO Sobre escribir el arbol completo
                ID = stoi(chain.substr(0, 2));
                string newAge = "";
                cout << "SOBREESCRIBIENDO AGE" << endl
                << "Introduzca una Era: ";
                cin >> newAge;

                ((DST<int>*)extract(ID))->addInfo_aux(newAge, 1);
                return;
            }

            /**Regular Expression que comprueba si la cadena cumple con ID de Grafo
            * Si el formato se cumple, se extrae una subcadena conteniendo los ID's de las estructuras mas profundas
            * Y se delega a la siguiente estructura el procesamiento de la subcadena
            */
            if(regex_search(chain, regex("^[0-9]{2}."))) {
                cout << "ID de grafo valido\n";
                ID = stoi(chain.substr(0, 2));

                subChain = chain.substr(2, chain.size() - 2);

                ((DST<int>*)extract(ID))->addInfo(subChain);
                return;
            }
            else {
                cout << "ID No valido\n";
                return;
            }
        }

        /**
         * @brief Funcion invocada para modificar informacion, dependiendo del ID proporcionado por el usuario
         * La funcion sobreescribira un unico personaje especifico.
         * 
         * Si existe un nodo con el ID valido, se delega a la siguiente estructura procesar la subcadena
         */
        void modifyInfo() {
            string chain = "";
            string subChain = "";
		    int ID = 0;
            cout << "    AGREGAR INFORMACION" << endl
            << "Introduzca la cadena de ID: ";
            cin >> chain;

            //Si la cadena introducida por el usuario contiene unicamente N, es invalido
            if(regex_match(chain, regex("N{12}"))) {
                //TODO Sobre escribir el arbol completo
                cout << "El primer ID no puede ser NN" << endl;
                return;
            }

            //Si la cadena contiene 12 digitos, es una cadena valida y se procede a procesar los IDs
            if(regex_search(chain, regex("^[0-9]{12}"))) {
                cout << "ID de grafo valido\n";
                ID = stoi(chain.substr(0, 2));

                subChain = chain.substr(2, chain.size() - 2);

                ((DST<int>*)extract(ID))->addInfo(subChain);
                return;
            }
            else {
                cout << "ID No valido\n";
                return;
            }
        }

        /**
         * @brief Funcion que elimina informacion almacenada en la estructura. Si el ID es valido la funcion determina si es necesario
         * Eliminar toda la estructura desde este nivel o si es necesario delegarle a la siguiente estructura el eliminado.
         *  
         */
        void removeInfo() {
            string chain = "";
            string subChain = "";
            int ID = 0;
            cout << "    REMOVER INFORMACION" << endl
            << "Introduzca la cadena de ID: ";
            cin >> chain;

            if(regex_match(chain, regex("^[0-9]{2}N{10}$"))) {
                //Eliminar el Grafo completo
                cout << "ID de grafo valido\n";
                ID = stoi(chain.substr(0, 2));
                ((DST<int>*)extract(ID))->removeInfo_aux();
                cout << "Se libero la estructura completa!!!\n";
                return;
            }
            if(regex_search(chain, regex("^[0-9]{2}."))) {
                cout << "ID de grafo valido\n";
                ID = stoi(chain.substr(0, 2));

                subChain = chain.substr(2, chain.size() - 2);

                ((DST<int>*)extract(ID))->removeInfo(subChain);
                return;
            }
            else {
                cout << "ID No valido\n";
                return;
            }
        }

        void removeAll(){
            ((DST<int>*)extract(1))->removeInfo_aux();
            ((DST<int>*)extract(2))->removeInfo_aux();
            ((DST<int>*)extract(3))->removeInfo_aux();
            ((DST<int>*)extract(4))->removeInfo_aux();
            ((DST<int>*)extract(5))->removeInfo_aux();
            ((DST<int>*)extract(6))->removeInfo_aux();
            ((DST<int>*)extract(7))->removeInfo_aux();
            ((DST<int>*)extract(8))->removeInfo_aux();
        }
};
