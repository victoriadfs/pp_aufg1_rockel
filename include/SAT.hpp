/*Bemerkung:
Variablen haben die als id 1 - anz_var und man kann dur die iD auch auf sie mit Variable var(id) zugreifen.
In dem  vector variablen sind diese aber mit einem id - 1 shift gespeichert, dies sollte man bedenken, wenn man 
direkt den vector<Variable>variablen benutzt.
Bei Klauseln bekommt man mit klausel(id) auch die Klausel zuruck die in klauseln[id] gespeichert wird. 
Im allgemeinen muss dies nicht mit der wirklichen Klausel_id uebereinstimmen, sondern entspricht nur 
der Reihenfolge in welchen die Klausel hinzugefuegt worden sind.
Wenn man die in examples/main.cpp einlesefunktion benutzt stimmt der Klausel_id auch mit dem klausel_id
ueberein, mit dem man die Klausel in der SAT Instanz erreicht */
#include <variable.hpp>
#include <klausel.hpp>


class SAT {
    public:
    SAT(const unsigned int& anz_var);

    //Attribute der SAT-Instanz ausgeben:
    unsigned int anz_var() const;
    unsigned int anz_klausel() const;
    const std::vector<Variable>& variablen() const;
    Variable var(const unsigned int& var_id) const;
    const std::vector<Klausel>& klauseln() const;
    Klausel klausel(const unsigned int& klausel_id) const;

    //Klausel hinzufuegen:
    void klausel_hinzu(const Klausel& neue_klausel);

    //Ausgeben SAT-Instanz:
    void print() const;

    private:
    const unsigned int anz_var_;
    unsigned int anz_klausel_;
    std::vector<Variable> variablen_;
    std::vector<Klausel> klauseln_;
};

