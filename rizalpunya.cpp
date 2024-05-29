#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Creating a 2D vector of size 4x5, where each item is a vector of two integers
    std::vector<std::vector<std::vector<int>>> matrix(4, std::vector<std::vector<int>>(5, std::vector<int>(2)));

    // Accessing and printing elements
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 5; ++j) {
            // Accessing default-initialized values of a plate
            std::cout << "(" << matrix[i][j][0] << ", " << matrix[i][j][1] << ") ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}