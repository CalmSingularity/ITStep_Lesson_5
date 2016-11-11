#include <iostream>   // std::cout
#include <algorithm>  // std::sort
#include <cstdlib>    // std::srand
#include <ctime>      // time
#include <cmath>      // sqrt

struct Point {
    int x;
    int y;
};

Point ZERO = {0.0, 0.0};

void printPointsArray(Point array[], size_t size) {
  const char* delimiter = "";
  std::cout << "[";
  for (size_t i = 0; i < size; ++i) {
    std::cout << delimiter << "(" << array[i].x << ", " << array[i].y << ")";
    delimiter = ", ";
  }
  std::cout << "]\n";
}

double distance(Point A, Point B) {
  return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

bool operator < (Point A, Point B) {
  return distance(A, ZERO) < distance(B, ZERO);
}

bool operator != (Point A, Point B) {
  if ((A.x != B.x) || (A.y != B.y)) {
    return true;
  } else {
    return false;
  }
}

void merge(Point left[], Point right[], size_t left_size, size_t right_size, Point output[]);

void mergeSort(Point array[], size_t size) {
  if (size < 2) {
    return;
  }

  size_t left_size = size / 2;
  size_t right_size = size - left_size;

  Point left[left_size];
  Point right[right_size];

  for (size_t i = 0; i < left_size; ++i) {
    left[i] = array[i];
  }

  for (size_t i = 0; i < right_size; ++i) {
    right[i] = array[i + left_size];
  }

  mergeSort(left, left_size);
  mergeSort(right, right_size);
  merge(left, right, left_size, right_size, array);
}

void merge(Point left[], Point right[], size_t left_size, size_t right_size, Point output[]) {
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

void copyArray(Point array[], Point copy[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    copy[i] = array[i];
  }
}

void generateArray(Point array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    array[i].x = rand();
    array[i].y = rand();
    // std::cout << "Generated point: (" << array[i].x << ", " << array[i].y << ")\n";
  }
}

bool compareArrays(Point A[], Point B[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    if (A[i] != B[i]) {
      const float ERROR = 0.01;
      std::cout << "--- Arrays mismatch in position " << i << ":\n";
      double A_to_zero = distance(A[i], ZERO);
      double B_to_zero = distance(B[i], ZERO);
      std::cout << "Value A = (" << A[i].x << ", " << A[i].y << "); Euclidean distance from zero point: " << A_to_zero << "\n";
      std::cout << "Value B = (" << B[i].x << ", " << B[i].y << "); Euclidean distance from zero point: " << B_to_zero << "\n";
      if (abs(A_to_zero - B_to_zero) < ERROR) {
        std::cout << "Euclidean distance difference less than " << ERROR << ", OK to proceed\n";
      } else {
        std::cout << "Euclidean distance difference more than " << ERROR << "\n";
        return false;
      }
    }
  }
  return true;
}


int main(int argc, char** argv) {
  
  const size_t N_OF_TESTS = 100;
  srand(time(NULL));

  for (size_t i = 1; i <= N_OF_TESTS; ++i) {  
    size_t size = rand();
    std::cout << "Test #" << i << ":\n";
    std::cout << "Array size: " << size << "\n";
    
    Point* array = new Point[size];
    Point* copy = new Point[size];
    generateArray(array, size);
    // printPointsArray(array, size);
    copyArray(array, copy, size);
    mergeSort(array, size);
    std::sort(copy, copy + size);
    // printPointsArray(array, size);
    // printPointsArray(copy, size);

    if (compareArrays(array, copy, size)) {
      std::cout << "Test #" << i << " - OK!\n\n";
    }
    else {
      std::cout << "Error!\n";
      break;
    }
    delete [] array;
    delete [] copy;
  }

  return 0;
}