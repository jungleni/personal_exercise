#include <iostream>
#include <string>
#include <cmath>

int main (int argc, char *argv[]) {
    std::cout << "Please enter two double nums and an operator!\n"
                    "for example: 3.14-2.0\n";
    double left_num = 0.0;
    double right_num = 0.0;
    char opera = '+';

    std::cin >> left_num >> opera >> right_num;

    double result = 0.0;
    bool input_legal = true;
    std::string opera_str = "sum";

    switch (opera) {
        case '+':
            opera_str = "sum";
            result = left_num + right_num;
            break;
        
        case '-':
            opera_str = "difference";
            result = left_num - right_num;
            break;

        case '*':
            opera_str = "product";
            result = left_num * right_num;
            break;

        case '/':
            if (right_num == 0.0) {
                input_legal = false;
            } else {
                opera_str = "division";
                result = left_num / right_num;
            }
            break;

        case '%':
            if (right_num == 0.0) {
                input_legal = false;
            } else {
                opera_str = "module";
                double convert_left_num = std::abs(left_num);
                double convert_right_num = std::abs(right_num);
                while (convert_left_num >= convert_right_num) {
                    convert_left_num -= convert_right_num;
                }
                if (left_num < 0) {
                    result = convert_left_num * (-1);
                } else {
                    result = convert_left_num;
                }
            }
            break;

        default:
            input_legal = false;
            break;
    }

    if (input_legal) {
        std::cout << "The " << opera_str << " of " << left_num << " and "
                    << right_num << " is " << result << std::endl;
    } else {
        std::cout << "Please check your input!\n";
    }

    return 0;
} 