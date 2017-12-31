#include <iostream>

const int MIN_NUM = 1;
const int MAX_NUM = 100;

bool get_guess_result_from_usr(int guess_num);

int main(int argc, char *argv[])
{
    int left_edge = MIN_NUM;
    int right_edge = MAX_NUM;
    int guess_num = (left_edge + right_edge) / 2;
    bool this_result = false;
    while (left_edge != right_edge) {
        this_result = get_guess_result_from_usr(guess_num);
        if (this_result) {
            right_edge = guess_num;
        } else {
            left_edge = guess_num;  
        }
        
        guess_num = (left_edge + right_edge) / 2;
        
        if (guess_num == left_edge) {
            if (this_result) {
                guess_num = left_edge;    
            } else {
                guess_num = right_edge;    
            }
            break;
        }
    }
    
    std::cout << "The num is " << guess_num << std::endl;
    
    return 0;
}

bool get_guess_result_from_usr(int guess_num) {
    std::cout << "Is your num less than " << guess_num << " ? (y/n): ";
    char res = 'y';
    std::cin >> res;
    if (res == 'y') {
        return true;    
    } else {
        return false;    
    }
}

