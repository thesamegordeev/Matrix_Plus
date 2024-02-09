#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

/* ТЕСТЫ КОНСТРУКТОРОВ */

TEST(Constructors, DefConst) {
  S21Matrix A;
  ASSERT_EQ(A.GetRows(), 3);
  ASSERT_EQ(A.GetCols(), 3);
}

TEST(Constructors, ConstColsRowsNorm) {
  S21Matrix A(2, 4);
  ASSERT_EQ(A.GetRows(), 2);
  ASSERT_EQ(A.GetCols(), 4);
}

TEST(Constructors, ConstColsRowsException) {
  ASSERT_ANY_THROW(S21Matrix(0, 0));
}

TEST(Constructors, CopyConst) {
  S21Matrix A(4, 4);
  A.fillMatrix();
  S21Matrix B(A);
  ASSERT_EQ(A.GetRows(), B.GetRows());
  ASSERT_EQ(A.GetCols(), B.GetCols());
  int cols = A.GetCols();
  int rows = A.GetRows();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(A(i, j), B(i, j));
    }
  }
}

TEST(Constructors, MoveConst) {
  S21Matrix A(4, 4);
  A.fillMatrix();
  S21Matrix tempA(A);
  S21Matrix B(std::move(A));
  ASSERT_EQ(tempA.GetRows(), B.GetRows());
  ASSERT_EQ(tempA.GetCols(), B.GetCols());
  int cols = tempA.GetCols();
  int rows = tempA.GetRows();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(tempA(i, j), B(i, j));
    }
  }
}

/* ТЕСТЫ СЕТТЕРОВ */

TEST(Setters, SetCols) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);

  A.SetCols(3);
  B.SetCols(6);

  ASSERT_EQ(A.GetCols(), 3);
  ASSERT_EQ(B.GetCols(), 6);
}

TEST(Setters, SetRows) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);

  A.SetRows(3);
  B.SetRows(6);

  ASSERT_EQ(A.GetRows(), 3);
  ASSERT_EQ(B.GetRows(), 6);
}

/* ТЕСТЫ МЕТОДОВ */

TEST(Metods, EqMatrix) {
  srand(time(NULL));
  S21Matrix A(4, 4);
  A.fillMatrix();
  S21Matrix A_eq(A);
  S21Matrix A_ne_size(3, 5);
  S21Matrix A_ne_vals(4, 4);
  ASSERT_EQ(A.EqMatrix(A_eq), true);
  ASSERT_NE(A.EqMatrix(A_ne_size), true);
  ASSERT_NE(A.EqMatrix(A_ne_vals), true);
}

TEST(Metods, SumMatrix) {
  S21Matrix A(4, 4);
  A.fillMatrix();
  S21Matrix B(A);
  A.SumMatrix(B);
  int cols = A.GetCols();
  int rows = A.GetRows();
  S21Matrix A_except(3, 2);
  ASSERT_ANY_THROW(A.SumMatrix(A_except));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(A(i, j), B(i, j) * 2);
    }
  }
}

TEST(Metods, SubMatrix) {
  S21Matrix A(4, 4);
  A.fillMatrix();
  S21Matrix B(A);
  int cols = A.GetCols();
  int rows = A.GetRows();

  A.SubMatrix(B);

  S21Matrix A_except(3, 2);
  ASSERT_ANY_THROW(A.SubMatrix(A_except));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(A(i, j), 0.0);
    }
  }
}

TEST(Metods, MulNumber) {
  S21Matrix A(4, 4);
  double num = 2.5;
  A.fillMatrix();
  S21Matrix copyA(A);
  int cols = A.GetCols();
  int rows = A.GetRows();

  A.MulNumber(num);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(A(i, j), copyA(i, j) * num);
    }
  }
}

TEST(Metods, MulMatrix) {
  S21Matrix A_except(3, 3);
  S21Matrix A(2, 2);
  A(0, 0) = 9;
  A(0, 1) = -6;
  A(1, 0) = 6;
  A(1, 1) = -4;
  S21Matrix B(2, 2);
  B(0, 0) = 2;
  B(0, 1) = -3;
  B(1, 0) = 4;
  B(1, 1) = -6;
  S21Matrix result(2, 2);
  result(0, 0) = -6;
  result(0, 1) = 9;
  result(1, 0) = -4;
  result(1, 1) = 6;
  int cols = A.GetCols();
  int rows = A.GetRows();

  ASSERT_ANY_THROW(A.MulMatrix(A_except));

  A.MulMatrix(B);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(A(i, j), result(i, j));
    }
  }
}

TEST(Metods, Transpose) {
  S21Matrix A_Transp(3, 2);
  S21Matrix A(2, 3);
  A(0, 0) = 4;
  A(0, 1) = 2;
  A(0, 2) = 0;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(1, 2) = 5;
  S21Matrix result(3, 2);
  result(0, 0) = 4;
  result(0, 1) = 3;
  result(1, 0) = 2;
  result(1, 1) = 4;
  result(2, 0) = 0;
  result(2, 1) = 5;
  int cols = result.GetCols();
  int rows = result.GetRows();

  A_Transp = A.Transpose();

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(A_Transp(i, j), result(i, j));
    }
  }
}

TEST(Metods, CalcComplements) {
  S21Matrix A_Compl(3, 3);
  S21Matrix A_except(3, 4);
  S21Matrix A(3, 3);
  A(0, 0) = 5;
  A(0, 1) = 7;
  A(0, 2) = 1;
  A(1, 0) = -4;
  A(1, 1) = 1;
  A(1, 2) = 0;
  A(2, 0) = 2;
  A(2, 1) = 0;
  A(2, 2) = 3;
  S21Matrix result(3, 3);
  result(0, 0) = 3;
  result(0, 1) = 12;
  result(0, 2) = -2;
  result(1, 0) = -21;
  result(1, 1) = 13;
  result(1, 2) = 14;
  result(2, 0) = -1;
  result(2, 1) = -4;
  result(2, 2) = 33;
  int cols = result.GetCols();
  int rows = result.GetRows();

  A_Compl = A.CalcComplements();

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(A_Compl(i, j), result(i, j));
    }
  }
  ASSERT_ANY_THROW(A_except.CalcComplements());
}

TEST(Metods, Determinant) {
  S21Matrix A_except(3, 4);
  S21Matrix A_ord3(3, 3);
  A_ord3(0, 0) = 1;
  A_ord3(0, 1) = 2;
  A_ord3(0, 2) = 6;
  A_ord3(1, 0) = 4;
  A_ord3(1, 1) = 3;
  A_ord3(1, 2) = -1;
  A_ord3(2, 0) = 2;
  A_ord3(2, 1) = -2;
  A_ord3(2, 2) = 5;
  S21Matrix A_ord2(2, 2);
  A_ord2(0, 0) = 1;
  A_ord2(0, 1) = 2;
  A_ord2(1, 0) = 3;
  A_ord2(1, 1) = 4;
  S21Matrix A_ord1(1, 1);
  A_ord1(0, 0) = 5;

  ASSERT_EQ(A_ord3.Determinant(), -115);
  ASSERT_EQ(A_ord2.Determinant(), -2);
  ASSERT_EQ(A_ord1.Determinant(), 5);
  ASSERT_ANY_THROW(A_except.Determinant());
}

TEST(Metods, InverseMatrix) {
  S21Matrix A_one(1, 1);
  A_one(0, 0) = 1;
  S21Matrix Inver_A_one(1, 1);
  S21Matrix A_Inver(3, 3);
  S21Matrix A_except(3, 3);
  S21Matrix A(3, 3);
  A(0, 0) = 2;
  A(0, 1) = 5;
  A(0, 2) = 7;
  A(1, 0) = 6;
  A(1, 1) = 3;
  A(1, 2) = 4;
  A(2, 0) = 5;
  A(2, 1) = -2;
  A(2, 2) = -3;
  S21Matrix result(3, 3);
  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;
  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;
  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;
  int cols = result.GetCols();
  int rows = result.GetRows();

  A_Inver = A.InverseMatrix();
  Inver_A_one = A_one.InverseMatrix();

  ASSERT_EQ(Inver_A_one(0, 0), 1);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(A_Inver(i, j), result(i, j));
    }
  }
  ASSERT_ANY_THROW(A_except.InverseMatrix());
}

/* ТЕСТЫ ОПЕРАТОРОВ */

TEST(Operators, op_plus) {
  S21Matrix A_except(3, 2);
  S21Matrix A(4, 4);
  A.fillMatrix();
  S21Matrix B(A);
  int cols = A.GetCols();
  int rows = A.GetRows();

  S21Matrix result = A + B;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(result(i, j), B(i, j) + A(i, j));
    }
  }
  ASSERT_ANY_THROW(A + A_except);
}

TEST(Operators, op_minus) {
  S21Matrix A_except(3, 2);
  S21Matrix A(4, 4);
  A.fillMatrix();
  S21Matrix B(A);
  int cols = A.GetCols();
  int rows = A.GetRows();

  S21Matrix result = A - B;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(result(i, j), 0);
    }
  }
  ASSERT_ANY_THROW(A - A_except);
}

TEST(Operators, op_mul_num) {
  S21Matrix A(4, 4);
  double num = 2.5;
  A.fillMatrix();
  S21Matrix copyA(A);
  int cols = A.GetCols();
  int rows = A.GetRows();

  S21Matrix result = A * num;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(result(i, j), copyA(i, j) * num);
    }
  }
}

TEST(Operators, op_mul_matrix) {
  S21Matrix A_except(3, 3);
  S21Matrix A(2, 2);
  A(0, 0) = 9;
  A(0, 1) = -6;
  A(1, 0) = 6;
  A(1, 1) = -4;
  S21Matrix B(2, 2);
  B(0, 0) = 2;
  B(0, 1) = -3;
  B(1, 0) = 4;
  B(1, 1) = -6;
  S21Matrix check(2, 2);
  check(0, 0) = -6;
  check(0, 1) = 9;
  check(1, 0) = -4;
  check(1, 1) = 6;
  int cols = A.GetCols();
  int rows = A.GetRows();

  ASSERT_ANY_THROW(A * A_except);

  S21Matrix result = A * B;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(result(i, j), check(i, j));
    }
  }
}

TEST(Operators, op_eq) {
  srand(time(NULL));
  S21Matrix A(4, 4);
  A.fillMatrix();
  S21Matrix A_eq(A);
  S21Matrix A_ne_size(3, 5);
  S21Matrix A_ne_vals(4, 4);
  ASSERT_EQ(A == A_eq, true);
  ASSERT_NE(A == A_ne_size, true);
  ASSERT_NE(A == A_ne_vals, true);
}

TEST(Operators, op_assign) {
  S21Matrix A(4, 4);
  A.fillMatrix();
  S21Matrix B = A;
  int cols = A.GetCols();
  int rows = A.GetRows();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(A(i, j), B(i, j));
    }
  }
}

TEST(Operators, op_assign_plus) {
  S21Matrix A(4, 4);
  A.fillMatrix();
  S21Matrix B(A);
  A += B;
  int cols = A.GetCols();
  int rows = A.GetRows();
  S21Matrix A_except(3, 2);
  ASSERT_ANY_THROW(A += A_except);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(A(i, j), B(i, j) * 2);
    }
  }
}

TEST(Operators, op_assign_minus) {
  S21Matrix A(4, 4);
  A.fillMatrix();
  S21Matrix B(A);
  int cols = A.GetCols();
  int rows = A.GetRows();

  A -= B;

  S21Matrix A_except(3, 2);
  ASSERT_ANY_THROW(A -= A_except);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(A(i, j), 0.0);
    }
  }
}

TEST(Operators, op_assign_mul_num) {
  S21Matrix A(4, 4);
  double num = 1.2;
  A.fillMatrix();
  S21Matrix copyA(A);
  int cols = A.GetCols();
  int rows = A.GetRows();

  A *= num;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(A(i, j), copyA(i, j) * num);
    }
  }
}

TEST(Operators, op_assign_mul_matrix) {
  S21Matrix A_except(3, 3);
  S21Matrix A(2, 2);
  A(0, 0) = 9;
  A(0, 1) = -6;
  A(1, 0) = 6;
  A(1, 1) = -4;
  S21Matrix B(2, 2);
  B(0, 0) = 2;
  B(0, 1) = -3;
  B(1, 0) = 4;
  B(1, 1) = -6;
  S21Matrix result(2, 2);
  result(0, 0) = -6;
  result(0, 1) = 9;
  result(1, 0) = -4;
  result(1, 1) = 6;
  int cols = A.GetCols();
  int rows = A.GetRows();

  ASSERT_ANY_THROW(A *= A_except);

  A *= B;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ASSERT_EQ(A(i, j), result(i, j));
    }
  }
}

TEST(Operators, op_iterator) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = -1;
  A(0, 2) = 1;
  A(1, 0) = -38;
  A(1, 1) = 41;
  A(1, 2) = -34;
  A(2, 0) = 27;
  A(2, 1) = -29;
  A(2, 2) = 24;

  ASSERT_ANY_THROW(A(4, 2));
  ASSERT_ANY_THROW(A(2, 4));
  ASSERT_EQ(A(0, 0), 1);
  ASSERT_EQ(A(1, 1), 41);
  ASSERT_EQ(A(2, 2), 24);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}