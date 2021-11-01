#include "t1.h"
#include <stdio.h>
#include <stdlib.h>

void fill_uniform(int *array, int size);
void printArray(int* arr, int size);
void fill_ascending(int *array, int size);
void fill_descending(int *array, int size);
void fill_with_duplicates(int *array, int size);
void fill_without_duplicates(int *array, int size);

int main()
{
    int number_array[10];
    fill_ascending(number_array, 10);
    printArray(number_array, 10);
    fill_descending(number_array, 10);
    printArray(number_array, 10);
    fill_with_duplicates(number_array, 10);
    printArray(number_array, 10);
    fill_uniform(number_array, 10);
    printArray(number_array, 10);
    fill_without_duplicates(number_array, 10);
    printArray(number_array, 10);
    //TODO test your functions here
    return 0;
}

//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size)
{
    //let the ith slot of the array equal the value of i for each slot
    for(int i = 0; i < size; i++)
    {
        array[i] = i;
    }
}

//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size)
{
    int k = 0;
    //let the first slot of the array equal the size of the array, then continually add 1 to the slot number and subtract 1 from the size of the array
    for(int i = size-1; i >= 0; i--) 
    {
        array[k] = i;
        k++;
    }
}

//Fills the array with uniform numbers.
void fill_uniform(int *array, int size)
{
    //fill the whole array with the same number as the first slot
    for(int i = 0; i < size; i++) 
    {
        array[i] = array[0];
    }
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed.
void fill_with_duplicates(int *array, int size)
{
    //fill the array with random numbers mod half the size of the array
    for(int i = 0; i < size; i++) 
    {
        array[i] = rand()%(size/2);
    }
}

//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size)
{
    //initialise a temporary variable
    int temp;
    //get an array
    fill_ascending(array, size);

    //for each slot in the array
    for(int i = 0; i < size; i++)
    {
        //initialise a random variable
        int j;
        j = rand()%(size/2);
        //swap the value in the original slot of the array with a value in a random slot in the array to shuffle it
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

//function to print the arrays
void printArray(int* arr, int size){
  int i;
  for(i=0; i<size;i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}
