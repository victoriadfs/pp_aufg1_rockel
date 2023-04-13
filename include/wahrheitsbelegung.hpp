/*Bemerkung:
Variablen haben die als id 1 - anz_var und man kann durch die ID deren Wahrheitwert erfahren oder wissen ob sie gesetzt wurde.
Beim (nicht) setzen von Variablen soll der eigendliche ID benutzt werden (1 - anz_var).
In den vectoren kommt immer ein id - 1 shift vor dem sich der user bewusst machen sollte.
*/
#include <vector>
#include <iostream>
class Wahrheitsbelegung {
    public:
    Wahrheitsbelegung(const unsigned int& anz_var);

    //Attribute Wahrheitsbeleging ausgeben:
    unsigned int anz_var() const;
    const std::vector<uint_fast8_t>& belegung() const;
    unsigned int var_wert (const unsigned int& var_id) const;
    const std::vector<uint_fast8_t>& gesetzt() const;
    unsigned int var_gesetzt(const unsigned int& var_id) const;

    // Hier bietet es sich an ein enum zu verwenden für den Zustand
    // einer Variable. Das macht es noch einfacher lesbar:
    // enum class VariablenWert {
    //    wahr,
    //    falsch,
    //    ungesetzt
    // };
    // Dann kannst Du Dir den 2. vector sparen und nur
    // std::vector<VariablenWert> belegung_;
    // speichern.
    // var_nicht_gesetzt kannst Du dann z.B. implementieren als  
    // belegung_[var_id-1] = VariablenWert::ungesetzt;
    
    //Wahrheitsbelegung aendern:
    void var_setzten(const unsigned int& var_id, const uint_fast8_t& wahrheitswert);
    void var_nicht_gesetzt(const unsigned int& var_id);

    //Ausgeben der Wahrheitsbelegung:
    void print() const; //maybe meter una exception si uno no esta gesetzt


    private:
    const unsigned int anz_var_;
    std::vector<uint_fast8_t> belegung_;
    std::vector<uint_fast8_t> gesetzt_;
};
