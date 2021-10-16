# hashing-assignment1-task1
My solution for Task 1 of Assignment 1 of 3D5 Data Structures and Algorithms.

The Assignment is detailed below:

Task 1: Getting Started - 5 Marks

For the first part of this assignment, you should write a hash table to store the frequency of
names in an (unordered) list of Irish surnames. It will therefore use char arrays as keys and
store int as values.

Use the hash function hash1 that adds the integer value of the chars in the string:

int hash(char* s){
int hash = 0;
while(*s){
hash = (hash + *s) % ARRAY_SIZE;
s++;
}
return hash;
}

You should use a linear probing strategy to handle collisions. For simplicity, you do not need to
worry about a dynamically growing hash table. You can use an array to store each key
(assuming that there is a known MAX_STRING_SIZE) as well as its count, and a
fixed size for the hash table (ARRAY_SIZE) and focus on implementing hashing and
linear probing.
Set up your program so that it takes a CSV file as an argument and test your hash table by
loading the test data provided in names.csv. Extend the solution to take in a name as input
from a user and returning its frequency.
