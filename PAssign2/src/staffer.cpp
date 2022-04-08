#include "banker.h"
int Banker::getRows() { return this->rows; }
int Banker::getCols() { return this->cols; }

void Banker::setRows(int row) { this->rows = row; }
void Banker::setCols(int col) { this->cols = col; }
Banker::Banker(int row, int col) {
  // std::cout << "init new Banker" << std::endl;
  rows = row;
  cols = col;
  // std::cout << "Rows: " << rows << " Cols: " << cols << std::endl;
  this->Alloc = Eigen::MatrixXi::Constant(rows, cols, 0);
  this->Max = matrix_t::Constant(rows, cols, 0);
  this->Avail = vector_t::Constant(cols, 0);
  // std::cout << "Alloc is of size " << Alloc.rows() << "X" << Alloc.cols()
  //<< std::endl;
  // std::cout << Alloc << std::endl;
  // std::cout << "Passed Matrix Init" << std::endl;
}

Banker::Banker(void) {}

void Banker::calcNeed() { this->Need = Max - Alloc; }
