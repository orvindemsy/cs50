#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[]){

    // Check if there are 2 arguments
    if (argc == 2){

        // Check if argv[1] has length of 26 characters
        if (strlen(argv[1]) == 26){

            // Check if argv[1] contain digits
            for (int i=0, n=strlen(argv[1]); i < n; i++){
                if (!isalpha(argv[1][i])) {
                    printf("Usage: ./substitution key\n");

                    return 1;
                }
            }

            // Check if argv[1] contains dupplicate
            char atozupper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            int sumascii[2] = {0, 0};
            for (int i=0, n=strlen(argv[1]); i < n; i++){
                sumascii[0] += toupper(argv[1][i]);
                sumascii[1] += toupper(atozupper[i]);
            }

            // Return 1 if contains duplicate
            if (sumascii[0] != sumascii[1]){
                return 1;
            }

            // Setting key from argv[1] and get plaintext from user
            string key = argv[1];
            string plain = get_string("plaintext:");
            int idx;

            // Encode plaintext to ciphertext preserve upper and lowercase
            printf("ciphertext:");
            for (int i=0, n=strlen(plain); i<n; i++){

                // Get index in key for character substitution for character plain[i]
                idx = tolower(plain[i])-97;

                if islower(plain[i]){
                    printf("%c", tolower(key[idx]));
                }

                else if isupper(plain[i]){
                    printf("%c", toupper(key[idx]));
                }

                else {
                    printf("%c", plain[i]);
                }
            }
            printf("\n");

            return 0;
        }

        // If argv[1] has less or more than 26 character
        else {
            printf("Usage: ./substitution key\n");

            return 1;
        }

    }

    // Reject if there is more than 2 argument
    else{
        printf("Usage: ./substitution key\n");

        return 1;
    }
}