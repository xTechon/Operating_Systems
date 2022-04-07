#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <fstream>
#include <iostream>
#include <string>

// Defined in staffer.cpp
class Bank {
public:
  using matrix_t = Eigen::MatrixXi;
  using vector_t = Eigen::RowVectorXi;
  // getters and setters
  int getRows();
  void setRows(int row);
  int getCols();
  void setCols(int col);

private:
  static int rows;
  static int cols;
};

class Banker : Bank {
public:
  Banker(int row, int col);
  matrix_t Alloc, Max;
  vector_t Avail;
};

// Defined in file.cpp
class FileRead {
public:
  std::string reqFile();
  void DepositFunds(Bank NavyFederal);
};

/*
** OVRERALL TODO LIST:
** TODO: INITALIZE
** TODO: SAFETY ALGORITHM
** TODO: GRANT REQUEST CHECK
*/

/*
** FILE FORMAT AS CSV, ALL INTS:
** #res,#procs\n
** #ALLOCATION ROWS
** 0,...,#res\n
** .
** .
** .
** #procs
** #MAX ROWS
** 0,...,#res\n
** .
** .
** .
** #procs
*/

/*
** INITALIZE TODO LIST:
** - TODO: Read Files
** - TODO: Store Input from Files into eigen lib row vectors
** - TODO: Need 1 Available Row Vector
** - TODO: Need 1 Alloc Row Vector for each Process
** - TODO: ALLOC matrix that is #procX#res
** - TODO: Need 1 MAX Row Vector for each Process
** - TODO: MAX matrix that is #procX#res
** - TODO: NEED = MAX - ALLOC
** - TODO: WORK = AVAIL
*/
