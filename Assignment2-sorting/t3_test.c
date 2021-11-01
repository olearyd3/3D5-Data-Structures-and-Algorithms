#include "t1.h"
#include "t2.h"
#include <stdio.h> 
#include <stdlib.h>

void fill_uniform(int *array, int size);
void printArray(int* arr, int size);
void fill_ascending(int *array, int size);
void fill_descending(int *array, int size);
void fill_with_duplicates(int *array, int size);
void fill_without_duplicates(int *array, int size);
void selectionSort(int arr[], int size);
void insertionSort(int arr[], int size);
void quickSort(int arr[], int size);

int compare(int a, int b) ;
void swap(int *a, int *b);

int number_comparisons = 0;
int number_swaps = 0;

int is_sorted(int* array, int size);
void print_test_headers();
void print_test_results(char* test_name, int sorted,  int num_swaps, int num_comparisons);
void test_and_print_for_given_array(void (*f) (int*,int), int size, int* array, char* test_name);
void test_all_arrays_of_given_size(void (*f) (int*,int), int size);
void test_all_functions_for_given_size(int size);

int main()
{
    
    test_all_functions_for_given_size(10000);

    return 0;
}


int is_sorted(int* array, int size){
    int i=0;
	for( i=0; i<size-1; i++ ) {
		if( array[i] > array[i+1] ) { 
            printf("unsorted\n");
            return 0; 
        }
	}
     printf("sorted\n");
	return 1;
}

void fill_uniform(int *array, int size)
{
    array[0] = 3;
    for(int i = 0; i < size; i++) 
    {
        array[i] = array[0];
    }
}

void print_test_headers(){
    int n =10; // column width
    int n_first =25; //first column width
    printf("%*s | %*s | %*s | %*s |\n", n_first, "TEST", n, "SORTED", n, "SWAPS", n, "COMPS");
}

void print_test_results(char* test_name, int sorted,  int num_swaps, int num_comparisons){
    int n =10; // column width
    int n_first =25; //first column width
    printf("%*s | %*s | %*d | %*d |\n",n_first, test_name, n, sorted? "YES" : "NO", n, num_swaps, n, num_comparisons);

}

void test_and_print_for_given_array(void (*f) (int*,int), int size, int* array, char* test_name){
    number_comparisons = 0; 
    number_swaps = 0;
    (*f)(array, size);
    print_test_results( test_name, is_sorted(array,size),number_swaps,number_comparisons);
}

void test_all_arrays_of_given_size(void (*f) (int*,int), int size){
    
    print_test_headers();

    int* array =  malloc(size * sizeof(int));

    fill_ascending(array,size);
    test_and_print_for_given_array(f,size, array, "Ascending");
    
    
    fill_descending(array,size);
    test_and_print_for_given_array(f,size, array, "Descending");


    fill_uniform(array,size);
    test_and_print_for_given_array(f,size, array, "Uniform");


    fill_with_duplicates(array,size);
    test_and_print_for_given_array(f,size, array, "Random w duplicates");


    fill_without_duplicates(array,size);
    test_and_print_for_given_array(f,size, array, "Random w/o  duplicates");
    
    printf("\n\n");


}

void test_all_functions_for_given_size(int size){
    printf("Arrays of size %d: \n", size); 
    printf("  Selection sort\n");
    test_all_arrays_of_given_size(selectionSort, size);
    printf("  Insertion sort\n");
    test_all_arrays_of_given_size(insertionSort, size);
    printf("  Quick sort\n");
    test_all_arrays_of_given_size(quickSort, size);
    printf("\n\n");

}

//function to compare two numbers
int compare(int a, int b) 
{
  number_comparisons++;
  return a-b;
}

//function to swap two numbers
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size)
{
    //TODO
    for(int i = 0; i < size; i++)
    {
        array[i] = i;
    }
}

//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size)
{
    int k = 0;
    //TODO
    for(int i = size-1; i >= 0; i--) 
    {
        array[k] = i;
        k++;
    }
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed.
void fill_with_duplicates(int *array, int size)
{
    //TODO
    for(int i = 0; i < size; i++) 
    {
        array[i] = rand()%(size/2);
    }
    
}

//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size)
{
    //TODO
    int temp;
    fill_ascending(array, size);

    for(int i = 0; i < size; i++)
    {
        int j;
        j = rand()%(size/2);
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

//function to implement a selection sort
void selectionSort(int arr[], int size) 
{ 
  //for each value
  for(int i = 0; i < size-1; i++) 
  {
    int min = i;
    //for the next value
    for(int j = i+1; j < size; j++)
    {
      number_comparisons++;
      //if the ith value is bigger than the next value, let it be the next value
      if(arr[min] > arr[j]) 
      {
        min = j;
      }
    }
    number_swaps++;
    //if the value has changed, swap the two values of the array
    if(min != i)
    {
      swap(&arr[i], &arr[min]);
    }
  }
} 

//function to implement an insertion sort
void insertionSort(int arr[], int size) 
{ 
  //for each value
  for(int pass = 0; pass < size-1; pass++)
  {
    //for the next value
    for(int i = pass+1; i > 0; i--)
    {
      number_comparisons++;
      //if the first value is bigger than the next one, swap them
      if(arr[i-1] > arr[i])
      {
        swap(&arr[i], &arr[i-1]);
        number_swaps++;
      }
      //otherwise don't swap them
      else
      {
        break;
      }
    }
  }
}

//function to implement a quicksort
void quickSort(int arr[], int size) 
{   
  int low = 0; //initialise a low variable to start at the start of the array
  int high = size-1; //initialise a high variable to start at the last slot of the array
  int piv = arr[size/2]; //let the pivot be the halfway point of the array

  //if there is only one thing in the array, or nothing in the array, there is no need to sort it
  if(size < 2)
  {
    return;
  }

  //partitioning
  for(;;)
  {
    //while the number in the first slot of the array is smaller than the pivot, add 1 to the value of low until a value smaller than the pivot is found
    while(compare(arr[low], piv) < 0)
    {
      low++;
    }
    //while the number in the last slot of the array is greater than the pivot, subtract 1 from the value of high, until a value larger than the pivot is found
    while(compare(arr[high], piv) > 0)
    {
      high--;
    }
    //if the searching from the left and the right meet at the same value then exit the loop
    if(low >= high)
    {
      break;
    }
    //swap the values of low and high that were found to be larger and smaller than the pivot respectfully
    number_swaps++;
    swap(&arr[low++], &arr[high--]);
  }

  //recursively call function to sort lower and upper halves
  quickSort(arr, low); //recursively sort the lower half of the array
  quickSort(arr+high+1, size-high-1); //recursively sort the upper half of the array

}
