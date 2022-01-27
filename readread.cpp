/*
    readread.cpp

    Read an entire file from stdin using read()
*/

#include <iostream>

#include <sys/types.h>
#if !defined(_MSC_VER)
#include <unistd.h>
#else
#include <io.h>
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif
#include <errno.h>

int main(int argc, char* argv[]) {

    int count = 0;
    while (true) {

        const int BUFFER_SIZE = 4096;
        char buf[BUFFER_SIZE];
        ssize_t numbytes = 0;
        while (((numbytes = read(0, buf, BUFFER_SIZE)) == -1) && (errno == EINTR)) {
        }
        if (numbytes == -1)
            return 1;
        if (numbytes == 0)
            break;
        count += numbytes;
    }

    std::cout << count << '\n';

    return 0;
}
