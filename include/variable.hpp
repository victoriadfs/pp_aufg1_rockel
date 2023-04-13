#include <vector>
#include <iostream>

class Variable {
    public:
    Variable(const unsigned int& var_id); //vllt noch exception bei var_id <= 0
    
    //Attribute der Variable ausgeben:
    unsigned int id() const; 
    const std::vector<unsigned int>& klausel_wahr() const;
    const std::vector<unsigned int>& klausel_falsch() const;

    //In Klausel einfuegen
    void wahr_in_klausel_hinzu(const unsigned int& neue_klausel);
    void falsch_in_klausel_hinzu(const unsigned int& neue_klausel);

    
    private:
    const unsigned int var_id_;
    std::vector<unsigned int> klausel_wahr_;
    std::vector<unsigned int> klausel_falsch_;
};