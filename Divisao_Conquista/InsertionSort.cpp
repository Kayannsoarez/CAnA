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

void InsertionSort(int* vetor, int p, int r) {
    int i,j,carta;
    for (j=p+1;j<=r;j++) {
        carta = vetor[j];
        i = j-1;
        while ((i>=p)&&(vetor[i]>carta)) {
            vetor[i+1] = vetor[i];
            i--;
        }
        vetor[i+1] = carta;
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
  InsertionSort(vetor, 0, N - 1);
  int time_finish = getTick();

  cout << "InsertionSort " << (time_finish - time_start) << "miliseg" << endl;

  imprimir_vetor(vetor, N, "saida_Insertion.txt");

  delete[] vetor;
  delete[] vetor2;
  delete[] vetor3;
  return 0;
}
