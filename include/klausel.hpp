#include <vector>
#include <iostream>

class Klausel {
    public:
    Klausel(const unsigned int& klausel_id);

    //Attribute der Klausel ausgeben:
    unsigned int id() const;
    unsigned int anz_variablen() const;
    const std::vector<unsigned int>& var_positiv() const;
    const std::vector<unsigned int>& var_negativ() const;

    //Variable hinzufuegen:
    //muss der Absolute Wert der Variable jeweils gegeben werden:
    void positive_var_hinzu(const unsigned int& var_id);
    void negative_var_hinzu(const unsigned int& var_id);
    //hier mit VZ eingefuegt, muss nicht manuell eintscheiden ob die Variable positiv oder negativ ist
    void var_hinzu(const int& var_mit_vz); 

    //Ausgeben der Klausel:
    void print() const;

    private:
    const unsigned int klausel_id_;
    unsigned int anz_variablen_;
    std::vector<unsigned int> var_positiv_;
    std::vector<unsigned int> var_negativ_;
};