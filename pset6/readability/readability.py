from cs50 import get_string


def main():
    # get text
    text = get_string("Text: ")
    # count letters
    letters = count_letters(text)
    # count words
    words = count_words(text)
    # count sentences
    sentences = count_sentences(text)

    # index
    l = 100 / words * letters
    s = 100 / words * sentences
    index = round(0.0588 * l - 0.296 * s - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_letters(text):
    letters = 0
    for i in range(len(text)):
        # only alpha
        if text[i].isalpha() == True:
            letters += 1
    return letters


def count_words(text):
    words = 0
    spaces = 0
    # words = spaces + 1
    for i in range(len(text)):
        if text[i].isspace() == True:
            spaces += 1
    words = spaces + 1
    return words


def count_sentences(text):
    sentences = 0
    # end punctuation
    for i in range(len(text)):
        if text[i] == "." or text[i] == "?" or text[i] == "!":
            sentences += 1
    return sentences


main()
