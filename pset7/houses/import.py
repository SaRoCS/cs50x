from cs50 import SQL
from sys import argv
import sys
import csv

#access to db
db = SQL("sqlite:///students.db")

#check arguments
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    sys.exit(1)

#open csv
with open(argv[1]) as file:
    reader = csv.DictReader(file)
    for row in reader:
        #parse name
        namel = []
        name = row['name']
        space = 0
        for i in range(len(name)):
            #add names
            if name[i].isspace():
                namel.append(name[space:i])
                space = i + 1
            #add last name
            if i == len(name) - 1:
                namel.append(name[space:i + 1])
        #add null middle name
        if len(namel) != 3:
            namel.insert(1, None)
        first= namel[0]
        middle = namel[1]
        last = namel[2]
        house = row['house']
        birth = row['birth']

        #insert into db
        db.execute(f"INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", first, middle, last, house, birth)
