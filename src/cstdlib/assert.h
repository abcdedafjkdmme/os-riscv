#pragma once


void assert_failed(const char *file, int line, const char* expr);

#define assert(expr) \
    if (expr) \
        {} \
    else \
        assert_failed(__FILE__, __LINE__, #expr)


