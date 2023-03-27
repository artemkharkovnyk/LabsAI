#include "testcase_config.hpp"
#include "gen.hpp"

int main(){
    genalgorithm::Population population(n, f, pm, pc);
    population.StartEvolution(30);
}