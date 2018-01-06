#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    vector<int> answer{1, 2, 3, 4};
    vector<int> usr_input;
    usr_input.clear();

    for (int i = 0; i < 4; ++i) {
        int this_input = 0;
        cin >> this_input;
        usr_input.push_back(this_input);
    }

    int bull_num = 0;
    int cow_num = 0;

    for (vector<int>::size_type idx = 0; idx < usr_input.size(); ++idx) {
        if (answer[idx] == usr_input[idx]) {
            ++bull_num;
        } else {
            for (auto& item : answer) {
                if (item == usr_input[idx]) {
                    ++cow_num;
                    break;
                }
            }
        }
    }

    cout << "bull_num: " << bull_num << endl;
    cout << "cow_num: " << cow_num << endl;

    return 0;
}