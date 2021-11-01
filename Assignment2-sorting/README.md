# Assignment 1: Selection Sort, Insertion Sort and Quicksort

## Task 1 – Setting up the arrays

Generate arrays of the following types:

An ascending sorted array e.g. [ 0, 1, 2, 3, 4, 5 ]

A descending sorted array [ 5, 4, 3, 2, 1, 0 ]

An array where every value is the same (uniform) e.g. [ 3, 3, 3, 3, 3, 3 ]

A randomly shuffled array with no duplicate values e.g. [ 4, 3, 5, 1, 0, 2 ]

A randomly shuffled array with duplicate values e.g. [ 3, 3, 2, 1, 1, 4 ]

Only edit the function were indicated (do not change their signature), but you can add functions,
variables etc.

You can use the t1_test_skeleton.c file to your implementation locally. Note that the
functions are defined in t1_skeleton.c but used in t1_test_skeleton.c, thanks to the
header file t1.h which contains the signatures of the functions implemented in t1_skeleton.c. Note
how t1_test_skeleton.c includes the line:

    #include “t1.h”.
    
To compile this, you can simply write:

    gcc -Wall t1_skeleton.c t1_test_skeleton.c -o t1
    
and then run the executable t1.

## Task 2 - Sorting the data

In this task, you will implement some sorting algorithms. Edit the t2_skeleton.c file to implement the
following sorting algorithms:

- Insertion sort

- Selection sort

- Quicksort – you can choose any pivot selection and partitioning


## Task 3 - Algorithm Comparisons

Update your code for task 2 to count the number of swaps and counts for each of them (using the
global variables number_comparisons and number_swaps). Run t3_test.c to profile your
implementations of the sort functions. (eg gcc -Wall t1_skeleton.c t2_skeleton.c
t3_test.c -o t3).

## Task 4 - Finding most popular games in a dataset

You have been provided with a dataset of game reviews which have been gathered from IGN
over the last 20 years. Write a program that takes the game reviews as an argument and
sorts the reviews on the basis of game scores and finds out what the most popular games of
the last 20 years are. (You may need to make use of the atoi function in order to convert the scores from strings
to ints).
