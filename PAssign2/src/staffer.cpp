#include "banker.h"
/*
int Bank::getRows() { return this->rows; }
int Bank::getCols() { return this->cols; }

void Bank::setRows(int row) { this->rows = row; }
void Bank::setCols(int col) { this->cols = col; }
*/
Banker::Banker(int row, int col) {
  std::cout << "init new Banker" << std::endl;
  rows = row;
  cols = col;
  std::cout << "Rows: " << rows << " Cols: " << cols << std::endl;
  this->Alloc = Eigen::MatrixXi::Constant(rows, cols, 0);
  this->Max = matrix_t::Constant(rows, cols, 0);
  std::cout << "Alloc is of size " << Alloc.rows() << "X" << Alloc.cols()
            << std::endl;
  std::cout << Alloc << std::endl;
  std::cout << "Passed Matrix Init" << std::endl;
}

Banker::Banker(void) {}
