//Implementierung von belegung_wahr.hpp
#include <belegung_wahr.hpp>

bool belegung_erfullt_SAT (const SAT& instanz,const Wahrheitsbelegung& belegung) {
    for (KlauselIndex current_klausel = 0; current_klausel < instanz.anz_klausel(); current_klausel++ ) {
        bool klausel_wahrheitswert = false;
        for (VariableIndex var_id: instanz.klausel(current_klausel).var_positiv()) {
            if (belegung.var_wert(var_id) == VariableWert::wahr) {
                klausel_wahrheitswert = true;
                break;
            }
        }
        if (!klausel_wahrheitswert) {
            for (VariableIndex var_id: instanz.klausel(current_klausel).var_negativ()) {
            if (belegung.var_wert(var_id)  == VariableWert::falsch) {
                klausel_wahrheitswert = true;
                break;
            }
        }
        }
        if (!klausel_wahrheitswert) { //Eine Klausel falsch, dann kann die boolsche Formel nicht mehr erfuellt werden
            return false;
        }
    }
    return true; //Alle Klauseln sind wahr und somit auch die boolsche Formel
}