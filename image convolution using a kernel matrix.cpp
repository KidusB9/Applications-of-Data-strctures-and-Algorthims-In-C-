#include <iostream>
#include <vector>
#include <cassert>

using Matrix = std::vector<std::vector<int>>;

Matrix ApplyKernel(const Matrix& image, const Matrix& kernel) {
    int kernelSize = kernel.size();
    int imageHeight = image.size();
    int imageWidth = image[0].size();

    // The result image will be smaller than the input image by the kernel size - 1
    Matrix result(imageHeight - kernelSize + 1, std::vector<int>(imageWidth - kernelSize + 1, 0));

    for (int i = 0; i < imageHeight - kernelSize + 1; ++i) {
        for (int j = 0; j < imageWidth - kernelSize + 1; ++j) {
            int value = 0;
            for (int ki = 0; ki < kernelSize; ++ki) {
                for (int kj = 0; kj < kernelSize; ++kj) {
                    value += image[i + ki][j + kj] * kernel[ki][kj];
                }
            }
            result[i][j] = value;
        }
    }

    return result;
}

int main() {
    // Example kernel for edge detection
    Matrix kernel = {
        { -1, -1, -1 },
        { -1,  8, -1 },
        { -1, -1, -1 }
    };

    // Sample image
    Matrix image = {
        { 0, 0, 0, 0, 0 },
        { 0, 100, 100, 100, 0 },
        { 0, 100, 100, 100, 0 },
        { 0, 100, 100, 100, 0 },
        { 0, 0, 0, 0, 0 }
    };

    Matrix result = ApplyKernel(image, kernel);

    // Output the result
    for (const auto& row : result) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
