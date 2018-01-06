#include <iostream>

int main(int argc, char *argv[]) {
    int pre = 1;
    int now = 1;
    int nxt = 2;

    std::cout << pre << " " << now;
    while (nxt > now) {
        std::cout << " " << nxt;
        pre = now;
        now = nxt;
        nxt = pre + now;
    }
    
    return 0;
}