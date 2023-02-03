template <typename type>
class DST: public dynamicDS<type>,public insertable<type>, public identifiable<type>,public measurable {
    private:
        NodeT<type>* T;

        void* createNode() override {
            return malloc(sizeof(NodeT<type>));
        }

        int height(NodeT<type>* tree){
            if(tree == NULL) return 0;
            return max( 1 + height(tree->left) , 1 + height(tree->right) );
        }
        void insert_aux(NodeT<type>* tree, NodeT<type>* node){
            if(node->id <= tree->id)
                if(tree->left == NULL){
                    node->parent = tree;
                    tree->left = node;
                }else insert_aux(tree->left,node);
            else
                if(tree->right == NULL){
                    node->parent = tree;
                    tree->right = node;
                }else insert_aux(tree->right,node);
        }
        void destroy_aux(NodeT<type>* tree){
            if(tree == NULL) return;
            destroy_aux(tree->left);
            destroy_aux(tree->right);
            free(tree);
        }
        bool search_aux(NodeT<type>* tree, type value){
            if(tree == NULL) return false;
            if(tree->data == value) return true;
            return search_aux(tree->left,value) || search_aux(tree->right,value);
        }
        type extract_alt(NodeT<type>* tree, int id) {
            if(tree == NULL)
                return 0;
            else if(id < tree->id)
                return extract_alt(tree->left, id);
            else if(id > tree->id)
                return extract_alt(tree->right, id);
            else 
                return tree->data;
        }
        int count_aux(NodeT<type>* tree, type value){
            if(tree == NULL) return 0;
            return ((tree->data == value)?1:0) + count_aux(tree->left,value) + count_aux(tree->right,value);
        }
        void show_aux(NodeT<type>* tree){
            if(tree == NULL){ cout << " NULL "; return; }
            cout << "[ " << tree->data << " ";
            show_aux(tree->left);
            show_aux(tree->right);
            cout << "]";
        }
        void overrideInfo(NodeT<type>* tree, string element, int pos){
            if(tree == NULL){ return; }
            overrideInfo(tree->left, element, pos);
            overrideInfo(tree->right, element, pos);
            ((DSDL<int>*)tree->data)->addInfo_aux(element, pos);
        }
        void deleteInfo(NodeT<type>* tree){
            if(tree == NULL){ return; }
            deleteInfo(tree->left);
            deleteInfo(tree->right);
            ((DSDL<int>*)tree->data)->removeInfo_aux();
            return;
        }
        void show_aux_verbose(NodeT<type>* tree, int cont){
            if(tree == NULL){
                cout << string(cont,'\t') << "Hijo nulo.\n";
                return;
            }
            cout << string(cont,'\t') << "Padre: " << tree->data << ".\n";
            cout << string(cont,'\t') << "Hijo izquierdo:\n";
            show_aux_verbose(tree->left,cont+1);
            cout << string(cont,'\t') << "Hijo derecho:\n";
            show_aux_verbose(tree->right,cont+1);
        }

    public:
        category getCategory() override {
            return BINARY_SEARCH_TREE;
        }
        void destroy() override {
            destroy_aux(T);
            T == NULL;
        }
        bool search(type value) override {
            return search_aux(T,value);
        }
        int count(type value) override {
            return count_aux(T,value);
        }
        void show(bool verbose) override {
            //Se implementa recorrido Pre-Order
            if(T == NULL){
                cout << "El árbol está vacío.\n";
                return;
            }
            if(verbose) show_aux_verbose(T,0);
            else{ show_aux(T); cout << "\n"; }
        }
        
        /**
         * *MÉTODO
         * @param Nid:id del nodo actual del Grafo
         * Método para navegar dentro del nodo especificado por Nid del Árbol
         */
        void navigate(int Nid) {
            if(T == NULL){
                cout << "El árbol está vacío.\n";
                return;
            }

            NodeT<type>* TCopy = T;

            int option, direction;   

            do {
                option = 0, direction = 0;

                cout << "GRAFO G -> NODO {" << Nid << "} -> ARBOL T: " << endl;

                cout << "Nodo {" << TCopy->id << "} " << endl; 
                if (TCopy->left != NULL)
                {
                    cout << "Izquierda {" << TCopy->left->id << "}\t";
                }
                else {cout << "Izquierda {NULL}\t";};
                if (TCopy->right != NULL)
                {
                    cout << "Derecha {" << TCopy->right->id << "} " << endl;
                }
                else {cout << "Derecha {NULL}" << endl;};

                cout << endl; 
                cout << "                  MENU" << endl
                << "1- Subir en el arbol" << endl
                << "2- Bajar en el arbol" << endl 
                << "3- Explorar el contenido del nodo actual" << endl
                << "4- Regresar a la etapa anterior" << endl
                << "SELECCION: ";
                cin >> option; 

                switch (option) {
                    case 1:
                        if (TCopy->parent != NULL)
                            TCopy = TCopy->parent;
                        else
                            cout << "La operacion es imposible" << endl;
                        cout << "<============================================================>" << endl;
                        break;
                    case 2:
                        cout << "Direccion: " << endl
                        << "1- Izquierda" << endl
                        << "2- Derecha" << endl
                        << "SELECCION: ";
                        cin >> direction;
                        switch (direction) {
                            case 1: 
                                if (TCopy->left != NULL)
                                    TCopy = TCopy->left;
                                else
                                cout << "La operacion es imposible" << endl;
                                break;
                            case 2: 
                                if (TCopy->right != NULL)
                                    TCopy = TCopy->right;
                                else
                                    cout << "La operacion es imposible" << endl;
                                break;
                        }
                        cout << "<============================================================>" << endl;
                        break;
                    case 3:
                        cout << "<============================================================>" << endl;
                        ((DSDL<int>*)TCopy->data)->navigate(TCopy->id);
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

        Node<type>* getRoot(){
            return T;
        }
        void create() override {
            T = NULL;
        }

        void insert(type value) override {
            //Se asume Binary Search Tree
            NodeT<type>* temp = (NodeT<type>*) createNode();
            temp->data = value;
            temp->left   = NULL;
            temp->right  = NULL;
            if(T == NULL){
                temp->parent = NULL;
                T = temp;
            }else insert_aux(T,temp);
        }

        void insert_id(int id, type value) override {
            //Se asume Binary Search Tree
            NodeT<type>* temp = (NodeT<type>*) createNode();
            temp->id = id;
            temp->data = value;
            temp->left   = NULL;
            temp->right  = NULL;
            if(T == NULL){
                temp->parent = NULL;
                T = temp;
            }else insert_aux(T,temp);
        }

        int extension() override {
            return height(T);
        }

        type extract(NodeT<type>* tree, int id) {
            return extract_alt(tree, id);
        }

        void addInfo(string chain) {
		    int ID = 0;
            string subChain = "";
            cout << "subcadena Arbol: " + chain + "\n" << endl;
            
            if(regex_match(chain, regex("^[0-9]{2}N{8}"))) {
                //TODO Sobre escribir el arbol completo
                string newRealm = "";
                cout << "SOBREESCRIBIENDO REALM" << endl
                << "Introduzca un Reino: ";
                cin >> newRealm;

                overrideInfo(T, newRealm, 2);
                return;
            }
            if(regex_search(chain, regex("^[0-9]{2}."))) {
                cout << "ID de Arbol valido\n";
                ID = stoi(chain.substr(0, 2));

                subChain = chain.substr(2, chain.size() - 2);
                if(extract_alt(T, ID) != 0){
                    cout << "Se encontro con el ID proporcionado \n";
                    ((DSDL<int>*)extract(T, ID))->addInfo(subChain);
                }
                else
                    cout << "ERROR";
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

            if(regex_match(chain, regex("^[0-9]{2}N{8}$"))) {
                //Eliminar el Arbol completo
                cout << "ID de Arbol valido\n";
                ID = stoi(chain.substr(0, 2));
                ((DSDL<int>*)extract_alt(T, ID))->removeInfo_aux();
                return;
            }
            if(regex_search(chain, regex("^[0-9]{2}."))) {
                cout << "ID de Arbol valido\n";
                ID = stoi(chain.substr(0, 2));

                subChain = chain.substr(2, chain.size() - 2);

                ((DSDL<int>*)extract_alt(T, ID))->removeInfo(subChain);
                return;
            }
            else {
                cout << "ID No valido\n";
                return;
            }
        }

        void removeInfo_aux() {
            cout << "Removiendo todo el Arbol\n";
            deleteInfo(T);
            cout << "Liberando el Arbol\n";
            free(T);
            return;
        }

        /**
         * @brief Funcion que sobreescribe la informacion al nivel de REALM en toda el Arbol
         * La funcion introducira un nuevo elemento en la estructura
         * 
         * @param element string que contiene el elemento
         * @param pos posicion donde debera sobreescribirse el nuevo elemento
         */
        void addInfo_aux(string element, int pos) {
            cout << "Nuevo elemento a guardar: " + element + " en la posicion " << pos <<" \n" << endl;

            overrideInfo(T, element, pos);
            return;
        }
};
