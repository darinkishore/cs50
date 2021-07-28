"""Builds a 'mario pyramid' thing."""
from cs50 import get_int

height = 0
while not(height in range(1, 9)):
    height = get_int("gime ur hite")

for i in range(1, height + 1):
    print((height - i) * ' ' + (i * '#') + ('  ') + (i * '#'))