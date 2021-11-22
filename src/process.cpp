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
  int el, p, process, i = 0;
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

  while (i < process)
  {

    pid_t PID = fork();

    if (PID == 0)
    {
      vector<int> l1, c1;
      vector<string> resultVector;
      int j = 0;

      stringstream dataFileResult;

      dataFileResult << "../data/process" << i + 1 << ".txt";

      fstream dataFile;
      dataFile.open(dataFileResult.str(), fstream::out);

      if (dataFile.fail())
      {
        cerr << "Erro ao abrir o arquivo" << endl;
      }

      chrono::time_point<std::chrono::system_clock> start, end;
      start = std::chrono::system_clock::now();

      int lin = int(p * i / col2);
      int col = (p * i) % col2;

      while (j < p)
      {
        stringstream resultLin;
        int result = 0;

        task1(col2, &c1, &mat2, col);
        task1(lin1, &l1, &mat1, lin);

        for (int y = 0; y < lin1; y++)
        {
          result += l1[y] * c1[y];
        }

        cout << "result" << result << "/ process" << getpid() << endl;

        resultLin << "c" << lin + 1 << col + 1 << " " << result << endl;
        resultVector.push_back(resultLin.str());

        l1.clear();
        c1.clear();

        col++;

        if (col >= col2)
        {
          lin++;
          col = int(p * i / col2);

          if (lin >= lin1)
          {
            break;
          }
        }

        j++;
      }

      end = std::chrono::system_clock::now();
      auto time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
      cout << "Tempo: " << time << "ms" << endl;

      dataFileResult << lin1 << ' ' << col2 << endl;
      for (size_t w = 0; w < resultVector.size(); w++)
      {
        dataFileResult << resultVector[w];
      }
      dataFileResult << time << endl;

      exit(0);
    }
    else if (PID < 0)
    {
      cerr << "Erro : o processo não foi criado." << endl;
      exit(-1);
    }

    i++;
  }
  int z = 0;
  while (z < process)
  {
    wait(NULL);
    z++;
  }

  //TODO

  return 0;
}
