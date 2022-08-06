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

void imprime_Parent(int i, int j, int **s) {
  if (i == j) {
    cout << i + 1;
    return;
  }

  cout << "(";
  imprime_Parent(i, s[i][j], s);
  cout << "*";
  imprime_Parent(s[i][j] + 1, j, s);
  cout << ")";
}

void imprime_matriz(int **m, int N) {
  int i, j;
  for (i = 0; i < N; i++) {
    for (j = 0; j < i; j++)
      cout << "- ";
    for (j = i; j < N; j++)
      cout << m[i][j] << " ";
    cout << endl;
  }
}

unsigned int MCM(int *p, int N, int **&s) {
  int i, j, k, l;
  int **m = new int *[N];
  for (i = 0; i < N; i++)
    m[i] = new int[N];
  if (s == NULL) {
    s = new int *[N];
    for (i = 0; i < N; i++)
      s[i] = new int[N];
  }

  for (i = 0; i < N; i++)
    m[i][i] = 0;

  for (l = 2; l <= N; l++) {
    for (i = 0; i < N - l + 1; i++) {
      j = i + l - 1;
      m[i][j] = INT_MAX;
      for (k = i; k < j; k++) {
        int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
        if (q < m[i][j]) {
          m[i][j] = q;
          s[i][j] = k;
        }
      }
    }
  }
  imprime_matriz(m, N);
  cout << endl << endl << endl;
  int r = m[0][N - 1];
  for (i = 0; i < N; i++)
    delete[] m[i];
  delete[] m;
  return r;
}

int main() {
  unsigned int time_start, time_finish;

  int **s = NULL;

  // Teste 1
  int N = 3;
  int p[4] = {10, 100, 5, 50};

  time_start = getTick();
  cout << "Numero de Multiplicacoes Escalares = " << MCM(p, N, s) << endl
       << endl;
  time_finish = getTick();

  imprime_Parent(0, N - 1, s);
  cout << "\nTeste 1 - Tempo: " << (time_finish - time_start) << "miliseg" << endl;
  cout << endl << endl << endl;
  
  if (s != NULL) {
    for (int i = 0; i < N; i++)
      delete[] s[i];
    delete[] s;
    s = NULL;
  }

  // Teste 2
  N = 6;
  int q[7] = {30, 35, 15, 5, 10, 20, 25};

  time_start = getTick();
  cout << "Numero de multiplicacoes escalares = " << MCM(q, N, s) << endl
       << endl;
  time_finish = getTick();

  imprime_Parent(0, N - 1, s);
  cout << "\nTeste 2 - Tempo: " << (time_finish - time_start) << "miliseg" << endl;
  cout << endl << endl << endl;
  
  if (s != NULL) {
    for (int i = 0; i < N; i++)
      delete[] s[i];
    delete[] s;
    s = NULL;
  }

  return 0;
}
