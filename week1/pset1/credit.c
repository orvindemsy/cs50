#include<stdio.h>
#include<cs50.h>
#include<math.h>
int get_digits(long num, int n);
int find_length(long num);
int get_first_two_digits(long num,  int num_len);
int checksum(long cnum, int num_len);

int main(void){
    long cnum;
    int number;
    int clen;
    int two_digits;
    int total;

    cnum = get_long("Number: ");
    // printf("%ld\n\n", cnum);

    // number = get_digits(cnum, i);
    // printf("Number: %d\n", number);

    clen = find_length(cnum);
    printf("Length cnum: %d\n", clen);

    total = checksum(cnum, clen);
    printf("Total: %d\n", total);

    // Get first two digits of credit card number
    two_digits = get_first_two_digits(cnum, clen);
    printf("Two digits: %d\n", two_digits);

    // Veryfying type and validity
    if (total % 10 == 0){
        // printf("This is valid, brand...\n");

        // Check if VISA
        if (clen == 13 || clen == 16){
            if (two_digits / 10 == 4){
                printf("VISA\n");
            }

            // Check if MASTERCARD
            else if (two_digits >= 51 & two_digits <= 55) {
                printf("MASTERCARD\n");
            }
            else{
                printf("INVALID\n");
            }
        }

        // Check if AMERICAN EXPRESS AMEX
        else if (clen == 15){
            if (two_digits == 37 || two_digits == 34){
                printf("AMEX\n");
            }
            else{
                printf("INVALID\n");
            }
        }
        else{
            printf("INVALID\n");
        }
    }
    else{
        printf("INVALID\n");
    }
}



int get_digits(long num, int n){
    long temp;
    temp = num / (long) pow(10,n-1);
    temp = temp % 10;
    // % (int) (pow(10, (n+1))) / (int) pow(10, n);

    return temp;

}

int checksum(long cnum, int num_len){
    // Every other digits starts from second-to-last digit
    // int number;
    int sum1 = 0;
    int sum2 = 0;
    int total;

    for (int i=2; i<=num_len; i+=2){
        int num = get_digits(cnum, i);
        num = num*2;

        // Check if num is two digits, separate digits and add them
        int nlen = find_length(num);

        // If current number has two digits, add them digit-wise
        if (nlen == 2){
            int digit1 = num / 10;
            int digit2 = num % 10;
            sum1 += (digit1 + digit2);
        }
        else{
            sum1 += num;
        }
    }

    // printf("\n");

    // printf("Not every other digits\n");
    for (int i=1; i<=num_len; i+=2){
        int num = get_digits(cnum, i);
        sum2 += num;
        // printf("%d ", num);
        // printf("sum: %d", sum2);
        // printf("\n");
    }

    // printf("Sum1: %d\n", sum1);
    // printf("Sum2: %d\n", sum2);


    return sum1 + sum2;
}

int find_length(long num){
    int i = 0;
    while (num > 0){
        num = num / 10;
        i += 1;
    }
    return i;
}

int get_first_two_digits(long num,  int num_len){
    num = num / (long) pow(10,num_len-2);

    return num;
}