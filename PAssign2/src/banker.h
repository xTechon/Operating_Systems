#include <cstddef>
#include <cstdlib>
#include <eigen3/Eigen/Dense>
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
  matrix_t Alloc, Max;
  vector_t Avail;
};

// Defined in file.cpp
class FileRead {
public:
  std::string reqFile();
  Banker *CreateAcc(std::string fileName);
  Bank::matrix_t fillMatrix(Bank::matrix_t mat, std::fstream &f,
                            std::string word, std::string line, int proc,
                            int res);
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
** #Avail vector: 0,1,...,#res
** #ALLOCATION ROWS
** 0,1,...,#res\n
** .
** .
** .
** #procs
** #MAX ROWS
** 0,1,...,#res\n
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
