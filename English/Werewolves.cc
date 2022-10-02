#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <unistd.h>
using namespace std;

            //CONSTANTS            ---------------------------------------------

const int pocionRevivir = 1;
const int pocionMatar = 1;
const int transformaciones_padre = 1;
const int encantamientos_flautista = 2;
const int vidas_anciano = 2;

const string RolSolitario1 = "sol1";
const string RolSolitario2 = "sol2";
const string RolSolitario3 = "sol3";
const string RolSolitario4 = "sol4";

            //GLOBAL VARIABLES    ---------------------------------------------
struct Persona {
    string nom;
    string rol;
    bool lobo = false;                  //Bool to know if someone is a wolf
    bool enamorado = false;             //Bool to know if someone is a lover
    bool encantado = false;             //Bool to know if someone is charmed by the piper
    int pocionR = 0;                    //Number of living potions of the witch
    int pocionM = 0;                    //Number of death potions of the witch
    int transf_padre = 0;               //Number of transformations the Wolf Father can do in a game
    int vidas = 1;                      //Number of lives in case of being the Ancient
    string mentor = "-";                //Name of the mentor of he Wild Kil
    
    string razon = "-";                 //Reason of death
};

using VS = vector<string>;
using VP = vector<Persona>;

map<int, Persona> personas;
map<int, Persona> muertos;
map<int, Persona> victimas;

int ending = 0;
    /* Ending List:
     * -1: Guatafac?
     * 0: Game haven't ended
     * 1: Town wins
     * 2: Wolves win
     * 3: Piper wins
     * 4: White wolf wins
     * 5: Angel Wins
     * 6: Lovers and Cupid win
     * 7: [RolSolitario1] wins
     * 8: [RolSolitario2] wins
     * 9: [RolSolitario3] wins
     * 10: [RolSolitario4] wins
     */
    
    
int noche = 1;
int dia = 1;

            //FUNCTIONS              ---------------------------------------------

//Turn a string into all lowercase
string minusculas(string s) {
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] >= 'A' and s[i] <= 'Z') s[i] = s[i] + 32;
    }
    
    return s;
}

//Write a map of People
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
            if (not ((it->second).rol == "seer")) {
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

//Function to find out if there is a role called "s" in a vector
bool existe(string s, vector<string>& roles) {
    bool trobat = false;
    
    for (int x = 0; x < roles.size() and not trobat; ++x) {
        if (roles[x] == s) trobat = true;
    }
    
    return trobat;
}

//Function to find out if there is a role called "s" in a map of People
bool existe(string s, map<int, Persona> & personas) {
    bool trobat = false;
    
    for (auto it = personas.begin(); it != personas.end() and not trobat; ++it) {
        if ((it->second).rol == s) trobat = true;
    }
    
    return trobat;
}

//Check if there are wolves left in a map of People 
bool haylobos(map<int, Persona> & personas) {
    bool trobat = false;
    
    for (auto it = personas.begin(); it != personas.end() and not trobat; ++it) {
        if ((it->second).lobo) trobat = true;
    }
    
    return trobat;
}

//Function to check if the game has ended
void comprueba_ending(map<int, Persona>& personas) {
    /* Ending List:
     * -1: Guatafac?
     * 0: Game haven't ended
     * 1: Town wins
     * 2: Wolves win
     * 3: Piper wins
     * 4: White wolf wins
     * 5: Angel Wins
     * 6: Lovers and Cupid win
     * 7: [RolSolitario1] wins
     * 8: [RolSolitario2] wins
     * 9: [RolSolitario3] wins
     * 10: [RolSolitario4] wins
     */
    
    //...
    
    //No one is alive, draw
    if (personas.empty()) ending = -1;
    
    //No wolves, Town wins
    else if (not haylobos(personas)) ending = 1;
    
    else {
        //Count stuff
        int countLobos = 0;
        int countEncantados = 0;
        for (auto it = personas.begin(); it != personas.end(); ++it) {
            if ((it->second).lobo) countLobos++;
            if ((it->second).encantado) countEncantados++;
        }
        
        //PRIORITY:
        
        //White wolf
        if (personas.size() == 1 and (personas.begin()->second).rol == "white_wolf") ending = 4;
        //Piper
        else if (existe("piper", personas) and countEncantados == personas.size() - 1) ending = 3;
        //Wolves
        else if (countLobos == personas.size()) ending = 2;
    }
    
}

//Daytime Function: Reveal victims & voting if the game haven't ended
void fase_dia(map<int, Persona>& personas) {
    
    //Reveal victims
    usleep(1000000);
    
    if (victimas.empty()) cout << "There were no victims this night" << endl;
    else {
        cout << "This night has been" << victimas.size() << " dead people: " << endl;
        
        usleep(1000000);
        
        //Show Victims
        auto it = victimas.begin();
        for (it = victimas.begin(); it != victimas.end(); ++it) {
            cout << (it->second).nom << " - " << (it->second).rol << " - " << (it->second).razon << endl;
            usleep(1500000);
            
            //If the hunter dies, he kills someone
            if ((it->second).rol == "hunter") {
                bool cadena = true;
                
                while (cadena) {
                
                    cout << "The Hunter kills someone in his last breath:" << endl;
                    escriu(personas, false, false);
                    
                    string cazado;
                    cin >> cazado;
                    bool acaba = false;
                    for (auto it = personas.begin(); it != personas.end() and not acaba; ++it) {
                        if ((it->second).nom == cazado) {
                            (it->second).razon = "Shot by the Hunter";
                            cout << (it->second).nom << " - " << (it->second).rol << " - " << (it->second).razon << endl;
                            if ((it->second).rol != "hunter") cadena = false;
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
        
        //Clean Victims data structure
        victimas.erase(victimas.begin(), victimas.end());
    }
    usleep(200000);
    cout << endl;
    
    //If the Ancient died by the Town, Town loses powers, else loses 1 life
    //...
    
    comprueba_ending(personas);
    if (ending) return;
    
    
    //The Bear growls?
    for (auto it = personas.begin(); it != personas.end(); ++it) {
        if ((it->second).rol == "bear_tamer") {
            if (it == personas.begin()) {
                if ((next(it)->second).lobo or (prev(personas.end())->second).lobo) 
                    cout << "Somewhere in the town, a bear growls." << endl;
            }
        
            else if (it == prev(personas.end())) {
                if ((prev(it)->second).lobo or (personas.begin()->second).lobo) 
                    cout << "Somewhere in the town, a bear growls." << endl;
            }
            
            else {
                if ((prev(it)->second).lobo or (next(it)->second).lobo) 
                    cout << "Somewhere in the town, a bear growls." << endl;
            }
            usleep(1500000);
            cout << endl;
        }
    }
    
    
    //Voting
    cout << "Town has to vote someone to lynch:" << endl;
    escriu(personas, false, false);
    
    string linchado;
    cin >> linchado;
    
    for (auto it = personas.begin(); it != personas.end(); ++it) {
        if ((it->second).nom == linchado) {
            (it->second).razon = "Lynched by the Town";
            cout << (it->second).nom << " - " << (it->second).rol << " - " << (it->second).razon << endl;
            usleep(1500000);
            
            //If the hunter dies, he kills someone
            if ((it->second).rol == "hunter") {
                bool cadena = true;
                
                while (cadena) {
                
                    cout << "The Hunter kills someone in his last breath:" << endl;
                    escriu(personas, false, false);
                    
                    string cazado;
                    cin >> cazado;
                    bool acaba = false;
                    for (auto it = personas.begin(); it != personas.end() and not acaba; ++it) {
                        if ((it->second).nom == cazado) {
                            (it->second).razon = "Shot by the Hunter";
                            cout << (it->second).nom << " - " << (it->second).rol << " - " << (it->second).razon << endl;
                            if ((it->second).rol != "hunter") cadena = false;
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
    }
    
    //The ancient died by voting?
    //...
    
    comprueba_ending(personas);
    if (ending) return;
    
    
    //Ending of daytime
    ++dia;
}

//Nighttime Function
void fase_noche(map<int, Persona> & personas) {
    
    //First night
    if (noche == 1) {
        /* Cupid
         * Lovers */
        // Seer
        if (existe("seer", personas)) {
            cout << "The seer wakes up:" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol == "seer") cout << "- " << (it->second).nom << endl;
                usleep(200000);
            }
            cout << endl << "And decides who to check:" << endl;
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
         /* 2 Sisters
         * Wild Kid
         * Bear Tamer (Recognise him)
         * Wolves + Dog Wolf + Little Kid*/
        if (existe("dog_wolf", personas)) {
            usleep(200000);
            cout << "The dog wolf is a wolf? Y/N" << endl;
            char answer;
            cin >> answer;
            if (answer == 'Y' or answer == 'S' or answer == 'y' or answer == 's') {
                for (auto it = personas.begin(); it != personas.end(); ++it) {
                    if ((it->second).rol == "dog_wolf") (it->second).lobo = true;
                }
            }
        }
        
        if (haylobos(personas)) {
            usleep(200000);
            cout << "The Werewolves wake up:" << endl;
            usleep(200000);
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).lobo) cout << "- " << (it->second).nom << " - " << (it->second).rol << endl;
                usleep(20000);
            }
            cout << endl << "And decide who to eat:" << endl;
            escriu(personas, true, false);
            
            
            string victima;
            cin >> victima;
            
            auto it = personas.begin();
            for (it = personas.begin(); it != personas.end() and (it->second).nom != victima; ++it);
            
            if (it != personas.end()) {
                (it->second).razon = "Eaten by the werewolves";
                muertos.insert(*it);
                victimas.insert(*it);
                //personas.erase(it);
            }
        }
        
         
        /* Wolf Father
         * Big Bad Wolf
         * Witch
         * Fox */
        // Piper
        if (existe("piper", personas)) {
            cout << "The Piper wakes up:" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol == "piper") cout << "- " << (it->second).nom << endl;
                usleep(200000);
            }
            
            cout << endl << "And charms " << encantamientos_flautista << " people:" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol != "piper" and not (it->second).encantado) cout << "- " << (it->second).nom << endl;
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
            
            // Charmed people
            cout << endl << "Charmed people wake up to recognise each other:" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                    if ((it->second).encantado) {
                        cout << "- " << (it->second).nom << endl;
                    }
            }
            cout << endl;
            
        }
    }
    
    //Not he first night
    else {
        // Seer
        if (existe("seer", personas)) {
            cout << "The seer wakes up:" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol == "seer") cout << "- " << (it->second).nom << endl;
                usleep(200000);
            }
            cout << endl << "And decides who to check:" << endl;
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
        
        // Werewolves + little kid
        if (haylobos(personas)) {
            usleep(200000);
            cout << "The Werewolves wake up:" << endl;
            usleep(200000);
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).lobo) cout << "- " << (it->second).nom << " - " << (it->second).rol << endl;
                usleep(20000);
            }
            cout << endl << "And decide who to eat:" << endl;
            escriu(personas, true, false);
            
            
            string victima;
            cin >> victima;
            
            auto it = personas.begin();
            for (it = personas.begin(); it != personas.end() and (it->second).nom != victima; ++it);
            
            if (it != personas.end()) {
                (it->second).razon = "Eaten by the werewolves";
                muertos.insert(*it);
                victimas.insert(*it);
                //personas.erase(it);
            }
        }
        
        // If it's and even night, White Wolf
        if (existe("white_wolf", personas) and not (noche % 2)) {
            usleep(200000);
            cout << "The White Werewolf wakes up:" << endl;
            usleep(200000);
            
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol == "white_wolf") cout << "- " << (it->second).nom << endl;
            }
            cout << endl;
            
            usleep(500000);
            
            cout << "And decides to murder (or not '-') one of his comrades:" << endl;
            
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).lobo and (it->second).rol != "white_wolf") {
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
                (it->second).razon = "Murdered by the White Wolf";
                muertos.insert(*it);
                victimas.insert(*it);
                //personas.erase(it);
            }
        }
        
        /* Wolf Father
         * Big Bad Wolf
         * Witch
         * Fox */
         // Piper
        if (existe("piper", personas)) {
            cout << "The Piper wakes up:" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol == "piper") cout << "- " << (it->second).nom << endl;
                usleep(200000);
            }
            
            cout << endl << "And charms " << encantamientos_flautista << " people:" << endl;
            for (auto it = personas.begin(); it != personas.end(); ++it) {
                if ((it->second).rol != "piper" and not (it->second).encantado) cout << "- " << (it->second).nom << endl;
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
            
            // Charmed people
            cout << endl << "Charmed people wake up to recognise each other:" << endl;
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
            
            
//PRE: 	The possible roles of the game are looked at and studied, so there are no complaints of imbalance
//		The maximum number of roles is 2^16 = 65536
int main(){

	//Seed for random stuff
	srand (time(NULL));

	cout << "Enter the names of the people ending with a ' - ':" << endl;

	Persona p;

	//Counter for the people to check role correctness later
	int countPers = 0;

	//Read people
	while (cin >> p.nom and p.nom != "-") {
        ++countPers;
		personas.insert(make_pair(countPers, p));
	}
	
	//Debugging
	//Hacer una copia chiquita de las personas para trabajar
	//VP personas_peq(countPers);
	//for (int x = 0; x < countPers; ++x) personas_peq[x] = personas[x];

	cout << endl;

	cout << "Enter the number of roles and the name separated with a space and ending with 0:" << endl;
	cout << "Example: 6 Villager" << endl << "         2 Wolf" << endl << "         0" << endl << endl;

	int countRol = 0;
	string nomR;
	int num;

	vector<string> roles(65536);
	int i = 0;

	//Read roles
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

	//Make a small copy of the roles to work with
	vector<string> roles_peq(countRol);
	for (int x = 0; x < countRol; ++x) roles_peq[x] = roles[x];
	random_shuffle(roles_peq.begin(),roles_peq.end());
    
    //Assign roles to people
    int ola = 0;
    for (auto it = personas.begin(); it != personas.end() and ola < countPers; ++it) {
        (it->second).rol = minusculas(roles_peq[ola]);
        
        //Modify the struct PERSONA of all data read
        if ((it->second).rol == "wolf" or (it->second).rol == "white_wolf" 
            or (it->second).rol == "wolf_father" or (it->second).rol == "wolf_father") 
            (it->second).lobo = true;
        //...
        
        ++ola;
    }

	//Check
	if (countRol < countPers) {
		cout << "The number of roles isn't enough." << endl;
	}
	else {
		if (countRol > countPers)
		cout << "There are more roles than people, there may be an imbalance." << endl << endl;
		
		//Write results		
		cout << "Results: " << endl;
        usleep(20000);

        for (auto it = personas.begin(); it != personas.end(); ++it) {
            cout << (it->second).nom << " - " << (it->second).rol << endl;
            usleep(20000);
        }
        cout << "---------------" << endl;
		
        //THE GAME BEGINS
        usleep(1000000);
        
        cout << endl << "The game begins:" << endl << endl;
        
        usleep(1000000);
        
        //If there is an angel, the game starts with a voting
        if (existe("angel", personas)) {
            dia = 0;
            
            fase_dia(personas);
        }
        
        while (not ending) {
            cout << " -----  Night " << noche << "  -----" << endl;
            fase_noche(personas);
            
            cout << " -----  Day " << dia << "  -----" << endl;
            fase_dia(personas);
        }
        
        //DECIR QUIÉN GANA
        {
            cout << " -----   FINAL   -----" << endl;
            if (ending == -1) cout << " No queda nadie vivo en la aldea. Empate" << endl;
            else if (ending == 1) cout << " Town wins" << endl;
            else if (ending == 2) cout << " Werewolves win" << endl;
            else if (ending == 3) cout << " Piper wins" << endl;
            else if (ending == 4) cout << " White Wolf wins" << endl;
            else if (ending == 5) cout << " Angel wins" << endl;
            else if (ending == 6) cout << " Lovers and Cupid win" << endl;
            else if (ending == 7) cout << " " << RolSolitario1 << " wins" << endl;
            else if (ending == 8) cout << " " << RolSolitario2 << " wins" << endl;
            else if (ending == 9) cout << " " << RolSolitario3 << " wins" << endl;
            else if (ending == 10) cout << " " << RolSolitario4 << " wins" << endl;
        }
	}
}
