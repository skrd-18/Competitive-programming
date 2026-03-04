#include <iostream>
#include <vector>

using namespace std;

void setZeroes(vector<vector<int>> &matrix);

void setZeroes(vector<vector<int>> &matrix) {
  bool isZeroCol = false;
  bool isZeroRow = false;

  for (unsigned long i = 0; i < matrix.size(); i++) { // check the first column
    if (matrix[i][0] == 0) {
      isZeroCol = true;
      break;
    }
  }
  for (unsigned long i = 0; i < matrix[0].size(); i++) { // check the first row
    if (matrix[0][i] == 0) {
      isZeroRow = true;
      break;
    }
  }
  for (unsigned long i = 1; i < matrix.size();
       i++) { // check except the first row and column
    for (unsigned long j = 1; j < matrix[0].size(); j++)
      if (matrix[i][j] == 0) {
        matrix[i][0] = 0;
        matrix[0][j] = 0;
      }
  }
  for (unsigned long i = 1; i < matrix.size();
       i++) { // process except the first row and column
    for (unsigned long j = 1; j < matrix[0].size(); j++)
      if (matrix[i][0] == 0 || matrix[0][j] == 0)
        matrix[i][j] = 0;
  }
  if (isZeroCol) { // handle the first column
    for (unsigned long i = 0; i < matrix.size(); i++)
      matrix[i][0] = 0;
  }
  if (isZeroRow) { // handle the first row
    for (unsigned long i = 0; i < matrix[0].size(); i++)
      matrix[0][i] = 0;
  }
}

int main(int argc, char *argv[]) {
  vector<vector<int>> matrix = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
  setZeroes(matrix);

  // Iterate through each row
  for (const auto &row : matrix) {
    // Iterate through each column in the current row
    for (const auto &element : row) {
      std::cout << element << " ";
    }
    std::cout << std::endl; // Move to the next line
  }
  return 0;
}
