#include <iostream>
#include <cmath>      // sqrt

template <typename T>
size_t binarySearch(T array[], size_t size, T x) {
  size_t middle;
  size_t left = 0;
  size_t right = size - 1;
  while (true) {
    middle = (left + right) / 2;
    if (x < array[middle]) {
      right = middle - 1;
    } else if (x > array[middle]) {
      left = middle + 1;
    } else {
      return middle;
    }
    if (left > right) {
      return -1;
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

std::istream& operator >> (std::istream& in, Point& A) {
  std::cin >> A.x >> A.y >> A.z;
  return in;
}

bool operator < (Point A, Point B) {
  return distance(A, ZERO) < distance(B, ZERO);
}

bool operator > (Point A, Point B) {
  return !(A < B);
}

bool operator <= (Point A, Point B) {
  return distance(A, ZERO) <= distance(B, ZERO);
}

bool operator >= (Point A, Point B) {
  return !(A <= B);
}

bool operator == (Point A, Point B) {
  return distance(A, ZERO) == distance(B, ZERO);
}

bool operator != (Point A, Point B) {
  return !(A == B);
}


template <typename T>
void enterArray(T array[], size_t size) {
  std::cout << "Enter a sorted array: ";
  for (size_t i = 0; i < size; ++i) {
    std::cin >> array[i];
  }
}

template <typename T>
void searchForEnteredKey(T array[], size_t size) {
  T key;
  std::cout << "Enter a key for binary search: ";
  std::cin >> key;
  size_t key_index = binarySearch(array, size, key);
  if (key_index == -1) {
    std::cout << "The key is not found\n";
  } else {
    std::cout << "The key is found in the array in position " << key_index << "\n";
  }
  std::cout << std::endl;
}


int main(int argc, char** argv) {
  size_t size;
  std::cout << "Enter the size of arrays: ";
  std::cin >> size;
  std::cout << std::endl;

  char array_char[size];
  std::cout << "Binary search of CHARS.\n";
  enterArray(array_char, size);
  searchForEnteredKey(array_char, size);

  int array_int[size];
  std::cout << "Binary search of INTEGERS.\n";
  enterArray(array_int, size);
  searchForEnteredKey(array_int, size);

  double array_double[size];
  std::cout << "Binary search of DOUBLES.\n";
  enterArray(array_double, size);
  searchForEnteredKey(array_double, size);

  Point array_point[size];
  std::cout << "Binary search of POINTS.\n";
  enterArray(array_point, size);
  searchForEnteredKey(array_point, size);

  return 0;
}