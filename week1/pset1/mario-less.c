#include<stdio.h>
#include<cs50.h>

int main(void){
    int h;
    do {
        h = get_int("Height: ");
    }
    while(h < 1 || h > 8);

    // Creating pyramid using nested loop
    for (int i = 0; i < h; i ++){
        for (int j = 0; j < h; j++ ){

                // Print " " when j < h - (i+1) otherwise print *
                if (j < h-(i+1)){
                    printf(" ");
                }
                else{
                    printf("#");
                }
        }
        printf("\n");
    }
}