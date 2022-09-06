from cs50 import get_int
# get height
height = get_int("Height: ")
# get valid height
while height < 1 or height > 8:
    height = get_int("Height: ")
counter = 1
spaces = height - 1
# print spaces decrease blocks increase
while height > 0:
    print(" " * spaces, end="")
    print("#" * counter, end="")
    print()
    height -= 1
    spaces -= 1
    counter += 1