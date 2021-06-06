#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[]){
    int key;

    if (argc == 2){
        // If there are only two arguments (including filename)
        for (int i=0, n = strlen(argv[1]); i < n; i++){

            // If non-digit character exist
            if (!isdigit(argv[1][i])){
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        // Convert string in argcv[1] to integer
        key = atoi(argv[1]);


    // Get the plaintext from user, copy it top cipher
    // Note that string is not originally defined in C, cs50.h makes this possible
    string plain = get_string("plaintext:");
    string cipher = plain;


    // Encoding plaintext
    for (int i=0, n=strlen(plain); i < n; i ++){
        if (isalpha(plain[i]) && islower(plain[i])){
            cipher[i] = ((int) plain[i] -97 + key) % 26 + 97;
        }
        else if (isalpha(plain[i]) && isupper(plain[i])){
            cipher[i] = ((int) plain[i] -65 + key) % 26 + 65;
        }
        else{
            cipher[i] = plain[i];
        }
    }

    // Print the ciphertext
    printf("ciphertext:%s\n", cipher);
    return 0;
    }

    // If there are more than or less than two arguments (including filename)
    else{
        printf("Usage: ./caesar key\n");
        return 1;
    }
}