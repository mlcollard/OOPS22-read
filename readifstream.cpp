/*
    readcin.cpp

    Read an entire file using std::ifstream
*/

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {

    int count = 0;
    std::ifstream in(argv[1]);
    in.unsetf(std::ios::skipws);
    char c;
    while (in >> c) {
        ++count;
    }
    if (in.bad())
        return 1;

    std::cout << count << '\n';

    return 0;
}
