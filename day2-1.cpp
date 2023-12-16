// #include "bits/stdc++.h"
// #include <sstream>
// #include <string>
// #include "print.h"

// void parse_file(std::vector<std::string>& lines) {
//     std::ifstream ifs;
//     ifs.open("day2-1.txt", std::ios::in);
//     std::string buf;
//     while(std::getline(ifs, buf)) {
//         lines.push_back(buf);
//     }
// }

// int main() {
//     std::vector<std::string> lines;
//     parse_file(lines);
//     const int rmax = 12, gmax = 13, bmax = 14;
//     std::unordered_map<std::string, int> colors = { {"red", rmax}, {"green", gmax}, {"blue", bmax} };
//     int ret{};
//     for (const std::string& line : lines) {
//         std::stringstream ss(line);
//         std::string game{}; ss >> game;
//         int id{}; ss >> id >> game;
//         std::string set{};
//         bool can_play{true};
//         while (std::getline(ss, set, ';')) {
//             int num{}; std::string color{};
//             auto temp_map = colors;
//             while (ss >> num) {
//                 ss >> color;
//                 if (!isalnum(color.back())) color.pop_back();
//                 temp_map[color] -= num;
//                 if (temp_map[color] < 0) {
//                     can_play = false;
//                 }
//             }
//         }
//         if (can_play) ret += id;
//     }
//     print(ret);
// }
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>

void GetInputs(std::vector<std::string>* vec) {
    std::ifstream ifs;
    ifs.open("day2-1.txt", std::ios::in);
    std::string buf;
    while(std::getline(ifs, buf)) {
        vec->push_back(buf);
    }
}

void RemovePrefix(std::string& s) {
    int32_t pos = s.find(':');
    s = s.substr(pos + 1);
}

void GenerateBatch(std::vector<std::string>* vec, std::string s) {
    int32_t start = 0, end = 0;
    while (true) {
        if (end == s.length()) {
            break;
        }
        if (s[end] == ';') {
            vec->push_back(s.substr(start, end-start));
            // std::cout << vec->back() << std::endl;
            end++;
            start = end;
        } else {
            end++;
        }
    }
    if (end > start) {
        vec->push_back(s.substr(start, end - start));
        // std::cout << vec->back() << std::endl;
    }
}

int64_t GetColor(const std::string& s, const std::string& color) {
    int32_t pos = s.find(color);
    if (pos == s.npos) {
        return 0;
    } else {
        pos -= 2;
        int32_t end = pos;
        while(pos >= 0) {
            if(s[pos] == ' ' || pos == 0) {
                break;
            } else {
                pos--;
            }
        }
        // std::cout << s << ':' << color <<  ':' << s.substr(pos, end - pos + 1) << std::endl;
        return std::stoll(s.substr(pos, end - pos + 1));
    }
}

int main() {
    std::vector<std::string> inputs;
    GetInputs(&inputs);
    int64_t ans = 0;
    int64_t id = 0;
    std::vector<std::string> batch;
    for (auto&& s : inputs) {
        id++;
        RemovePrefix(s);
        batch.clear();
        GenerateBatch(&batch, s);
        int64_t green = 0, red = 0, blue = 0;
        bool check_ok = true;
        for(auto&& b : batch) {
            green = std::max(green, GetColor(b, "green"));
            red = std::max(red, GetColor(b, "red"));
            blue = std::max(blue, GetColor(b, "blue"));
            // if (green <= 13 && red <= 12 && blue <= 14) {
            // } else {
            //     check_ok = false;
            //     break;
            // }
        }
        std::cout << green << ' ' << red << ' ' << blue << std::endl;
        // if (check_ok) {
        //     ans += id;
        // }
        ans += (green * red * blue);
    }
    std::cout << ans << std::endl;
}
