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

unsigned int LCS(char *x, char *y, int m, int n, char **&b) {
  int i, j;
  int **c = new int *[m + 1];
  for (int i = 0; i <= m; i++)
    c[i] = new int[n + 1];
  if (b == NULL) {
    b = new char *[m + 1];
    for (int i = 0; i <= m; i++)
      b[i] = new char[n + 1];
  }

  for (i = 0; i <= m; i++)
    c[i][0] = 0;
  for (j = 0; j <= n; j++)
    c[0][j] = 0;

  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      if (x[i - 1] == y[j - 1]) {
        c[i][j] = c[i - 1][j - 1] + 1;
        b[i][j] = '\\';
      } else if (c[i - 1][j] == c[i][j - 1]) {
        c[i][j] = c[i - 1][j];
        b[i][j] = '2';
      } else if (c[i - 1][j] < c[i][j - 1]) {
        c[i][j] = c[i][j - 1];
        b[i][j] = '-';
      } else {
        c[i][j] = c[i - 1][j];
        b[i][j] = '|';
      }
    }
  }
  int r = c[m][n];
  for (i = 0; i <= m; i++)
    delete[] c[i];
  delete[] c;
  return r;
}

void imprime_LCS(int i, int j, char *x, char **b, string lcs) {
  if ((i == 0) || (j == 0)) {
    cout << lcs << endl;
    return;
  }

  if (b[i][j] == '\\') {
    lcs = string(1, x[i - 1]) + lcs;
    imprime_LCS(i - 1, j - 1, x, b, lcs);
  } else if (b[i][j] == '2') {
    imprime_LCS(i - 1, j, x, b, lcs);
    imprime_LCS(i, j - 1, x, b, lcs);
  } else if (b[i][j] == '-') {
    imprime_LCS(i, j - 1, x, b, lcs);
  } else {
    imprime_LCS(i - 1, j, x, b, lcs);
  }
}

void imprime_matriz(char *x, char *y, int m, int n, char **b) {
  int i, j;
  cout << "  " << y << endl << " ";
  for (j = 0; j <= n; j++)
    cout << " ";
  cout << endl;
  for (i = 1; i <= m; i++) {
    cout << x[i - 1] << " ";
    for (j = 1; j <= n; j++)
      cout << b[i][j];
    cout << endl;
  }
}

int main() {

  int m = 7;
  int n = 6;
  char *x = "ABCBDAB";
  char *y = "BDCABA";
  cout << "Entrada X = " << x << endl;
  cout << "Entrada Y = " << y << endl << endl;

  char **b = NULL;
  int time_start = getTick();
  cout << "Tamanho da LCS = " << LCS(x, y, m, n, b) << endl
       << endl
       << "Todas as LCS's possiveis:" << endl;
  int time_finish = getTick();

  string lcs;
  imprime_LCS(m, n, x, b, lcs);
  cout << endl;


  imprime_matriz(x, y, m, n, b);
  if (b != NULL) {
    for (int i = 0; i <= m; i++)
      delete[] b[i];
    delete[] b;
  }

  cout << endl << "Simbolo \\ (diagonal)" << endl;
  cout << "Simbolo | (para cima)" << endl;
  cout << "Simbolo - (para esquerda)" << endl;
  cout << "Simbolo 2 (para ambos: cima ou esquerda)" << endl << endl;

cout << "LCS " << (time_finish - time_start) << "miliseg" << endl;  
  return 0;
}