#include <iostream>
#include <vector>

void generate_permutations(std::vector<int>& nums, std::vector<bool>& used, std::vector<int>& current_permutation) {
    // If the current permutation is the same size as the input set, print it out and return
    if (current_permutation.size() == nums.size()) {
        for (int i = 0; i < current_permutation.size(); i++) {
            std::cout << current_permutation[i] << " ";
        }
        std::cout << std::endl;
        return;
    }
    
    // Try adding each unused integer to the current permutation and generate new permutations recursively
    for (int i = 0; i < nums.size(); i++) {
        if (!used[i]) {
            used[i] = true;
            current_permutation.push_back(nums[i]);
            generate_permutations(nums, used, current_permutation);
            current_permutation.pop_back();
            used[i] = false;
        }
    }
}

int main() {
    std::vector<int> nums = {1, 2, 3};
    std::vector<bool> used(nums.size(), false);
    std::vector<int> current_permutation;
    
    generate_permutations(nums, used, current_permutation);
    
    return 0;
}
