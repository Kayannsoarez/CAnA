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

void CountingSort(int *A, int p, int r, int K) {
  int i, j;
  int N = r - p + 1;
  int *B = new int[N];
  int *C = new int[K + 1];
  for (i = 0; i <= K; i++)
    C[i] = 0;
  for (j = p; j <= r; j++)
    C[A[j]]++;
  for (i = 1; i <= K; i++)
    C[i] = C[i] + C[i - 1];
  for (j = r; j >= p; j--)
    B[--C[A[j]]] = A[j];
  for (j = p; j <= r; j++)
    A[j] = B[j - p];
  delete[] B;
  delete[] C;
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

int main() {
  int i, j;

  int K = 200;
  int N = 2000;
  int *vetor = (int *)new int[N];
  srand(time(NULL));
  for (i = 0; i < N; i++)
    vetor[i] = rand() % K;

  imprimir_vetor(vetor, N, "entrada.txt");
  
  int time_start = getTick();
  CountingSort(vetor, 0, N - 1, K);
  int time_finish = getTick();

  cout << "CountingSort " << (time_finish - time_start) << "miliseg"<< endl;
 
  imprimir_vetor(vetor, N, "saida_counting.txt");
  
  free(vetor);
  return 0;
}
