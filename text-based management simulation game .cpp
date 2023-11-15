#include <iostream>
#include <string>
#include <vector>
#include <map>

class Crop {
public:
    std::string name;
    int daysToHarvest;
    int yield;

    Crop(std::string name, int daysToHarvest, int yield) : name(std::move(name)), daysToHarvest(daysToHarvest), yield(yield) {}

    virtual int harvest() {
        std::cout << "Harvested " << name << " yielding " << yield << " units." << std::endl;
        return yield;
    }
};

class Farm {
    std::map<std::string, int> storage;
    std::vector<Crop> crops;

public:
    void plantCrop(const Crop& crop) {
        crops.push_back(crop);
        std::cout << "Planted " << crop.name << std::endl;
    }

    void harvestCrops() {
        for (auto& crop : crops) {
            int cropYield = crop.harvest();
            storage[crop.name] += cropYield;
        }
        crops.clear();
    }

    void showStorage() const {
        std::cout << "Farm Storage:" << std::endl;
        for (const auto& item : storage) {
            std::cout << item.first << ": " << item.second << " units" << std::endl;
        }
    }
};

int main() {
    Farm myFarm;
    myFarm.plantCrop(Crop("Wheat", 7, 10));
    myFarm.plantCrop(Crop("Corn", 5, 15));

    // Simulate passing of time
    myFarm.harvestCrops();

    myFarm.showStorage();

    return 0;
}
