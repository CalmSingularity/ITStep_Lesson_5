#include <iostream>
#include <cmath>      // std::abs

struct Point {
  double x;
  double y;
};

// You can't draw a circle through 3 points 
// if and only if the points lie on a straight line
bool isCircle(Point A, Point B, Point C) {
  double determinant = (A.x - C.x) * (B.y - C.y) - (B.x - C.x) * (A.y - C.y);
  if (std::abs(determinant) < 0.00001) {
    return false;
  } else {
    return true;
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


  if (isCircle(A, B, C)) {
    std::cout << "True: Points lie on a circle\n";
  } else {
    std::cout << "False: Points do not lie on a circle\n";
  }
  
  return 0;
}