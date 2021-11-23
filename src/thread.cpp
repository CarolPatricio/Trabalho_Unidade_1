#include <iostream>
#include <pthread.h>
#include <chrono>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

typedef struct data
{
  vector<vector<int>> mat1;
  vector<vector<int>> mat2;
  int p;
  int index;
  int lin1;
  int col1;
  int lin2;
  int col2;
} args;

void *multMatrices(void *arg)
{
  data *thread = ((args *)arg);

  stringstream dataFileResult;
  fstream dataFile;

  dataFileResult << "../data/threads/process" << thread->index + 1 << ".txt";

  dataFile.open(dataFileResult.str(), fstream::out);

  chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  vector<int> lin, col;
  vector<string> result;
  int counter = 0;

  int indexLin, indexCol;
  indexLin = int(thread->p * thread->index / thread->col2);
  indexCol = (thread->p * thread->index) % thread->col2;

  while (counter < thread->p)
  {
    stringstream linResult;
    int multiplicationResult = 0;

    int z, w, k;
    z = 0;
    w = 0;
    k = 0;

    while (z < thread->col1)
    {
      int el = (thread->mat1)[indexLin][z];
      lin.push_back(el);
      z++;
    }

    while (w < thread->lin2)
    {
      int el = (thread->mat2)[w][indexCol];
      col.push_back(el);
      w++;
    }

    while (k < thread->col1)
    {
      multiplicationResult += lin[k] * col[k];
      k++;
    }

    linResult << "c" << indexLin + 1 << indexCol + 1 << " " << multiplicationResult << endl;
    result.push_back(linResult.str());

    lin.clear();
    col.clear();

    indexCol++;
    if (indexCol >= thread->col2)
    {
      indexLin++;
      indexCol = int(thread->p * thread->index / thread->col2);
      if (indexLin >= thread->lin1)
      {
        break;
      }
    }
    counter++;
  }

  end = std::chrono::system_clock::now();
  auto time = chrono::duration_cast<chrono::milliseconds>(end - start).count();

  dataFile << thread->lin1 << ' ' << thread->col2 << endl;
  for (int k = 0; k < (int)result.size(); k++)
  {
    dataFile << result[k];
  }
  dataFile << time << endl;

  pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
  vector<vector<int>> mat1, mat2, result;
  int lin1, col1;
  int lin2, col2;
  int el, p, quant;

  fstream dataFile;
  dataFile.open(argv[1]);

  if (dataFile.fail())
  {
    cerr << "Erro ao abrir o arquivo" << endl;
  }

  dataFile >> lin1;
  dataFile >> col1;

  p = atoi(argv[3]);

  for (int i = 0; i < lin1; i++)
  {
    mat1.push_back(vector<int>());
    for (int j = 0; j < col1; j++)
    {
      dataFile >> el;
      mat1[i].push_back(el);
    }
  }

  dataFile.close();

  dataFile.open(argv[2]);
  if (dataFile.fail())
  {
    cerr << "Erro ao abrir o arquivo" << endl;
  }

  dataFile >> lin2;
  dataFile >> col2;

  for (int i = 0; i < lin2; i++)
  {
    mat2.push_back(vector<int>());
    for (int j = 0; j < col2; j++)
    {
      dataFile >> el;
      mat2[i].push_back(el);
    }
  }

  dataFile.close();

  quant = ceil(double(lin1 * col2) / double(p));

  args argsList[quant];
  pthread_t threads[quant];
  void *threadReturn;

  int x, y;

  x = 0;
  y = 0;

  while (x < quant)
  {
    argsList[x].p = p;
    argsList[x].index = x;
    argsList[x].lin1 = lin1;
    argsList[x].col1 = col1;
    argsList[x].lin2 = lin2;
    argsList[x].col2 = col2;
    argsList[x].mat1 = mat1;
    argsList[x].mat2 = mat2;
    pthread_create(&threads[x], NULL, multMatrices, &argsList[x]);
    x++;
  }

  while (y < quant)
  {
    pthread_join(threads[y], &threadReturn);
    y++;
  }

  return 0;
}