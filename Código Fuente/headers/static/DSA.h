template <typename T>
class DSA: public staticDS_1D<T>,public measurable,public positionable<T>,public reversible {
    private:
        T* array;
        int size;

    public:
        category getCategory() override {
            return ARRAY;
        }
        void destroy() override {
            free(array);
        }
        bool search(T value) override {
            bool ans = false;
            for(int i = 0; i < size; i++)
                if(array[i] == value){
                    ans = true;
                    break;
                }
            return ans;
        }
        int count(T value) override {
            int cont = 0;
            for(int i = 0; i < size; i++)
                if(array[i] == value)
                    cont++;
            return cont;
        }
        void show(bool verbose) override {
            if(verbose)
                for(int i = 0; i < size; i++)
                    cout << "Element #" << i+1 << " is: " << i + 1 << "\n";
            else{
                cout << "[ ";
                for(int i = 0; i < size-1; i++)
                    cout << i + 1 << ", ";
                cout << size << " ]\n";
            }
        }

        /**
         * *MÉTODO
         * @param Nid:id del nodo actual del Grafo
         * Método para navegar dentro del nodo especificado por Nid del Arreglo
         */
        void navigate(int Nid) {
            if(array == NULL){
                cout << "El arreglo esta vacio\n";
                return;
            }

            int option, id;
            bool gud;

            do {
                gud = false;
                option = 0; 

                cout << "GRAFO G -> ARBOL T -> LISTA DL -> MATRIZ M -> NODO {" << Nid << "} -> ARREGLO A: " << endl;

                show(false);

                cout << endl; 
                cout << "                  MENU" << endl
                << "1- Seleccionar un nodo" << endl
                << "2- Regresar a la etapa anterior" << endl
                << "SELECCION: ";
                cin >> option; 

                switch (option) {
                    case 1:
                        cout << "Moverse a: ";
                        cin >> id;
                        if(0 < id and id <= size) {
                            cout << ((Character*)array[id-1])->era << endl;
                            cout << ((Character*)array[id-1])->realm << endl;
                            cout << ((Character*)array[id-1])->race << endl;
                            cout << ((Character*)array[id-1])->name << endl;
                            cout << ((Character*)array[id-1])->weapon << endl;
                            cout << "<============================================================>" << endl;
                            gud = true;
                            break;
                        }
                        if (!gud) {
                            cout << "La operacion es imposible" << endl;
                            cout << "<============================================================>" << endl;
                        }
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

        void create(int n) override {
            size = n;
            array = (T*) malloc(sizeof(T)*n);
        }

        int extension() override {
            return size;
        }

        void insert(int pos, T value) override {
            array[pos] = value;
        }
        T extract(int pos) override {
            return array[pos - 1];
        }

        void reverse() override {
            T* array2 = (T*) malloc(sizeof(T)*size);
            for (int i = size-1; i >= 0; i--){
                array2[ size - (i + 1) ] = array[i];
            }
            destroy();
            array = array2;
        }

        /**
         * @brief Funcion que sobreescribe la informacion al nivel de WEAPON en todo el array
         * La funcion unicamente procesara la nueva informacion si el ID recibido es NN ya que estamos al final de la estructura
         * @param chain string que contiene el ID
         */
        void addInfo(string chain) {
		    int ID = 0;
            string subChain = "";
            cout << "subcadena de Array: " + chain + "\n" << endl;
            
            if(regex_match(chain, regex("N{2}"))) {
                //Sobre escribir el Array completo
                string newWeapon = "";
                cout << "SOBREESCRIBIENDO WEAPON" << endl
                << "Introduzca un Arma: ";
                cin >> newWeapon;

                cout << "Existe size y su valor es" << size
                << "Introduzca un Arma: ";

                for(int i = 0; i < size; i++) {
                    ((Character*)array[i])->weapon = newWeapon;
                }
                return;
            }
            if(regex_search(chain, regex("^[0-9]{2}"))) {
                cout << "ID de Array valido\n";
                ID = stoi(chain.substr(0, 2));
                cout << ((Character*)array[ID-1])->era << endl;
                cout << ((Character*)array[ID-1])->realm << endl;
                cout << ((Character*)array[ID-1])->race << endl;
                cout << ((Character*)array[ID-1])->name << endl;
                cout << ((Character*)array[ID-1])->weapon << endl;
                string newAge = "";
                string newRealm = "";
                string newRace = "";
                string newName = "";
                string newWeapon = "";
                int option = 0;
                do
	            {
	            	cout << "              AGREGANDO DATOS" << endl
	            	<< "1- Modificar AGE" << endl
	            	<< "2- Modificar REALM" << endl 
	            	<< "3- Modificar RACE" << endl
	            	<< "4- Modificar NAME" << endl
	            	<< "5- Modificar WEAPON" << endl 
                    << "6- Regresar" << endl
	            	<< "SELECCION: ";
	            	cin >> option;
	            	cout << "<============================================================>" << endl;

	            	switch (option) {
	            		case 1:
                            cout << "Introduzca una Era: ";
                            cin >> newAge;
                            addInfo_aux(newAge, 1);
	            			break;
	            		case 2:
                            cout << "Introduzca un Reino: ";
                            cin >> newRealm;
                            addInfo_aux(newRealm, 2);
	            			break;
	            		case 3:
                            cout << "Introduzca una Raza: ";
                            cin >> newRace;
                            addInfo_aux(newRace, 3);
	            			break;
	            		case 4:
                            cout << "Introduzca un Nombre: ";
                            cin >> newName;
                            addInfo_aux(newName, 4);
	            			break;
	            		case 5:
                            cout << "Introduzca una Arma: ";
                            cin >> newWeapon;
                            addInfo_aux(newWeapon, 5);
                            break;
                        case 6:
	            			cout << "Adios! " << endl;
                            break;
	            		default:
	            			cout << "Esa opcion no existe " << endl;
	            			cout << "<============================================================>" << endl;
	            	}
	            } while (option != 6);

                return;
            }
            else {
                cout << "ID No valido\n";
            }
        }

        void removeInfo(string chain) {
            int ID = 0;
            if(regex_search(chain, regex("^[0-9]{2}$"))) {
                cout << "ID de Array valido\n";
                ID = stoi(chain.substr(0, 2));

                free((Character*)array[ID]);
                return;
            }
            else {
                cout << "ID No valido\n";
            }
        }

        void removeInfo_aux() {
            cout << "Removiendo todo el Array\n";
            for(int i = 0; i < size; i++) {
                free((Character*)array[i]);
            }
            return;
        }

        /**
         * @brief Funcion que sobreescribe la informacion al nivel de WEAPON en todo el array
         * La funcion introducira un nuevo elemento para el personaje
         * 
         * @param element string que contiene el nuevo elemento
         * @param pos posicion donde debera sobreescribirse el nuevo elemento
         */
        void addInfo_aux(string element, int pos) {
            cout << "Sobreescribiendo Array, con elemento: " + element + " en la posicion " << pos <<" \n" << endl;

            switch (pos) {
			case 1:
                for(int i = 0; i < size; i++) {
                    ((Character*)array[i])->era = element;
                }
				break;
			case 2:
				for(int i = 0; i < size; i++) {
                    ((Character*)array[i])->realm = element;
                }
				break;
			case 3:
				for(int i = 0; i < size; i++) {
                    ((Character*)array[i])->race = element;
                }
				break;
			case 4:
				for(int i = 0; i < size; i++) {
                    ((Character*)array[i])->name = element;
                }
				break;
			case 5:
				for(int i = 0; i < size; i++) {
                    ((Character*)array[i])->weapon = element;
                }
				break;
			default:
				cout << "Esa opcion no existe " << endl;
				cout << "<============================================================>" << endl;
		    }
            return;
        }
};
