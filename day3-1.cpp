#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "print.h"
#include <queue>
#include <set>
#include <cassert>


int HEIGHT{};
int WIDTH{};
void GetInputs(std::vector<std::string>* vec) {
    std::ifstream ifs;
    ifs.open("day3-1.txt", std::ios::in);
    std::string buf;
    while(std::getline(ifs, buf)) {
        vec->push_back(buf);
    }
    HEIGHT = vec->size();
    WIDTH = vec[0].size();
}

std::set<std::pair<int, int>> find_symbols(std::vector<std::string>& inputs) {
    std::set<std::pair<int, int>> symbol_cords;
    for (int i = 0; i < inputs.size(); i++) {
        for (int j = 0; j < inputs[i].size(); j++) {
            const char c = inputs[i][j];
            if (c != '*') continue;
            auto par = std::make_pair(i, j);
            symbol_cords.insert(par);
        }
    }
    return symbol_cords;
}

std::vector<int> check(const int& x, const int& y, std::vector<std::string>& inputs) {
    const std::vector<std::vector<int>> directions = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
    std::set<std::pair<int, int>> visited;
    std::vector<int> res;
    for (const auto& dir : directions) {
        const int nx = x + dir[0], ny = y + dir[1];
        if (nx < 0 || ny < 0 || nx >= inputs.size() || ny >= inputs[x].size() ) continue;
        auto par = std::make_pair(nx, ny);
        if (visited.count(par)) continue;
        // now we check if there is a digit
        const char c = inputs[nx][ny];
        if (std::isdigit(c)) {
            // now we gather the whole num
            // go left till we have no more digits, then go all the way to the right
            char cur = c;
            int nc = ny;
            while (nc >= 0 && isdigit(inputs[nx][nc]))
                nc--;
            // cx + 1 is the start
            int start = nc + 1;
            std::string num{};
            while (start < WIDTH && std::isdigit(inputs[nx][start])) {
               num.push_back(inputs[nx][start]);
               visited.insert({nx, start});
               start++;
            }
            res.push_back(stoi(num));
        }
    }
    return res;
}
int main() {
    std::vector<std::string> inputs;
    GetInputs(&inputs);
    // go through the grid and find the location of all symbols
    auto symbols = find_symbols(inputs);
    int res{};
    for (const auto& cord : symbols) {
         const int x = cord.first, y = cord.second;
         // check the 8 directions around
         auto nums = check(x, y, inputs);
         if (nums.size() != 2) continue;
         res += nums[0] * nums[1];
    }
    print(res);
    return 0;
}
