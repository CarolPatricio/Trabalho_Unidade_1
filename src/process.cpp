#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cmath>
#include <sstream>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void task1(const int lin, vector<int> *col, const vector<vector<int>> *mat, const int index)
{
  int el;
  for (int x = 0; x < lin; x++)
  {
    el = (*mat)[index][x];
    col->push_back(el);
  }
}

void task2(const int col, vector<int> *lin, const vector<vector<int>> *mat, const int index)
{
  int el;
  for (int y = 0; y < col; y++)
  {
    el = (*mat)[index][y];
    lin->push_back(el);
  }
}

int main(int argc, char const *argv[])
{
  int lin1, col1;
  int lin2, col2;
  int el, p, process;
  vector<vector<int>> mat1, mat2, multResult;
  vector<int> row1, row2;

  p = atoi(argv[3]);

  fstream dataFileM1;
  dataFileM1.open(argv[1]);

  if (dataFileM1.fail())
  {
    cerr << "Erro ao abrir o arquivo" << endl;
  }

  dataFileM1 >> lin1;
  dataFileM1 >> col1;

  for (int x = 0; x < lin1; x++)
  {
    row1.clear();
    for (int y = 0; y < col1; y++)
    {
      dataFileM1 >> el;
      row1.push_back(el);
    }
    mat1.push_back(row1);
  }

  dataFileM1.close();

  fstream dataFileM2;
  dataFileM2.open(argv[2]);

  if (dataFileM2.fail())
  {
    cerr << "Erro ao abrir o arquivo" << endl;
  }

  dataFileM2 >> lin2;
  dataFileM2 >> col2;

  for (int x = 0; x < lin2; x++)
  {
    row2.clear();
    for (int y = 0; y < col2; y++)
    {
      dataFileM2 >> el;
      row2.push_back(el);
    }
    mat2.push_back(row2);
  }

  dataFileM2.close();

  process = ceil(double(lin1 * col2) / double(p));

  //TODO

  return 0;
}
