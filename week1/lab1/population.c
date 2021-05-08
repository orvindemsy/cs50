#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_size;
    int end_size;
    int born;
    int dead;
    int year;
    // Get start population size
    do{
        start_size = get_int("Input start size: ");
    }
    while (start_size < 9);

    // Get end population size
    do {
        end_size = get_int("Enter end size: ");
    }
    while (end_size < start_size);

    // Calculate number of years until we reach threshold
    year = 0;

    while (start_size < end_size)
    {
        born = start_size / 3;
        dead = start_size / 4;

        start_size = start_size + born - dead;
        year += 1;
    }

    // TODO: Print number of years
    printf("Years: %i\n", year);
}