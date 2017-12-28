#include <iostream>

class Test {
public:    
    template <typename T>
    void print(T& input) {
        std::cout << "template input = " << input << std::endl;
    }
};

template <>
void Test::print(double& input) {
    std::cout << "special case input = " << input << std::endl;
}

int main(void)
{
    Test test;
    double input = 3.14;
    test.print(input);
  
    return 0;
}

