"""
DNA. Would have used separate classes, but can't
submit multiple .py files. :(

Author: Darin Kishore
Date: 7/28/21
"""

import csv
import sys
import re


# small.csv 1.txt
def main():
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna data.csv sequence.txt")

    # data[0] = seq_counts , data[1] = test_seq, data[2] = possible_seqs
    data = list(read_data(sys.argv[1], sys.argv[2]))

    current_counts = dict.fromkeys(data[2], 0)

    update_and_sum(current_counts, data[1])

    suspect = is_match(current_counts, data)

    if suspect:
        print(suspect)
    else:
        print("No Match")


def is_match(current_counts, data) -> str:
    for person in data[0]:
        suspect = True
        count = 0
        for key in person.keys():
            if count != 0:
                if int(person[key]) != int(current_counts[key]):
                    suspect = False
            count += 1
        if suspect:
            return person['name']
    return ''

def update_and_sum(current_counts, sequence):
    """Returns longest consecutive repeats.
    :param dict current_counts:
    :param string sequence:
    """
    max = 0
    for key in current_counts.keys():  # gives string key AATG
        strings = re.findall(rf"(?:{key})+", sequence)
        for string in strings:
            if string.count(key) > max:
                max = string.count(key)
        current_counts[key] = max
        max = 0



def read_data(str_counts, dna_seq) -> (list, str, list):
    seq_counts = []
    with open(str_counts) as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            seq_counts.append(row)

    with open(dna_seq) as f:
        test_seq = f.read()

    possible_seqs = list(seq_counts[0].keys())
    del possible_seqs[0]
    return (seq_counts, test_seq, possible_seqs)


if __name__ == main():
    main()
