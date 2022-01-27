/*
    readcinread.cpp

    Read an entire file from stdin using std::cin.read()
*/

#include <iostream>

int main(int argc, char* argv[]) {

    int count = 0;
    while (true) {

        const int BUFFER_SIZE = 4096;
        char buf[BUFFER_SIZE];
        std::cin.read(buf, BUFFER_SIZE);
        if (std::cin.bad())
            return 1;
        if (std::cin.gcount() == 0)
            break;
        count += std::cin.gcount();
    }

    std::cout << count << '\n';

    return 0;
}
