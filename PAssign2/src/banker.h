#include <cstddef>
#include <cstdlib>
#include <eigen3/Eigen/Dense>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

// Defined in staffer.cpp

namespace Gov {
class Bank;
class Banker;
class FileRead;
}; // namespace Gov

class Bank {
public:
  typedef Eigen::MatrixXi matrix_t;
  typedef Eigen::RowVectorXi vector_t;
  int rows;
  int cols;
};

class Banker : Bank {
public:
  Banker(void);
  Banker(int row, int col);
  void calcNeed();
  matrix_t Alloc, Max, Need;
  vector_t Avail;
  int getRows();
  int getCols();
  void setRows(int row);
  void setCols(int col);
};

// Defined in file.cpp
class FileRead {
public:
  std::string reqFile();
  Banker *CreateAcc(std::string fileName);
  template <typename T>
  Bank::matrix_t fillMatrix(T mat, std::fstream &f, std::string word,
                            std::string line, int proc, int res);
  void menuPrompt();
  void printStatus(Bank::matrix_t Alloc, Bank::matrix_t Max,
                   Bank::matrix_t Need, Bank::vector_t vec, int row);
};

/*
** OVRERALL TODO LIST:
** COMPLETE INITALIZE
** TODO: SAFETY ALGORITHM
** TODO: GRANT REQUEST CHECK
*/

/*
** INITALIZE TODO LIST:
** - COMPLETE Read Files
** - COMPLETE Store Input from Files into eigen lib row vectors
** - COMPLETE Need 1 Available Row Vector
** - COMPLETE Need 1 Alloc Row Vector for each Process
** - COMPLETE ALLOC matrix that is #procX#res
** - COMPLETE Need 1 MAX Row Vector for each Process
** - COMPLETE MAX matrix that is #procX#res
*/

/*
** SAFETY ALGORITHM
** - TODO: Print Current State
** - TODO: CHECK ALLOC < MAX
** - TODO: NEED = MAX - ALLOC
** - TODO: WORK = AVAIL
** - TODO: Randomize Values
*/

/*
** GRANT REQUEST CHECK
** - TODO: Add Request Feature
**   - TODO: add by filePath manually
**   - TODO: add by filePath argument
** - TODO: Preview state as request
** - TODO: Check if Request is Safe State
*/
