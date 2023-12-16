#pragma once

#include <iostream>

template<char sep=' ', char end='\n', class T, class... U>
void print( const T& first, const U&... rest) {
    int debug_mode = 1;
    if (!debug_mode) return;
    std::cout << first;
    ((std::cout << sep << rest ), ...);
    std::cout << end;
}
