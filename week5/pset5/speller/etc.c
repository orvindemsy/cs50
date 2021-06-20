#include <stdio.h>
#include <stdlib.h>
// #include
const int LENGTH = 45;

// TODO
int main(int argc, char *argv[]){

    char *dictionary = argv[1];


    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL){
        return 1;
    }

    // char *w = malloc(sizeof(char) * LENGTH);
    char w[LENGTH + 1];
    printf("here\n");

    while(fscanf(dict, "%s", w) != EOF){

        // node *n = malloc(sizeof(node));
        
        // // Create node to store each word
        // if (!n){
        //     return 1;
        // }
        printf("It's here\n");
        printf("%s\n", w);
        // strcpy(n->word, w)


        // free(n);

    }
}