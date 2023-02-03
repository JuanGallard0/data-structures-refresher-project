template <typename T>
class DSDL: public dynamicDS<T>,public insertable<T>,public measurable,public identifiable<T>,public positionable<T>,public reversible {
    private:
        NodeDL<T>* L;

        void* createNode() override {
            return malloc(sizeof(NodeDL<T>));
        }

    public:
        category getCategory() override {
            return DOUBLE_LINKED_LIST;
        }
        void destroy() override {
            NodeDL<T>* temp;
            while(L != NULL){
                temp = L;
                L = L->next;
                free(temp);
            }
        }
        bool search(T value) override {
            bool ans = false;
            NodeDL<T>* Lcopy = L;
            while(Lcopy != NULL){
                if(Lcopy->data == value){
                    ans = true;
                    break;
                }
                Lcopy = Lcopy->next;
            }
            return ans;
        }
        int count(T value) override {
            int cont = 0;
            NodeDL<T>* Lcopy = L;
            while(Lcopy != NULL){
                if(Lcopy->data == value) cont++;
                Lcopy = Lcopy->next;
            }
            return cont;
        }
        void show(bool verbose) override {
            if(L == NULL){
                cout << "La lista está vacía.\n";
                return;
            }
            NodeDL<T>* Lcopy = L;
            if(verbose){
                int index = 1;
                while(Lcopy != NULL){
                    cout << "Element #" << index << " is: " << Lcopy->data << "\n";
                    index++;
                    Lcopy = Lcopy->next;
                }       
            }else{
                while(Lcopy != NULL){
                    cout << Lcopy->data << " <-> ";
                    Lcopy = Lcopy->next;
                }
                cout << "NULL\n";
            }
        }

        /**
         * *MÉTODO
         * @param Nid:id del nodo actual del Grafo
         * Método para navegar dentro del nodo especificado por Nid de la Lista Doble
         */
        void navigate(int Nid) {
            if(L == NULL){
                cout << "La lista esta vacia\n";
                return;
            }

            NodeDL<T>* LCopy = L;

            int option;  

            do {
                option = 0; 

                cout << "GRAFO G -> ARBOL T -> NODO {" << Nid << "} -> LISTA DL: " << endl;

                if (LCopy->prev != NULL)
                {
                    cout << "Previo {" << LCopy->prev->id << "}\t";
                }
                else {cout << "Previo {NULL}\t";};
                cout << "Nodo {" << LCopy->id << "}\t"; 
                if (LCopy->next != NULL)
                {
                    cout << "Siguiente {" << LCopy->next->id << "}\t";
                }
                else {cout << "Siguiente {NULL}\t";};

                cout << endl; 
                cout << "                  MENU" << endl
                << "1- Ir al nodo previo" << endl
                << "2- Ir al nodo siguiente" << endl 
                << "3- Explorar el contenido del nodo actual" << endl
                << "4- Regresar a la etapa anterior" << endl
                << "SELECCION: ";
                cin >> option; 

                switch (option) {
                    case 1:
                        if (LCopy->prev != NULL)
                            LCopy = LCopy->prev;
                        else
                            cout << "La operacion es imposible" << endl;
                        cout << "<============================================================>" << endl;
                        break;
                    case 2:
                        if (LCopy->next != NULL)
                            LCopy = LCopy->next;
                        else
                            cout << "La operacion es imposible" << endl;
                        cout << "<============================================================>" << endl;
                        break;      
                    case 3:
                        cout << "<============================================================>" << endl;
                        ((DSM<int>*)LCopy->data)->navigate(LCopy->id);
                        break;
                    case 4:
                        cout << "<============================================================>" << endl;
                        break;
                    default:
                        cout << "Esa opcion no existe" << endl;
                        cout << "<============================================================>" << endl;
                } 
            } while(option != 4);
        }

        Node<T>* getRoot(){
            return L;
        }
        void create() override {
            L = NULL;
        }

        void insert(T value) override {
            //Se asume inserción al inicio de la lista
            NodeDL<T>* temp = (NodeDL<T>*) createNode();
            temp->data = value;
            temp->prev = NULL;
            if(L == NULL) temp->next = NULL;
            else{
                L->prev = temp;
                temp->next = L;
            }
            L = temp;
        }
        void insert_id(int id, T value) override {
            //Se asume inserción al inicio de la lista
            NodeDL<T>* temp = (NodeDL<T>*) createNode();
            temp->id = id;
            temp->data = value;
            temp->prev = NULL;
            if(L == NULL) temp->next = NULL;
            else{
                L->prev = temp;
                temp->next = L;
            }
            L = temp;
        }

        int extension() override {
            int cont = 0;
            NodeDL<T>* Lcopy = L;
            while(Lcopy != NULL){
                cont++;
                Lcopy = Lcopy->next;
            }
            return cont;
        }

        void insert(int pos, T value) override {
            //Se asume pre-validación de una posición válida
            NodeDL<T>* temp = (NodeDL<T>*) createNode();
            temp->data = value;

            NodeDL<T>* Lcopy = L;
            for(int i = 0; i < pos-1; i++) Lcopy = Lcopy->next;

            temp->prev = Lcopy;
            temp->next = Lcopy->next;
            Lcopy->next->prev = temp;
            Lcopy->next       = temp;
        }
        T extract(int pos) override {
            //Se asume pre-validación de una posición válida
            NodeDL<T>* Lcopy = L;
            for(int i = 0; i < pos - 1; i++) { 
                Lcopy = Lcopy->next;
            }
            return Lcopy->data;
        }

        void reverse() override {
            NodeDL<T>* new_one = NULL;
            NodeDL<T>* Lcopy = L;
            NodeDL<T>* temp;
            while(Lcopy != NULL){
                temp = (NodeDL<T>*) createNode();
                temp->data = Lcopy->data;
                temp->prev = NULL;
                if(new_one == NULL) temp->next = NULL;
                else{
                    new_one->prev = temp;
                    temp->next = new_one;
                }
                new_one = temp;
                Lcopy = Lcopy->next;
            }
            destroy();
            L = new_one;
        }

        void addInfo(string chain) {
		    int ID = 0;
            string subChain = "";
            cout << "subcadena de Lista doble: " + chain + "\n" << endl;
            
            if(regex_match(chain, regex("^[0-9]{2}N{6}"))) {
                //TODO Sobre escribir el arbol completo
                string newRace = "";
                cout << "SOBREESCRIBIENDO RACE" << endl
                << "Introduzca una Raza: ";
                cin >> newRace;

                NodeDL<T>* Lcopy = L;
                while(Lcopy != NULL){
                    ((DSM<int>*)Lcopy->data)->addInfo_aux(newRace, 3);
                    Lcopy = Lcopy->next;
                }
                return;
            }
            if(regex_search(chain, regex("^[0-9]{2}."))) {
                cout << "ID de Lista doble valido\n";
                ID = stoi(chain.substr(0, 2));

                subChain = chain.substr(2, chain.size() - 2);
                ((DSM<int>*)extract(ID))->addInfo(subChain);
                return;
            }
            else {
                cout << "ID No valido\n";
                return;
            }
        }

        void removeInfo(string chain) {
            string subChain = "";
            int ID = 0;

            if(regex_match(chain, regex("^[0-9]{2}N{6}$"))) {
                //Eliminar la Lista Doble completo
                cout << "ID de Lista Doble valido\n";
                ID = stoi(chain.substr(0, 2));
                ((DSM<int>*)extract(ID))->removeInfo_aux();
                return;
            }
            if(regex_search(chain, regex("^[0-9]{2}."))) {
                cout << "ID de Lista Doble valido\n";
                ID = stoi(chain.substr(0, 2));

                subChain = chain.substr(2, chain.size() - 2);


                ((DSM<int>*)extract(ID))->removeInfo(subChain);
                return;
            }
            else {
                cout << "ID No valido\n";
                return;
            }
        }

        void removeInfo_aux() {
            cout << "Removiendo toda la Lista Doble\n";
            NodeDL<T>* Lcopy = L;
            while(Lcopy != NULL){
                ((DSM<int>*)Lcopy->data)->removeInfo_aux();
                Lcopy = Lcopy->next;
            }
            cout << "Liberando la Lista Doble\n";
            free(L);
            return;
        }

        /**
         * @brief Funcion que sobreescribe la informacion al nivel de RACE en toda la Lista Doble
         * La funcion introducira un nuevo elemento en la estructura
         * 
         * @param element string que contiene el elemento
         * @param pos posicion donde debera sobreescribirse el nuevo elemento
         */
        void addInfo_aux(string element, int pos) {
            cout << "Sobreescribiendo Lista Doble, con elemento: " + element + " en la posicion " << pos <<" \n" << endl;

            NodeDL<T>* Lcopy = L;
            while(Lcopy != NULL){
                ((DSM<int>*)Lcopy->data)->addInfo_aux(element, pos);
                Lcopy = Lcopy->next;
            }
            return;
        }
};
