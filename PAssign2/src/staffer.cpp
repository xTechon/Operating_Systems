#include "banker.h"

int Bank::getRows() { return this->rows; }
int Bank::getCols() { return this->cols; }

void Bank::setRows(int row) { this->rows = row; }
void Bank::setCols(int col) { this->cols = col; }

Banker::Banker(int row, int col) {
  setRows(row);
  setCols(col);
  this->Alloc(row, col);
  this->Max(row, col);
  this->Avail(col);
}
