//Implementierung vom Backtracking Algorithmus
#include <backtracking.hpp>

struct KlauselZustand {
    //Initialisiert auf Werte vor dem keine Variable gesetzt worden ist
    unsigned int anz_gesetzer_variablen = 0;
    unsigned int anz_wahrer_variablen = 0;
};

struct BacktrackingZustand {
    const SAT& instanz;
    Wahrheitsbelegung belegung;
    std::vector<KlauselZustand> klausel_zustand;
};

//Variable neu setzten und pruefen ob hierbei ein Wiederspruch entsteht:

bool pruefe_ob_klausel_noch_wahr_werden_kann (const KlauselZustand& current_klausel_zustand, const Klausel& current_klausel) {
    //klausel kann nur noch wahr werden, wenn sie schon wahr ist oder noch variablen gesetzt werden mussen
    if (current_klausel_zustand.anz_wahrer_variablen > 0 || current_klausel.anz_variablen() != current_klausel_zustand.anz_gesetzer_variablen) {
        return true;
    }
    return false;
}

bool pruefe_ob_widerspruch_und_zustand_klauseln_nach_setzten_variable_aktualisieren (BacktrackingZustand& current_zustand, const bool variable_wert_in_klausel, const std::vector<KlauselIndex>& klauseln_zu_aktualisieren) {
    //variable_wert_in_klausel stellt den Wert da den die Variable in der Klausel animmt:
    // ZB variable x ist wahr und tritt positiv in Klausel auf variable_wert_in_klausel=true, falls sie negativ auftaucht variable_wert_in_klausel=false
    bool widerspruch = false;
    for (const KlauselIndex current_klausel: klauseln_zu_aktualisieren) {
        //Variable wird zum ersten Mal gesetzt
        current_zustand.klausel_zustand[current_klausel].anz_gesetzer_variablen++;
        
        if (variable_wert_in_klausel) {
            current_zustand.klausel_zustand[current_klausel].anz_wahrer_variablen++;
        }
        else {
            if (!pruefe_ob_klausel_noch_wahr_werden_kann(current_zustand.klausel_zustand[current_klausel], current_zustand.instanz.klausel(current_klausel))) {
                widerspruch = true;
            }
        }
    }
    return widerspruch;
}

bool pruefe_ob_widerspruch_und_variable_neu_setzten (const VariableIndex current_variable, BacktrackingZustand& current_zustand, VariableWert variable_new_wert) {
    
    //Zustand der Klauseln in der die Variable vorkommt aktualisieren:
    //variable_wert_in_klausel stellt den Wert da den die Variable in der Klausel animmt:
    //ZB variable x ist wahr und tritt positiv in Klausel auf variable_wert_in_klausel = true, falls sie negativ auftaucht variable_wert_in_klausel = false
    bool variable_wert_in_klausel = (VariableWert::wahr == variable_new_wert);
    bool const widerspruch_im_wahren_vorkommen = pruefe_ob_widerspruch_und_zustand_klauseln_nach_setzten_variable_aktualisieren(current_zustand, variable_wert_in_klausel, current_zustand.instanz.var(current_variable).klausel_wahr());
    variable_wert_in_klausel = not(variable_wert_in_klausel);
    bool const widerspruch_im_falschen_vorkommen = pruefe_ob_widerspruch_und_zustand_klauseln_nach_setzten_variable_aktualisieren(current_zustand, variable_wert_in_klausel, current_zustand.instanz.var(current_variable).klausel_falsch());
    
    //Aktualisieren Variable:
    current_zustand.belegung.var_wert_aendern(current_variable, variable_new_wert);
    
    return widerspruch_im_wahren_vorkommen or widerspruch_im_falschen_vorkommen; //Wenn es beim Aktualisieren der Klauseln zu keinem Wiederspruch gekommen ist, ist die Belegung bis zum Moment gueltig und man kann die naechste Variable setzten
}



//Reseten einer Variable und aktualisieren des Zustandes der Klauseln:

void klauseln_aktualisieren_variable_reseted(std::vector<KlauselZustand>& klausel_zustand, const std::vector<KlauselIndex>& klauseln_zu_aktualisieren, const bool variable_wert_in_klausel) {
    for (const KlauselIndex current_klausel : klauseln_zu_aktualisieren) {
        klausel_zustand[current_klausel].anz_gesetzer_variablen--; //Eine der frueher gesetzten Variablen ist nicht mehr gesetzt
        if (variable_wert_in_klausel) {
            //Die Variable war eine wahre Variable in der aktuellen Klausel
            klausel_zustand[current_klausel].anz_wahrer_variablen--;
        }
    }
}

void reset_variable (const VariableIndex current_variable, BacktrackingZustand& current_zustand){
    //Zustand der Klauseln in der die Variable vorkommt aktuallisieren
    bool variable_wert_in_klausel = (VariableWert::wahr == current_zustand.belegung.var_wert(current_variable));
    klauseln_aktualisieren_variable_reseted(current_zustand.klausel_zustand, current_zustand.instanz.var(current_variable).klausel_wahr(), variable_wert_in_klausel);
    variable_wert_in_klausel = not(variable_wert_in_klausel);
    klauseln_aktualisieren_variable_reseted(current_zustand.klausel_zustand, current_zustand.instanz.var(current_variable).klausel_falsch(), variable_wert_in_klausel);

    //Wert der Variable aktualisieren:
    current_zustand.belegung.var_wert_aendern(current_variable, VariableWert::ungesetzt);
}



/*Beim Backtracking gehen wir folgendes Schema durch:
    1. Variable auf wahr setzten, wenn es geht gehen wir zur naechsten Variable sonst zu 2.
    2. Variable auf falsch setzten, wenn es geht gehen wir zur naechsten Variable sonst zu 3.
    3. Variable auf nicht gesetzt und gehen eine Variable nach hinten und untersuchen sie vom neuen
 */

std::optional<Wahrheitsbelegung> loese_mit_backtracking_algo(const SAT& instanz) {
    BacktrackingZustand current_zustand {instanz, Wahrheitsbelegung(instanz.anz_var()), std::vector<KlauselZustand>(instanz.anz_klausel())}; //Initialisierung auf alle Variablen ungesetzt
    VariableIndex current_variable = 1;
    while (current_variable > 0) {
        if (current_variable > instanz.anz_var()) { //Alle Variablen wurden ohne Wiederspruch belegt, somit eine Belegung gefunden
            return current_zustand.belegung;
        }

        if (current_zustand.belegung.var_wert(current_variable) == VariableWert::falsch) { //Schritt 3: Sowohl bei Wert der Variable true, wie auch false kommt es zu einem Wiederspruch
            reset_variable(current_variable, current_zustand);
            current_variable--; //Gehen zuruck im Backtracking
            continue;
        }
        
        bool wiederspruch = false;
        if (current_zustand.belegung.var_wert(current_variable) == VariableWert::ungesetzt) { //Schritt 1
            wiederspruch = pruefe_ob_widerspruch_und_variable_neu_setzten(current_variable, current_zustand, VariableWert::wahr);
        }
        else { //Schritt 2
            reset_variable(current_variable, current_zustand); //Wird gemacht, da in naechster Funktion angenommen wird, dass die Variable nicht gesetzt ist
            wiederspruch = pruefe_ob_widerspruch_und_variable_neu_setzten(current_variable, current_zustand, VariableWert::falsch);
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