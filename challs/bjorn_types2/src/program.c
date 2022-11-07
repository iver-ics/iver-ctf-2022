#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned int balance = 999;

void menu()
{
    printf("\n\n");
    puts("------------------------------");
    puts("     Hacker Store     ");
    puts("------------------------------");
    puts(" 1. Buy Halloween Hat (10 SEK)  ");
    puts(" 2. Buy Bloody Flag (1000 SEK)  ");
    puts(" 0. Exit  ");
    puts("------------------------------");
    printf("Your Balance: %d\n", balance);
    printf("Your choice : ");
};

int main()
{
    setvbuf(stdout, 0, 2, 0);
    setvbuf(stdin, 0, 2, 0);
    char buf[100];

    while (1)
    {
        menu();
        read(0, buf, 4);
        switch (atoi(buf))
        {
        case 1:
            int number_of_hats = 0;
            printf("How many hats do you want to buy?: ");
            scanf("%d", &number_of_hats);
            if (number_of_hats < 0) {
                printf("Sorry, you can't buy negative hats\n");
            }
            else if ((number_of_hats * 10) > (int)balance)
            {
                printf("Sorry, you don't have enough cash for that\n");
            }
            else
            {
                printf("OK!\n");
                balance -= (number_of_hats * 10);
            }
            break;
        case 2:
            if (balance < 1000)
            {
                printf("Sorry, you don't have enough cash for that\n");
            }
            else
            {
                printf("OK!\n");
                system("cat flag.txt");
                balance -= 1000;
            }
            break;
        default:
            printf("We don't sell that here\n");
            break;
        }
    }
    return 0;
}