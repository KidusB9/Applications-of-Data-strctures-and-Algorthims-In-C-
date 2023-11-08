#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

// Parameters for the genetic algorithm
const int POP_SIZE = 100;  // Size of the population
const std::string TARGET = "Kidus is Awesome!"; // Target string to evolve to
const int GENES = TARGET.size();  // Number of genes (characters in this case)
const int MAX_GEN = 1000;  // Maximum number of generations
const double MUTATION_RATE = 0.01;  // Mutation rate

// Function to generate a random character
char random_char() {
    int ascii = rand() % 90 + 32;  // Printable ASCII range
    return static_cast<char>(ascii);
}

// Individual in the population
struct Individual {
    std::string chromosome;
    int fitness;

    Individual() : chromosome(GENES, ' '), fitness(0) {}

    // Generate random genes
    void generate_genes() {
        for (auto& c : chromosome) {
            c = random_char();
        }
    }

    // Calculate fitness score, how many characters match the target
    void calculate_fitness() {
        fitness = 0;
        for (size_t i = 0; i < TARGET.size(); ++i) {
            if (chromosome[i] == TARGET[i]) {
                ++fitness;
            }
        }
    }
};

// Overload the < operator to sort by fitness
bool operator<(const Individual &ind1, const Individual &ind2) {
    return ind1.fitness < ind2.fitness;
}

// Main evolutionary algorithm
void evolve() {
    srand(static_cast<unsigned>(time(nullptr)));
    std::vector<Individual> population(POP_SIZE);

    // Initialize population
    for (auto& individual : population) {
        individual.generate_genes();
        individual.calculate_fitness();
    }

    int generation = 0;
    while (generation < MAX_GEN) {
        // Sort the population by fitness
        std::sort(population.begin(), population.end());

        // If the fittest individual matches the target, we're done
        if (population.back().fitness == GENES) {
            std::cout << "Generation " << generation << " | " << "Genes: " << population.back().chromosome << std::endl;
            break;
        }

        // Otherwise, create a new generation
        std::vector<Individual> new_generation;
        int s = POP_SIZE * 0.1;  // 10% of population goes to next generation
        for (int i = 0; i < s; ++i) {
            new_generation.push_back(population[i]);
        }

        // Breed the rest of the next generation
        s = POP_SIZE * 0.9;  // 90% of population is offspring
        for (int i = 0; i < s; ++i) {
            int len = POP_SIZE / 2;
            int r1 = rand() % len;
            int r2 = rand() % len;
            Individual offspring;
            offspring.chromosome = population[r1].chromosome.substr(0, GENES / 2) + population[r2].chromosome.substr(GENES / 2, GENES);
            // Mutations
            for (char &c : offspring.chromosome) {
                if ((rand() % 100) / 100.0 < MUTATION_RATE) {
                    c = random_char();
                }
            }
            offspring.calculate_fitness();
            new_generation.push_back(offspring);
        }
        population = new_generation;
        std::cout << "Generation " << generation << " | " << "Best fitness: " << population.back().fitness << std::endl;
        generation++;
    }
}

int main() {
    evolve();
    return 0;
}
