//Implemenetierung von variable.hpp

#include <variable.hpp>

// Wenn Du einen check machen willst hier, dann wäre ein assert ganz gut
// #include <cassert>
// Dann kannst Du hier im body des Konstruktors schreiben
// assert(var_id > 0);
// Sollte das mal nicht wahr sein, dann gibt es eine exception.
Variable::Variable(const unsigned int& var_id): 
    var_id_(var_id) {}
    
// Solltest Du, wie im header empfohlen hier var_id nicht als const reference übergeben,
// dann ist es trotzdem möglich und hilfreich die variable hier als const parameter zu bekommen.
// Also
/**
 * Variable::Variable(const VariableIndex var_id): 
 *   var_id_(var_id) {}
 */

//Ausgeben von Attributen:
unsigned int Variable::id() const {
    return var_id_;
}

const std::vector<unsigned int>& Variable::klausel_wahr() const {
    return klausel_wahr_;
}

const std::vector<unsigned int>& Variable::klausel_falsch() const {
    return klausel_falsch_;
}


//In Klausel einfuegen:
void Variable::wahr_in_klausel_hinzu(const unsigned int& neue_klausel) {
    klausel_wahr_.push_back(neue_klausel);
}

void Variable::falsch_in_klausel_hinzu(const unsigned int& neue_klausel) {
    klausel_falsch_.push_back(neue_klausel);
}
