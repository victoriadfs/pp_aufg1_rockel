//Implementierung von klausel.hpp
#include <klausel.hpp>

Klausel::Klausel(const KlauselIndex klausel_id):
    klausel_id_(klausel_id), anz_variablen_(0) {}

//Attribute der Klausel ausgeben:
KlauselIndex Klausel::id() const {
    return klausel_id_;
}

unsigned int Klausel::anz_variablen() const {
    return anz_variablen_;
}

const std::vector<VariableIndex>& Klausel::var_positiv() const {
    return var_positiv_;
}

const std::vector<VariableIndex>& Klausel::var_negativ() const {
    return var_negativ_;
}


//Variable hinzufuegen:
void Klausel::positive_var_hinzu(const VariableIndex var_id) {
    assert(var_id > 0);
    var_positiv_.push_back(var_id);
    anz_variablen_++;
}

void Klausel::negative_var_hinzu(const VariableIndex var_id) {
    assert(var_id > 0);
    var_negativ_.push_back(var_id);
    anz_variablen_++;
}

void Klausel::var_hinzu(const int var_mit_vz) {
    if(var_mit_vz > 0) {
        positive_var_hinzu(var_mit_vz);
    }
    else {
        negative_var_hinzu(abs(var_mit_vz));
    }
}

//Ausgeben der Klausel:
void Klausel::print() const {
    std::cout << "Klausel " << klausel_id_ << ":  ";
    for (const VariableIndex var_id : var_positiv_) {
        std::cout << var_id << " ";
    }
    for (const VariableIndex var_id : var_negativ_) {
        std::cout << -var_id << " ";
    }
    std::cout << "\n";
}