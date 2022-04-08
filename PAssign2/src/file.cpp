#include "banker.h"

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

    // std::cout << JimBob.Alloc << std::endl;
    JimBob.Alloc =
        fillMatrix(JimBob.Alloc, fin, word, line, proccesses, resources);
    JimBob.Max = fillMatrix(JimBob.Max, fin, word, line, proccesses, resources);
  } else {
    std::cout << "Could not open the file\n"
              << "Please try Again\n"
              << std::endl;
    return (Banker *)nullptr;
  }
  return &JimBob;
}

Bank::matrix_t FileRead::fillMatrix(Bank::matrix_t mat, std::fstream &f,
                                    std::string word, std::string line,
                                    int proc, int res) {
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
