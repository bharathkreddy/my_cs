#include <stdio.h>
#include <string.h>
#include "bm.h"

struct TestCase {
    char *expr;
    int expected; // 1 = balanced, 0 = not balanced
};
void runTests(void);

void runTests(void)
{
    struct TestCase tests[] = {
        {"(a+b)", 1},
        {"((a+b))", 1},
        {"(a+b", 0},
        {"a+b)", 0},
        {"{[()]}", 1},
        {"{[(])}", 0},
        {"[a+(b*c)-{d/e}]", 1},
        {"(((())))", 1},
        {"(((())", 0},
        {"", 1},  // empty string is balanced
    };

    int total = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < total; i++){
        int result = isBalanced(tests[i].expr);
        printf("Test %d: %-20s | Expected: %s | Got: %s\n",
               i+1,
               tests[i].expr,
               tests[i].expected ? "Balanced" : "Not Balanced",
               result ? "Balanced" : "Not Balanced");

        if (result == tests[i].expected) {
            passed++;
        }
    }

    printf("\n%d/%d tests passed.\n", passed, total);
}

int main(void)
{
    runTests();
    return 0;
}
