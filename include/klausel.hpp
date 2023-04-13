#include <vector>
#include <iostream>

// Für die Klausel-Indizes wäre ein typedef ebenfalls hilfreich
// z.B. using KlauselIndex = unsigned int;

class Klausel {
    public:
    // Ebenfalls ohne reference. Siehe variable.hpp.
    // Ich werde das an den restlichen Stellen nicht mehr schreiben,
    // Aber natürlich gilt das für alle const unsigned int&, 
    // die hier vorkommen.
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
