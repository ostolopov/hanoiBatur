#include "utils.h"

int getInt(int &number, int min, int max) {
    while (true) {
        if (!(std::cin >> number)) {
            if (std::cin.eof()) {
                std::cout << "\nProgram terminated.\n";
                return 0;
            }
            std::cout << "Invalid number. Please try again!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (number < min || number > max) {
            std::cout << "The number is out of the allowed range. Please try again!\n";
            continue;
        }
        break;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return 1;
}