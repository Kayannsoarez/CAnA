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

void trocar(int &x, int &y) {
  int z = x;
  x = y;
  y = z;
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

int Particiona(int *vetor, int p, int r) {
  int pivo = vetor[r];
  int i = p - 1;
  for (int j = p; j < r; j++) {
    if (vetor[j] <= pivo) {
      i++;
      trocar(vetor[i], vetor[j]);
    }
  }
  trocar(vetor[i + 1], vetor[r]);
  return i + 1;
}

int Particione_aleat(int *vetor, int p, int r) {
  srand(time(NULL));
  int pos_pivo = p + rand() % (r - p + 1);
  trocar(vetor[pos_pivo], vetor[r]);
  return Particiona(vetor, p, r);
}

void QuickSort(int *vetor, int p, int r) {
  if (p >= r)
    return;
  int q = Particione_aleat(vetor, p, r);
  QuickSort(vetor, p, q - 1);
  QuickSort(vetor, q + 1, r);
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
  QuickSort(vetor2, 0, N - 1);
  int time_finish = getTick();

  cout << "QuickSort " << (time_finish - time_start) << "miliseg" << endl;

  imprimir_vetor(vetor2, N, "saida_quick.txt");

  delete[] vetor;
  delete[] vetor2;
  delete[] vetor3;
  return 0;
}
