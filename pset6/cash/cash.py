from cs50 import get_float


def main():
    coins = 0
    change = get_change()

    # quarters
    while change >= .25:
        change -= .25
        coins += 1
        change = round(change, 2)

    # dimes
    while change >= .10:
        change -= .10
        coins += 1
        change = round(change, 2)

    # nickles
    while change >= .05:
        change -= .05
        coins += 1
        change = round(change, 2)

     # pennies
    while change >= .01:
        change -= .01
        coins += 1
        change = round(change, 2)

    print(coins)


def get_change():
    # get valid change
    change = get_float("Change owed: ")
    while change < 0:
        change = get_float("Change owed: ")
    # round
    change = round(change, 2)
    return change


main()