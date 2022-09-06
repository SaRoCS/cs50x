from cs50 import SQL
from sys import argv
import sys

#access db
db = SQL("sqlite:///students.db")

#check argv
if len(argv) != 2:
    print("Usage: python roster.py House_name")
    sys.exit(1)

#query
house = argv[1]
names_list = []
names_list = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", house)

#print
for row in names_list:
    temp = row
    first = temp['first']
    middle = temp['middle']
    last = temp['last']
    birth = temp['birth']

    #if middle name exists print
    if middle != None:
        print(f"{first} {middle} {last}, born {birth}")
    #no middle name
    else:
        print(f"{first} {last}, born {birth}")