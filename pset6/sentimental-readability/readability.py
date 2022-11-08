# TODO
from cs50 import get_string

def main():
    text = get_string("Text: ")
    sentences = spaces = letters = 0
    for letter in text:
        if letter.isalpha():
            letters += 1
        elif (letter == "?" or letter == "!" or letter == "."):
            sentences += 1
        elif (letter.isspace()):
            spaces += 1
        else:
            continue
    words = spaces + 1
    l = (letters / words) * 100
    s = (sentences / words) * 100
    index = Coleman_Liau_index(l, s)
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")

def Coleman_Liau_index(L, S):
    return round(0.0588 * L - 0.296 * S - 15.8)

main()