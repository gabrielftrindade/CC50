from cs50 import get_int

while True:
    answer = get_int("Height: ")
    if answer > 0 and answer < 9:
        break
for row in range(answer):
    for col in range(answer):
        calculate = answer - (row + 1)
        if col >= calculate:
            print("#", end="")
        else:
            print(" ", end="")
    print("  ", end="")
    for col in range(row + 1):
        print("#", end="")
    print()
