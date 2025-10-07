#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int SCRABBLE_SCORES[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                               1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Prompt the user for two words
    string player1_word = get_string("Player 1: ");
    string player2_word = get_string("Player 2: ");

    // Compute the score of each word
    int score1 = compute_score(player1_word);
    int score2 = compute_score(player2_word);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int total = 0;
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        if (isupper(word[i]))
        {
            // We are subtracting the each letter of word ASCII's point to first letter of alphabet,
            // so we can find the index for scrabble scores array.
            total += SCRABBLE_SCORES[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            total += SCRABBLE_SCORES[word[i] - 'a'];
        }
        else
        {
            total += 0;
        }
    }
    return total;
}
