#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <locale>
#include <algorithm>

#include "String.hpp"

int strToInt(const char* buffer, char** end) {
    long value = std::strtol(buffer, end, 0);

    if (value > 2147483647) {
        return 2147483647;
    }

    if (value < -2147483647 - 1) {
        return -2147483647 - 1;
    }

    return static_cast<int>(value);
}

double strToDouble(const char* buffer, char** end) {
    return std::strtod(buffer, end);
}

char* copyStr(const char* str) {
    if(!str) {
        char* copy = (char*)malloc(sizeof(char));
        copy[0] = '\0';
        return copy;
    }

    unsigned int size = strlen(str);
    char* copy = (char*)malloc(sizeof(char) * size);

    strcpy(copy, str);
    return copy;
}

