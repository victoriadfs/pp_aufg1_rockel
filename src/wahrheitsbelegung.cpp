//Implementierung von wahrheitsbelegung.hpp
#include <wahrheitsbelegung.hpp>

Wahrheitsbelegung::Wahrheitsbelegung(const unsigned int anz_var):
    anz_var_(anz_var), belegung_(anz_var, VariableWert::ungesetzt) {}

//Ausgeben der Attribute:
unsigned int Wahrheitsbelegung::anz_var() const {
    return anz_var_;
}

const std::vector<VariableWert>& Wahrheitsbelegung::belegung() const {
    return belegung_;
}

VariableWert Wahrheitsbelegung::var_wert(const VariableIndex var_id) const{
    assert(var_id > 0);
    assert(var_id <= anz_var_);
    return belegung_[var_id - 1];
}


//Wahrheitsbelegung aendern:
void Wahrheitsbelegung::var_wert_aendern(const VariableIndex var_id, const VariableWert neuer_wert) {
    assert(var_id > 0);
    assert(var_id <= anz_var_);
    belegung_[var_id - 1] = neuer_wert;
}

//Ausdrucken der Wahrheitsbelegung:
void Wahrheitsbelegung::print() const {
    for (VariableIndex current_variable = 1; current_variable <= anz_var_; current_variable++) {
        std::cout << "Variable " << current_variable << ": ";
        if (belegung_[current_variable - 1] == VariableWert::wahr) {
            std::cout << 1 << "\n";
        }
        else if (belegung_[current_variable - 1] == VariableWert::falsch) {
            std::cout << 0 << "\n";
        }
        else {
            std::cout << "ungesetzt" <<"\n";
        }
    }
}
