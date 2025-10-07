#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc != 2 || !only_digits(argv[1]))
    {
        // Make sure every character in argv[1] is a digit
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string plaintext = get_string("plaintext:  ");

    int len = strlen(plaintext);
    char ciphertext[len + 1];

    // For each character in the plaintext:
    for (int i = 0; i < len; i++)
    {
        // Rotate the character if it's a letter
        ciphertext[i] = rotate(plaintext[i], key);
    }
    ciphertext[strlen(plaintext)] = '\0';

    printf("ciphertext:  %s\n", ciphertext);

    return 0;
}

bool only_digits(string s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int n)
{
    if (isalpha(c))
    {
        if (isupper(c))
        {
            c = ((c - 'A') + n) % 26 + 'A';
        }
        else if (islower(c))
        {
            c = ((c - 'a') + n) % 26 + 'a';
        }
    }
    return c;
}
