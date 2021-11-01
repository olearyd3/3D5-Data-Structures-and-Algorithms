#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum

#define MAX_STRING_SIZE 81 //max length of a title string
#define ARRAY_SIZE 18626   //a large array size to read in the whole file

//make a struct with character arrays for the title, platform, score and release year
struct Game {
	char title[MAX_STRING_SIZE];
  char platform[MAX_STRING_SIZE];
	int score;
	int release_year;
};

//declare the functions that will be used
int next_token(FILE* f, char *buf, int string_max);
void fetch_data(FILE *csv, struct Game *g);
int load_file(char *fname);
struct Game* compare(struct Game a, struct Game b);
void swap(struct Game *a, struct Game *b);
void insertionSort(struct Game* arr, int size);
void printArray(struct Game* arr, int size);

//main function
int main(int argc, char *argv[]) {

	  // Try to open the input file. If there is a problem, report failure and quit
	  if (load_file("t4_ign.csv") == 0) {
        perror("ERROR: File unable to be opened");
    }
    else {
        printf("\n");
    }

    return EXIT_SUCCESS;
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
void fetch_data(FILE *csv, struct Game* g) {
  //initialise buffer of size max_string_size
    char buf[MAX_STRING_SIZE];
  //call next_token for each term in a line
	  next_token(csv, g->title, MAX_STRING_SIZE);
	  next_token(csv, g->platform, MAX_STRING_SIZE);
	  next_token(csv, buf, MAX_STRING_SIZE);
    g->score = atoi(buf);
	  next_token(csv, buf, MAX_STRING_SIZE);
    g->release_year = atoi(buf);

}

//Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file(char *fname) {
  FILE *f;
  struct Game game_array[ARRAY_SIZE];

  //boiler plate code to ensure we can open the file
  f = fopen(fname, "r");
  if (!f) {
    printf("Unable to open %s\n", fname);
    return 0;
  }
    int numgames = 0;
    while(!feof(f)) {
		fetch_data(f, &game_array[numgames]);
    
    //quicksort goes here
		numgames++;
	}
  insertionSort(game_array, ARRAY_SIZE);
  printf("Title                                          |  Platform              |  Score  |     Release Year|\n");
  printf("----------------------------------------------------------------------------------------------------|\n");
  for(int i = 0; i < 10; i++) {
    printf("%-45s  |  %-20s  |  %-5d  |  %15d|", game_array[i].title, game_array[i].platform, game_array[i].score, game_array[i].release_year);
    printf("\n");
  }
  //close the file stream
  fclose(f);

  return 1;
}

//function to swap two numbers
void swap(struct Game *a, struct Game *b)
{
  struct Game temp = *a;
  *a = *b;
  *b = temp;
}

//function to implement an insertion sort
void insertionSort(struct Game* arr, int size) 
{ 
  //for each value
  for(int pass = 0; pass < size-1; pass++)
  {
    //for the next value
    for(int i = pass+1; i > 0; i--)
    {
      //if the first score is bigger than the next one, swap them
      if(arr[i].score > arr[i-1].score)
      {
        swap(&arr[i], &arr[i-1]);
      }
      //otherwise don't swap them
      else
      {
        break;
      }
    }
  }
}
