#include <iostream>
#include <cmath>      // std::abs

struct Point {
  double x;
  double y;
};

bool isLine(Point A, Point B, Point C) {
  double determinant = (A.x - C.x) * (B.y - C.y) - (B.x - C.x) * (A.y - C.y);
  if (std::abs(determinant) < 0.00001) {
    return true;
  } else {
    return false;
  }
}

int main(int argc, char** argv) {
  Point A, B, C;
  std::cout << "Enter first point coordinates: ";
  std::cin >> A.x >> A.y;
  std::cout << "Enter second point coordinates: ";
  std::cin >> B.x >> B.y;
  std::cout << "Enter third point coordinates: ";
  std::cin >> C.x >> C.y;

  if (isLine(A, B, C)) {
    std::cout << "True: Points lie on a straight line\n";
  } else {
    std::cout << "False: Points do not lie on a straight line\n";
  }
  
  return 0;
}