#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])

{
  vector<vector<int>> mat1, mat2, multResult;
  vector<int> row1, row2;

  int lin1, col1;
  int lin2, col2;
  int el;

  //Abre o primeiro arquivo com a matriz 1 e preenche a matriz 1 para fazer a multiplicação

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

  //Abre o segundo arquivo com a matriz 2 e preenche a matriz 2 para fazer a multiplicação
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

  //Multiplica matrizes caso passe na condição de multiplicação de matrizes
  chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  if (col1 == lin2)
  {
    for (int x = 0; x < lin1; x++)
    {
      multResult.push_back(vector<int>());
      for (int y = 0; y < col2; y++)
      {
        multResult[x].push_back(0);
        for (int z = 0; z < col1; z++)
        {
          multResult[x][y] += mat1[x][z] * mat2[z][y];
        }
      }
    }
    end = std::chrono::system_clock::now();
  }
  else
  {
    cout << "Uma matriz só pode ser multiplicada se o número de colunas da primeira matriz for igual ao número de linhas da segunda matriz." << endl;
    exit(1);
  }

  auto time = chrono::duration_cast<chrono::milliseconds>(end - start).count();

  cout << "Tempo: " << time << "ms" << endl;

  //Armazena o resulta da multiplicação das matrizes, caso seja possível o cálculo
  fstream dataFile;
  dataFile.open("../data/matrices/multResult.txt", fstream::out);

  if (dataFile.fail())
  {
    cerr << "Erro ao abrir o arquivo" << endl;
  }

  dataFile << lin1 << ' ' << col2 << endl;

  for (int x = 0; x < lin1; x++)
  {
    for (int y = 0; y < col2; y++)
    {
      dataFile << "c" << x + 1 << y + 1 << ' ' << multResult[x][y] << endl;
    }
  }

  dataFile << time;

  dataFile.close();

  return 0;
}
