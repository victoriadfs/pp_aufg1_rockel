#include <wahrheitsbelegung.hpp>

Wahrheitsbelegung::Wahrheitsbelegung(const unsigned int& anz_var):
    anz_var_(anz_var), belegung_(anz_var, 0), gesetzt_(anz_var, 0) {
        //Speichern Daten der Variblen mit einen shift -1 in den Vektoren:
    };

//Attribute Wahrheitsbelegung ausgeben:
unsigned int Wahrheitsbelegung::anz_var() const{
    return anz_var_;
}

const std::vector<uint_fast8_t>& Wahrheitsbelegung:: belegung() const {
    return belegung_;
}

unsigned int Wahrheitsbelegung::var_wert(const unsigned int& var_id) const {
    return belegung_[var_id - 1];
}

const std::vector<uint_fast8_t>& Wahrheitsbelegung:: gesetzt() const {
    return gesetzt_;
}

unsigned int Wahrheitsbelegung::var_gesetzt(const unsigned int& var_id) const{
    return gesetzt_[var_id - 1];
}


//Wahrheitsbelegung aendern:
void Wahrheitsbelegung::var_setzten(const unsigned int& var_id, const uint_fast8_t& wahrheitswert) {
    belegung_[var_id - 1] = wahrheitswert;
    gesetzt_[var_id - 1] = 1; //Gesetzt auf wahr
}

void Wahrheitsbelegung::var_nicht_gesetzt(const unsigned int& var_id) {
    belegung_[var_id - 1] = 0;
    gesetzt_[var_id - 1] = 0; //gesetzt auf falsch
}


//Wahrheitsbelegung ausgeben:
void Wahrheitsbelegung::print() const{
    for (unsigned int var_id = 0 ; var_id < anz_var_ ; var_id++) {
        std::cout << "Variable " << var_id + 1 << ": " << this -> var_wert(var_id + 1) << "\n";
    }
}



