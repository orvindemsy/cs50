from cs50 import get_float

def main():

    # Get non-negative input from the use
    while True:
        cents = get_float("Change owed: ")
        cents = cents * 100
        if cents > 0:
            break

    # Initialize number of coins
    coins = 0

    # Compute coins needed using greedy algorithm
    while cents > 0:
        # print(cents)
        if (cents - 25 >= 0):
            cents -= 25
            coins += 1

        elif (cents - 10 >= 0):
            cents -= 10
            coins += 1

        elif (cents - 5 >= 0):
            cents -= 5
            coins += 1

        else:
            cents -= 1
            coins += 1

    print(coins)

if __name__ == "__main__":
    main()