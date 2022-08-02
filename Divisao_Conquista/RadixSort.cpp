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

int digito(double valor, int d) {
  double mult = pow(10, -d - 1);
  valor *= mult;
  int dig = 10 * (valor - floor(valor));
  return dig;
}

void RadixSort(double *A, int p, int r, int d1, int d2) {
  int i, j, d;
  int N = r - p + 1;
  int K = 9;
  double *B = new double[N];
  int *C = new int[K + 1];

  for (d = d1; d < d2; d++) {
    for (i = 0; i <= K; i++)
      C[i] = 0;
    for (j = p; j <= r; j++)
      C[digito(A[j], d)]++;
    for (i = 1; i <= K; i++)
      C[i] = C[i] + C[i - 1];
    for (j = r; j >= p; j--)
      B[--C[digito(A[j], d)]] = A[j];
    for (j = p; j <= r; j++)
      A[j] = B[j - p];
  }
  delete[] B;
  delete[] C;
}

void imprimir_vetor(double *vetor, int N, string filename) {
  if (filename == "")
    filename = "saida.txt";
  ofstream arq;
  arq.open(filename.c_str());
  for (int i = 0; i < N; i++)
    arq << vetor[i] << " ";
  arq.close();
}

int main() {
  int i, j;
  
  int N = 2000;
  double *vetor = (double *)new double[N];
  srand(time(NULL));
  for (i = 0; i < N; i++)
    vetor[i] = (double)1000 * rand() / RAND_MAX;

  imprimir_vetor(vetor, N, "entrada.txt");
  
  int time_start = getTick();
  RadixSort(vetor, 0, N - 1, -6, 6);
  int time_finish = getTick();

  cout << "RadixSort " << (time_finish - time_start) << "miliseg"<< endl;
  
  imprimir_vetor(vetor, N, "saida_radix.txt");
  delete[] vetor;
  return 0;
}
