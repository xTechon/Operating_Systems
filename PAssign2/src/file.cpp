#include "banker.h"
#include <eigen3/Eigen/src/Core/IO.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string FileRead::reqFile() {
  // request file name
  std::cout << "Enter File Name or type q to quit:" << std::endl;
  std::string fileName;
  std::cin >> fileName;
  return fileName;
}

// Returns a point to a static Banker object if successful, Null otherwise
Banker *FileRead::CreateAcc(std::string fileName) {
  static Banker JimBob;
  int resources = 0, proccesses = 0;

  std::string line, word;
  // second argument is the mode
  static std::fstream fin(fileName, std::ios::in);
  if (fin.is_open()) {
    std::cout << "State File " << fileName << " Opened" << std::endl;
    getline(fin, line);
    std::stringstream str(line);
    getline(str, word, ',');
    resources = stoi(word); // set resources
    getline(str, word, ',');
    proccesses = stoi(word); // set proccesses

    // std::cout << "Row: " << resources << " Col: " << proccesses << std::endl;
    JimBob = Banker(proccesses, resources,
                    false); // Hire JimBob to create our account

    // get the data for the available vector
    JimBob.Avail = fillMatrix(JimBob.Avail, fin, word, line, 1, resources);

    // std::cout << JimBob.Avail << std::endl;
    // Data for the Allocation matrix
    JimBob.Alloc =
        fillMatrix(JimBob.Alloc, fin, word, line, proccesses, resources);
    // Data for the Max matrix
    JimBob.Max = fillMatrix(JimBob.Max, fin, word, line, proccesses, resources);
  } else {
    std::cout << "Could not open the file\n"
              << "Please try Again\n"
              << std::endl;
    return (Banker *)nullptr;
  }
  fin.close();
  return &JimBob;
}
template <typename T>
Bank::matrix_t FileRead::fillMatrix(T mat, std::fstream &f, std::string word,
                                    std::string line, int proc, int res) {
  for (int i = 0; i < proc; i++) { // Rows
    getline(f, line);
    // std::cout << line << std::endl;
    std::stringstream str(line);
    for (int j = 0; j < res; j++) { // Columns
      getline(str, word, ',');
      mat(i, j) = stoi(word);
    }
  }
  return mat;
}

void FileRead::menuPrompt() {
  std::cout << "Choose Options:\n"
            << "1. Print Current State\n"
            << "2. Check Current State's Safety\n"
            << "3. Add a request for a Proccess\n"
            << "4. Print Request State\n"
            << "5. Check Safety of Request(s)\n"
            << "6. Restart with a Randomized State\n"
            << "7. Quit" << std::endl;
}

void FileRead::menuInputHandler(char input, Banker man,
                                std::vector<Request> *reqs) {
  std::vector<std::string> solution;
  std::string fileName;
  switch (input) {
  case '1':
    // Print Current State
    std::cout << "CURRENT STATE" << std::endl;
    printStatus(man);
    break;
  // Check the current State's Safety
  case '2':
    solution = man.checkSafety();
    if (solution.empty() != true) {
      std::cout << "SOLUTION VECTOR: < ";
      for (auto i = solution.begin(); i != solution.end(); ++i) {
        std::cout << *i << " ";
      }
      std::cout << ">" << std::endl;
    } else {
      std::cout << "STATE IS UNSAFE" << std::endl;
    }
    break;
  // Add Request for a Process
  case '3':
    fileName = "";
    std::cout << "Enter Request File Name: ";
    std::cin >> fileName;
    std::cout << "File requested: " << fileName << std::endl;
    reqs = genReqQueue(fileName, &man);
    if (reqs != (std::vector<Request> *)nullptr) {
      // print queue of request to confirm
      // std::cout << "REQUEST(S) READ:" << std::endl;
      // for (auto i = reqs->begin(); i != reqs->end(); ++i) {
      //   std::cout << "P" << i->proccess << ": " << i->ReqVect << std::endl;
      // }
      printReqs(reqs);
    } else {
      std::cout << "FAIL TO GENERATE REQUESTS" << std::endl;
    }
    break;
  case '4':
  case '5':
  case '6':
  case '7':
    exit(1);
    break;
  default:
    std::cout << "INVALIID INPUT, RETRY" << std::endl;
  }
}

void FileRead::printStatus(Banker man) {
  std::stringstream ss;
  std::string temp;
  int width = man.getCols() * 3;
  int col = man.getCols();
  int row = man.getRows();
  std::cout << "STATE: " << std::endl;
  // Headers
  std::cout << fmt::format("{:<7}", "Proc")
            << fmt::format(fmt::format("{{:<{}}}", width), "Alloc")
            << fmt::format("{:<5}", " ")
            << fmt::format(fmt::format("{{:<{}}}", width), "Max")
            << fmt::format("{:<5}", " ")
            << fmt::format(fmt::format("{{:<{}}}", width), "Need")
            << fmt::format("{:<5}", " ")
            << fmt::format(fmt::format("{{:<{}}}", width), "Avail")
            << std::endl;
  // First line to include Avail Man.Availtor
  std::cout << fmt::format("{:<7}", "P0");
  for (int i = 0; i < col; i++) {
    ss.clear();
    ss << man.Alloc(0, i);
    ss >> temp;
    std::cout << fmt::format("{:>3}", temp);
  }
  std::cout << fmt::format("{:<5}", " ");
  for (int i = 0; i < col; i++) {
    ss.clear();
    ss << man.Max(0, i);
    ss >> temp;
    std::cout << fmt::format("{:>3}", temp);
  }
  std::cout << fmt::format("{:>5}", " ");
  for (int i = 0; i < col; i++) {
    ss.clear();
    ss << man.Need(0, i);
    ss >> temp;
    std::cout << fmt::format("{:>3}", temp);
  }
  std::cout << fmt::format("{:>5}", " ");
  for (int i = 0; i < col; i++) {
    ss.clear();
    ss << man.Avail(i);
    ss >> temp;
    std::cout << fmt::format("{:>3}", temp);
  }
  std::cout << std::endl;

  // All subsequent rows
  for (int j = 1; j < row; j++) {
    // Proccess Number
    std::cout << fmt::format("{}{:<6}", "P", j);
    // Values from other Matricies
    for (int i = 0; i < col; i++) {
      ss.clear();
      ss << man.Alloc(j, i);
      ss >> temp;
      std::cout << fmt::format("{:>3}", temp);
    }
    std::cout << fmt::format("{:<5}", " ");
    for (int i = 0; i < col; i++) {
      ss.clear();
      ss << man.Max(j, i);
      ss >> temp;
      std::cout << fmt::format("{:>3}", temp);
    }
    std::cout << fmt::format("{:>5}", " ");
    for (int i = 0; i < col; i++) {
      ss.clear();
      ss << man.Need(j, i);
      ss >> temp;
      std::cout << fmt::format("{:>3}", temp);
    }
    std::cout << std::endl;
  }
}

std::vector<Request> *FileRead::genReqQueue(std::string fileName,
                                            Banker *curState) {
  static std::vector<Request> queue; // create a queue
  // Request tempReq;
  std::string line, word; // temporary buffers for the line reads
  Bank::vector_t temp = Bank::vector_t::Constant(
      curState->getCols(), 0); // init a temp array to zero
  int procTemp = 0;            // int to hold the Process ID
  // The number of requests defined in the begining of the request csv
  int numReq = 0;
  // open the file
  static std::fstream fbin(fileName, std::ios::in);
  if (fbin.is_open()) {
    // open notification
    std::cout << "Request File " << fileName << " Opened" << std::endl;
    getline(fbin, line);
    numReq = stoi(line); // get the number of requests from the file
    for (int i = 0; i < numReq; i++) {
      getline(fbin, line);
      std::stringstream str(line);
      getline(str, word, ',');
      procTemp = stoi(word);
      for (int j = 0; j < curState->getCols(); j++) {
        getline(str, word, ',');
        temp(j) = stoi(word); // Fill in values to vector
      }
      queue.push_back(Request(curState, temp, procTemp));
    }
  } else {
    std::cout << "ERROR: FAIL TO OPEN REQUEST FILE" << std::endl;
    return (std::vector<Request> *)nullptr;
  }
  return &queue;
}

void FileRead::printReqs(std::vector<Request> *reqs) {
  std::cout << "REQUEST(S) READ:" << std::endl;
  for (auto i = reqs->begin(); i != reqs->end(); ++i) {
    std::cout << "P" << i->proccess << ": " << i->ReqVect << std::endl;
  }
}
