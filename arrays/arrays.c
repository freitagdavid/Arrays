#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Array {
  int capacity;    // How many elements can this array hold?
  int count;       // How many states does the array currently hold?
  char **elements; // The string elements contained in the array
} Array;

/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array(int capacity) {
  struct Array *array = malloc(sizeof(Array));
  array->capacity = capacity;
  array->count = 0;
  array->elements = malloc(capacity * sizeof(char *));
  return array;
}
/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {
  for (int i = 0; i <= arr->count; i++) {
    free(arr->elements[i]);
  }
  free(arr->elements);
  free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {
  int new_capacity = arr->capacity * 2;
  char **new_elements = malloc(new_capacity * sizeof(char *));
  for (int i = 0; i < arr->capacity; i++) {
    new_elements[i] = arr->elements[i];
  }
  free(arr->elements);
  arr->capacity = new_capacity;
  arr->elements = new_elements;
}

/************************************
 *   ARRAY FUNCTIONS
 ************************************/

/*****
 * Return the element in the array at the given index.
 *
 * Throw an error if the index is out of range.
 *****/
char *arr_read(Array *arr, int index) {
  if (index >= arr->count) {
    printf("Array only has %d items.\n", arr->count);
    return NULL;
  } else {
    return arr->elements[index];
  }
}

/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {

  // Throw an error if the index is greater than the current count
  if (index > arr->count) {
    printf("Array only has %i items.\n", arr->count);
    return;
  }
  // Resize the array if the number of elements is over capacity
  if (arr->count + 1 > arr->capacity) {
    resize_array(arr);
  }

  // Move every element after the insert index to the right one position
  for (int i = arr->count; i > index; i--) {
    arr->elements[i + 1] = arr->elements[i];
  }
  // Copy the element and add it to the array
  arr->elements[index] = strdup(element);
  // Increment count by 1
  arr->count++;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.

  if (arr->count + 1 > arr->capacity) {
    resize_array(arr);
  }

  // Copy the element and add it to the end of the array
  arr->elements[arr->count] = strdup(element);

  // Increment count by 1
  arr->count++;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) {

  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  int item_index = 0;
  for (int i = 0; i <= arr->count; i++) {
    if (arr->elements[i] == element) {
      free(arr->elements[i]);
      item_index = i;
    } else {
      printf("Element does not exist.\n");
      return;
    }
  }

  // Shift over every element after the removed element to the left one position
  for (int i = item_index; i < arr->count; i++) {
    arr->elements[i] = arr->elements[i + 1];
  }
  // Decrement count by 1
  arr->count--;
}

/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr) {
  printf("[");
  for (int i = 0; i < arr->count; i++) {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1) {
      printf(",");
    }
  }
  printf("]\n");
}

#ifndef TESTING
int main(void) {

  Array *arr = create_array(3);

  printf("%d\n", arr->count);
  printf("%d\n", arr->capacity);
  printf("%s \n", arr_read(arr, 0));
  arr_append(arr, "VALUE-1");
  printf("%s \n", arr_read(arr, 0));
  printf("%s \n", arr_read(arr, 1));
  printf("%d \n", arr->count);
  arr_append(arr, "VALUE-2");
  printf("%s \n", arr_read(arr, 1));
  printf("%d \n", arr->count);

  destroy_array(arr);

  return 0;
}
#endif
