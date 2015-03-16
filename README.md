Phone Number Tranlator
======================

A little C program to find words in your phone number.

Author: Tim Allen

Note: A couple of different algorithms are present in this code, but only
one is used. (The code for the former algorithm is still present, just not called.)

The original approach build a four way tree structure representing all possible
letter permutations in a phone number, and then for each word in the dictionary
traversed the tree looking for that word.  This was inefficient as it had to do
number of words in dict * number of digits in number factorial * 4 comparisons (in the worst case).

The currently used approach instead builds a tree structure representing all
words in the dictionary (hence only have to deal with each letter in each word
in the dictionary once) and then traverses that tree with respect to the number.  This is much faster.

To build:

```
make ph
```

To run:

```
./ph
```

Should build and run on pretty much any system that has GCC and make.
