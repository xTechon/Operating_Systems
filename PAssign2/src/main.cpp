#include "banker.h"

int main(int argc, char **argv) {
  std::cout << "Banker's Algorithm Tester\n"
            << "CSV file formats in the readme\n"
            << "Github: https://github.com/xTechon/Operating_Systems\n"
            << std::endl;
  FileRead secretary;
  std::string fileName;
  Banker *JimBob = nullptr;
  std::vector<Request> *reqs = nullptr; // create a vector for requests
  // menu handling
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
    JimBob = secretary.CreateAcc(argv[1]);
    if (JimBob == (Banker *)nullptr) {
      std::cout << "Invalid File Name, please run again" << std::endl;
      exit(1);
    }
    reqs = secretary.genReqQueue(argv[2], JimBob);
    if (reqs == (std::vector<Request> *)nullptr) {
      std::cout << "FAIL TO GENERATE REQUESTS" << std::endl;
      exit(1);
    }
    break;
  default:
    std::cout << "Usage:\n"
              << "./BankersAlgo\n"
              << "./BankersAlgo [StateFilePath]\n"
              << "./BankersAlgo [StateFilePath] [RequestFilePath]" << std::endl;
    exit(1);
    break;
  }
  JimBob->calcNeed();
  secretary.printStatus(*JimBob);
  if (argc == 3) {
    secretary.printReqs(reqs);
  }
  std::string in;
  while (true) {
    secretary.menuPrompt();
    std::cin >> in;
    // Make sure the input can handle extreneous input
    if (in.length() < 2)
      secretary.menuInputHandler(in[0], *JimBob, reqs);
    else
      std::cout << "INVALIID INPUT, RETRY" << std::endl;
  }
  exit(1);
}
