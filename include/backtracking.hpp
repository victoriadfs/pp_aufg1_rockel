#include <SAT.hpp>
#include <wahrheitsbelegung.hpp>
#include <optional>

std::optional<Wahrheitsbelegung> loese_mit_backtracking_algo(const SAT& instanz);
std::optional<Wahrheitsbelegung> loese_mit_backtracking_alg_und_print_loesung(const SAT& instanz);