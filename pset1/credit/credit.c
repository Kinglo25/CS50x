#include <cs50.h>
#include <stdio.h>
#include <math.h>

int valid_number(long number)
{
    int sum1 = 0, sum2 = 0, checksum = 0;

    while (number)
    {
        sum1 += number % 10;
        number /= 10;
        if ((number % 10) * 2 > 9)
        {
            sum2 += (number % 10) * 2 % 10;
            sum2 += (number % 10) * 2 / 10;
        }
        else
            sum2 += (number % 10) * 2;
        number /= 10;
    }
    checksum = sum1 + sum2;
    return (!(checksum % 10));
}

//Recursively finds the lenght of the given number
int number_lenght(long number)
{
    if (number < 10)
        return (1);
    return (1 + number_lenght(number / 10));
}

//checks if the number follows amex structure
int is_amex(long number)
{
    int nb_len, first_two_digits;

    nb_len = number_lenght(number);
    first_two_digits = number / pow(10, nb_len - 2);
    return (nb_len == 15 && (first_two_digits == 34 || first_two_digits == 37));
}

//checks if the number follows mastercard structure
int is_mastercard(long number)
{
    int nb_len, first_two_digits;

    nb_len = number_lenght(number);
    first_two_digits = number / pow(10, nb_len - 2);
    return (nb_len == 16 && (first_two_digits == 51 || first_two_digits == 52
    || first_two_digits == 53 || first_two_digits == 54 || first_two_digits == 55));
}

//checks if the number follows visa structure
int is_visa(long number)
{
    int nb_len, first_digit;

    nb_len = number_lenght(number);
    first_digit = number / pow(10, nb_len - 1);
    return ((nb_len == 13 || nb_len == 16) && first_digit == 4);
}

int main(void)
{
    long number = -1;

    // Prompt the user for number
    do
    {
        number = get_long("Number: ");
    }
    while (number == -1);
    if (valid_number(number))
    {
        if (is_amex(number))
            printf("AMEX\n");
        else if (is_mastercard(number))
            printf("MASTERCARD\n");
        else if (is_visa(number))
            printf("VISA\n");
        else
            printf("INVALID\n");
    }
    else
        printf("INVALID\n");
    return (0);
}