#include "banker.h"

int main(int argc, char **argv) {
  Eigen::MatrixXd m = Eigen::MatrixXd::Random(3, 3);
  m = (m + Eigen::MatrixXd::Constant(3, 3, 5)) * 50;
  Eigen::VectorXd v(3);
  v << 1, 2, 3;
  /*
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;
  m(2, 0) = 3;
  m(2, 1) = 3;
  */
  /*
  cout << m << "\n" << v << endl;
  ifstream testFile(fileName);
  string fileContents;
  if (testFile.is_open()) {
    while (testFile.good()) {
      testFile >> fileContents;
      cout << fileContents;
    }
  }
  */
  using namespace std;
  vector<vector<int>> content;
  vector<int> row;
  string line, word;
  // second argument is the mode
  FileRead getter;
  fstream fin(getter.reqFile(), ios::in);
  if (fin.is_open()) {
    while (getline(fin, line)) {
      row.clear();

      stringstream str(line);

      while (getline(str, word, ','))
        row.push_back(stoi(word));
      content.push_back(row);
    }
  } else
    cout << "Could not open the file\n";
  // print contents of vector
  for (int i = 0; i < content.size(); i++) {
    for (int j = 0; j < content[i].size(); j++) {
      cout << content[i][j] << " ";
    }
    cout << "\n";
  }
  return 0;
}
