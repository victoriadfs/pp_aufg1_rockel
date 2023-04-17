//Implemenetierung von variable.hpp

#include <variable.hpp>

Variable::Variable(const VariableIndex var_id): 
    var_id_(var_id) {
        assert(var_id > 0);
    }

//Ausgeben von Attributen:
VariableIndex Variable::id() const {
    return var_id_;
}

const std::vector<KlauselIndex>& Variable::klausel_wahr() const {
    return klausel_wahr_;
}

const std::vector<KlauselIndex>& Variable::klausel_falsch() const {
    return klausel_falsch_;
}


//In Klausel einfuegen:
void Variable::wahr_in_klausel_hinzu(const KlauselIndex neue_klausel) {
    klausel_wahr_.push_back(neue_klausel);
}

void Variable::falsch_in_klausel_hinzu(const KlauselIndex neue_klausel) {
    klausel_falsch_.push_back(neue_klausel);
}
