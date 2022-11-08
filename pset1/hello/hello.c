#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Ask the user for their name
    string name = get_string("What is your name?\n");
    //Print 
    printf("hello, %s\n", name);
}