#include <iostream>
#include <vector>
#include <string>

//  To Compute the Longest Prefix Suffix (LPS) array
std::vector<int> computeLPSArray(const std::string& pattern) {
    int M = pattern.size();
    std::vector<int> lps(M, 0);
    int len = 0;
    int i = 1;

    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

// KMP algorithm for substring search
std::vector<int> KMPSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> lps = computeLPSArray(pattern);
    std::vector<int> indices;
    int i = 0;
    int j = 0;

    while (i < text.size()) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == pattern.size()) {
            indices.push_back(i - j);
            j = lps[j - 1];
        } else if (i < text.size() && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return indices;
}

int main() {
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABCABAB";
    std::vector<int> indices = KMPSearch(text, pattern);

    if (!indices.empty()) {
        std::cout << "Pattern found at indices: ";
        for (int index : indices) {
            std::cout << index << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Pattern not found in text" << std::endl;
    }

    return 0;
}
