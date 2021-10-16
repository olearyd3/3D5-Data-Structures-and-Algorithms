#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum

#define MAX_STRING_SIZE 20 //max length of a string
#define ARRAY_SIZE 99991 //a large array size (best if prime)

//make a struct with a pointer key and value for counting the amount of times words appear
typedef struct Element{
    char *key;
    int value;
} element;

//make a hash_table array of type element to be used
element* hash_table[ARRAY_SIZE];

//defining global variables for num_terms and collisions - easier than accessing from struct inside of functions
int capacity = -1;
int num_terms = 0;
int collisions = 0;

//declare the functions that will be used
int hash1(char* s);
int hash3(char* s);
int hash_function(char* name_to_hash);
element* create_new_element(char* name);
element* search(char* name);
void insert(char* name);
void add_or_increment(char* name);
void print_number_of_occurences(char* name);
void next_token(char *buf, FILE *f, int string_max);
int load_file(char *fname);

int main(int argc, char *argv[]) { 
    //define a variable to check a name entered by a user
	char name_to_check[MAX_STRING_SIZE];
    double load_factor = 0.000000;

    //if the file can't open then give error message, otherwise say the file loaded
    if(load_file(argv[1]) == 0) {
        perror("ERROR: File unable to be opened");
    }
    else {
        printf("File %s loaded\n", argv[1]);
    }
    capacity = capacity-1;
    load_factor = ((double)num_terms/(double)capacity);

    printf(" Capacity: %i\n", capacity);
    printf(" Num Terms: %i\n", num_terms);
    printf(" Collisions: %i\n", collisions+1);
    printf(" Load: %f\n", load_factor);
    //instruct user to enter words
    printf("Enter term to get frequency or type \"quit\" to escape\n");
    //read in words and print the number of occurrences of them unless the word is 'quit'
    do {
		scanf("%20s", name_to_check);
		print_number_of_occurences(name_to_check);
	} while (strcmp(name_to_check, "quit") != 0);
    
    return 0;
}

//hash1 function
int hash1(char* s) {
    int hash = 0;
    while(*s) {
        hash = (hash + *s)%ARRAY_SIZE;
        s++;
    }
    return hash;
}

//returns the sum of integer values of chars in a string - function for double hashing that was provided in code
int hash3(char* s) {
    int hash = 0;
    while(*s) {
        hash = 1 + (hash + *s)%(ARRAY_SIZE-1);
        s++;
    }
    return hash;
}

//function to double hash
int hash_function(char* name_to_hash) {
    int hash1_value;
    int hash3_value;
    hash1_value = hash1(name_to_hash);
    hash3_value = hash3(name_to_hash);
    int hash_value = hash1_value + hash3_value;
    return hash_value;
}
//creates a new element for the new string to be stored
element* create_new_element(char* name) {
    //create a variable and allocate it memory. Give key and value NULL and 0
	element* temp = (element*)malloc(sizeof(element));
	temp->key = NULL;
	temp->value = 0;
    num_terms++;
    //now copy name to key and add 1 to value
	temp->key = strdup(name);
	temp->value++;
    return temp;   
}


//returns the element with name name or NULL if the element is not present
element* search(char* name) {
    //create an index variable and allocate it the value of the sum of integers in its string
    int index = hash_function(name);
    //if NULL, return NULL
    if(hash_table[index] == NULL) {
        return NULL;
    }
    //if not NULL
    else {
        //continuously
        for(;;) {
            if(hash_table[index] != NULL) {
            //compare the strings, if equal return, else add 1 to the index
                if(strcmp(hash_table[index]->key, name) == 0) {
                    return hash_table[index];
                }
                else {
                    //if the index is 58, make it return to 0
                    if(index == ARRAY_SIZE-1) {
                        index = 0;
                    }
                    //add 1 to index
                    index++;
                }
            }
            else {
                return NULL;
            }
        }
    }
}

//function to insert the new string into the hash_table
void insert(char* name) {
   int index = hash_function(name);
   hash_table[index] = create_new_element(name);
}

//searches the name in the array, if it is there increment its count, if not, add it
void add_or_increment(char* name) {
    //sum the integers in hash1
    int index = hash_function(name);
    //if the index number slot of hash_table is NULL, then insert()
	if(hash_table[index] == NULL) {
		insert(name);
	}
    //otherwise
    else {
        //while the slot is already full
        collisions++;
		while(hash_table[index] != NULL) {
            //if the strings are the same, add 1 to amount of appearances of the word
			if(strcmp(hash_table[index]->key, name) == 0) {
				hash_table[index]->value++;
                //exit the function
				return;
			}
            //otherwise
            else {
                //if the index is 58, make it return to 0
                if(index == (ARRAY_SIZE-1)) {
                    index = 0;
                }
				index++;
                if(hash_table[index] == NULL) {
                    hash_table[index] = create_new_element(name);
                    //exit the function
                    return;
                }
			}
		}
	}
}


// prints the number of occurences, or 0 if not in the file
void print_number_of_occurences(char* name) {
    //initialise a counter variable which will be used for the amount of appearances of each word
    int counter = 0;
    //search for the name and give to word
	element* name_entered = search(name);
    //if name is not NULL, then print out the name and amount of appearances
	if(name_entered != NULL) {
		name = strdup(name_entered->key);
		counter = name_entered->value;
		printf(">>> %s - %i \n", name, counter);
	}
    else if(strcmp(name, "quit") == 0) {
        printf(">>> ");
    }
    else {
		printf(">>> %s - 0 \n", name);
	}
}

// function from the assignment 0
// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
void next_token(char *buf, FILE *f, int string_max) {
	// start by skipping any characters we're not interested in
	buf[0] = fgetc(f);
	while (!isalnum(buf[0]) && !feof(f)) { 
        buf[0] = fgetc(f); 
    }
	// read string of alphanumeric characters
	int i=1;
	for (;;) {
		buf[i] = fgetc(f);  // get next character from file          
		if(!isalnum(buf[i])) { 
            break; 
        } // only load letters and numbers
		if(feof(f) ) { 
            break; 
        }          // file ended?
		if(i < (string_max-1)) { 
            ++i; 
        } // truncate strings that are too long
	}
	buf[i] = '\0'; // NULL terminate the string
}


// Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file(char *fname) {
	FILE *f;
	char buf[MAX_STRING_SIZE];
	//boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return 0; 
	}
	
	// read until the end of the file
	while (!feof(f)) {
        capacity++;
		next_token(buf, f, MAX_STRING_SIZE);
		add_or_increment(buf);  //here you call your function from above!
	}

	// always remember to close your file stream
	fclose(f);

	return 1;
}
