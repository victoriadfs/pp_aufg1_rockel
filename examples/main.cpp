#include <backtracking.hpp>
#include <DIMACS_einlesen.hpp>
#include <belegung_wahr.hpp>


int main(int argc, char* argv[]){
    if (argc > 1) {
        SAT instanz = dimacs_einlesen(argv[1]); //Einlesen
        std::optional<Wahrheitsbelegung> loesung = loese_mit_backtracking_alg_und_print_loesung(instanz);
        if (loesung != std::nullopt)
            std::cout << belegung_erfullt_SAT(instanz, loesung.value());
    }
}
//clang++ -std=c++17 -o test -I./include src/DIMACS_einlesen.cpp src/SAT.cpp src/belegung_wahr.cpp src/wahrheitsbelegung.cpp src/backtracking.cpp src/klausel.cpp src/variable.cpp \examples/main.cpp 
//./test \files/test1.txt




