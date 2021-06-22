from cs50 import get_int


def main():
    # Prompt height from user to be between 1 and 8, inclusive
    while True:
        height = get_int("Height: ")

        if (height >= 1 and height <= 8):
            break

    # Print bricks
    for i in range(1, height+1):
        brick(height-i, i)


# Function to create one line of brick
def brick(space, brick):
    print(" " * space + "#" * brick)


if __name__ == "__main__":
    main()