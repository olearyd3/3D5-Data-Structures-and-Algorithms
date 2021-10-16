#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum

#define MAX_STRING_SIZE 20 //max length of a string
#define ARRAY_SIZE 99991   //a large array size (best if prime)

//make a struct with a character arrays for each of the ten pieces of data
typedef struct Element element; 
struct Element{
	char person_id[MAX_STRING_SIZE];
  char deposition_id[MAX_STRING_SIZE];
	char surname[MAX_STRING_SIZE];
	char forename[MAX_STRING_SIZE];
  char age[MAX_STRING_SIZE];
	char person_type[MAX_STRING_SIZE];
	char gender[MAX_STRING_SIZE];
	char nationality[MAX_STRING_SIZE];
	char religion[MAX_STRING_SIZE];
	char occupation[MAX_STRING_SIZE];
  element *next;
};

//make a hash_table array of type element to be used
element *hash_table[ARRAY_SIZE];
//define global variables for num_terms and collisions - easier than accessing from struct inside of functions
int num_terms = 0;
int collisions = 0;

//declare the functions that will be used
int hash1(char *s);
element *create_new_element();
element *search(char *name);
void insert(element *name);
void add_or_increment(element *name);
void print_number_of_occurences(char *name);
int next_token(FILE* f, char *buf, int string_max);
int load_file(char *fname);
element *fetch_data(FILE *csv);

//main function
int main(int argc, char *argv[]) {
  //define a variable to check a name entered by a user
  char name_to_check[MAX_STRING_SIZE];
  double load_factor = 0.000000;
  //if the file can't open then give error message, otherwise say the file loaded
  if (load_file(argv[1]) == 0) {
    perror("ERROR: File unable to be opened");
  }
  else {
    printf("File %s loaded\n", argv[1]);
  }

  load_factor = ((double)num_terms / (double)ARRAY_SIZE);

  //print out the capacity, number of terms, collisions and load
  printf(" Capacity: %i\n", ARRAY_SIZE);
  printf(" Num Terms: %i\n", num_terms);
  printf(" Collisions: %i\n", collisions);
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

//returns sum of integer values of chars in a string
int hash1(char *s) {
  int hash = 0;
  while (*s) {
    hash = (hash + *s) % ARRAY_SIZE;
    s++;
  }
  return hash;
}

//creates a new element for the new string to be stored
element *create_new_element() {
  //create a variable and allocate it memory. Give key and value NULL and 0
  element *p = (element *)malloc(sizeof(element));
  num_terms++;
  return p;
}

//returns the element with name name or NULL if the element is not present
element *search(char *name) {
  //create an index variable and allocate it the value of the sum of integers in its string
  int index = hash1(name);
  //if NULL, return NULL
  if (hash_table[index] == NULL) {
    return NULL;
  }
  //if not NULL
  else {
    //continuously
    for (;;) {
      if (hash_table[index] != NULL) {
        //compare the strings, if equal return, else add 1 to the index
        if ((strcmp(hash_table[index]->surname, name) == 0)) {
          return hash_table[index];
        }
        else {
          //if the index is 58, make it return to 0
          if (index == ARRAY_SIZE - 1) {
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
void insert(element *name) {
  int index = hash1(name->surname);
  hash_table[index] = name;
}

//searches the name in the array, if it is there increment its count, if not, add it
void add_or_increment(element *name) {
  //sum the integers in hash1
  int index = hash1(name->surname);
  //if the index number slot of hash_table is NULL, then insert()
  if (hash_table[index] == NULL) {
    hash_table[index] = name;
  }
  //otherwise
  else {
    //while the slot is already full
    while (hash_table[index] != NULL) {
      //if the strings are the same
      if (strcmp(hash_table[index]->surname, name->surname) == 0) {
        name->next = hash_table[index];
        hash_table[index] = name;
        //exit the function
        return;
      }
      //otherwise
      else {
        collisions++;
        //if the index is 58, make it return to 0
        if (index == (ARRAY_SIZE - 1)) {
          index = 0;
        }
        index++;
        if (hash_table[index] == NULL) {
          hash_table[index] = name;
          //exit the function
          return;
        }
      }
    }
  }
}

// prints the number of occurences, or 0 if not in the file
void print_number_of_occurences(char *name) {
  //search for the name and give to word
  element *name_entered = search(name);
  //if name is not NULL, then print out the name and amount of appearances
  if (name_entered != NULL) {
    //name = strdup(name_entered->surname);
    printf(">>> Person ID Deposition ID         Surname        Forename Age Person Type  Gender Nationality Religion Occupation\n");
	  while(name_entered != NULL) {
      printf("    %s    %s            %s         %s   %s      %s    %s     %s  %s  %s", name_entered->person_id, name_entered->deposition_id, 
      name_entered->surname, name_entered->forename, name_entered->age, name_entered->person_type, name_entered->gender, name_entered->nationality, name_entered->religion, name_entered->occupation);
      printf("\n");
      //if there is no name in the next slot exit
      if(name_entered->next == NULL) {
        return;
      }
      //if there is a name in the next slot make that the new name_entered
      else {
        name_entered = name_entered->next;
      }
    }
  }
  else if (strcmp(name, "quit") == 0) {
    printf(">>> ");
  }
  else {
    printf(">>> %s not in table\n", name);
  }
}

// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
int next_token(FILE* f, char *buf, int string_max) {
 int i=0, end=0, quoted=0;
	
	while(!feof(f)) {
		// fetch the next character from file		
		buf[i] = fgetc(f);
		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"') { 
      quoted=!quoted; 
      buf[i] = fgetc(f); 
    }
		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted) { 
      break; 
    }
		// end record on newline or end of file
		if(feof(f) || buf[i]=='\n') { 
      end=1; 
      break; 
    } 
		// truncate fields that would overflow the buffer
		if(i < string_max-1) { 
      ++i; 
    } 
	}
	buf[i] = '\0'; // null terminate the string
	return end; // flag stating whether or not this is end of the line
}

//function to fetch data
element *fetch_data(FILE *csv) {
  //initialise buffer of size max_string_size
  //malloc inside this
	element *p = create_new_element();

  //call next_token for each term in a line
	next_token(csv, p->person_id, MAX_STRING_SIZE);
	next_token(csv, p->deposition_id, MAX_STRING_SIZE);
	next_token(csv, p->surname, MAX_STRING_SIZE);
	next_token(csv, p->forename, MAX_STRING_SIZE);
	next_token(csv, p->age, MAX_STRING_SIZE);
	next_token(csv, p->person_type, MAX_STRING_SIZE);
	next_token(csv, p->gender, MAX_STRING_SIZE);
	next_token(csv, p->nationality, MAX_STRING_SIZE);
	next_token(csv, p->religion, MAX_STRING_SIZE);
	next_token(csv, p->occupation, MAX_STRING_SIZE);
	p->next = NULL; // sets next pointer to NULL

	return p;
}

// Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file(char *fname) {
  FILE *f;
  //boiler plate code to ensure we can open the file
  f = fopen(fname, "r");
  if (!f) {
    printf("Unable to open %s\n", fname);
    return 0;
  }
  //remove the first line before reading in the rest of the file
  element* first_line = fetch_data(f);
  num_terms--;
  free(first_line);
  // read until the end of the file
  while (!feof(f)) {
    add_or_increment(fetch_data(f));
  }

  // always remember to close your file stream
  fclose(f);

  return 1;
}
