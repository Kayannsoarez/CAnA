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

int Busca_Binaria_Rec(int *vetor, int elemento, int p, int r) {
  if (p > r)
    return -1;
  int q = (p + r) / 2;
  if (elemento < vetor[q])
    return Busca_Binaria_Rec(vetor, elemento, p, q - 1);
  if (elemento > vetor[q])
    return Busca_Binaria_Rec(vetor, elemento, q + 1, r);
  return q;
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
  Busca_Binaria_Rec(vetor, -1, 0, N - 1);
  int time_finish = getTick();

  cout << "BuscaBinaria_Recursiva " << (time_finish - time_start) << "miliseg"
       << endl;

  imprimir_vetor(vetor, N, "saida_binaryS_rec.txt");

  delete[] vetor;
  delete[] vetor2;
  delete[] vetor3;
  return 0;
}
