/*Bemerkung:
Variablen haben  als id 1 - anz_var und man kann dur die iD auch auf sie mit Variable var(id) zugreifen.
In dem  vector variablen sind diese aber mit einem id - 1 shift gespeichert, dies sollte man bedenken, wenn man 
direkt den vector<Variable>variablen benutzt.
Bei Klauseln bekommt man mit klausel(id) auch die Klausel zuruck die in klauseln[id] gespeichert wird. 
Diese stirmmt mit dem Klauselindex ueberein, wird bei klausel_hinzu erzwungen */
#include <variable.hpp>
#include <klausel.hpp>
#pragma once

class SAT {
    public:
    SAT(const unsigned int anz_var);

    //Attribute der SAT-Instanz ausgeben:
    unsigned int anz_var() const;
    unsigned int anz_klausel() const;
    const std::vector<Variable>& variablen() const;
    const Variable& var(const VariableIndex var_id) const;
    const std::vector<Klausel>& klauseln() const;
    const Klausel& klausel(const KlauselIndex klausel_id) const;

    //Klausel hinzufuegen:
    void klausel_hinzu(const Klausel& neue_klausel); //Nur Klausel mit Klauselindex = anz_klausel_ vor dem Einfuegen kann eingefuegt werden

    //Ausgeben SAT-Instanz:
    void print() const;

    private:
    const unsigned int anz_var_;
    unsigned int anz_klausel_;
    std::vector<Variable> variablen_;
    std::vector<Klausel> klauseln_;
};

