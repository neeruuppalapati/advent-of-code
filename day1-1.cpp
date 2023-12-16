#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>



int main() {
    std::ifstream in("day1.txt");
    std::string line{};

    int ret = 0;
    while (in >> line) {
        std::string res{};
        std::copy_if(line.begin(), line.end(), std::back_inserter(res), [](char c) {
            return std::isdigit(c);
        });
        int val = (res.front() - '0') * 10 + (res.back() - '0');
        ret += val;
    }
    std::cout << ret << "\n";

}
