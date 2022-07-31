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

void BubbleSort(int *vetor, int p, int r) {
  int i;
  while (true) {
    bool stop = true;
    for (i = p; i < r; i++) {
      if (vetor[i] > vetor[i + 1]) {
        trocar(vetor[i], vetor[i + 1]);
        stop = false;
      }
    }
    if (stop)
      break;
  }
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
  BubbleSort(vetor, 0, N - 1);
  int time_finish = getTick();

  cout << "BubbleSort " << (time_finish - time_start) << "miliseg" << endl;

  imprimir_vetor(vetor, N, "saida_bubble.txt");

  delete[] vetor;
  delete[] vetor2;
  delete[] vetor3;
  return 0;
}
