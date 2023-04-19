#include <vector>
#include <cassert>
#include <typedef.hpp>
#pragma once

class Variable {
    public:
    Variable(const VariableIndex var_id); // var_id > 0, sonst tritt Fehlermeldung auf
    
    //Attribute der Variable ausgeben:
    VariableIndex id() const; 
    const std::vector<KlauselIndex>& klausel_wahr() const;
    const std::vector<KlauselIndex>& klausel_falsch() const;

    //In Klausel einfuegen
    void wahr_in_klausel_hinzu(const KlauselIndex neue_klausel);
    void falsch_in_klausel_hinzu(const KlauselIndex neue_klausel);

    
    private:
    const VariableIndex var_id_;
    std::vector<KlauselIndex> klausel_wahr_;
    std::vector<KlauselIndex> klausel_falsch_;
};