#include <backtracking.hpp>
#include <cmath>
#include <fstream>
#include <sstream>
#include <limits>
#include <string> 
#include <iostream>
#include <stdexcept>
#include <string>

//neue Klausel mit gegebenen Input erstellen:
Klausel neue_klausel(const std::string& line, const int& klausel_id, const int& anz_var) {
    Klausel neue_klausel = Klausel(klausel_id);// leere Klausel erstellt, ID ist Nummerierung nach Reihenfolge im Input

    //Variablen einlesen und hinzufuegen:
    int neue_variable;
    std::stringstream ss(line); 
    ss >> neue_variable;
    if (not ss) {
        throw std::runtime_error("Dateiformat wurde nicht respektiert.");
    }
    
    while (neue_variable != 0) { //nach DIMACS-Darstellung Klausel Ende wenn eine 0 eingelesen wird
        neue_klausel.var_hinzu(neue_variable);
        ss >> neue_variable;
        if (not ss || abs(neue_variable) > anz_var) { // Variablen duerfen nur 1 bis anz_var als Betrag haben
            throw std::runtime_error("Dateiformat wurde nicht respektiert.");
        }
    }

    return neue_klausel;
}

SAT SAT_initialisieren(const std::string& line, int& anz_klausel){
    std::string p, cnf;
    int anz_var;
    std::stringstream ss(line); 
    ss >> p >> cnf >> anz_var >> anz_klausel; 
    if (not ss) {
        throw std::runtime_error("Dateiformat wurde nicht respektiert.");
    }

    if (cnf == "cnf") {
        return SAT(anz_var); //SAT Instanz inistiallisiert
    }
    else {
        throw std::runtime_error("Dateiformat wurde nicht respektiert."); 
    }
    
    return SAT(0);
}

SAT dimacs_einlesen (char const * filename) {
    std::ifstream file(filename); 
    if (not file) {
        throw std::runtime_error("File konnte nicht geoffnet werden.");
    }
    else {
        std::string line;
        while (std::getline(file, line)) {
            if (line[0] == 'p') { //Anfangs des Inputs der boolschen Formel
                int anz_klauseln = 0;
                SAT instanz = SAT_initialisieren(line, anz_klauseln);//Einlesen der ersten Zeile und initialisieren

                //Einlesen und hinzufuegen von allen Klauseln:
                for (int klausel_id = 0; klausel_id < anz_klauseln; klausel_id++) {
                    std::getline(file, line);
                    instanz.klausel_hinzu(neue_klausel(line, klausel_id, instanz.anz_var()));
                }

                return instanz;
            }
            else if (line[0] != 'c') { //DIMACS Darstellung muessen Kommentare mit 'c' anfangen und vor dem Input der boolschen Formel kommen
               throw std::runtime_error("Dateiformat wurde nicht respektiert."); 
            }
        }
     }

     return SAT(0);
}


int main(int argc, char* argv[]){
    if (argc > 1) {
        SAT instanz = dimacs_einlesen(argv[1]); //Einlesen
        Backtracking_Loesung(instanz).loesen(); //Loesen
    }
}
//clang++ -std=c++17 -o test -I./include src/SAT.cpp src/wahrheitsbelegung.cpp src/backtracking.cpp src/klausel.cpp src/variable.cpp \examples/main.cpp 
//./test \files/test1.txt