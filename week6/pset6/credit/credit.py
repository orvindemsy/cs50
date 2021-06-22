from cs50 import get_string

def main():
    # Assume that input only contain numeric characters
    credit_num = list(input("Number: "))

    # Get credit card number
    credit_len = len(credit_num)

    # Check validity using luhn's algorithm
    valid = luhn_algo(credit_num)

    # Grab first two digits of credit card number
    first_two = int("".join(credit_num[:2]))

    # Find the credit card brand
    brand = credit_brand(valid, credit_len, first_two)
    print(brand)


def luhn_algo(credit_number):
    sum_digits = 0
    sum_digits = 0

    # Starting from second to last digit, decrement with interval of 2
    for i in range(len(credit_number)-2, -1, -2):

        # Multiply those number by 2
        num = int(credit_number[i]) * 2

        # Add two digits add them digits-wise
        if num // 10 > 0:
            sum_digits += num // 10
            sum_digits += num % 10
        else:
            sum_digits += num

    # Add those with number not multiplied by two, starting from the end (last digit)
    for i in range(len(credit_number)-1, -1, -2):
        # print(credit_number[i])
        sum_digits += int(credit_number[i])

    if sum_digits % 10 == 0:
        return True
    else:
        return False


def credit_brand(valid, credit_length, first_two_digits):
    # If not valid return INVALID
    if not valid:
        return "INVALID"

    # If credit card length is 16 it can be either VISA or MASTERCARD
    if (credit_length == 16):

        # VISA starts with 4
        if first_two_digits // 10 == 4:
            return "VISA"

        # First two digits of MASTER CARD can be 51, 52, 53, 54, 55
        elif (first_two_digits >= 51 and first_two_digits <= 55):
            return "MASTERCARD"

        else:
            return "INVALID"

    # VISA can also has length of 13 and starts with 4
    elif (credit_length == 13 and first_two_digits // 10 == 4):
        return "VISA"

    # AMERICAN EXPRESS has length of 15 and starts with 34 or 37
    elif (credit_length == 15 and (first_two_digits == 34 or first_two_digits == 37)):
        return "AMEX"

    else:
        return "INVALID"


if __name__ == "__main__":
    main()