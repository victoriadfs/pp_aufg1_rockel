//Implementierung vom Backtracking Algorithmus
#include <backtracking.hpp>

struct KlauselZustand {
    //Initialisiert auf Werte vor dem keine Variable gesetzt worden ist
    unsigned int anz_gesetzer_variablen = 0;
    unsigned int anz_wahrer_variablen = 0;
};


//Variable neu setzten und pruefen ob hierbei ein Wiederspruch entsteht:

bool pruefe_ob_klausel_noch_wahr_werden_kann (const KlauselZustand& current_klausel_zustand, const Klausel& current_klausel) {
    //klausel kann nur noch wahr werden, wenn sie schon wahr ist oder noch variablen gesetzt werden mussen
    if (current_klausel_zustand.anz_wahrer_variablen > 0 || current_klausel.anz_variablen() != current_klausel_zustand.anz_gesetzer_variablen) {
        return true;
    }
    return false;
}

void pruefe_ob_wiederspruch_und_zustand_klauseln_nach_setzten_variable_aktualisieren (const SAT& instanz, std::vector<KlauselZustand>& klausel_zustand, const bool current_variable_fueher_gesetzt, const bool variable_wert_in_klausel, const std::vector<KlauselIndex>& klauseln_zu_aktualisieren, bool& wiederspruch) {
    //variable_wert_in_klausel stellt den Wert da den die Variable in der Klausel animmt:
    // ZB variable x ist wahr und tritt positiv in Klausel auf variable_wert_in_klausel=true, falls sie negativ auftaucht variable_wert_in_klausel=false

    for (const KlauselIndex& current_klausel: klauseln_zu_aktualisieren) {
        if (!current_variable_fueher_gesetzt) { //Variable wird zum ersten Mal gesetzt
            klausel_zustand[current_klausel].anz_gesetzer_variablen++;
        }

        if (variable_wert_in_klausel) {
            klausel_zustand[current_klausel].anz_wahrer_variablen++;
        }
        else {
            if (current_variable_fueher_gesetzt) { //Variable die frueher wahr war, wird falsch
                klausel_zustand[current_klausel].anz_wahrer_variablen--;
            }
            if (!pruefe_ob_klausel_noch_wahr_werden_kann(klausel_zustand[current_klausel], instanz.klausel(current_klausel))) {
                wiederspruch = true;
            }
        }
    }
}

bool pruefe_ob_wiederspruch_und_variable_neu_setzten (const VariableIndex current_variable, const SAT& instanz, Wahrheitsbelegung& belegung, std::vector<KlauselZustand>& klausel_zustand, bool variable_new_wert) {
    bool wiederspruch = false;
    bool current_variable_frueher_gesetzt = true;
    if (belegung.var_wert(current_variable) == VariableWert::ungesetzt) {
        current_variable_frueher_gesetzt = false;
    }
    
    //Zustand der Klauseln in der die Variable vorkommt aktualisieren:
    //variable_wert_in_klausel stellt den Wert da den die Variable in der Klausel animmt:
    //ZB variable x ist wahr und tritt positiv in Klausel auf variable_wert_in_klausel = true, falls sie negativ auftaucht variable_wert_in_klausel = false
    bool variable_wert_in_klausel = (true == variable_new_wert);
    pruefe_ob_wiederspruch_und_zustand_klauseln_nach_setzten_variable_aktualisieren(instanz, klausel_zustand, current_variable_frueher_gesetzt, variable_wert_in_klausel, instanz.var(current_variable).klausel_wahr(), wiederspruch);
    variable_wert_in_klausel = (false == variable_new_wert);
    pruefe_ob_wiederspruch_und_zustand_klauseln_nach_setzten_variable_aktualisieren(instanz, klausel_zustand, current_variable_frueher_gesetzt, variable_wert_in_klausel, instanz.var(current_variable).klausel_falsch() ,wiederspruch);
    
    //Aktualisieren Variable:
    if (variable_new_wert) {
        belegung.var_wert_aendern(current_variable, VariableWert::wahr);
    }
    else {
        belegung.var_wert_aendern(current_variable, VariableWert::falsch);
    }

    return wiederspruch; //Wenn es beim Aktualisieren der Klauseln zu keinem Wiederspruch gekommen ist, ist die Belegung bis zum Moment gueltig und man kann die naechste Variable setzten
}

//Reseten einer Variable und aktualisieren des Zustandes der Klauseln
void klauseln_aktualisieren_variable_reseted(std::vector<KlauselZustand>& klausel_zustand, const std::vector<KlauselIndex>& klauseln_zu_aktualisieren, const bool variable_vz_in_klausel) {
    for (const KlauselIndex& current_klausel : klauseln_zu_aktualisieren) {
        klausel_zustand[current_klausel].anz_gesetzer_variablen--; //Eine der frueher gesetzten Variablen ist nicht mehr gesetzt
        if (variable_vz_in_klausel == false) {
            //Die Variable war eine wahre Variable in der aktuellen Klausel
            //nur Variablen mit Wert false kommen in diese Funktion
            klausel_zustand[current_klausel].anz_wahrer_variablen--;
        }
    }
}

void reset_variable (const VariableIndex current_variable, const SAT& instanz, Wahrheitsbelegung& belegung, std::vector<KlauselZustand>& klausel_zustand){
    //Zustand der Klauseln in der die Variable vorkommt aktuallisieren
    klauseln_aktualisieren_variable_reseted(klausel_zustand, instanz.var(current_variable).klausel_wahr(), true);
    klauseln_aktualisieren_variable_reseted(klausel_zustand, instanz.var(current_variable).klausel_falsch(), false);

    //Wert der Variable aktualisieren:
    belegung.var_wert_aendern(current_variable, VariableWert::ungesetzt);
}

/*Beim Backtracking gehen wir folgendes Schema durch:
    1. Variable auf wahr setzten, wenn es geht gehen wir zur naechsten Variable sonst zu 2.
    2. Variable auf falsch setzten, wenn es geht gehen wir zur naechsten Variable sonst zu 3.
    3. Variable auf nicht gesetzt und gehen eine Variable nach hinten und untersuchen sie vom neuen
 */

std::optional<Wahrheitsbelegung> loese_mit_backtracking_algo(const SAT& instanz) {
    Wahrheitsbelegung belegung = Wahrheitsbelegung(instanz.anz_var()); //Wahrheitsbelegung mit allen Variablen auf ungesetzt
    std::vector<KlauselZustand> klausel_zustand (instanz.anz_klausel()); //Zunaechst auf Zustand gebracht wo alle Variablen ungesetzt sind
    VariableIndex current_variable = 1;

    while (current_variable > 0) {
        if (current_variable > instanz.anz_var()) { //Alle Variablen wurden ohne Wiederspruch belegt, somit eine Belegung gefunden
            return belegung;
        }

        if (belegung.var_wert(current_variable) == VariableWert::falsch) { //Schritt 3: Sowohl bei Wert der Variable true, wie auch false kommt es zu einem Wiederspruch
            reset_variable(current_variable, instanz, belegung, klausel_zustand);
            current_variable--; //Gehen zuruck im Backtracking
            continue;
        }
        
        bool wiederspruch = false;
        if (belegung.var_wert(current_variable) == VariableWert::ungesetzt) { //Schritt 1
            wiederspruch = pruefe_ob_wiederspruch_und_variable_neu_setzten(current_variable, instanz, belegung, klausel_zustand, true);
        }
        else { //Schritt 2
            wiederspruch = pruefe_ob_wiederspruch_und_variable_neu_setzten(current_variable, instanz, belegung, klausel_zustand, false);
        }

        if (!wiederspruch) { 
            current_variable++;
        }
    }
    //Falls current_variable == 0 heisst dies die Variable 1 wurde auf wahr und falsch gestelllt
    //und keine gueltige belgung wurde gefunden
    return std::nullopt;
}

//Ausdrucken der Loesung
std::optional<Wahrheitsbelegung> loese_mit_backtracking_alg_und_print_loesung(const SAT& instanz) {
    std::optional<Wahrheitsbelegung> loesung = loese_mit_backtracking_algo(instanz);
    if (loesung == std::nullopt) {
        std::cout << "Es gibt keine Loesung." << "\n";
    } 
    else {
        std::cout << "Folgende Wahrheitsbelgeung liefert Loesung" << "\n";
        loesung -> print();
    }
    return loesung;
}