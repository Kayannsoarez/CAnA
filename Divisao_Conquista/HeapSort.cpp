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

void maxheapify(int* vetor, int i, int p, int r) {
    int m = i;
    int esq = p+2*(i-p)+1;
    int dir = p+2*(i-p)+2;
    if ((esq<=r)&&(vetor[esq]>vetor[i])) m = esq;
    if ((dir<=r)&&(vetor[dir]>vetor[m])) m = dir;
    if (m != i) {
        trocar(vetor[i], vetor[m]);
        maxheapify(vetor,m,p,r);
    }
}

void HeapSort(int* vetor, int p, int r) {
    int i;
    for (i=(r+p-1)/2; i>=p; i--) {
        maxheapify(vetor,i,p,r);
    }
    for (i=r;i>p;i--) {
        trocar(vetor[p], vetor[i]);
        r = r-1;
        maxheapify(vetor,p,p,r);
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
  HeapSort(vetor3, 0, N - 1);
  int time_finish = getTick();

  cout << "HeapSort " << (time_finish - time_start) << "miliseg" << endl;

  imprimir_vetor(vetor3, N, "saida_heap.txt");

  delete[] vetor;
  delete[] vetor2;
  delete[] vetor3;
  return 0;
}
