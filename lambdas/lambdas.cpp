
#include <cstdio>

int main(int argc, char* argv[])
{
    auto x = [] {
        printf("Hello, World!");
    };

    x();
    return 0;
}