#include <stdio.h>
#include <stdlib.h>
void UI_Menu()
{
    while (1)
    {
        puts("\t\t\t==============================");
        puts("\t\t\t     WELCOME TO THE SHOP  ");
        puts("\t\t\t==============================");
        puts("\t\t\t* * * * * * * * * * * * * * * *");
        puts("\t\t\t1. Manage Cat\n\n\t\t\t2. Manage Products\n\n\t\t\t3. Your Cart\n\n\t\t\t4. Manage Finance\n\n\t\t\t5. Manage Client\n\n\t\t\t6. Exit");
        printf("\t\t\tSelect your choice  ");
        int u;
        scanf("%d", &u);
        if (u == 1)
        {
            printf("Your choice is 1");
            exit(0);
        }
        else if (u == 2)
        {
            printf("Your choice is 2");
            exit(0);
        }
        else if (u == 3)
        {
            printf("Your choice is 3");
            exit(0);
        }
        else if (u == 4)

        {
            printf("Your choice is 4");
            exit(0);
        }
        else if (u == 5)
        {
            printf("Your choice is 5");
            exit(0);
        }
        else if (u == 6)
        {
            printf("exit");
            exit(0);
        }
        else
        {
            puts("Invalid option. Please select one of the available options");
        }
    }
}

int main()
{
    UI_Menu();
    return 0;
}
