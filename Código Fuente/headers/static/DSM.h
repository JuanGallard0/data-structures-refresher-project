template <typename T>
class DSM: public staticDS_2D<T> {
    private:
        T** matrix;
        int nrows, ncols;

    public:
        category getCategory() override {
            return MATRIX;
        }
        void destroy() override {
            for(int i = 0; i < nrows; i++)
                free(*(matrix+i));
            free(matrix);
        }
        bool search(T value) override {
            bool ans = false;
            for(int i = 0; i < nrows*ncols; i++)
                if(matrix[i/ncols][i%ncols] == value){
                    ans = true;
                    break;
                }
            return ans;
        }
        int count(T value) override {
            int cont = 0;
            for(int i = 0; i < nrows*ncols; i++)
                if(matrix[i/ncols][i%ncols] == value) cont++;
            return cont;
        }
        void show(bool verbose) override {
            if(verbose)
                for(int i = 0; i < nrows*ncols; i++)
                    cout << "Element in cell [ " << i/ncols+1 << ", " << i%ncols+1 << " ] is: " << matrix[i/ncols][i%ncols] << "\n";
            else{
                cout << "[\n";
                for(int i = 0; i < nrows; i++){
                    cout << "[ ";
                    for(int j = 0; j < ncols-1; j++) {
                        if (matrix[i][j] == -1)
                            cout << "N/A" << ", ";
                        else
                            cout << i + 1 << "/" << j + 1 << ", ";
                    }
                    if (matrix[i][ncols - 1] == -1)
                        cout << "N/A" << " ]\n";
                    else
                        cout << i + 1 << "/" << ncols << " ]\n";
                }
                cout << "]\n";
            }
        }

        /**
         * *MÉTODO
         * @param Nid:id del nodo actual del Grafo
         * Método para navegar dentro del nodo especificado por Nid de la Matriz
         */
        void navigate(int Nid) {
            if(matrix == NULL){
                cout << "La matriz esta vacia\n";
                return;
            }

            int option, ff, cc;

            do {
                option = 0; 

                cout << "GRAFO G -> ARBOL T -> LISTA DL -> NODO {" << Nid << "} -> MATRIZ M: " << endl;

                show(false);

                cout << endl; 
                cout << "                  MENU" << endl
                << "1- Seleccionar un nodo" << endl
                << "2- Regresar a la etapa anterior" << endl
                << "SELECCION: ";
                cin >> option; 

                switch (option) {
                    case 1:
                        cout << "Numero de fila: ";
                        cin >> ff;
                        cout << "Numero de columna: ";
                        cin >> cc;
                        cout << "<============================================================>" << endl;

                        // Se asume que se empieza a contar desde 1 para facilidad al usuario
                        if(0 < ff and ff <= nrows and 0 < cc and cc <= ncols) {
                            ((DSA<int>*)matrix[ff-1][cc-1])->navigate( (ncols * (ff - 1)) + (cc - 1) );
                        } 
                        else {
                            cout << "La operacion es imposible" << endl;
                        }
                        cout << "<============================================================>" << endl;
                        break;
                    case 2:
                        cout << "<============================================================>" << endl;
                        break;
                    default:
                        cout << "Esa opcion no existe" << endl;
                        cout << "<============================================================>" << endl;
                } 
            } while(option != 2);
        }

        void create(Data dim) override {
            nrows = dim.n;
            ncols = dim.m;
            matrix = (T**) malloc(sizeof(T*)*nrows);
            for(int i = 0; i < nrows; i++)
                *(matrix+i) = (T*) malloc(sizeof(T)*ncols);
        }
        Data extension() override {
            Data dim;
            dim.n = nrows; dim.m = ncols;
            return dim;
        }
        void insert(Data pos, T value) override {
            matrix[pos.n][pos.m] = value;
        }
        T extract(Data pos) override {
            return matrix[pos.n - 1][pos.m - 1];
        }

        void addInfo(string chain) {
            string subChain = "";
            cout << "subcadena de matriz: " + chain + "\n" << endl;
            
            if(regex_match(chain, regex("^[0-9]{4}N{2}"))) {
                //TODO Sobre escribir el arbol completo
                string newName = "";
                cout << "SOBREESCRIBIENDO NAME" << endl
                << "Introduzca un Nombre: ";
                cin >> newName;

                for(int i = 0; i < nrows; i++){
                    for(int j = 0; j < ncols-1; j++){
                        if (matrix[i][j] != -1)
                            ((DSA<int>*)matrix[i][j])->addInfo_aux(newName, 4);
                    }
                }
                return;
            }
            if(regex_search(chain, regex("^[0-9]{4}."))) {
                cout << "ID de Matriz valido\n";
                Data dim;
                dim.n = stoi(chain.substr(0, 2));
                subChain = chain.substr(2, chain.size() - 2);
                dim.m = stoi(subChain.substr(0, 2));
                subChain = subChain.substr(2, chain.size() - 2);

                ((DSA<int>*)extract(dim))->addInfo(subChain);
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

            if(regex_match(chain, regex("^[0-9]{4}N{2}"))) {
                //Eliminar la Matrix completo
                cout << "ID de Matrix valido\n";
                ID = stoi(chain.substr(0, 2));

                for(int i = 0; i < nrows; i++){
                    for(int j = 0; j < ncols-1; j++){
                        if (matrix[i][j] != -1)
                            ((DSA<int>*)matrix[i][j])->removeInfo_aux();
                    }
                }
                return;
            }
            if(regex_search(chain, regex("^[0-9]{4}."))) {
                cout << "ID de Matrix valido\n";
                Data dim;
                dim.n = stoi(chain.substr(0, 2));
                subChain = chain.substr(2, chain.size() - 2);
                dim.m = stoi(subChain.substr(0, 2));
                subChain = subChain.substr(2, chain.size() - 2);

                ((DSA<int>*)extract(dim))->removeInfo(subChain);
                return;
            }
            else {
                cout << "ID No valido\n";
                return;
            }
        }

        void removeInfo_aux() {
            cout << "Removiendo toda la Matrix\n";
            for(int i = 0; i < nrows; i++){
                for(int j = 0; j < ncols; j++){
                    if (matrix[i][j] != -1)
                        ((DSA<int>*)matrix[i][j])->removeInfo_aux();
                }
            }
            cout << "Liberando la Matrix\n";
            free(matrix);
            return;
        }

        /**
         * @brief Funcion que sobreescribe la informacion al nivel de NAME en toda la Matrix
         * La funcion introducira un nuevo elemento en la estructura
         * 
         * @param element string que contiene el elemento
         * @param pos posicion donde debera sobreescribirse el nuevo elemento
         */
        void addInfo_aux(string element, int pos) {
            cout << "Sobreescribiendo Matrix, con elemento: " + element + " en la posicion " << pos <<" \n" << endl;

            for(int i = 0; i < nrows; i++){
                for(int j = 0; j < ncols; j++){
                    if (matrix[i][j] != -1)
                        ((DSA<int>*)matrix[i][j])->addInfo_aux(element, pos);
                }
            }
            return;
        }
};
