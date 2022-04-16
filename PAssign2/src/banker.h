#include <cstddef>
#include <cstdlib>
#include <eigen3/Eigen/Dense>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

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
  // bool req sets if the banker is a request or not
  Banker(int row, int col, bool req); // Class constructor
  void calcNeed();
  bool CalcNeed; // whether need has been calculated
                 // [false = need not calculated]
                 // [true = need calculated]
  bool Reqbool;  // whether this instance is a request or not
  matrix_t Alloc, Max, Need;
  vector_t Avail;
  int getRows();
  int getCols();
  void setRows(int row);
  void setCols(int col);
  std::vector<std::string> checkSafety();
};

// Defined in req.cpp
class Request : Bank {
public:
  // Class Constructors
  Request(Banker *mnk);
  Request(Banker *mnk, int proc);
  Request(Banker *mnk, vector_t req, int proc);
  Request(vector_t req, int proc);
  Request(Request *prev, vector_t req, int proc);
  Request(Request const &source); // copy constructor
  Request(void);
  int proccess;
  vector_t ReqVect;
  int pushReq();
  int state;    // make sure the result from pushReq is accessible after calling
  bool reqPush; // used to prevent pushing the request twice
  // Just in case I need a linked list of Requests
  // I already have a vector of requests for this though
  Request *prev; // pointer to the previous request state
  Banker man;
};

// Defined in file.cpp
class FileRead {
public:
  std::string reqFile();
  Banker *CreateAcc(std::string fileName);
  // create a new request queue
  std::vector<Request> *genReqQueue(std::string fileName, Banker *curState);
  // Append to an existing request queue
  void appReqQueue(std::string fileName, Banker *curState,
                   std::vector<Request> *queue);
  template <typename T>
  Bank::matrix_t fillMatrix(T mat, std::fstream &f, std::string word,
                            std::string line, int proc, int res);
  void menuPrompt();
  void menuInputHandler(char input, Banker man, std::vector<Request> *reqs);
  void printStatus(Banker man);
  void printReqs(std::vector<Request> *queue);
};

/*
** OVRERALL TODO LIST:
** COMPLETE INITALIZE
** TODO: SAFETY ALGORITHM
** TODO: GRANT REQUEST CHECK
*/

/*
** INITALIZE:
** - COMPLETE Read Files
** - COMPLETE Store Input from Files into eigen lib row vectors
** - COMPLETE Need 1 Available Row Vector
** - COMPLETE Need 1 Alloc Row Vector for each Process
** - COMPLETE ALLOC matrix that is #procX#res
** - COMPLETE Need 1 MAX Row Vector for each Process
** - COMPLETE MAX matrix that is #procX#res
*/

/*
** SAFETY ALGORITHM:
** - COMPLETE: Print Current State
** - COMPLETE: CHECK ALLOC < MAX
** - COMPLETE: NEED = MAX - ALLOC
** - COMPLETE: WORK = AVAIL
** - TODO: Randomize Values
** - TODO: Output State to .csv file
*/

/*
** GRANT REQUEST CHECK:
** - TODO: Add Request Feature
**   - COMPLETE: add by filePath manually
**   - TODO: add by filePath argument
**   - TODO: add in program manually
** - TODO: Preview state as request
** - TODO: Check if Request is Safe State
** - TODO: Randomize Request
*/
