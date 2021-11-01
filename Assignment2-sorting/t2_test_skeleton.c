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

int main()
{
    int number_array[10];

    fill_with_duplicates(number_array, 10);
    printArray(number_array, 10);

    insertionSort(number_array, 10);
    printArray(number_array, 10);
    return 0;
}

void fill_uniform(int *array, int size)
{
    array[0] = 3;
    for(int i = 0; i < size; i++) 
    {
        array[i] = array[0];
    }
}

void printArray(int* arr, int size)
{
  int i;
  for(i=0; i<size;i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
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

void selectionSort(int arr[], int size) 
{ 
  //TODO
  for(int i = 0; i < size-1; i++) 
  {
    int min = i;
    for(int j = i+1; j < size; j++)
    {
      if(arr[min] > arr[j]) 
      {
        min = j;
      }
    }
    if(min != i)
    {
      swap(&arr[i], &arr[min]);
    }
  }
} 

//function to implement an insertion sort
void insertionSort(int arr[], int size) 
{ 
  for(int pass = 0; pass < size-1; pass++)
  {
    for(int i = pass+1; i > 0; i--)
    {
      number_comparisons++;
      if(arr[i-1] > arr[i])
      {
        swap(&arr[i], &arr[i-1]);
      }
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
    swap(&arr[low++], &arr[high--]);
  }

  //recursively call function to sort lower and upper halves
  quickSort(arr, low); //recursively sort the lower half of the array
  quickSort(arr+high+1, size-high-1); //recursively sort the upper half of the array

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
  number_swaps++;
  int temp = *a;
  *a = *b;
  *b = temp;
}
