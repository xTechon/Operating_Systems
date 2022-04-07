#include "banker.h"

std::string FileRead::reqFile() {
  // request file name
  std::cout << "Enter File Name:" << std::endl;
  std::string fileName;
  std::cin >> fileName;
  return fileName;
}

// void FileRead::DepositFunds(Bank<int> Navy) {}
