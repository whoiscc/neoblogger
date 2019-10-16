//
#ifndef NEOBLOGGER_TESTS_HELPER_H
#define NEOBLOGGER_TESTS_HELPER_H

#include <stdio.h>
#include <assert.h>


#define SECTION(title) printf("- " #title "\n");

#define TEST(title) \
static void test_main(void); \
\
int main(void) { \
    printf(#title "\n"); \
    test_main(); \
    return 0; \
} \
\
static void test_main(void)

#endif

