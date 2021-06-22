#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int count_index(int num_letters, int num_words, int num_sentences);

int main(void){
    // Gettting input from user
    string input = get_string("Text: ");

    // Count number of letters, words, and sentences
    int n_letters     = count_letters(input);
    int n_words       = count_words(input);
    int n_sentences   = count_sentences(input);
    
    // Displaying number of words, letters, sentences
    printf("%d letter(s)\n", n_letters);
    printf("%d word(s)\n", n_words);
    printf("%d sentences(s)\n", n_sentences);
    printf("\n");

    // Compute Coleman-Liau index
    int index = count_index(n_letters, n_words, n_sentences);

    if (index < 1){
        printf("Before Grade 1\n");
    }
    else if (index >= 16){
        printf("Grade 16+\n");
    }
    else{
        printf("Grade %d\n", index);
    }
}


int count_letters(string text){
    int count = 0;

    // Count only alphabetic character, no punctuation, exclamation mark, digits, etc.
    for (int i = 0, n = strlen(text); i < n; i++){
        if (toupper(text[i]) >= 65 && toupper(text[i]) <= 90){
            count  += 1;
        }
    }

    return count;
}


int count_words(string text){
    int count = 0;

    // One word is defined as a sequence of characters separated by a space
    for (int i = 0, n = strlen(text); i < n; i++){
        if (text[i] == 32){
            count  += 1;
        }
    }
    return count + 1;
}


int count_sentences(string text){
    int count = 0;

    // Character ., !, ? marks the end of a sentence
    for (int i = 0, n = strlen(text); i < n; i++){
        if (text[i] == 33 || text[i] == 46 || text[i] == 63){
            count  += 1;
        }
    }
    return count;
}


int count_index(int num_letters, int num_words, int num_sentences){
    // Average number of letters and sentences per 100 words
    float L = (float) num_letters / num_words * 100.0;
    float S = (float) num_sentences / num_words * 100.0;

    // printf("L: %f\n", L);
    // printf("S: %f\n", S);

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}