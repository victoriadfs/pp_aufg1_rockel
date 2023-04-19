//Implementierung DIMACS_einlesen.cpp
#include <DIMACS_einlesen.hpp>
typedef unsigned int KlauselIndex;

//neue Klausel mit gegebenen Input erstellen:
Klausel neue_klausel(const std::string& line, const KlauselIndex klausel_id, const int anz_var) {
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

std::pair<SAT, unsigned int> SAT_initialisieren(const std::string& line){
    std::string p, cnf;
    unsigned int anz_var, anz_klausel;
    std::stringstream ss(line); 
    ss >> p >> cnf >> anz_var >> anz_klausel; 
    if (not ss) {
        throw std::runtime_error("Dateiformat wurde nicht respektiert.");
    }

    if (cnf == "cnf") {
        return std::make_pair(SAT(anz_var),anz_klausel); //SAT Instanz inistiallisiert
    }
    else {
        throw std::runtime_error("Dateiformat wurde nicht respektiert."); 
    }
    
    return std::make_pair(SAT(0),0);
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
                //unsigned int anz_klauseln = 0;
                auto[instanz, anz_klauseln] = SAT_initialisieren(line);//Einlesen der ersten Zeile und initialisieren

                //Einlesen und hinzufuegen von allen Klauseln:
                for (KlauselIndex klausel_id = 0; klausel_id < anz_klauseln; klausel_id++) {
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

