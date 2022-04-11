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
  this->Reqbool = req;
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

std::vector<std::string> Banker::checkSafety() {
  // STEP 1:
  //  let work and finish be vector of length m,n resp
  Bank::vector_t work = this->Avail;
  std::vector<bool> Finish;
  std::vector<std::string> solution;
  std::string proc;
  Finish.reserve(this->getRows());
  // Init Finish to all false
  for (int i = 0; i < this->getRows(); i++)
    Finish.push_back(false);
  int j = 0;
  Bank::vector_t temp = (Bank::vector_t)(this->Need.row(j));
  Bank::vector_t res;
  // Worst case is O(n^2), where n is the number of procs,
  // because you have to itterate through all processes at least 1 time
  // and if all are fails after every itteration, then you would have to do
  // n loops, so n loops n times is n^2
  // therefore:
  for (int k = 0; k < this->getRows(); k++) {
    j = 0; // re-initalize j
    // iterate through the false vector
    // STEP 2:
    // Find an i such that both
    // finish[i] = false
    // needi < work
    // if no such i exists, go to step 4
    for (auto i = Finish.begin(); i != Finish.end(); ++i) {
      // convert from one row to a vector
      temp = (Bank::vector_t)(this->Need.row(j));
      // hopefully store the comparison
      res = work - temp;
      // std::cout << "WORK - NEEDi = " << res << std::endl;
      //  If Needi < Work, than Work - Needi > 0 for all values
      if ((*i == false) && (res.minCoeff() >= 0)) {
        // std::cout << "CONDITION PASSED" << std::endl;
        //  STEP 3:
        //   work = work + Alloci
        temp = (Bank::vector_t)(this->Alloc.row(j));
        work += temp;
        Finish[j] = true; //  Finish[i] = true
        // std::cout << "WORK + ALLOCi = " << work << std::endl;
        // std::cout << "FINISH[i] = " << *i << std::endl;
        //  Push Process Number to the solution vector
        proc = "P" + (std::to_string(j));
        solution.push_back(proc);
      }
      /*
      else {
        std::cout << "CONDITION FAILED" << std::endl;
      }*/
      j++;
    } // for I in Finish Loop end
    // STEP 4:
    // If Finish[i] == true than safe state
    bool done = true;
    for (auto j = Finish.begin(); j != Finish.end(); ++j) {
      if (*j == false) {
        done = false;
        continue;
      }
    }
    if (done == true) {
      std::cout << "SAFE STATE" << std::endl;
      return solution;
    }
  } // For K loop end
  // empty whatever was in the solution if there was anything
  solution.clear();
  return solution;
}
