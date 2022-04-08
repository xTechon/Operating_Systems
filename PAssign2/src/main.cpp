#include "banker.h"

int main(int argc, char **argv) {
  std::cout << "Banker's Algorithm Tester\n"
            << "CSV file formats in the readme\n"
            << "Github: https://github.com/xTechon/Operating_Systems"
            << std::endl;
  FileRead secretary;
  std::string fileName;
  Banker *JimBob = nullptr;
  if (argc == 1) {
    do {
      fileName = secretary.reqFile();
      if (fileName == "q") {
        exit(1);
      }
      JimBob = secretary.CreateAcc(fileName);
    } while (JimBob == (Banker *)nullptr);
  } else if (argc == 2) {
    JimBob = secretary.CreateAcc(argv[1]);
    if (JimBob == (Banker *)nullptr) {
      std::cout << "Invalid File Name, please run again" << std::endl;
      exit(1);
    }
  } else {
    std::cout << "Usage:\n"
              << "./BankersAlgo\n"
              << "./BankersAlgo [FilePath]" << std::endl;
    exit(1);
  }
  std::cout << "Allocation Array:\n" << JimBob->Alloc << std::endl;
  std::cout << "Max Array:\n" << JimBob->Max << std::endl;
  std::cout << "Available Vector:\n" << JimBob->Avail << std::endl;
  exit(1);
}
