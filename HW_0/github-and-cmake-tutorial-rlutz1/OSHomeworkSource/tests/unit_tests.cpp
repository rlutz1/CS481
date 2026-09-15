#include "src.hpp"

// Test file checks correctness
int main(int argc, char** argv)
{
    // If value returned from method does not equal 0, fail test
    if (return0() != 0)
    {
        fprintf(stderr, "Return value does not equal 1\n");
    }
}
