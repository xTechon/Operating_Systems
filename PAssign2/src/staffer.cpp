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
  std::cout << this->getRows() << std::endl;
  Finish.reserve(this->getRows());
  for (int i = 0; i < this->getRows(); i++)
    Finish.push_back(false);
  // std::cout << "FINISH VECTOR MADE: " << Finish.size() << std::endl;
  /*
  for (auto i = Finish.begin(); i != Finish.end(); ++i)
    std::cout << *i << " ";
  std::cout << std::endl;
  */
  // Find an i such that both
  // finish[i] = false
  // needi < work
  // if no such i exists, go to step 4
  int j = 0;
  Bank::vector_t temp = (Bank::vector_t)(this->Need.row(j));
  Bank::vector_t res;
  for (auto i = Finish.begin(); i != Finish.end(); ++i) {
    // convert from one row to a vector
    temp = (Bank::vector_t)(this->Need.row(j));
    // hopefully store the comparison
    res = work - temp;
    std::cout << "WORK - NEEDi = " << res << std::endl;
    // If Needi < Work, than Work - Needi > 0 for all values
    if ((*i == false) && (res.minCoeff() >= 0)) {
      std::cout << "CONDITION PASSED" << std::endl;
    } else {
      std::cout << "CONDITION FAILED" << std::endl;
    }
    j++;
  }
  return 0;
}
