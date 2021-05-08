#include<stdio.h>
#include<cs50.h>

void printchar(char c, int n);

int main(void){
    int h;
    do {
        h = get_int("Height: ");
    }
    while(h < 1 || h > 8);

    // createblock('#', 2);
    for (int i = 0; i < h; i++){
        printchar(' ', h-i-1);
        printchar('#', i+1);
        printchar(' ', 2);
        printchar('#', i+1);
        printf("\n");
    }
}

void printchar(char c, int n){
    for (int i=0; i<n; i++){
        printf("%c", c);
    }
}