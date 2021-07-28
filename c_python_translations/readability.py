"""
Readability:
Gives reading level of text using Coleman-Liau Index.

Author: Darin Kishore
Date: 7/28/21
"""


def main():
    text = input("Text: ")
    letters_sentences = get_counts(text)
    index = .0588 * letters_sentences[0] - .296 * letters_sentences[1] - 15.8
    if index < 1:
        print('Before Grade 1')
    elif index > 16:
        print('Grade 16+')
    else:
        print(f'Grade {round(index)}')


def get_counts(text) -> (int, int):
    """ Gives letters per 100 words and sents. per 100 words"""
    letters, words, sentences = 0, 0, 0
    for letter in text:
        if letter == ' ':
            words += 1
        if letter in {'.', '!', '?'}:
            sentences += 1
        if letter.isalpha():
            letters += 1
    words += 1  # last word

    return letters / words * 100, sentences / words * 100


if __name__ == '__main__':
    main()
