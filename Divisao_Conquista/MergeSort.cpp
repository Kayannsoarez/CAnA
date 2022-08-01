#include <climits>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;

uint32_t getTick() {
  struct timespec ts;
  unsigned theTick = 0U;
  clock_gettime(CLOCK_REALTIME, &ts);
  theTick = ts.tv_nsec / 1000000;
  theTick += ts.tv_sec * 1000;
  return theTick;
}

void imprimir_vetor(int *vetor, int N, string filename) {
  if (filename == "")
    filename = "saida.txt";
  ofstream arq;
  arq.open(filename.c_str());
  for (int i = 0; i < N; i++)
    arq << vetor[i] << " ";
  arq.close();
}

void Merge(int *vetor, int p, int q, int r) {
  int infinito = INT_MAX;
  int N1 = q - p + 1;
  int N2 = r - q;
  int *esq = new int[N1 + 1];
  int *dir = new int[N2 + 1];
  for (int i = 0; i < N1; i++)
    esq[i] = vetor[p + i];
  for (int j = 0; j < N2; j++)
    dir[j] = vetor[q + j + 1];
  esq[N1] = infinito;
  dir[N2] = infinito;

  int i = 0;
  int j = 0;
  for (int k = p; k <= r; k++) {
    if (esq[i] <= dir[j])
      vetor[k] = esq[i++];
    else
      vetor[k] = dir[j++];
  }
  delete[] esq;
  delete[] dir;
}

void MergeSort(int *vetor, int p, int r) {
  if (p >= r)
    return;
  int q = (p + r) / 2;
  MergeSort(vetor, p, q);
  MergeSort(vetor, q + 1, r);
  Merge(vetor, p, q, r);
}

int main() {

  int N = 2000;
  int *vetor = new int[N];
  srand(time(NULL));

  for (int i = 0; i < N; i++)
    vetor[i] = rand() % 10000;

  imprimir_vetor(vetor, N, "entrada.txt");
  int *vetor2 = new int[N];
  int *vetor3 = new int[N];

  for (int i = 0; i < N; i++) {
    vetor2[i] = vetor[i];
    vetor3[i] = vetor[i];
  }

  int time_start = getTick();
  MergeSort(vetor, 0, N - 1);
  int time_finish = getTick();

  cout << "MergeSort " << (time_finish - time_start) << "miliseg" << endl;

  imprimir_vetor(vetor, N, "saida_Merge.txt");

  delete[] vetor;
  delete[] vetor2;
  delete[] vetor3;
  return 0;
}
