# TODO


while True:
    try:
        height = int(input("Height: "))
        if (height > 0 and height < 9):
            break
    except ValueError:
        continue

for i in range(1, height + 1):
    print(" " * (height - i), end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i)
