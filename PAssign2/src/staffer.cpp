#include "banker.h"
int Banker::getRows() { return this->rows; }
int Banker::getCols() { return this->cols; }

void Banker::setRows(int row) { this->rows = row; }
void Banker::setCols(int col) { this->cols = col; }

// Class Constructor
Banker::Banker(int row, int col, bool req) {
  // std::cout << "init new Banker" << std::endl;
  rows = row;
  cols = col;
  // std::cout << "Rows: " << rows << " Cols: " << cols << std::endl;
  this->Alloc = Eigen::MatrixXi::Constant(rows, cols, 0);
  this->Max = matrix_t::Constant(rows, cols, 0);
  this->Avail = vector_t::Constant(cols, 0);
  this->Req = req;
  this->CalcNeed = false;
  // std::cout << "Alloc is of size " << Alloc.rows() << "X" << Alloc.cols()
  //<< std::endl;
  // std::cout << Alloc << std::endl;
  // std::cout << "Passed Matrix Init" << std::endl;
}

Banker::Banker(void) {}

void Banker::calcNeed() {
  this->Need = Max - Alloc;
  this->CalcNeed = true;
}

int Banker::checkSafety() {
  // let work and finish be vector of length m,n resp
  Bank::vector_t work = this->Avail;
  std::vector<bool> Finish;
  Finish.reserve(this->getRows());
  std::fill(Finish.begin(), Finish.end(), (bool)false);
  std::cout << "FINISH VECTOR MADE" << std::endl;
  for (auto i = Finish.begin(); i != Finish.end(); ++i)
    std::cout << *i << " ";
  std::cout << std::endl;
  return 0;
}
