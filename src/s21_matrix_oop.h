#include <cmath>
#include <iostream>
#include <stdexcept>

#define EPS 1e-7
using namespace std;

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  //  Вспомогательные функции
  void CreateMatrix();
  void RemoveMatrix();
  void TerminateMatrix();
  S21Matrix GetMinor(int del_row, int del_col);

 public:
  int GetCols();
  int GetRows();
  S21Matrix SetCols(int cols);
  S21Matrix SetRows(int rows);
  // Конструкторы и деструктор
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();
  // Для тестов
  void fillMatrix();
  // Операторы
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix operator=(S21Matrix&& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const double num);
  S21Matrix operator*=(const S21Matrix& other);
  double& operator()(int i, int j);
  //   const double& operator()(int i, int j) const;
  // Операции
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
};