#include <iostream>
#include <cmath>      // std::abs

struct Point {
  double x;
  double y;
  double z;
};

bool isLine(Point A, Point B, Point C) {
  double determinant = A.x * B.y * C.z + A.y * B.z * C.x + A.z * B.x * C.y
                     - A.z * B.y * C.x - A.y * B.x * C.z - A.x * B.z * C.y;
  if (std::abs(determinant) < 0.00001) {
    return true;
  } else {
    return false;
  }
}

int main(int argc, char** argv) {
  Point A, B, C;
  std::cout << "Enter first point coordinates: ";
  std::cin >> A.x >> A.y >> A.z;
  std::cout << "Enter second point coordinates: ";
  std::cin >> B.x >> B.y >> B.z;
  std::cout << "Enter third point coordinates: ";
  std::cin >> C.x >> C.y >> C.z;

  if (isLine(A, B, C)) {
    std::cout << "True: Points lie on a straight line\n";
  } else {
    std::cout << "False: Points do not lie on a straight line\n";
  }

  return 0;
}