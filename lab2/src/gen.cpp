

#include "gen.hpp"

genalgorithm::Population::Population(
    int numberOfindividuals, 
    std::function<double(double)> qualityCriterion,
    double mutationProb, 
    double crossingProb){

    this->numberOfindividuals = numberOfindividuals;
    this->qualityCriterion = qualityCriterion;
    int *individuals = new int[numberOfindividuals];
    double *crossingProbs = new double[numberOfindividuals];
    this->individuals = individuals;
    this->mutationProb = mutationProb;
    this->crossingProb = crossingProb;
    int **parentPairs = new int*[numberOfindividuals/2];
    for(int i = 0; i < numberOfindividuals/2; ++i) {
        parentPairs[i] = new int[2];
    }
    this->parentPairs = parentPairs;
    this->crossingProbs = crossingProbs;
    for (int i = 0; i < numberOfindividuals; i++){
        this->individuals[i] = std::rand() % 256;
    }

}

void genalgorithm::Population::Mutation(int* individual){
    for (int i = 0; i < 8; i++){
        double x = ((double)rand()/(double)RAND_MAX);
        if (x <= this->mutationProb){
            this->Mutation(individual, i);
        }
    }
}

void genalgorithm::Population::Mutation(int* individual, int bitindex){
    int sign = !((int)((*individual) / std::pow(2, bitindex)) % 2) * 2 - 1;
    int delta = std::pow(2, bitindex);
    (*individual) = (*individual) + sign * delta;
}

void genalgorithm::Population::ComputeCrossingProbs(){
    double min_value = 1e+10;
    double fsum = 0;
    for(int i = 0; i < this->numberOfindividuals; i++){
        double f = this->qualityCriterion(this->individuals[i]);
        if (f < min_value){
            min_value = f;
        }
        fsum = fsum + f;
        this->crossingProbs[i] = f;
    }
    min_value = min_value - 1;
    std::cout << "  mean value of quality function: " << fsum / this->numberOfindividuals << std::endl;
    std::cout << "  first 5 individuals: ";
    for (int i = 0 ; i < 5; i++){
        std::cout << this->individuals[i] << " ";
    }
    std::cout << std::endl;
    fsum = fsum - min_value * this->numberOfindividuals;
    for(int i = 0; i < this->numberOfindividuals; i++){
        this->crossingProbs[i] = (this->crossingProbs[i] - min_value) / fsum;
        if (i != 0){
            this->crossingProbs[i] = this->crossingProbs[i] + this->crossingProbs[i-1];
        }
    }
    
}

void genalgorithm::Population::SelectPairs(){
    for (int i = 0; i < this->numberOfindividuals; i++){
        double x = ((double)rand()/(double)RAND_MAX);
        int j = 0;
        while(x > this->crossingProbs[j]){ j++; }
        this->parentPairs[i/2][i%2] = this->individuals[j];
    }
}

double genalgorithm::Population::Crossing(int parent1, int parent2){
    int
        input1 = parent1,
        n_bits1 = 8,
        *bits1 = (int*)malloc(sizeof(int) * n_bits1),
        bit1 = 0;
    for(bit1 = 7; bit1 != -1; bit1--)
        bits1[bit1] = (input1 >> bit1) & 1;

    int
        input2 = parent2,
        n_bits2 = 8,
        *bits2 = (int*)malloc(sizeof(int) * n_bits2),
        bit2 = 0;
    for(bit2 = 7; bit2 != -1; bit2--)
        bits2[bit2] = (input2 >> bit2) & 1;

    int child = 0;
    int gen;
    for (int i = 0; i < 8; i++){
        int x = std::rand() % 2;
        if (x == 0){ gen = bits1[i]; }
        else{ gen = bits2[i]; }
        if (gen == 1){child = child + std::pow(2, i); }
    }
    this->Mutation(&child);
    return child;
    
}

void genalgorithm::Population::Crossing(){
    for (int i = 0; i < this->numberOfindividuals / 2; i++){
        double x = ((double)rand()/(double)RAND_MAX);
        if (x < this->crossingProb){
            this->individuals[i*2] = this->Crossing(this->parentPairs[i][0], this->parentPairs[i][1]);
            this->individuals[i*2+1] = this->Crossing(this->parentPairs[i][0], this->parentPairs[i][1]);
        }
        else{
            this->individuals[i*2] = this->parentPairs[i][0];
            this->individuals[i*2+1] = this->parentPairs[i][1];
        }
    }
}

void genalgorithm::Population::StartEvolution(int epochs){
    for (int epoch = 1; epoch <= epochs; epoch++){
        std::cout << "epoch " << epoch << std::endl;
        this->ComputeCrossingProbs();
        this->SelectPairs();
        this->Crossing();
    }
}