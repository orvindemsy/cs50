#include<stdio.h>
#include<cs50.h>
#include<math.h>

int main(void){
    float cents;
    int coins = 0;

    do {
        cents = get_float("Changed owed: ");
        cents = round(cents * 100);
    }
    while (cents < 1);

    // compute how many coins needed using greedy algorithm
    while (cents > 0 ){
        if (cents - 25 >= 0){
            cents -= 25;
            coins += 1;
        }
        else if (cents - 10 >= 0 ){
            cents -= 10;
            coins += 1;
        }
        else if (cents - 5 >= 0){
            cents -= 5;
            coins += 1;
        }
        else{
            cents -= 1;
            coins += 1;
        }
    }

    printf("%d\n", coins);
}
