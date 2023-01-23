//kidus berhanu
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

const int POPULATION_SIZE = 100;
const int CHROMOSOME_LENGTH = 10;
const int MAX_GENERATIONS = 1000;

struct Individual {
    std::vector<int> chromosome;
    double fitness;
    Individual(const std::vector<int> &chromosome) : chromosome(chromosome) {}
};

// Generates a random chromosome
std::vector<int> generateRandomChromosome() {
    std::vector<int> chromosome;
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        chromosome.push_back(rand() % 2);
    }
    return chromosome;
}

// Evaluates the fitness of an individual
double evaluateFitness(const std::vector<int> &chromosome) {
    int sum = 0;
    for (int gene : chromosome) {
        sum += gene;
    }
    return (double)sum / CHROMOSOME_LENGTH;
}

// Selects an individual using tournament selection
Individual tournamentSelection(const std::vector<Individual> &population) {
    std::vector<Individual> competitors;
    for (int i = 0; i < 4; i++) {
        competitors.push_back(population[rand() % POPULATION_SIZE]);
    }
    std::sort(competitors.begin(), competitors.end(), [](const Individual &a, const Individual &b) {
        return a.fitness > b.fitness;
    });
    return competitors[0];
}

// Performs crossover (recombination) of two individuals' chromosomes
std::vector<int> crossover(const std::vector<int> &chromosome1, const std::vector<int> &chromosome2) {
    std::vector<int> offspring;
    for (int i = 0; i < CHROMOSOME_LENGTH; i++) {
        offspring.push_back(rand() % 2 == 0 ? chromosome1[i] : chromosome2[i]);
    }
    return offspring;
}

// Introduces random mutations in an individual's chromosome
void mutate(std::vector<int> &chromosome) {
    for (int &gene : chromosome) {
        if (rand() / (double)RAND_MAX < 0.05) {
            gene ^= 1;
        }
    }
}

int main() {
    std::vector<Individual> population;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population.push_back(Individual(generateRandomChromosome()));
    }

    for (int generation = 0; generation < MAX_GENERATIONS; generation++) {
        for (auto &individual : population) {
            individual.fitness = evaluateF
