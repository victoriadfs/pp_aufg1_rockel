#include <vector>
#include <iostream>
#pragma once
typedef unsigned int VariableIndex;
typedef unsigned int KlauselIndex;

class Klausel {
    public:
    Klausel(const KlauselIndex klausel_id);

    //Attribute der Klausel ausgeben:
    KlauselIndex id() const;
    unsigned int anz_variablen() const;
    const std::vector<VariableIndex>& var_positiv() const;
    const std::vector<VariableIndex>& var_negativ() const;

    //Variable hinzufuegen:
    //muss der Absolute Wert der Variable jeweils gegeben werden:
    void positive_var_hinzu(const VariableIndex var_id);
    void negative_var_hinzu(const VariableIndex var_id);
    //hier mit VZ eingefuegt, muss nicht manuell eintscheiden ob die Variable positiv oder negativ ist
    void var_hinzu(const int var_mit_vz); 
    
    //Ausgeben der Klausel:
    void print() const;

    private:
    const KlauselIndex klausel_id_;
    unsigned int anz_variablen_;
    std::vector<VariableIndex> var_positiv_;
    std::vector<VariableIndex> var_negativ_;
};