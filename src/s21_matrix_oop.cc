#include "s21_matrix_oop.h"

int S21Matrix::GetCols() { return cols_; }
int S21Matrix::GetRows() { return rows_; }

S21Matrix S21Matrix::SetCols(int cols) {
  S21Matrix temp(rows_, cols);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < ((cols_ < cols) ? cols_ : cols); j++) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(temp);
  return *this;
}

S21Matrix S21Matrix::SetRows(int rows) {
  S21Matrix temp(rows, cols_);
  for (int i = 0; i < ((rows_ < rows) ? rows_ : rows); i++) {
    for (int j = 0; j < cols_; j++) {
      temp.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(temp);
  return *this;
}

/* КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ */

S21Matrix::S21Matrix() : S21Matrix(3, 3){};

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1) {
    throw std::invalid_argument("Rows and cols must be greater than 0.");
  }
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = other.matrix_;
  other.TerminateMatrix();
}

S21Matrix::~S21Matrix() {
  RemoveMatrix();
  TerminateMatrix();
}

/* МЕТОДЫ */

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] != other.matrix_[i][j]) result = false;
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw exception(std::invalid_argument(
        "SumMatrix: Different dimensions of the matrices"));
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw exception(std::invalid_argument(
        "SubMatrix: Different dimensions of the matrices"));
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw exception(std::invalid_argument(
        "MulMatrix: the number of columns of the first matrix is not equal to "
        "the number of rows of the second matrix"));
  }
  S21Matrix temp(rows_, other.cols_);
  for (int i = 0; i < temp.rows_; i++) {
    for (int j = 0; j < temp.cols_; j++) {
      for (int p = 0; p < cols_; p++) {
        temp.matrix_[i][j] += matrix_[i][p] * other.matrix_[p][j];
      }
    }
  }
  *this = std::move(temp);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_) {
    throw exception(
        std::invalid_argument("CalcComplements: the matrix is not square"));
  }
  S21Matrix minor(rows_ - 1, cols_ - 1);
  S21Matrix result(rows_, cols_);
  double det = 0.0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      minor = GetMinor(i, j);
      det = minor.Determinant();
      result.matrix_[i][j] = (int)pow(-1, i + j) * det;
    }
  }
  minor.RemoveMatrix();
  return result;
}

double S21Matrix::Determinant() {
  if (cols_ != rows_) {
    throw exception(
        std::invalid_argument("Determinant: the matrix is not square"));
  }
  double result = 0.0;
  int order = rows_;
  if (order == 1)
    result = matrix_[0][0];
  else if (order == 2)
    result += matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  else if (order > 2) {
    S21Matrix minor(rows_ - 1, cols_ - 1);
    for (int j = 0; j < cols_; j++) {
      minor = GetMinor(0, j);
      double det = 0.0;
      det = minor.Determinant();
      result += (int)pow(-1, j) * matrix_[0][j] * det;
    }
    minor.RemoveMatrix();
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (fabs(det) < EPS) {
    throw exception(
        std::invalid_argument("InverseMatrix: Determinant of the matrix is 0"));
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1)
    result.matrix_[0][0] = 1 / det;
  else {
    result = CalcComplements().Transpose();
    result.MulNumber(1 / det);
  }
  return result;
}

/* ОПЕРАТОРЫ */

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw exception(std::invalid_argument(
        "Operator + : Different dimensions of the matrices"));
  }
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw exception(std::invalid_argument(
        "Operator - : Different dimensions of the matrices"));
  }
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw exception(
        std::invalid_argument("Operator * : the number of columns of the first "
                              "matrix is not equal to "
                              "the number of rows of the second matrix"));
  }
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  S21Matrix temp(*this);
  return temp.EqMatrix(other);
}

S21Matrix S21Matrix::operator=(S21Matrix&& other) {
  RemoveMatrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.TerminateMatrix();
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw exception(std::invalid_argument(
        "Operator += : Different dimensions of the matrices"));
  }
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw exception(std::invalid_argument(
        "Operator -= : Different dimensions of the matrices"));
  }
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw exception(
        std::invalid_argument("Operator *= : the number of columns of the "
                              "first matrix is not equal to "
                              "the number of rows of the second matrix"));
  }
  MulMatrix(other);
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i > rows_ || j > cols_) {
    throw exception(std::out_of_range("Index is out of range"));
  }
  return matrix_[i][j];
}

/* ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ */

void S21Matrix::CreateMatrix() {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::fillMatrix() {
  srand(time(NULL));
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = rand() % 50;
    }
  }
}

void S21Matrix::RemoveMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  TerminateMatrix();
}

void S21Matrix::TerminateMatrix() {
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

S21Matrix S21Matrix::GetMinor(int del_row, int del_col) {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i_minor = 0, i_Mat = 0; i_minor < minor.rows_; i_minor++, i_Mat++) {
    for (int j_minor = 0, j_Mat = 0; j_minor < minor.cols_;
         j_minor++, j_Mat++) {
      if (i_Mat == del_row) i_Mat++;
      if (j_Mat == del_col) j_Mat++;
      minor.matrix_[i_minor][j_minor] = matrix_[i_Mat][j_Mat];
    }
  }
  return minor;
}