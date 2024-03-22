#pragma once


void assert_failed(char *file, int line, char* expr);

#define assert(expr) \
    if (expr) \
        {} \
    else \
        assert_failed(__FILE__, __LINE__, #expr)


