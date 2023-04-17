/*Bemerkung:
Variablen haben die als id 1 - anz_var und man kann durch die ID deren Wahrheitwert erfahren oder wissen ob sie gesetzt wurde.
Beim (nicht) setzen von Variablen soll der eigendliche ID benutzt werden (1 - anz_var).
In den vectoren kommt immer ein id - 1 shift vor dem sich der user bewusst machen sollte.
*/
#include <vector>
#include <iostream>
#include <cassert>
#pragma once
typedef unsigned int VariableIndex;

enum class VariableWert {
    wahr,
    falsch,
    ungesetzt
};

class Wahrheitsbelegung {
    public:
    Wahrheitsbelegung(const unsigned int anz_var);

    //Attribute ausgeben:
    unsigned int anz_var() const;
    const std::vector<VariableWert>& belegung() const;
    VariableWert var_wert(const VariableIndex var_id) const;

    //Wahrheitsbelegung aendern:
    void var_wert_aendern(const VariableIndex var_id, const VariableWert neuer_wert);

    //Ausdrucken der Wahrheitsbelegung
    void print() const;
    
    private:
    const unsigned int anz_var_;
    std::vector<VariableWert> belegung_;
};
