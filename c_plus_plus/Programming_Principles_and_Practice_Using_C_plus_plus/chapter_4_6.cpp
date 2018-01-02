#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

int main(int argc, char *argv[]) {
    std::vector<std::string> digit_spell_table {"zero", "one", "two", "three",   \
                                                "four", "five", "six", "seven",  \
                                                "eight", "nine"};
    std::string input;
    std::cin >> input;
    int index = 0;
    try {
        int digit = std::stoi(input);
        if ((digit < 0) || (digit >= digit_spell_table.size())) {
            std::cout << "Input error\n";
        } else {
            std::cout << digit_spell_table[digit] << std::endl;
        }
    } catch (std::invalid_argument) {
        for (auto& item : digit_spell_table) {
            if (item == input) {
                std::cout << index << std::endl;
                break;    
            } else {
                ++index;
            }
        }
        if (index >= digit_spell_table.size()) {
            std::cout << "Input error\n";
        }
    }
 
    return 0;
}