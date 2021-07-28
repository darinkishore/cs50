"""
Credit.py checks if input is valid credit card,
and outputs the type of card it is if so.
I am very proud of this code.

Author: Darin Kishore
Date: 7/28/21
"""
import re

import cs50


def main():
    card_num = cs50.get_string("Card #: ")
    card_list = list(card_num)
    if luhns_check(card_list):
        classify(card_num)
    else:
        print("INVALID")


def luhns_check(card_list):
    """Checks if card num. valid based on luhn's algorithm
    :param list card_list:
    :return bool:
    """
    sum_card = card_list
    for digit in range(len(sum_card) - 2, -1, -2):
        sum_card[digit] = str(2 * int(sum_card[digit]))
    total = 0
    for number in sum_card:
        total += sum(int(digit) for digit in number)
    return total % 10 == 0


def classify(card) -> print():
    """Regex-based beginning number checking and ensuring proper length.
    :type card: str"""
    # and True used to cast to bool.
    if (re.match(r"\A4", card) and (len(card) == 13 or 16)) and True:
        print("VISA")
    elif (re.match(r"\A3(?=4|7)", card) and len(card) == 15) and True:
        print("AMEX")
    elif (re.match(r"\A5(?=[1-5])", card) and len(card) == 16) and True:
        print("MASTERCARD")
    else:
        print("INVALID")


if __name__ == '__main__':
    main()