#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c, rc;
    //    FILE* input = fopen(stdin);
    //    c = read(input)
    FILE *random = fopen("/dev/urandom", "r");
    FILE *selected_random = fopen("randoms.bin", "w");
    FILE *result = fopen("result.bin", "w");

    char current = 0;

    while ((c = getc(stdin)) != -1)
    {
        rc = getc(random);
        putc(rc, selected_random);
        current ^= rc;
        current ^= c;
        putc(current, result);
    }



    pclose(random);
    pclose(selected_random);
    pclose(result);

    return 0;
}
