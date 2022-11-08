#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int is_valid_key(string key)
{
    int key_len, tab[26] = { 0 };

    key_len = strlen(key);
    //Check the lenght of the key
    if (key_len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return (0);
    }
    //Search for non-alphabetic char
    for (int i = 0; i < key_len; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return (0);
        }
    }
    //Search for repeated char
    for (int i = 0; i < key_len; i++)
    {
        if (tab[tolower(key[i]) - 97]++)
        {
            printf("Key must not contain repeated characters.\n");
            return (0);
        }
    }
    return (1);
}

string encipher(string str, string key)
{
    int i = 0;

    while (str[i])
    {
        if (islower(str[i]))
        {
            str[i] = tolower(key[str[i] - 97]);
        }
        else if (isupper(str[i]))
        {
            str[i] = toupper(key[str[i] - 65]);
        }
        i++;
    }
    return (str);
}

int main(int argc, string argv[])
{
    string plaintext, ciphertext;

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return (1);
    }
    if (is_valid_key(argv[1]))
    {
        plaintext = get_string("plaintext: ");
        ciphertext = encipher(plaintext, argv[1]);
        printf("ciphertext: %s\n", ciphertext);
    }
    else
        return (1);
    return (0);
}