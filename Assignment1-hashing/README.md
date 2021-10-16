hashing-assignment1
This folder contains my solution for Assignment 1 of 3D5 Data Structures and Algorithms.

The Assignment is detailed below:

Task 1: Getting Started

For the first part of this assignment, you should write a hash table to store the frequency of names in an (unordered) list of Irish surnames. It will therefore use char arrays as keys and store int as values.

Use the hash function hash1 that adds the integer value of the chars in the string:

int hash(char* s){ int hash = 0; while(*s){ hash = (hash + *s) % ARRAY_SIZE; s++; } return hash; }

You should use a linear probing strategy to handle collisions. For simplicity, you do not need to worry about a dynamically growing hash table. You can use an array to store each key (assuming that there is a known MAX_STRING_SIZE) as well as its count, and a fixed size for the hash table (ARRAY_SIZE) and focus on implementing hashing and linear probing. Set up your program so that it takes a CSV file as an argument and test your hash table by loading the test data provided in names.csv. Extend the solution to take in a name as input from a user and returning its frequency.

Task 2: Choosing a hash function

Now find a better hash function hash2 for the data considered. Feel free to consult online resources, but make a reference to them in your report. Note, the sample data is only a sample! Do not overfit your function to the sample provided, it should work well with any lists of Irish surnames. Test your function on the sample data, indicate in your report how many collisions occur, is it better than the result from task 1? (Note that it is expected that you will get less collisions than the automatic tests here!)

Task 3: Twice the Fun

Using the hashing function hash3 below, augment your solution to Task 1 such that it uses double hashing instead of linear probing. Use this to demonstrate the improvement of double hashing over linear probing. Document in the report whether hash3 is a good choice to implement double hashing and explain why.

int hash3(char* s) { int hash = 0; while(*s) { hash = 1 + (hash + *s)%(ARRAY_SIZE-1); s++; } return hash; }

Task 4: A More Interesting Application - 5 Marks

Hash tables have numerous applications in computer science. One domain where they can find great use is that of Information Retrieval. Search terms extracted from a collection of documents are used as the keys and lists of documents are stored as values in the table. When a user issues a query, the list of all documents which may be of interest to them can be rapidly retrieved, ranked and presented. For this task you have been given a file containing a list of people. The data which you have been given is real data produced with great effort and expense by a number of Trinity historians. The people mentioned are all individuals who were in some way involved with the 1641 Irish rebellion. Learning about these people is of great interest to historians, but the challenging nature of working with 17th century data can make this difficult. For this task you should expand (a copy of) your solution to the previous tasks. Instead of storing term counts at each index, you should store a list of people with a given surname. The keys of the hash table will be surnames. The values will be linked lists of people. As before you should provide a way to search for information in the hash table. Allow a user to enter a surname and get a list of people with the given surname as a search result. Test on the truncated data and then on the full dataset.
