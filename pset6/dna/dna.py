from sys import argv
import sys
import csv


def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    # open files
    csv_f = open(argv[1])
    text = open(argv[2])
    dna = text.read()

    # read the first line to get STR names
    reader = csv.reader(csv_f)
    strs = []
    for row in reader:
        strs = row
        break
    strs.pop(0)
    # find the strs in the sequence
    found_strs = []
    for i in range(len(strs)):
        found_strs.append(str(count_str(strs[i], dna)))
    # find size of database
    csv_f = open(argv[1])
    database = csv.DictReader(csv_f)
    sizel = []
    for row in database:
        sizel.append(row['name'])
    size = len(sizel)

    # compare
    found = False
    csv_f = open(argv[1])
    read = csv.reader(csv_f)
    test = []
    for i in range(size):
        for row in read:
            test = row
            ctest = test[1:len(strs) + 1]
            if found_strs == ctest:
                print(test[0])
                found = True

    if found == False:
        print("No match")
    # close files
    csv_f.close()
    text.close()


def count_str(c_str, dna):
    counter = 0
    max = 0
    # for every base
    for i in range(len(dna)):
        start = i
        end = i + len(c_str)
        sub = dna[start:end]
        # if it matches check the next
        while sub == c_str:
            start += len(c_str)
            end += len(c_str)
            counter += 1
            if counter > max:
                max = counter
            sub = dna[start:end]
        counter = 0
    return max


main()

