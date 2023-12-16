#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>

void GetInputs(std::vector<std::string>* vec) {
    std::ifstream ifs;
    ifs.open("day1-2.txt", std::ios::in);
    std::string buf;
    while(std::getline(ifs, buf)) {
        vec->push_back(buf);
    }
}

int main() {
    std::vector<std::string> inputs;
    std::vector<std::string> numbers =
        { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    GetInputs(&inputs);
    int64_t ans = 0;
    for (auto&& s : inputs) {
        int32_t first = s.length() - 1, last = 0;
        for (int i = 0; i < 9; i++) {
            char c = '1' + i;
            int32_t pos = s.find(c);
            if (pos != s.npos) {
                first = std::min(first, pos);
            }
            pos = s.rfind(c);
            if (pos != s.npos) {
                last = std::max(last, pos);
            }
        }
        int32_t first_word = -1, last_word = -1;
        for (int i = 0; i < 9; i++) {
            int32_t pos = s.find(numbers.at(i));
            if (pos != s.npos && pos < first) {
                first = pos;
                first_word = i + 1;
            }
            pos = s.rfind(numbers.at(i));
            if (pos != s.npos && pos > last) {
                last = pos;
                last_word = i + 1;
            }
        }
        if (first_word == -1) {
            first_word = s[first] - '0';
        }
        if (last_word == -1) {
            last_word = s[last] - '0';
        }
        int64_t number = first_word * 10 + last_word;
        ans += number;
    }
    std::cout << ans << std::endl;
}
