# TODO
def main():
    while True:
        try:
            number = int(input("Number: "))
        except:
            continue
        else:
            break
    if Luhn_algo(number):
        print_type(str(number))
    else:
        print("INVALID")


def print_type(n):
    n_len = len(n)
    n = n[:2]
    if (n_len == 15 and (n == "34" or n == "37")):
        print("AMEX")
    elif (n_len == 16 and (n == "51" or n == "52" or n == "53" or n == "54" or n == "55")):
        print("MASTERCARD")
    elif ((n_len == 13 or n_len == 16) and n[0] == "4"):
        print("VISA")
    else:
        print("INVALID")

def Luhn_algo(n):
    sum1 = sum2 = 0
    while (n):
        sum1 += n % 10
        n = int(n / 10)
        x = int(n % 10) * 2
        if x > 9:
            sum2 += x % 10 + 1
        else:
            sum2 += x
        n = int(n / 10)
    total = sum1 + sum2
    if total % 10 == 0:
        return True
    else:
        return False

main()