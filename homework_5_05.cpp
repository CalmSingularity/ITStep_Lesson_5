// This program compares time required for each of the following method of sorting arrays of integers:
// 1. Insertion Sort
// 2. Merge Sort
// 3. Merge Sort* (modified when arrays of 16 or less numbers sorted by Insertion Sort to eliminate excessive overhead)
// 4. std::sort

#include <iostream>   // std::cout
#include <algorithm>  // std::sort
#include <cstdlib>    // std::srand
#include <ctime>      // time, clock
#include <iomanip>    // std::setw

void insertionSort (int array[], size_t size) {
  for (size_t i = 1; i < size; ++i) {
    int key = array[i];
    int j = i - 1;
    while (j >= 0 && array[j] > key) {
      int temp = array[j];
      array[j] = key;
      array[j + 1] = temp;
      --j;
    }
  }
}

// merge two sorted arrays into one; called from mergeSort
void merge(int left[], int right[], size_t left_size, size_t right_size, int output[]) {
  size_t l = 0, r = 0, k = 0;

  while (l < left_size && r < right_size) {
    if (left[l] < right[r]) {
      output[k] = left[l];
      ++l;
    }
    else {
      output[k] = right[r];
      ++r;
    }
    ++k;
  }

  if (l == left_size) {
    while (r < right_size) {
      output[k] = right[r];
      ++r;
      ++k;
    }
  }

  if (r == right_size) {
    while (l < left_size) {
      output[k] = left[l];
      ++l;
      ++k;
    }
  }
}

void mergeSort(int array[], size_t size, bool modified = false) {
  if (size < 2) {
    return;
  }

  if ((modified == true) && (size <= 16)) {
    insertionSort(array, size);
    return;
  }

  size_t left_size = size / 2;
  size_t right_size = size - left_size;

  int* left = new int[left_size];
  int* right = new int[right_size];

  for (size_t i = 0; i < left_size; ++i) {
    left[i] = array[i];
  }

  for (size_t i = 0; i < right_size; ++i) {
    right[i] = array[i + left_size];
  }

  mergeSort(left, left_size, modified);
  mergeSort(right, right_size, modified);
  merge(left, right, left_size, right_size, array);
  delete[] left;
  delete[] right;
}

void copyArray(int array[], int copy[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    copy[i] = array[i];
  }
}

void generateArray(int array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    array[i] = rand();
  }
}


int main(int argc, char** argv) {
  
  // srand(time(NULL));  // not initialize random number generator for stress-testing
  clock_t start;
  
  const size_t MAX_N_ARRAYS = 5000;  // empirically found that generating more than 5000 arrays can cause the programm to crash (depending on the platform)
  int** array[MAX_N_ARRAYS];
  size_t size[MAX_N_ARRAYS];

  std::cout << "Generation of arrays has started...\n";
  double elapsed_generation = 0;
  start = clock();
  size_t current_array = 0;
  while ((elapsed_generation < 5) && (current_array < MAX_N_ARRAYS)) {
    size[current_array] = rand() + 10000;  // size of array is random but > 10000
    
    // create 4 arrays for each method of sorting:
    array[current_array] = new int*[4];  
    for (size_t i = 0; i < 4; ++i) {
      array[current_array][i] = new int[size[current_array]];
    }

    // fill the first array with random numbers:
    generateArray(array[current_array][0], size[current_array]);  
    // copy the first array into 3 other arrays to have the same input for each method of sorting:
    for (size_t i = 1; i < 4; ++i) {  
      copyArray(array[current_array][0], array[current_array][i], size[current_array]);
    }

    elapsed_generation = (double) (clock() - start) / CLOCKS_PER_SEC;  // check how much time elapsed while generating arrays
    ++current_array;
  };

  size_t n_arrays = current_array;
  std::cout << "Generated " << n_arrays << " arrays within " << elapsed_generation << " seconds\n";

  double elapsed[4];
  std::cout << " Size      | Insertion | Merge     | Merge*    | std::sort |\n";

  for (size_t current_array = 0; current_array < n_arrays; ++current_array) {

    // sort each array with different method of sorting:

    start = clock();
    insertionSort(array[current_array][0], size[current_array]);
    elapsed[0] = (double)(clock() - start) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(array[current_array][1], size[current_array]);
    elapsed[1] = (double)(clock() - start) / CLOCKS_PER_SEC;

    start = clock();
    mergeSort(array[current_array][2], size[current_array], true);
    elapsed[2] = (double)(clock() - start) / CLOCKS_PER_SEC;

    start = clock();
    std::sort(array[current_array][3], array[current_array][3] + size[current_array]);
    elapsed[3] = (double)(clock() - start) / CLOCKS_PER_SEC;

    // free memory:
    for (size_t i = 0; i < 4; ++i) {
      delete[] array[current_array][i];
    }
    delete[] array[current_array];

    // print time spent for each method of sorting:
    std::cout << " " << std::setw(9) << std::left << std::fixed << std::setprecision(3) << size[current_array] << " |";
    for (size_t i = 0; i < 4; ++i) {
      std::cout << std::setw(10) << std::right << std::fixed << std::setprecision(3) << elapsed[i] << " |";
    }
    std::cout << "\n";
  }
  return 0;
}