#include <iostream>
#include <cmath>      // sqrt

struct Point {
  double x;
  double y;
  double z;
};

double distance(Point A, Point B) {
  return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) + (A.z - B.z) * (A.z - B.z));
}

int main(int argc, char** argv) {
  Point A, B;
  std::cout << "Enter first point coordinates: ";
  std::cin >> A.x >> A.y >> A.z;
  std::cout << "Enter second point coordinates: ";
  std::cin >> B.x >> B.y >> B.z;
  
  std::cout << "Euclidean distance is " << distance(A, B) << "\n";

  return 0;
}