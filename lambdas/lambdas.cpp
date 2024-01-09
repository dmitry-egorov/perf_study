
#include <cstdio>

int main(int argc, char* argv[])
{
    auto plain_print = [] {
        printf("Hello, World!\n");
    };

    auto param_print = [&] {
        printf("Hello, World! %d\n", argc);
    };

    plain_print();
    param_print();
    return 0;
}