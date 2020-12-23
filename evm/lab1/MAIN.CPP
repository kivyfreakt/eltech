#include <stdio.h>
#include <limits.h>

void long_to_bin(unsigned long num)
{
    int i;

    printf("Number %lu in binary: \n", num);
    for (i = (int)(sizeof(unsigned long)*CHAR_BIT)-1; i > -1; i--)
		printf("%d", (num >> i) & 1);
	puts("");
}


void float_to_bin(float *num)
{
    int i;
    unsigned long val = *((unsigned long*)num);

    printf("Number %f in binary: \n", *num);
    for (i = (int)(sizeof(float)*CHAR_BIT)-1; i > -1; i--)
		printf("%d", (val >> i) & 1);
	puts("");
}


unsigned long long_swap(unsigned long num)
{
    int position, pairs, left_bit, right_bit;
    unsigned long res = num;
    char i;

    do
    {
        printf("Enter the most significant digit: ");
        scanf("%d", &position);
        if (position > sizeof(unsigned long)*CHAR_BIT - 1)
            printf("\nMost significant digit can't be more than %d\n\n", sizeof(unsigned long)*CHAR_BIT - 1);
    }
    while(position > sizeof(unsigned long)*CHAR_BIT - 1);

    do
    {
        printf("Enter the number of pairs: ");
        scanf("%d", &pairs);
        if(position - 2*pairs + 1 < 0)
            printf("\nNumber of pairs can't be more than %d\n\n", (position+1)/2);
    }
    while(position - 2*pairs + 1 < 0);


    for (i = 0; i < pairs; i++)
    {
        left_bit = 1L & (res >> (position-2*i));
        right_bit = 1L & (res >> (position-2*i-1));

        if (left_bit)
            res = res | (1L << (position-2*i-1));
        else
            res = res & ~(1L << (position-2*i-1));

        if (right_bit)
            res = res | (1L << (position-2*i));
        else
            res = res & ~(1L << (position-2*i));
    }
    return res;
}

float float_swap(float *num)
{
    int position, pairs, left_bit, right_bit;
    unsigned long res = *((unsigned long*)num);
    char i;

    do
    {
        printf("Enter the most significant digit: ");
        scanf("%d", &position);
        if (position > sizeof(unsigned long)*CHAR_BIT - 1)
            printf("\nMost significant digit can't be more than %d\n\n", sizeof(unsigned long)*CHAR_BIT - 1);
    }
    while(position > sizeof(unsigned long)*CHAR_BIT - 1);

    do
    {
        printf("Enter the number of pairs: ");
        scanf("%d", &pairs);
        if(position - 2*pairs + 1 < 0)
            printf("\nNumber of pairs can't be more than %d\n\n", (position+1)/2);
    }
    while(position - 2*pairs + 1 < 0);

    for (i = 0; i < pairs; i++)
    {
        left_bit = 1L & (res >> (position-2*i));
        right_bit = 1L & (res >> (position-2*i-1));

        if (left_bit)
            res = res | (1L << (position-2*i-1));
        else
            res = res & ~(1L << (position-2*i-1));

        if (right_bit)
            res = res | (1L << (position-2*i));
        else
            res = res & ~(1L << (position-2*i));
    }

    return *((float*)&res);
}

void print_menu()
{
    printf("Menu: \n");
    printf("1. Unsigned long\n");
    printf("2. Float\n");
    printf("0. Exit\n");
}

int main()
{
    unsigned long input_long, result_long;
    float input_float, result_float;
    int choice;
    do
    {
        print_menu();
        printf("\n> ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                printf("Enter unsigned long number: ");
                scanf("%lu", &input_long);
                long_to_bin(input_long);
                result_long = long_swap(input_long);
                long_to_bin(result_long);
                break;
            case 2:
                printf("Enter float number: ");
                scanf("%f", &input_float);
                float_to_bin(&input_float);
                result_float = float_swap(&input_float);
                float_to_bin(&result_float);
                break;
            case 0:
                break;
            default:
                printf("\nWrong menu item. Try again.\n");
            break;
        }
    }
    while (choice != 0);

    return 0;
}

