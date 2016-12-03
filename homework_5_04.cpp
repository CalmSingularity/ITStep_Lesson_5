#include <iostream>   // std::cout
#include <algorithm>  // std::sort
#include <cstdlib>    // std::srand
#include <ctime>      // time

void insertionSort(int array[], size_t size) {
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

void merge(int left[], int right[], size_t left_size, size_t right_size, int output[]);

void mergeSortModified(int array[], size_t size) {
  if (size < 2) {
    return;
  }

  if (size <= 16) {
    insertionSort(array, size);
    return;
  }

  size_t left_size = size / 2;
  size_t right_size = size - left_size;

  int left[left_size];
  int right[right_size];

  for (size_t i = 0; i < left_size; ++i) {
    left[i] = array[i];
  }

  for (size_t i = 0; i < right_size; ++i) {
    right[i] = array[i + left_size];
  }

  mergeSortModified(left, left_size);
  mergeSortModified(right, right_size);
  merge(left, right, left_size, right_size, array);
}

void merge(int left[], int right[], size_t left_size, size_t right_size, int output[]) {
  size_t l = 0, r = 0, k = 0;

  while (l < left_size && r < right_size) {
    if (left[l] < right[r]) {
      output[k] = left[l];
      ++l;
    } else {
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

void print(int array[], size_t size) {
  const char* delimiter = "";
  std::cout << "[";
  for (size_t i = 0; i < size; ++i) {
    std::cout << delimiter << array[i];
    delimiter = " ";
  }
  std::cout << "]\n";
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

bool compareArrays(int A[], int B[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    if (A[i] != B[i]) {
      return false;
    }
  }
  return true;
}



int main(int argc, char** argv) {
  
  // srand(time(NULL));
  const size_t N_OF_TESTS = 100;
  
  for (size_t i = 1; i <= N_OF_TESTS; ++i) {
    size_t size = rand();
    std::cout << "Test #" << i << ":\n";
    std::cout << "Array size: " << size << "\n";

    int array[size];
    int copy[size];
    generateArray(array, size);
    // print(array, size);
    copyArray(array, copy, size);
    mergeSortModified(array, size);
    std::sort(copy, copy + size);
    // print(array, size);
    // print(copy, size);

    if (compareArrays(array, copy, size)) {
      std::cout << "Test #" << i << " - OK\n";
    }
    else {
      std::cout << "Error!\n";
      break;
    }
  }

  return 0;
}