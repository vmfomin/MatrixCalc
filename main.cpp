#include "include/matrix_calc.h"

int main() {
  system("cls");
  matrix::Matrix<int64_t> a = {
      {5, 6, 7}, {2, 2, 1}, {2, -5, 2}, {4, 2, 3}, {2, 4, 8},
  };

  matrix::Matrix<int64_t> b = {
      {3, 2},
      {1, 2},
      {1, 5},
  };

  matrix::Matrix<int64_t> g = {
      {5, 6, 7, 4, 2},
      {2, 2, 1, 5, 9},
      {2, -5, 2, 3, 1},
  };

  matrix::Matrix<int64_t> v_row = {{5, 6, 7, 4, 2}};

  matrix::Matrix<int64_t> v_col = {{5}, {6}, {7}, {4}, {2}};

  //   matrix::Matrix<int64_t> square = {
  //       {5, 6, 7, 12},
  //       {4, 3, 2, 15},
  //       {8, 9, 11, 16},
  //       {7, 10, 9, 8},
  //   };

  matrix::Matrix<int64_t> square = {
      {5, 6, 7},
      {4, 3, 2},
      {8, 9, 11},
  };

  // auto det = square.Determinant();
  std::cout << square.Determinant().value();

  // auto vec = g * v_col;
  // if (!vec.IsEmpty()) vec.Print();

  // a.Print();
  // std::cout << std::endl;
  // auto d = matrix::Transpose(a);
  // d.Transpose();
  // d.Print();
}
