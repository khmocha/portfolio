#include <iostream>

int main() {
    int a = 3;
    int b = 11;

    int ISize = 100000;
    int JSize = 300000;

    for (int i = 1; i < ISize; i++) {
        if ((a * i) - (b * 1) <= 0) {
            continue;
        }

        for (int j = -100000; j < JSize; j++) {
            if ((a * i) - (b * JSize) <= 0) {
                break;
            }

            if ((a * i) - (b * j) == 1) {
                std::cout << i << " " << j << "\n";
                std::cout << "The multiplicative inverse is " << i << "\n";
                return 0;
            }

            
        }
    }

    std::cout << "No multiplicative inverse exist" << std::endl;

    return 0;
}