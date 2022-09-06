from cs50 import get_string


def main():
    number = get_string("Number: ")
    # check length
    if len(number) < 13 or len(number) > 16 or len(number) == 14:
        print("INVALID")
    elif is_visa(number) == True:
        # check visa
        print("VISA")
    elif is_master(number) == True:
        # check mastercard
        print("MASTERCARD")
    elif is_amex(number) == True:
        # check amex
        print("AMEX")
    else:
        print("INVALID")


def is_visa(number):
    # check length
    if len(number) == 13 or len(number) == 16:
        # check beginning and checksum
        if number[0] == "4" and checksum(number) == True:
            return True
    else:
        return False


def is_master(number):
    # check length and checksum
    if len(number) == 16 and checksum(number) == True:
        # check beginning
        if number[0] == "5":
            if number[1] == "1" or number[1] == "2" or number[1] == "3" or number[1] == "4" or number[1] == "5":
                return True
    else:
        return False


def is_amex(number):
    # check length and checksum
    if len(number) == 15 and checksum(number) == True:
        # check beginning
        if number[0] == "3":
            if number[1] == "4" or number[1] == "7":
                return True
    else:
        return False


def checksum(number):
    # turn string into list of ints
    digits = []
    for i in range(len(number)):
        temp = int(number[i])
        digits.append(temp)

    doubles = []
    start = len(number) % 2
    length = len(number)
    end = int(len(number) / 2)

    # create list of digits to be doubled
    for i in range(start, length, 2):
        doubles.append(digits[i])
    # double them
    for i in range(end):
        doubles[i] = doubles[i] * 2
        # add digits of greater than ten
        if doubles[i] > 9:
            sdig = str(doubles[i])
            dig = int(sdig[0]) + int(sdig[1])
            doubles[i] = dig

    sum = 0
    # add them
    for i in range(end):
        sum += doubles[i]

    start = len(number) + 1
    start %= 2
    others = []
    end += len(number) % 2

    # create list of other digits
    for i in range(start, length, 2):
        others.append(digits[i])
    # add them
    for i in range(end):
        sum += others[i]
    if sum % 10 == 0:
        return True
    else:
        return False


main()