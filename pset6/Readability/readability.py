from cs50 import get_string

def main():
    texts = get_string("Text: ")

    letters = 0
    words = 1
    sentences = 0

    for text in texts:
        if text.upper() >= 'A' and text.upper() <= 'Z':
            letters += 1

        elif text == ' ':
            words += 1

        elif text == '.' or text == '!' or text == '?':
            sentences += 1

    # print(f"letters: {letters}")
    # print(f"words: {words}")
    # print(f"sentences: {sentences}")

    L = (letters / words) * 100.0
    # print(f"L: {L}")
    S = (sentences / words) * 100.0
    # print(f"S: {S}")

    index = (0.0588 * L) - (0.296 * S) - 15.8
    grade = round(index)
    # print(grade)

    if grade >= 16:
        print("Grade 16+")

    elif grade < 1:
        print("Before Grade 1")

    else:
        print(f"Grade {grade}")


main()