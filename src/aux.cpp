#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{

  int dimensions[4];
  int index = 0;

  //Armazena dentro do vetor dimensões os argumentos passados na linha de comando
  for (int i = 1; i < argc; i++)
  {
    dimensions[index] = atoi(argv[i]);
    index++;
  }

  vector<vector<int>> mat1, mat2;
  vector<int> row1, row2;

  //Gera as matrizes 1 e 2

  srand((int)time(NULL));

  for (int x = 0; x < dimensions[0]; x++)
  {
    row1.clear();
    for (int y = 0; y < dimensions[1]; y++)
    {
      row1.push_back(rand() % 10 + 1);
    }

    mat1.push_back(row1);
  }

  for (int x = 0; x < dimensions[2]; x++)
  {
    row2.clear();
    for (int y = 0; y < dimensions[3]; y++)
    {
      row2.push_back(rand() % 10 + 1);
    }

    mat2.push_back(row2);
  }

  //Armaze as matrizes em arquivos .txt

  fstream dataFileM1;

  dataFileM1.open("../data/matrices/mat1.txt", fstream::out);

  if (dataFileM1.fail())
  {
    cerr << "Erro ao abrir o arquivo" << endl;
  }

  dataFileM1 << dimensions[0] << ' ' << dimensions[1] << endl;

  for (int x = 0; x < dimensions[0]; x++)
  {
    for (int y = 0; y < dimensions[1]; y++)
    {
      dataFileM1 << mat1[x][y] << (y < dimensions[1] - 1 ? ' ' : '\n');
    }
  }

  dataFileM1.close();

  fstream dataFileM2;

  dataFileM2.open("../data/matrices/mat2.txt", fstream::out);

  if (dataFileM2.fail())
  {
    cerr << "Erro ao abrir o arquivo" << endl;
  }

  dataFileM2 << dimensions[2] << ' ' << dimensions[3] << endl;

  for (int x = 0; x < dimensions[2]; x++)
  {
    for (int y = 0; y < dimensions[3]; y++)
    {
      dataFileM2 << mat2[x][y] << (y < dimensions[3] - 1 ? ' ' : '\n');
    }
  }

  dataFileM2.close();

  return 0;
}
