#include <climits>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
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

void imprime_matriz(string X, string Y, char **R) {
  int i, j;
  int m = X.size();
  int n = Y.size();

  cout << "  " << Y << endl << " ";
  for (j = 0; j <= n; j++)
    cout << " ";
  cout << endl;
  for (i = 1; i <= m; i++) {
    cout << X[i - 1] << " ";
    for (j = 1; j <= n; j++)
      cout << R[i][j];
    cout << endl;
  }
}

void imprime_matriz(string X, string Y, int **R) {
  int i, j;
  int m = X.size();
  int n = Y.size();

  cout << "   " << Y << endl << "  ";
  for (j = 0; j <= n; j++)
    cout << R[0][j];
  cout << endl;
  for (i = 1; i <= m; i++) {
    cout << X[i - 1] << " ";
    for (j = 0; j <= n; j++)
      cout << R[i][j];
    cout << endl;
  }
}

int EditDistance(string X, string Y, char **&R) {
  int i, j;
  int m = X.size();
  int n = Y.size();
  int **Ed = new int *[m + 1];
  for (int i = 0; i <= m; i++)
    Ed[i] = new int[n + 1];
  if (R == NULL) {
    R = new char *[m + 1];
    for (int i = 0; i <= m; i++)
      R[i] = new char[n + 1];
  }

  for (j = 0; j <= n; j++) {
    Ed[0][j] = j;
    R[0][j] = '2';
  }
  for (i = 0; i <= m; i++) {
    Ed[i][0] = i;
    R[i][0] = '3';
  }

  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      int dif = 1;
      if (X[i - 1] == Y[j - 1])
        dif = 0;
      int a = Ed[i - 1][j - 1] + dif;
      int b = Ed[i][j - 1] + 1;
      int c = Ed[i - 1][j] + 1;
      if ((a < b) && (a < c)) {
        Ed[i][j] = a;
        R[i][j] = '1';
      } else if ((b < a) && (b < c)) {
        Ed[i][j] = b;
        R[i][j] = '2';
      } else if ((c < a) && (c < b)) {
        Ed[i][j] = c;
        R[i][j] = '3';
      } else if ((a == b) && (a < c)) {
        Ed[i][j] = a;
        R[i][j] = '4';
      } else if ((a == c) && (a < b)) {
        Ed[i][j] = a;
        R[i][j] = '5';
      } else if ((b == c) && (b < a)) {
        Ed[i][j] = b;
        R[i][j] = '6';
      } else { // if ((a==b)&&(b==c)) {
        Ed[i][j] = a;
        R[i][j] = '7';
      }
    }
  }

  int edit = Ed[m][n];
  cout << endl
       << "-------------------------------------------------------" << endl;
  cout << "Matriz de Distancias de Edicao:" << endl << endl;
  imprime_matriz(X, Y, Ed);

  for (i = 0; i <= m; i++)
    delete[] Ed[i];
  delete[] Ed;
  return edit;
}

void imprime_edit_op(int i, int j, char **R, string X, string Y, string op1,
                     string op2) {
  if ((i == 0) && (j == 0)) {
    cout << op1 << endl;
    cout << op2 << endl << endl;
    return;
  }
  if (R[i][j] == '1') {
    imprime_edit_op(i - 1, j - 1, R, X, Y, string(1, X[i - 1]) + op1,
                    string(1, Y[j - 1]) + op2);
    return;
  } else if (R[i][j] == '2') {
    imprime_edit_op(i, j - 1, R, X, Y, "_" + op1, string(1, Y[j - 1]) + op2);
    return;
  } else if (R[i][j] == '3') {
    imprime_edit_op(i - 1, j, R, X, Y, string(1, X[i - 1]) + op1, "_" + op2);
    return;
  } else if (R[i][j] == '4') {
    imprime_edit_op(i - 1, j - 1, R, X, Y, string(1, X[i - 1]) + op1,
                    string(1, Y[j - 1]) + op2);
    imprime_edit_op(i, j - 1, R, X, Y, "_" + op1, string(1, Y[j - 1]) + op2);
    return;
  } else if (R[i][j] == '5') {
    imprime_edit_op(i - 1, j - 1, R, X, Y, string(1, X[i - 1]) + op1,
                    string(1, Y[j - 1]) + op2);
    imprime_edit_op(i - 1, j, R, X, Y, string(1, X[i - 1]) + op1, "_" + op2);
    return;
  } else if (R[i][j] == '6') {
    imprime_edit_op(i, j - 1, R, X, Y, "_" + op1, string(1, Y[j - 1]) + op2);
    imprime_edit_op(i - 1, j, R, X, Y, string(1, X[i - 1]) + op1, "_" + op2);
    return;
  } else if (R[i][j] == '7') {
    imprime_edit_op(i - 1, j - 1, R, X, Y, string(1, X[i - 1]) + op1,
                    string(1, Y[j - 1]) + op2);
    imprime_edit_op(i, j - 1, R, X, Y, "_" + op1, string(1, Y[j - 1]) + op2);
    imprime_edit_op(i - 1, j, R, X, Y, string(1, X[i - 1]) + op1, "_" + op2);
    return;
  }
}

int main() {
  unsigned int t1, t2;

  // string X = "SNOWY";
  // string Y = "SUNNY";
  string X = "ALGORITMO";
  string Y = "SALGADO";
  int m = X.size();
  int n = Y.size();

  cout << endl
       << "-------------------------------------------------------" << endl;
  cout << "Entrada X = " << X << endl;
  cout << "Entrada Y = " << Y << endl << endl;

  char **R = NULL;
  int time_start = getTick();
  cout << "Edit Distance = " << EditDistance(X, Y, R) << endl << endl;
  int time_finish = getTick();
  cout << endl
       << "-------------------------------------------------------" << endl;
  cout << "Todas as Solucoes Otimas:" << endl << endl;
  string op1, op2;
  imprime_edit_op(m, n, R, X, Y, op1, op2);

  cout << endl
       << "-------------------------------------------------------" << endl;
  cout << "Matriz de Operacoes de Edicao:" << endl << endl;
  imprime_matriz(X, Y, R);

  cout << endl << endl;
  cout << "LEGENDA:" << endl;
  cout << "1 (diagonal == substituir)" << endl;
  cout << "2 (pra esquerda == inserir)" << endl;
  cout << "3 (pra cima == remover)" << endl;
  cout << "4 (1 ou 2)" << endl;
  cout << "5 (1 ou 3)" << endl;
  cout << "6 (2 ou 3)" << endl;
  cout << "7 (1 ou 2 ou 3)" << endl;
  cout << endl
       << "-------------------------------------------------------" << endl;
  cout << endl;
  
  cout << "Distância de Edição " << (time_finish - time_start) << "miliseg" << endl;  
  
  if (R != NULL) {
    for (int i = 0; i <= m; i++)
      delete[] R[i];
    delete[] R;
  }
  return 0;
}
