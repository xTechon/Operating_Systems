#include "banker.h"
#include <eigen3/Eigen/src/Core/IO.h>
#include <sstream>
#include <string>

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
    std::cout << "File " << fileName << " Opened" << std::endl;
    getline(fin, line);
    std::stringstream str(line);
    getline(str, word, ',');
    resources = stoi(word); // set resources
    getline(str, word, ',');
    proccesses = stoi(word); // set proccesses

    std::cout << "Row: " << resources << " Col: " << proccesses << std::endl;
    JimBob = Banker(proccesses, resources); // Hire JimBob to create our account

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
            << "3. Add a request(s) for (a) Proccess(es)\n"
            << "4. Print Request State\n"
            << "5. Check Safety of Request(s)" << std::endl;
}
/*
void FileRead::printStatus(Bank::matrix_t Alloc, Bank::matrix_t Max,
                           Bank::matrix_t Need, Bank::vector_t vec, int row) {
  // std::cout << fmt::format("Proc") << std::endl;
  std::cout << "Proc\t"
            << "Alloc\t\t"
            << "Max\t\t"
            << "Need\t\t"
            << "Available" << std::endl;
  // First row of the state
  std::cout << fmt::format(fmt::format("{{:<{}}}|", 10), "Proc")
            << fmt::format(fmt::format("{{:<{}}}|", 10), "Alloc") << std::endl;
  std::stringstream ss;
  std::string temp;
  ss << Alloc.row(0);
  ss >> temp;
  std::cout << fmt::format(fmt::format("{{:<{}}}", 11), "P0")
            << fmt::format(fmt::format("{{:^{}}}|", 10), temp) << std::endl;
  std::cout << "P" << 0 << "\t\t" << Alloc.row(0) << "\t" << Max.row(0)
            << "\t\t" << Need.row(0) << "\t\t" << vec << std::endl;
  // Subsequent Rows of the state
  for (int i = 1; i < Alloc.rows(); i++) {
    std::cout << "P" << i << "\t\t" << Alloc.row(i) << "\t\t" << Max.row(i)
              << "\t\t" << Need.row(i) << std::endl;
  }
}
*/

void FileRead::printStatus(Bank::matrix_t Alloc, Bank::matrix_t Max,
                           Bank::matrix_t Need, Bank::vector_t vec, int row) {
  Eigen::IOFormat CleanFmt(1, 0, " ", " ", " ", " ", " ");
  // std::cout << Alloc.row(0).format(CleanFmt);
  std::stringstream ss;
  std::string temp;
  ss << Alloc.row(0).format(CleanFmt);
  ss >> temp;
  std::cout << fmt::format(fmt::format("{{:<{}}}|", 10), "Proc")
            << fmt::format(fmt::format("{{:<{}}}|", 10), "Alloc") << std::endl;
  std::cout << fmt::format(fmt::format("{{:<{}}}", 11), "P0")
            << fmt::format(fmt::format("{{:^{}}}|", 10), temp) << std::endl;
}
