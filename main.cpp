#include "include/matrix_calc.h"

int main() {
  system("cls");
  matrix::Matrix<int64_t> a = {
      {5, 6, 7}, {2, 2, 1}, {2, -5, 2}, {4, 2, 3}, {2, 4, 8}};
  matrix::Matrix<int64_t> b = {{3, 2}, {1, 2}, {1, 5}};

  matrix::Matrix<int64_t> c = {
      {5, 6, 7}, {2, 2, 1}, {2, -5, 500}, {4, 2, 3}, {2, 4, 100}};

  a.Print();
  std::cout << std::endl;
  auto d = matrix::Transpose(a);
  d.Transpose();
  d.Print();
}
