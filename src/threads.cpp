#include <iostream>
#include <pthread.h>
#include <chrono>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

//Cada thread calcula um único elemento na matriz resultante
void *multMatrices(void *arg)
{
  int *data = (int *)arg;
  int z = 0, x = 0;

  int y = data[0];
  for (x = 1; x <= y; x++)
    z += data[x] * data[x + y];

  int *p = (int *)malloc(sizeof(int));
  *p = z;

  // Usado para encerrar um thread
  pthread_exit(p);
}

//Driver code
int main(int argc, char const *argv[])
{

  int i, y, k;

  vector<vector<int>> mat1, mat2;
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

  int max = lin1 * col2;

  //Declarando um array de threads de tamanho lin1*col2
  pthread_t *threads;
  threads = (pthread_t *)malloc(max * sizeof(pthread_t));

  int count = 0;
  int *data = NULL;
  for (i = 0; i < lin1; i++)
    for (y = 0; y < col2; y++)
    {

      //Armazenando linha e coluna em data
      data = (int *)malloc((20) * sizeof(int));
      data[0] = col1;

      for (k = 0; k < col1; k++)
        data[k + 1] = mat1[i][k];

      for (k = 0; k < lin2; k++)
        data[k + col1 + 1] = mat2[k][y];

      //Criando as threads
      pthread_create(&threads[count++], NULL,
                     multMatrices, (void *)(data));
    }

  printf("RESULTANT MATRIX IS :- \n");
  for (i = 0; i < max; i++)
  {
    void *k;

    //Joining all threads and collecting return value
    pthread_join(threads[i], &k);

    int *p = (int *)k;
    printf("%d ", *p);
    if ((i + 1) % col2 == 0)
      printf("\n");
  }

  return 0;
}