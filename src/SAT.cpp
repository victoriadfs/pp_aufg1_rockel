//Momentan speichern der Variablen mit id-1
#include <SAT.hpp>

SAT::SAT (const unsigned int& anz_var):
    anz_var_(anz_var), anz_klausel_(0) {
    //Intialisierung der Variablen mit ID Zuordnung von 1 bis anz_var_
    for (unsigned int var_id = 1; var_id <= anz_var_; var_id++) {
        variablen_.push_back(Variable(var_id));
    }
}

//Attribute der SAT-Instanz ausgeben:
unsigned int SAT:: anz_var() const {
    return anz_var_;
}

unsigned int SAT:: anz_klausel() const {
    return anz_klausel_;
}

const std::vector<Variable>& SAT:: variablen() const {
    return variablen_;
}

// Hier würde sich ein assert(var_id > 0) auf jeden Fall anbieten.
Variable SAT::var(const unsigned int& var_id) const {
    return variablen_[var_id - 1]; //speichern Variablen mit einen Shift -1 in variablen_
}

const std::vector<Klausel>& SAT:: klauseln() const {
    return klauseln_;
}

Klausel SAT::klausel(const unsigned int& klausel_id) const {
    return klauseln_[klausel_id];
}


//Klausel hinzufuegen:
void SAT::klausel_hinzu(const Klausel& neue_klausel) {
    klauseln_.push_back(neue_klausel);
    anz_klausel_++;

    //Variablen aktualisieren, die in der Klausel auftauchen:
    for (const unsigned int& var_id : neue_klausel.var_positiv()) {
       variablen_[var_id - 1].wahr_in_klausel_hinzu(neue_klausel.id());
    }
    for (const unsigned int& var_id : neue_klausel.var_negativ()) {
        variablen_[var_id - 1].falsch_in_klausel_hinzu(neue_klausel.id());
    }
}

//Ausgeben der SAT-Instanz:
void SAT::print() const {
    std::cout << "Anzahl Variablen: " << anz_var_ << "\n";
    std::cout << "Anzahl Klauseln: " << anz_klausel_ << "\n";
    for (const Klausel& klausel : klauseln_){
        klausel.print();
    }
}
