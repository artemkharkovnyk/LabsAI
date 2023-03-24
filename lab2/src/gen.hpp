#include <stdlib.h>
#include <math.h>
#include <functional>
#include <iostream>

namespace genalgorithm{
    class Population{
        public:
            int numberOfindividuals;
            int* individuals;
            std::function<double(double)> qualityCriterion;
            int** parentPairs;
            double mutationProb;
            double crossingProb;
            Population(
                int numberOfindividuals, 
                std::function<double(double)> qualityCriterion,
                double mutationProb, 
                double crossingProb);

            void StartEvolution(int epochs);

        private:
            double* crossingProbs;
            void Mutation(int* individual, int bitindex);
            void Mutation(int* individual);
            void ComputeCrossingProbs();
            void SelectPairs();
            double Crossing(int parent1, int parent2);
            void Crossing();
    };
}

