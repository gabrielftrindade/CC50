from cs50 import get_float

while True:
    answer = get_float("Cash: ")
    if answer > 0 and answer < 200000000:
        break

centavos = answer * 100
print(f"Cash {centavos}")

total = 0
while centavos > 0:
    if centavos >= 25:
        centavos -= 25
    elif centavos >= 10:
        centavos -= 10
    elif centavos >= 5:
        centavos -= 5
    else:
        centavos -= 1

    total += 1

print(f"Total {total}")