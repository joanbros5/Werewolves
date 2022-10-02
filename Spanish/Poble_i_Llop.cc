#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <unistd.h>
using namespace std;

            //CONSTANTES            ---------------------------------------------

const int pocionRevivir = 1;
const int pocionMatar = 1;
const int transformaciones_padre = 1;
const int encantamientos_flautista = 2;
const int vidas_anciano = 2;

const string RolSolitario1 = "sol1";
const string RolSolitario2 = "sol2";
const string RolSolitario3 = "sol3";
const string RolSolitario4 = "sol4";

            //VARIABLES GLOBALES    ---------------------------------------------
struct Persona {
    string nom;
    string rol;
    bool lobo = false;                  //Bool para saber si en ese momento es Lobo
    bool enamorado = false;             //Bool para saber si está enamorado por Cupido
    bool encantado = false;             //Bool para saber si está encantado por el Flautista
    int pocionR = 0;                    //Numero de pociones de la Bruja para revivir
    int pocionM = 0;                    //Numero de pociones de la Bruja para matar
    int transf_padre = 0;               //Numero de transformaciones que puede hacer el padre lobo por partida
    int vidas = 1;                      //Numero de vidas en caso de ser Anciano
    string mentor = "-";                //Nombre del mentor en caso de ser Niño Salvaje
    
    string razon = "-";                 //Razón por la que ha muerto
};

using VS = vector<string>;
using VP = vector<Persona>;

map<int, Persona> personas;
map<int, Persona> muertos;
map<int, Persona> victimas;

int ending = 0;
    /* Lista de endings:
     * -1: Guatafac?
     * 0: No se acaba la partida aún
     * 1: El pueblo gana
     * 2: Los lobos ganan
     * 3: El flautista gana
     * 4: El lobo albino gana
     * 5: El ángel gana
     * 6: Los enamorados y Cupido ganan
     * 7: El/La [RolSolitario1] gana
     * 8: El/La [RolSolitario2] gana
     * 9: El/La [RolSolitario3] gana
     * 10: El/La [RolSolitario4] gana
     */
    
    
int noche = 1;
int dia = 1;

            //FUNCIONES              ---------------------------------------------

//Función para convertir un string a todo minúsculas
string minusculas(string s) {
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] >= 'A' and s[i] <= 'Z') s[i] = s[i] + 32;
    }
    
    return s;
}

//Función para escribir un map de personas.
void escriu(map<int, Persona> & personas, bool lobos, bool vidente) {
    bool fin = false;
    for (auto it = personas.begin(); it != personas.end() and not fin; ++it) {
        
        if (lobos) {
            if (not (it->second).lobo) {
                cout << " - " << (it->second).nom << endl;
                usleep(200000);
            }
        }
        else if(vidente) {
            if (not ((it->second).rol == "vidente")) {
                cout << " - " << (it->second).nom << endl;
                usleep(200000);
            }
        }
        else {
            cout << " - " << (it->second).nom << endl;
            usleep(200000);
        }
        
    }
    cout << endl;
}

//Función para saber si existe un rol llamado "s" en un vector
bool existe(string s, vector<string>& roles) {
    bool trobat = false;
    
    for (int x = 0; x < roles.size() and not trobat; ++x) {
        if (roles[x] == s) trobat = true;
    }
    
    return trobat;
}

//Función para saber si existe un rol llamado "s" en un map de personas
bool existe(string s, map<int, Persona> & personas) {
    bool trobat = false;
    
    for (auto it = personas.begin(); it != personas.end() and not trobat; ++it) {
        if ((it->second).rol == s) trobat = true;
    }
    
    return trobat;
}

//Función que comprueba si quedan lobos
bool haylobos(map<int, Persona> & personas) {
    bool trobat = false;
    
    for (auto it = personas.begin(); it != personas.end() and not trobat; ++it) {
        if ((it->second).lobo) trobat = true;
    }
    
    return trobat;
}

//Función que comprueba si la partida ha terminado
void comprueba_ending(map<int, Persona>& personas) {
    /* Lista de endings:
     * -1: Guatafac?
     * 0: No se acaba la partida aún
     * 1: El pueblo gana
     * 2: Los lobos ganan
     * 3: El flautista gana
     * 4: El lobo albino gana
     * 5: El ángel gana
     * 6: Los enamorados y Cupido ganan
     * 7: El/La [RolSolitario1] gana
     * 8: El/La [RolSolitario2] gana
     * 9: El/La [RolSolitario3] gana
     * 10: El/La [RolSolitario4] gana
     */
    
    //...
    
    //Si no queda nadie vivo, hay empate
    if (personas.empty()) ending = -1;
    
    //No hay lobos, la aldea gana
    else if (not haylobos(personas)) ending = 1;
    
    else {
        //Contar cosas
        int countLobos = 0;
        int countEncantados = 0;
        for (auto it = personas.begin(); it != personas.end(); ++it) {
            if ((it->second).lobo) countLobos++;
            if ((it->second).encantado) countEncantados++;
        }
        
        //PRIORIDAD:
        
        //Lobo albino
        if (personas.size() == 1 and (personas.begin()->second).rol == "lobo_albino") ending = 4;
        //Flautista
        else if (existe("flautista", personas) and countEncantados == personas.size() - 1) ending = 3;
        //Lobos
        else if (countLobos == personas.size()) ending = 2;
    }
    
}

//Función que hace la fase del día: Revelar víctimas y votación si no ha acabado la partida
void fase_dia(map<int, Persona>& personas) {
    
    //Revelar víctimas
    usleep(1000000);
    
    if (victimas.empty()) cout << "Esta noche no ha habido víctimas" << endl;
    else {
        cout << "Esta noche han habido " << victimas.size() << " muertos: " << endl;
        
        usleep(1000000);
        
        //Mostrar víctimas
        auto it = victimas.begin();
        for (it = victimas.begin(); it != victimas.end(); ++it) {
            cout << (it->second).nom << " - " << (it->second).rol << " - " << (it->second).razon << endl;
            usleep(1500000);
            
            //Si muere el cazador, otro muere
            if ((it->second).rol == "cazador") {
                bool cadena = true;
                
                while (cadena) {
                
                    cout << "El cazador se lleva a alguien consigo:" << endl;
                    escriu(personas, false, false);
                    
                    string cazado;
                    cin >> cazado;
                    bool acaba = false;
                    for (auto it = personas.begin(); it != personas.end() and not acaba; ++it) {
                        if ((it->second).nom == cazado) {
                            (it->second).razon = "Disparado por el cazador";
                            cout << (it->second).nom << " - " << (it->second).rol << " - " << (it->second).razon << endl;
                            if ((it->second).rol != "cazador") cadena = false;
                            personas.erase(it);
                            acaba = true;
                            usleep(1500000);
                        }
                    }
                }
            }
            
            auto it2 = personas.find(it->first);
            personas.erase(it2);
        }
        
        //Limpiar víctimas
        victimas.erase(victimas.begin(), victimas.end());
    }
    usleep(200000);
    cout << endl;
    
    //Si el Anciano ha muerto por el pueblo, pierden poderes, else pierde 1 vida
    //...
    
    comprueba_ending(personas);
    if (ending) return;
    
    
    //El oso gruñe?
    //...
    for (auto it = personas.begin(); it != personas.end(); ++it) {
        if ((it->second).rol == "domador_osos") {
            if (it == personas.begin()) {
                if ((next(it)->second).lobo or (prev(personas.end())->second).lobo) 
                    cout << "En algún lugar de la aldea, un oso gruñe." << endl;
            }
        
            else if (it == prev(personas.end())) {
                if ((prev(it)->second).lobo or (personas.begin()->second).lobo) 
                    cout << "En algún lugar de la aldea, un oso gruñe." << endl;
            }
            
            else {
                if ((prev(it)->second).lobo or (next(it)->second).lobo) 
                    cout << "En algún lugar de la aldea, un oso gruñe." << endl;
            }
            usleep(1500000);
            cout << endl;
        }
    }
    
    
    //Votación
    cout << "La aldea ha de votar a alguien para linchar:" << endl;
    escriu(personas, false, false);
    
    string linchado;
    cin >> linchado;
    
    bool acaba = false;
    for (auto it = personas.begin(); it != personas.end() and not acaba; ++it) {
        if ((it->second).nom == linchado) {
            (it->second).razon = "Linchado por la aldea";
            cout << (it->second).nom << " - " << (it->second).rol << " - " << (it->second).razon << endl;
            personas.erase(it);
            acaba = true;
            usleep(1500000);
            
            //Si muere el cazador, otro muere
            if ((it->second).rol == "cazador") {
                bool cadena = true;
                
                while (cadena) {
                
                    cout << "El cazador se lleva a alguien consigo:" << endl;
                    escriu(personas, false, false);
                    
                    string cazado;
                    cin >> cazado;
                    bool acaba = false;
                    for (auto it = personas.begin(); it != personas.end() and not acaba; ++it) {
                        if ((it->second).nom == cazado) {
                            (it->second).razon = "Disparado por el cazador";
                            cout << (it->second).nom << " - " << (it->second).rol << " - " << (it->second).razon << endl;
                            if ((it->second).rol != "cazador") cadena = false;
                            personas.erase(it);
                            acaba = true;
                            usleep(1500000);
                        }
                    }
                }
            }
        }
    }
    
    //...
    //Se muere el Anciano por votación?
    
    comprueba_ending(personas);
    if (ending) return;
    
    
    //Final del día
    ++dia;
}

//Función que hace la fase de noche
void fase_noche(map<int, Persona> & personas) {
    
    //La primera noche
    if (noche == 1) {
        /* Cupido
         * Enamorados */
        // Vidente
        if (existe("vidente", personas)) {
            cout << "Se despierta la vidente:" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol == "vidente") cout << "- " << (it->second).nom << endl;
                usleep(200000);
            }
            cout << endl << "Y decide a quién descubrir el rol:" << endl;
            escriu(personas, false, true);
            
            string videntado;
            cin >> videntado;
            
            bool acaba = false;
            for (auto it = personas.begin(); it != personas.end() and not acaba; ++it) {
                if ((it->second).nom == videntado) {
                    cout << (it->second).nom << " - " << (it->second).rol << endl;
                    acaba = true;
                    usleep(1500000);
                }
            }
            cout << endl;
        }
         /* 2 Hermanas
         * Niño Salvaje
         * Domador de osos (reconocerlo)
         * Lobos + Perro Lobo si quiere + Niña*/
        if (existe("perro_lobo", personas)) {
            usleep(200000);
            cout << "El perro lobo es lobo? Y/N" << endl;
            char answer;
            cin >> answer;
            if (answer == 'Y' or answer == 'S' or answer == 'y' or answer == 's') {
                for (auto it = personas.begin(); it != personas.end(); ++it) {
                    if ((it->second).rol == "perro_lobo") (it->second).lobo = true;
                }
            }
        }
        
        if (haylobos(personas)) {
            usleep(200000);
            cout << "Se despiertan los lobos:" << endl;
            usleep(200000);
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).lobo) cout << "- " << (it->second).nom << " - " << (it->second).rol << endl;
                usleep(20000);
            }
            cout << endl << "Y deciden a quién comerse:" << endl;
            escriu(personas, true, false);
            
            
            string victima;
            cin >> victima;
            
            auto it = personas.begin();
            for (it = personas.begin(); it != personas.end() and (it->second).nom != victima; ++it);
            
            if (it != personas.end()) {
                (it->second).razon = "Devorado por los lobos";
                muertos.insert(*it);
                victimas.insert(*it);
                //personas.erase(it);
            }
        }
        
         
        /* Padre de los lobos
         * Lobo Feroz
         * Bruja
         * Zorro */
        // Flautista
        if (existe("flautista", personas)) {
            cout << "Se despierta el flautista:" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol == "flautista") cout << "- " << (it->second).nom << endl;
                usleep(200000);
            }
            
            cout << endl << "Y encanta a " << encantamientos_flautista << " personas:" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol != "flautista" and not (it->second).encantado) cout << "- " << (it->second).nom << endl;
                usleep(200000);
            }
            cout << endl;
            
            for (int i = 0; i < encantamientos_flautista; ++i) {
                string encantado;
                cin >> encantado;
                
                for (auto it = personas.begin(); it != personas.end(); ++it) {
                    if ((it->second).nom == encantado) (it->second).encantado = true;
                }
            }
            
            // Hechizados del Flautista
            cout << endl << "Se despiertan los encantados para reconocerse de momento" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                    if ((it->second).encantado) {
                        cout << "- " << (it->second).nom << endl;
                    }
            }
            cout << endl;
            
        }
    }
    
    else {
        // Vidente
        if (existe("vidente", personas)) {
            cout << "Se despierta la vidente:" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol == "vidente") cout << "- " << (it->second).nom << endl;
                usleep(200000);
            }
            cout << endl << "Y decide a quién descubrir el rol:" << endl;
            escriu(personas, false, true);
            
            string videntado;
            cin >> videntado;
            
            bool acaba = false;
            for (auto it = personas.begin(); it != personas.end() and not acaba; ++it) {
                if ((it->second).nom == videntado) {
                    cout << (it->second).nom << " - " << (it->second).rol << endl;
                    acaba = true;
                    usleep(1500000);
                }
            }
            cout << endl;
        }
        
        // Lobos + Niña
        if (haylobos(personas)) {
            usleep(200000);
            cout << "Se despiertan los lobos:" << endl;
            usleep(200000);
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).lobo) cout << "- " << (it->second).nom << " - " << (it->second).rol << endl;
                usleep(20000);
            }
            cout << endl << "Y deciden a quién comerse:" << endl;
            escriu(personas, true, false);
            
            string victima;
            cin >> victima;
            cout << endl;
            
            auto it = personas.begin();
            for (it = personas.begin(); it != personas.end() and (it->second).nom != victima; ++it);
            
            if (it != personas.end()) {
                (it->second).razon = "Devorado por los lobos";
                muertos.insert(*it);
                victimas.insert(*it);
                //personas.erase(it);
            }
        }
        
        // Si la noche es par, Lobo Albino
        if (existe("lobo_albino", personas) and not (noche % 2)) {
            usleep(200000);
            cout << "Se despierta el lobo albino:" << endl;
            usleep(200000);
            
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol == "lobo_albino") cout << "- " << (it->second).nom << endl;
            }
            cout << endl;
            
            usleep(500000);
            
            cout << "Y decide si comerse a alguno de sus compañeros:" << endl;
            
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).lobo and (it->second).rol != "lobo_albino") {
                    cout << "- " << (it->second).nom << endl;
                }
                usleep(20000);
            }
            cout << endl;
            
            string victima;
            cin >> victima;
            cout << endl;
            
            auto it = personas.begin();
            for (it = personas.begin(); it != personas.end() and (it->second).nom != victima; ++it);
            
            if (it != personas.end()) {
                (it->second).razon = "Devorado por el lobo albino";
                muertos.insert(*it);
                victimas.insert(*it);
                //personas.erase(it);
            }
        }
        
        /* Padre de los Lobos
         * Lobo Feroz
         * Bruja
         * Zorro */
         // Flautista
         if (existe("flautista", personas)) {
            cout << "Se despierta el flautista:" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol == "flautista") cout << "- " << (it->second).nom << endl;
                usleep(200000);
            }
            
            cout << endl << "Y encanta a " << encantamientos_flautista << " personas:" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol != "flautista" and not (it->second).encantado) cout << "- " << (it->second).nom << endl;
                usleep(200000);
            }
            
            cout << endl;
            for (int i = 0; i < encantamientos_flautista; ++i) {
                string encantado;
                cin >> encantado;
                
                for (auto it = personas.begin(); it != personas.end(); ++it) {
                    if ((it->second).nom == encantado) (it->second).encantado = true;
                }
            }
            
            // Hechizados del Flautista
            cout << endl << "Se despiertan los encantados para reconocerse de momento" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                    if ((it->second).encantado) {
                        cout << "- " << (it->second).nom << endl;
                    }
            }
            cout << endl;
            
        }
    }
    
    ++noche;
}

            //MAIN                   ---------------------------------------------
            
            
//PRE: 	Los posibles roles de la partida están mirados y estudiados, así que no hay quejas de desbalance
//		El máximo número de roles es 2^16 = 65536
int main(){

	//Semilla para cosas random
	srand (time(NULL));

	cout << "Introduzca los nombres de las personas acabando con un guión (-):" << endl;

	Persona p;

	//Contador de personas para checkear que esté todo correcto
	int countPers = 0;

	//Leer personas
	while (cin >> p.nom and p.nom != "-") {
        ++countPers;
		personas.insert(make_pair(countPers, p));
	}
	
	//Hacer una copia chiquita de las personas para trabajar
	//VP personas_peq(countPers);
	//for (int x = 0; x < countPers; ++x) personas_peq[x] = personas[x];

	cout << endl;

	cout << "Introduzca el número de roles y el nombre separados con espacio y acabado en 0:" << endl;
	cout << "Ejemplo: 4 Aldeano" << endl << "         1 Lobo" << endl << "         0" << endl << endl;

	int countRol = 0;
	string nomR;
	int num;

	vector<string> roles(65536);
	int i = 0;

	//Leer roles
	while (cin >> num and num != 0) {
		cin >> nomR;
		for (int j = i; j < i + num; ++j){
			roles[j] = nomR;
		}
		countRol += num;
		i += num;
	}
	
	usleep(200000);

	cout << "---------------" << endl;

	//Hacer una copia chiquita de los roles para trabajar
	vector<string> roles_peq(countRol);
	for (int x = 0; x < countRol; ++x) roles_peq[x] = roles[x];
	random_shuffle(roles_peq.begin(),roles_peq.end());
    
    //Asignar roles a las personas
    int ola = 0;
    for (auto it = personas.begin(); it != personas.end() and ola < countPers; ++it) {
        (it->second).rol = minusculas(roles_peq[ola]);
        
        //Modificar la Struct PERSONA de cada uno para los datos
        if ((it->second).rol == "lobo" or (it->second).rol == "lobo_albino" 
            or (it->second).rol == "lobo_feroz" or (it->second).rol == "padre_lobo") 
            (it->second).lobo = true;
        //...
        
        ++ola;
    }

	//Check
	if (countRol < countPers) {
		cout << "El número de roles no es suficiente" << endl;
	}
	else {
		if (countRol > countPers)
		cout << "Hay más roles que personas, puede haber desbalance." << endl << endl;
		
		//Saca por pantalla los resultados		
		cout << "Resultados: " << endl;
        usleep(20000);

        for (auto it = personas.begin(); it != personas.end(); ++it) {
            cout << (it->second).nom << " - " << (it->second).rol << endl;
            usleep(20000);
        }
        cout << "---------------" << endl;
		
        //COMIENZA LA PARTIDA
        usleep(1000000);
        
        cout << endl << "Comienza la partida:" << endl << endl;
        
        usleep(1000000);
        
        //Si hay un ángel, la partida empieza por una votación
        if (existe("angel", personas)) {
            dia = 0;
            
            fase_dia(personas);
        }
        
        while (not ending) {
            cout << " -----  Noche " << noche << "  -----" << endl;
            fase_noche(personas);
            
            cout << " -----  Día " << dia << "  -----" << endl;
            fase_dia(personas);
        }
        
        //DECIR QUIÉN GANA
        {
            cout << " -----   FINAL   -----" << endl;
            if (ending == -1) cout << " No queda nadie vivo en la aldea. Empate" << endl;
            else if (ending == 1) cout << " El pueblo gana" << endl;
            else if (ending == 2) cout << " Los lobos ganan" << endl;
            else if (ending == 3) cout << " El flautista gana" << endl;
            else if (ending == 4) cout << " El lobo albino gana" << endl;
            else if (ending == 5) cout << " El ángel gana" << endl;
            else if (ending == 6) cout << " Los enamorados y Cupido ganan" << endl;
            else if (ending == 7) cout << " El/La " << RolSolitario1 << " gana" << endl;
            else if (ending == 8) cout << " El/La " << RolSolitario2 << " gana" << endl;
            else if (ending == 9) cout << " El/La " << RolSolitario3 << " gana" << endl;
            else if (ending == 10) cout << " El/La " << RolSolitario4 << " gana" << endl;
        }
	}
}
