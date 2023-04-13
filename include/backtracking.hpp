/*Bemerkung:
    Im folgenden Code wird von SAT, Klausel, Variablen aktualisieren, aendern, setzten gespeochen.
    Hierbei ist immer die Wahrheitsbelegung und andere Attribute wie Anzahl der gesetzten Variablen in einer Klausel gemeint.
    Obwohl dies nicht ganz formal korrekt ist, wird es so ausgedrueckt um den Code zu vereinfachen.
    Die SAT Instanz selber wird in keinem Moment modifiziert.
*/
#include <SAT.hpp>
#include <wahrheitsbelegung.hpp>

class Backtracking_Loesung {
    public:
    Backtracking_Loesung (const SAT& instanz);
    void loesen();

    private:
    //Atribute:
    const SAT instanz;
    Wahrheitsbelegung wbelegung;
    std::vector<unsigned int> klausel_anz_gez_var;
    std::vector<unsigned int> klausel_anz_wahrer_var;
    std::vector<uint_fast8_t> klausel_wwert;
    
    //Hilfsfunktionen:

    //Variablen aendern in der Wbelegung:
    unsigned int variable_wahr(const unsigned int& var_id);
    unsigned int variable_falsch(const unsigned int& var_id);
    unsigned int variable_nicht_gesetzt(const unsigned int& var_id);

    //SAT aktualisieren nach setzten einer Variable:
    bool klausel_kann_noch_wahr_werden (const unsigned int& klausel_id) const;
    void klausel_var_wahr_setzten(const unsigned int& klausel_id, const bool& frueher_gesetzt);
    void klausel_var_falsch_setzten(const unsigned int& klausel_id, const bool& frueher_gesetzt);
    void klauseln_aktualisieren_setzten_variable(const unsigned int& var_id, const bool& neuer_wwert, const std::vector<unsigned int>& klausel, const bool& var_vz, bool& belegung_gueltig);
    bool SAT_aktualisieren_setzten_variable(const unsigned int& var_id, const bool& neuer_wwert);

    //SAT aktualisieren nach Variable auf nicht gesetzt:
    void klausel_wahre_var_nicht_gesetzt(const unsigned int& klausel_id);
    void klausel_falsche_var_nicht_gesetzt(const unsigned int& klausel_id);
    void klauseln_aktualisieren_variable_nicht_setzten(const unsigned int& var_id, const std::vector<unsigned int>& klausel, const bool& var_vz);
    void SAT_aktualisieren_variable_nicht_setzten(const unsigned int& var_id);

    //Ende Backtracking und Output
    void keine_loesung() const;
    void loesung_ausgeben() const;
    bool ende_backtracking(const unsigned int& var_id) const;
};