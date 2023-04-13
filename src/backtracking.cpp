#include <backtracking.hpp>

Backtracking_Loesung::Backtracking_Loesung(const SAT& neue_instanz):
    instanz(neue_instanz), wbelegung(instanz.anz_var()), klausel_anz_gez_var(instanz.anz_klausel(), 0),
    klausel_anz_wahrer_var(instanz.anz_klausel(), 0), klausel_wwert(instanz.anz_klausel(), 0) {}



//SAT aktualisieren nach setzten einer Variable und Gueltigkeit der Belegung checken:

bool Backtracking_Loesung:: klausel_kann_noch_wahr_werden(const unsigned int& klausel_id) const {
    //klausel kann nur noch wahr werden, wenn sie schon wahr ist oder noch variablen gesetzt werden mussen
    if (klausel_wwert[klausel_id] || klausel_anz_gez_var[klausel_id] != instanz.klausel(klausel_id).anz_variablen()) {
        return true;
    }
    else {
        return false;
    }
}

void Backtracking_Loesung::klausel_var_wahr_setzten(const unsigned int& klausel_id, const bool& fruher_gesetzt) {
    klausel_anz_wahrer_var[klausel_id]++;
    klausel_wwert[klausel_id] = 1;
    if (!fruher_gesetzt) {
        klausel_anz_gez_var[klausel_id]++;
    }
}

void Backtracking_Loesung::klausel_var_falsch_setzten(const unsigned int& klausel_id, const bool& fruher_gesetzt) {
    if (!fruher_gesetzt) {
        klausel_anz_gez_var[klausel_id]++;
    }
    else {
        klausel_anz_wahrer_var[klausel_id]--;
        if (klausel_anz_wahrer_var[klausel_id] == 0) {
            klausel_wwert[klausel_id] = 0;
        }
    }
}

void Backtracking_Loesung::klauseln_aktualisieren_setzten_variable(const unsigned int& var_id, const bool& neuer_wwert, const std::vector<unsigned int>& klausel, const bool& var_vz, bool& belegung_gueltig) {
    //var_vz steht fuer das VZ in dem die aktuelle Variable in den zu betrachtenten Klauseln vorkommt

    bool fruher_gesetzt = wbelegung.var_gesetzt(var_id);
    for (const unsigned int& klausel_id : klausel) {
        if (neuer_wwert == var_vz) {
            klausel_var_wahr_setzten(klausel_id, fruher_gesetzt);
        }
        else {
            klausel_var_falsch_setzten(klausel_id, fruher_gesetzt);
            if (!klausel_kann_noch_wahr_werden(klausel_id)) {
                belegung_gueltig = false;
            }
        }
    }
}

bool Backtracking_Loesung::SAT_aktualisieren_setzten_variable(const unsigned int& var_id,const bool& neuer_wwert) {
    bool belegung_gueltig = true; //Wird die Information speicher, ob alle Klauseln, die durch das Setzten der Variable verandert wurden noch wahr werden koennen

    //Aktualisieren der Klauseln, wo die Variable positiv und negativ vorkommt:
    klauseln_aktualisieren_setzten_variable(var_id, neuer_wwert, instanz.var(var_id).klausel_wahr(), true, belegung_gueltig);
    klauseln_aktualisieren_setzten_variable(var_id, neuer_wwert, instanz.var(var_id).klausel_falsch(), false, belegung_gueltig);

    //Aktualisieren Variable:
    wbelegung.var_setzten(var_id, neuer_wwert);

    return belegung_gueltig;//Falls alle Klauseln noch wahr werden konnen, konnen wir die Belegung weiter untersuchen
}



//SAT aktualisiern nach Variable auf nicht gesetzt:

void Backtracking_Loesung::klausel_wahre_var_nicht_gesetzt(const unsigned int& klausel_id) {
    klausel_anz_gez_var[klausel_id]--;
    klausel_anz_wahrer_var[klausel_id]--;
    if (klausel_anz_wahrer_var[klausel_id] == 0) {
            klausel_wwert[klausel_id] = 0;
    }
}

void Backtracking_Loesung::klausel_falsche_var_nicht_gesetzt(const unsigned int& klausel_id) {
    klausel_anz_gez_var[klausel_id]--;
}

void Backtracking_Loesung::klauseln_aktualisieren_variable_nicht_setzten(const unsigned int& var_id, const std::vector<unsigned int>& klausel, const bool& var_vz) {
    //var_vz steht fuer das VZ in dem die aktuelle Variable in den zu betrachtenten Klauseln vorkommt

    for (const unsigned int& klausel_id: klausel) {
        if (wbelegung.var_wert(var_id) == var_vz) {
            klausel_wahre_var_nicht_gesetzt(klausel_id);
        }
        else {
            klausel_falsche_var_nicht_gesetzt(klausel_id);
        }
    }
}

void Backtracking_Loesung::SAT_aktualisieren_variable_nicht_setzten(const unsigned int& var_id) {
    
    //Klauseln wo die Variable negativ und postiv auftaucht werden aktualisiert, sodass diese Variable als nicht gesetzt gilt
    klauseln_aktualisieren_variable_nicht_setzten(var_id, instanz.var(var_id).klausel_wahr(), true);
    klauseln_aktualisieren_variable_nicht_setzten(var_id, instanz.var(var_id).klausel_falsch(), false);

    //Variable auf nicht gesetzt setzten
    wbelegung.var_nicht_gesetzt(var_id);
}
 


//Ende Backtracking und Output
void Backtracking_Loesung::keine_loesung() const {
    std::cout << "Es gibt keine Loesung" << "\n";
}

void Backtracking_Loesung::loesung_ausgeben() const {
    std::cout << "Folgende Wahrheitsbelegung liefert Loesung" << "\n";
    wbelegung.print();
}

bool Backtracking_Loesung::ende_backtracking(const unsigned int& var_id) const{
    if (var_id < 1) { //Es wurde versucht 1 auf wahr und auf falsch zu stellen und fuer keines gueltige Belegung gefunden
        keine_loesung();
        return true;
    }
    else if (var_id > instanz.anz_var()) { //Alle Variablen sind besetzt und die Klauseln wahr
        loesung_ausgeben();
        return true;
    }
    else {
        return false;
    }
}


//Variablen aendern in der Wbelegung:

unsigned int Backtracking_Loesung::variable_wahr(const unsigned int& var_id) {
    if (!ende_backtracking(var_id)) {
        if (SAT_aktualisieren_setzten_variable(var_id, true) ) {
            return var_id + 1;
        } 
        else {
            return variable_falsch(var_id);
        }
    }
    return 0;
}

unsigned int Backtracking_Loesung::variable_falsch(const unsigned int& var_id) {
    if (!ende_backtracking(var_id)) {
        if (SAT_aktualisieren_setzten_variable(var_id, false)) {
            return var_id + 1;
        } 
        else {
            return variable_nicht_gesetzt(var_id);
        }
    }
    return 0;
}

unsigned int Backtracking_Loesung::variable_nicht_gesetzt(const unsigned int& var_id){
    if (!ende_backtracking(var_id)) {
        SAT_aktualisieren_variable_nicht_setzten(var_id);
        return var_id - 1; //gehen eine Variable zuruck, da wir mit der jetztigen Belegung keine wahre Belegung erreichen koennen
    }
    return 0;
}



//Backtracking:

/**
 * Ich finde Deine implementierung grade immer noch verhältnismäßig komplex.
 * Das liegt glaube ich daran, dass es sehr indirekt aufgeschrieben ist.
 * Es gibt 2 Punkte, die das verursachen.
 * 1. Die Funktionen die in aus der while schleife aufgerufen werden machen mehr als sie sollten.
 *    Sie setzen nicht nur die variable um, sondern prüfen (ohne das im namen zu sagen)
 *    auch noch ob die Wahrheitsbelegung schon einen widerspruch hat oder nicht
 *    und suchen dann noch den nächsten index raus, also increment, oder backtracking.
 * 2. Basierend darauf ist hier der pfad in viele kleine Funktionen verzweigt
 *    und erreicht auch noch eine relativ hohe tiefe.
 *    Dh. um zu verstehen, was hier passiert, muss man den Code-pfad über viele 
 *    verzweigungen verfolgen.
 *    Es gibt dazu einen schönen talk von der CppCon 2019: 
 *    Auf youtube: 'CppCon 2019: Chandler Carruth “There Are No Zero-cost Abstractions”'
 *    Der behandelt noch viel mehr und Du musst Dir den nicht ansehen. Ist aber sehenswert.
 * 
 * Ok, jetzt zu der Frage, wie man das lösen kann. 
 * Ich glaube ein hilfreicher Ansatz ist, sich das als mathematischen pseudocode vorzustellen,
 * in dem erlaubt ist einfache tasks durch text auszudrücken und dann zu sehen, wie das aussieht.
 * 
 * Ich hab das mal für Deinen algorithmus gemacht. So würde ich den im (semi-) pseudocode
 * aufschreiben:
 * 
 * Wahrheitsbelegung belegung = Alle nicht gesetzt
 * VariableIndex current_variable = 1;
 * while (current_variable > 0) {
 *    if (current_variable > Anzahl variablen) {
 *       return belegung;
 *    }
 *    if ( belegung.wert(current_variable) == VariablenWert::falsch ) {
 *       reset variable ( current_variable);
 *       --current_variable;
 *       continue;
 *    }
 *    
 *    bool widerspruch = false;
 *    if ( belegung.wert(current_variable) == VariablenWert::ungesetzt ) {
 *       widerspruch = setze und prüfe auf widerspruch (current_variable, VariablenWert::wahr);
 *    } else {
 *       reset variable ( current_variable );
 *       widerspruch = setze und prüfe auf widerspruch (current_variable, VariablenWert::falsch);
 *    }
 *    if (not widerspruch) {
 *       ++current_variable;
 *    }
 * }
 * return Keine Lösung (std::nullopt)
 */


/*Beim Backtracking gehen wir folgendes Schema durch:
    1. Variable auf wahr setzten, wenn es geht gehen wir zur naechsten Variable sonst zu 2.
    2. Variable auf falsch setzten, wenn es geht gehen wir zur naechsten Variable sonst zu 3.
    3. Variable auf nicht gesetzt und gehen eine Variable nach hinten und untersuchen sie vom neuen
 */

void Backtracking_Loesung::loesen() {
    unsigned int var_id = 1;
    while (!ende_backtracking(var_id)) {
        if(!wbelegung.var_gesetzt(var_id)) { //Schritt 1
            var_id = variable_wahr(var_id);
        }
        else if (wbelegung.var_wert(var_id)) { //Schritt 2
            var_id = variable_falsch(var_id);
        }
        else {
            var_id = variable_nicht_gesetzt(var_id); //Schritt 3
        }
    }
}
