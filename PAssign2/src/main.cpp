#include "banker.h"

int main(int argc, char **argv) {
  std::cout << "Banker's Algorithm Tester\n"
            << "CSV file formats in the readme\n"
            << "Github: https://github.com/xTechon/Operating_Systems"
            << std::endl;
  FileRead secretary;
  std::string fileName;
  Banker *JimBob = nullptr;
  switch (argc) {
    // No arguments are given
  case 1:
    do {
      fileName = secretary.reqFile();
      if (fileName == "q") {
        exit(1);
      }
      JimBob = secretary.CreateAcc(fileName);
    } while (JimBob == (Banker *)nullptr);
    break;
    // One argument is given [filePath]
  case 2:
    JimBob = secretary.CreateAcc(argv[1]);
    if (JimBob == (Banker *)nullptr) {
      std::cout << "Invalid File Name, please run again" << std::endl;
      exit(1);
    }
    break;
    // 2 arguments are given [filePath] [requestfilePath]
  case 3:
  default:
    std::cout << "Usage:\n"
              << "./BankersAlgo\n"
              << "./BankersAlgo [FilePath]" << std::endl;
    exit(1);
    break;
  }
  std::cout << "Allocation Array:\n" << JimBob->Alloc << std::endl;
  std::cout << "Max Array:\n" << JimBob->Max << std::endl;
  std::cout << "Available Vector:\n" << JimBob->Avail << std::endl;
  JimBob->calcNeed();
  std::cout << "Need Matrix:\n" << JimBob->Need << std::endl;
  secretary.printStatus(JimBob->Alloc, JimBob->Max, JimBob->Need, JimBob->Avail,
                        JimBob->getRows());
  exit(1);
}
