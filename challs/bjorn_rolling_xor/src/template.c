#include <stdio.h>
#include <stdlib.h>

void main()
{
    char c, rc;

    // During the competition this variable was
    // not unsigned with made the program not 
    // work as intended, the challenge was
    // still solvable by using reverse engineering
    unsigned char current = 0;

    int i = 0;

    while ((c = getc(stdin)) != -1)
    {
        if (c == '\n')
            break;
        rc = randoms_bin[i];
        current ^= rc;
        current ^= c;
        if (result_bin[i] != current)
        {
            printf("FAIL");
            exit(1);
        }
        i++;
    }

    if (i != result_bin_len)
    {
        printf("Wrong Length");
        exit(1);
    }

    printf("SUCCESS");
    exit(0);
}
