from sys import argv
import csv

def main():
    if len(argv) != 3:
        print("Missing command-line argumen")

    people = []
    with open(argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            # print(row)
            people.append(row)

    sequenceSTR = []
    with open(argv[1], "r") as file2:
        reader2 = csv.reader(file2)
        for row2 in reader2:
            if row2[0] == 'name':
                sequenceSTR = (row2)

    sequenceText = ''
    with open(argv[2], "r") as fileTxt:
        sequenceText = fileTxt.read()

    # AGATC AATG TATC
    # print(sequenceSTR)
    # print(people)
    # print(sequenceText)
    print(len(text))
    for text in sequenceText:
        print(text)

main()