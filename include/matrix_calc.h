/**
 * @file      matrix_calc.h
 * @author    vmf0min (vlifom@yandex.ru)
 * @brief     Class of matrices operations
 * @version   0.1
 * @date      27-10-2021
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <iostream>
#include <iterator>
#include <optional>
#include <vector>

// TODO обратная матрица Invertible matrix

namespace matrix {
template <typename T>
using Matrix_t = std::vector<std::vector<T>>;

template <typename T>
class Matrix {
 public:
  Matrix() = default;
  Matrix(size_t row, size_t col)
      : row_(row),
        col_(col),
        is_empty_(false),
        matrix_(row, std::vector<T>(col)) {}
  Matrix(const std::initializer_list<std::initializer_list<T>>& list)
      : row_(list.size()),
        col_(list.begin()->size()),
        is_empty_(false),
        matrix_(row_, std::vector<T>(col_)) {
    size_t i = 0;
    for (auto&& element : list) {
      std::copy(std::begin(element), std::end(element), matrix_[i].begin());
      ++i;
    }
  }

  ~Matrix() = default;
  Matrix(const Matrix& other) = default;
  Matrix(Matrix&& other) = default;
  Matrix& operator=(const Matrix& other) = default;
  Matrix& operator=(Matrix&& other) = default;

  auto& operator[](const size_t index) { return matrix_[index]; }
  const auto& operator[](const size_t index) const { return matrix_[index]; }

  Matrix& operator+=(Matrix& rhs) {
    for (size_t i = 0; i < rhs.GetRow(); ++i)
      for (size_t j = 0; j < rhs.GetCol(); ++j) matrix_[i][j] += rhs[i][j];
    return *this;
  }

  Matrix& operator-=(Matrix& rhs) {
    for (size_t i = 0; i < rhs.GetRow(); ++i)
      for (size_t j = 0; j < rhs.GetCol(); ++j) matrix_[i][j] -= rhs[i][j];
    return *this;
  }

  template <typename U>
  Matrix& operator*=(U value) {
    for (size_t i = 0; i < row_; ++i)
      for (size_t j = 0; j < col_; ++j) matrix_[i][j] *= value;
    return *this;
  }

  auto size() const { return std::pair(row_, col_); }
  bool IsEmpty() const { return is_empty_; }

  size_t GetRow() const { return row_; };
  size_t GetCol() const { return col_; };

  void Transpose() {
    Matrix_t<T> transpose(col_, std::vector<T>(row_));
    for (size_t i = 0; i < row_; ++i)
      for (size_t j = 0; j < col_; ++j) transpose[j][i] = matrix_[i][j];
    std::swap(matrix_, transpose);
  }

  [[nodiscard]] std::optional<T> Determinant() {
    if (row_ != col_) return {};
    // TODO добавить многопоточку
    return DeterminantImpl(matrix_);
  }

  T DeterminantImpl(const Matrix_t<T>& minor) {
    if (minor.size() == 2)
      return minor[0][0] * minor[1][1] - minor[1][0] * minor[0][1];

    int64_t det = 0;
    Matrix_t<T> tmp(row_ - 1, std::vector<T>(col_ - 1));
    int16_t sign = -1;
    for (size_t i = 0; i < row_; ++i) {
      for (size_t j = 0; j < col_ - 1; ++j) {
        size_t col = 0;
        for (size_t k = 0; k < col_; ++k) {
          if (k == i) continue;
          tmp[j][col] = matrix_[j + 1][k];
          ++col;
        }
      }

      // TODO добавить многопоточку
      sign = ~sign + 1;
      det += sign * DeterminantImpl(tmp) * matrix_[0][i];
    }
    return det;
  }

  void Print() const {
    for (size_t i = 0; i < matrix_.size(); ++i) {
      for (size_t j = 0; j < matrix_[i].size(); ++j)
        std::cout << matrix_[i][j] << "\t";
      std::cout << std::endl;
    }
  }

 private:
  size_t row_ = 0;
  size_t col_ = 0;
  bool is_empty_ = true;
  Matrix_t<T> matrix_ = {};
};

template <typename T>
[[nodiscard]] Matrix<T> operator*(Matrix<T>& a, Matrix<T>& b) {
  Matrix<T> mult(a.GetRow(), b.GetCol());
  if (a.GetCol() != b.GetRow()) return {};

  for (size_t i = 0; i < b.GetCol(); ++i)
    for (size_t j = 0; j < a.GetRow(); ++j)
      for (size_t k = 0; k < b.GetRow(); ++k) mult[j][i] += a[j][k] * b[k][i];
  return mult;
}

template <typename T, typename U>
[[nodiscard]] Matrix<T> operator*(Matrix<T>& rhs, U value) {
  Matrix<T> mult_scalar(rhs.GetRow(), rhs.GetCol());
  for (size_t i = 0; i < rhs.GetRow(); ++i)
    for (size_t j = 0; j < rhs.GetCol(); ++j)
      mult_scalar[i][j] = rhs[i][j] * value;
  return mult_scalar;
}

template <typename T>
[[nodiscard]] Matrix<T> operator+(Matrix<T>& lhs, Matrix<T>& rhs) {
  if (lhs.size() != rhs.size()) return {};
  Matrix<T> sum(lhs.GetRow(), lhs.GetCol());

  for (size_t i = 0; i < lhs.GetRow(); ++i)
    for (size_t j = 0; j < lhs.GetCol(); ++j) sum[i][j] = lhs[i][j] + rhs[i][j];
  return sum;
}

template <typename T>
[[nodiscard]] Matrix<T> operator-(Matrix<T>& lhs, Matrix<T>& rhs) {
  if (lhs.size() != rhs.size()) return {};
  Matrix<T> subtraction(lhs.GetRow(), lhs.GetCol());

  for (size_t i = 0; i < lhs.GetRow(); ++i)
    for (size_t j = 0; j < lhs.GetCol(); ++j)
      subtraction[i][j] = lhs[i][j] - rhs[i][j];
  return subtraction;
}

template <typename T>
[[nodiscard]] Matrix<T> Transpose(Matrix<T>& rhs) {
  Matrix<T> transpose(rhs.GetCol(), rhs.GetRow());
  for (size_t i = 0; i < rhs.GetRow(); ++i)
    for (size_t j = 0; j < rhs.GetCol(); ++j) transpose[j][i] = rhs[i][j];
  return transpose;
}
}  // namespace matrix
