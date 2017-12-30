#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::cout << "Please enter your name: ";
    std::string first_name;
    std::cin >> first_name;
    std::cout << "Hello, " << first_name << "!" << std::endl;
    std::cout << "Enter the name of the person you want to write to: ";
    std::cin >> first_name;
    std::cout << "Dear " << first_name << "," << std::endl;
    std::cout << "    How are you? I am fine. I miss you." << std::endl;
    std::cout << "Please enter the name of another friend's name: ";
    std::string friend_name;
    std::cin >> friend_name;
    std::cout << "Have you seen " << friend_name << " lately?" << std::endl;
    char friend_sex = 0;
    std::cout << "If " << friend_name << " is a man, please enter 'm';" << std::endl;
    std::cout << "else if " << friend_name << " is a woman, please enter 'f'." << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> friend_sex;
    if (friend_sex == 'm') {
        std::cout << "If you see " << friend_name << " please ask him to call me." << std::endl;
    } else if (friend_sex == 'f') {
        std::cout << "If you see " << friend_name << " please ask her to call me." << std::endl;   
    } else {
        std::cout << "Input error, please enter 'm' or 'f'!" << std::endl;
    }
    
    int age = 0;
    std::cout << "Please enter " << first_name << "'s age: ";
    std::cin >> age;
    if (age <= 0 || age >= 110) {
        std::cout << "you'r kidding!" << std::endl;    
    } else {
        std::cout << "I hear you just had a birthday and you are " << age << " years old." << std::endl;
        if (age < 12) {
            std::cout << "Next year you will be " << age + 1 << "." << std::endl;    
        } else if (age == 17) {
            std::cout << "Next year you will be able to vote." << std::endl;    
        } else if (age > 70) {
            std::cout << "I hope you are enjoying retirement." << std::endl;    
        }
    }
    
    std::cout << "Yours sincerely,";
    std::cout << std::endl;
    std::cout << std::endl;
    
    return 0;
}

