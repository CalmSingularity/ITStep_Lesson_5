#include <iostream>
#include <cmath>      // sqrt
#include <algorithm>  // std::binary_search
#include <ctime>      // time


template <typename T>
bool binarySearch(T array[], size_t size, T x) {
  size_t middle;
  size_t left = 0;
  size_t right = size - 1;
  while (true) {
    // middle = (left + right) / 2;
    middle = left + (right - left) / 2; 
    if (x < array[middle]) {
      right = middle - 1;
    } else if (x > array[middle]) {
      left = middle + 1;
    } else {
      return true;
    }
    if (left > right) {
      return false;
    }
  }
}


struct Point {
  double x;
  double y;
  double z;
};

double distance(Point A, Point B) {
  return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) + (A.z - B.z) * (A.z - B.z));
}

const Point ZERO = {0.0, 0.0, 0.0};

bool operator < (Point A, Point B) {
  return distance(A, ZERO) < distance(B, ZERO);
}

bool operator >= (Point A, Point B) {
  return !(A < B);
}

bool operator > (Point A, Point B) {
  return distance(A, ZERO) > distance(B, ZERO);
}

bool operator <= (Point A, Point B) {
  return !(A > B);
}

bool operator == (Point A, Point B) {
  return distance(A, ZERO) == distance(B, ZERO);
}

bool operator != (Point A, Point B) {
  return !(A == B);
}


template <typename T>
T getRandom() {}

template <>
int getRandom<int>() {
  return rand();
}

template <>
double getRandom<double>() {
  return (double) rand() / rand(); 
}

template <>
char getRandom<char>() { 
  return rand() % 94 + 32; // using ASCII characters from 32 to 126
}

template <>
Point getRandom<Point>() {
  return {getRandom<double>(), getRandom<double>(), getRandom<double>()};
}


template <typename T>
void generateArray(T array[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    array[i] = getRandom<T>();
  }
}

template <typename T>
void copyArray(T array[], T copy[], size_t size) {
  for (size_t i = 0; i < size; ++i) {
    copy[i] = array[i];
  }
}


template <typename T>
bool generateAndTest(size_t n_of_tests) {
  for (size_t i = 1; i <= n_of_tests; ++i) {
    size_t size = rand() + 10000;  // size of array is random but > 10000
    std::cout << "Array size: " << size << "\n";
    T* array = new T[size];
    T* copy = new T[size];
    generateArray(array, size);
    std::sort(array, array + size);
    copyArray(array, copy, size);

    T key = getRandom<T>();
    if (binarySearch(array, size, key) == std::binary_search(array, array + size, key)) {
      std::cout << "Test #" << i << " - OK\n";      
    } else {
      std::cout << "Error!\n";
      return false;
    }
    delete [] array;
    delete [] copy;
  }
  return true;
}



int main(int argc, char** argv) {
  // srand(time(NULL));

  size_t n_of_tests;
  std::cout << "Enter the number of tests: ";
  std::cin >> n_of_tests;

  std::cout << "TESTING INTEGERS\n";
  if (!generateAndTest<int>(n_of_tests)) {
    return 0;
  }
  
  std::cout << "\nTESTING DOUBLES\n";
  if (!generateAndTest<double>(n_of_tests)) {
    return 0;
  }
  
  std::cout << "\nTESTING CHARS\n";
  if (!generateAndTest<char>(n_of_tests)) {
    return 0;
  }
  
  std::cout << "\nTESTING POINTS\n";
  if (!generateAndTest<Point>(n_of_tests)) {
    return 0;
  }

  return 0;
}