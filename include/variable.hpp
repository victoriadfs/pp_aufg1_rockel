#include <vector>
#include <iostream>

// Hier könntest Du einen typedef machen für die Variablen-Indizes.
// Das wäre hier möglich mit der folgenden Zeile
// using VariableIndex = unsigned int;
// Dann kannst Du den Namen VariableIndex im code verwenden 
// anstatt unsigned int.
// Also könntest Du den Konstruktor hier zum Beispiel deklarieren als
// Variable(const VariableIndex & var_id);
// Ist dann nur ein anderer Name für unsigned int, 
// aber viel einfacher zu lesen

class Variable {
    public:
    // integers brauchen nicht als const reference übergeben werden
    // Es ist besser dann zu kopieren, also
    // Variable(unsigned int var_id); 
    // (bzw mit dem typedef von oben Variable(VariableIndex var_id);)
    Variable(const unsigned int& var_id); //vllt noch exception bei var_id <= 0
    
    //Attribute der Variable ausgeben:
    unsigned int id() const; 
    const std::vector<unsigned int>& klausel_wahr() const;
    const std::vector<unsigned int>& klausel_falsch() const;

    // Hier auch ohne reference.
    //In Klausel einfuegen
    void wahr_in_klausel_hinzu(const unsigned int& neue_klausel);
    void falsch_in_klausel_hinzu(const unsigned int& neue_klausel);

    
    private:
    const unsigned int var_id_;
    std::vector<unsigned int> klausel_wahr_;
    std::vector<unsigned int> klausel_falsch_;
};
