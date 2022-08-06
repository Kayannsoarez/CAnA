#include <cfloat>
#include <climits>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
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

typedef struct aresta {
  int viz;
  double peso;
} aresta;

typedef struct vertice {
  int grau;
  list<aresta> AdjL;
} vertice;

typedef struct wdigraph {
  int N; // numero de vertices
  int M; // numero de arestas
  vertice *V;
} wdigraph;

int wdigraph_create(wdigraph &G) {
  aresta A;
  ifstream arq;
  arq.open("entrada_floyd_adjL.txt");
  if (arq.fail())
    return 0;
  arq >> G.N;
  G.M = 0;
  G.V = NULL;
  G.V = new vertice[G.N];

  for (int x = 0; x < G.N; x++) {
    int grau;
    arq >> grau;
    G.V[x].grau = grau;
    G.M += grau;
    for (int k = 0; k < grau; k++) {
      int viz;
      double peso;
      arq >> viz >> peso;
      A.viz = viz;
      A.peso = peso;
      G.V[x].AdjL.push_back(A);
    }
  }
  arq.close();
  return 1;
}

void wdigraph_delete(wdigraph &G) {
  delete[] G.V;
  G.V = NULL;
}

void imprime_matriz(double **d, int m, int n) {
  int i, j;
  cout << "\n\n";
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      if (d[i][j] < DBL_MAX)
        cout << d[i][j] << "      ";
      else
        cout << "inf      ";
    }
    cout << "\n";
  }
}

void MenorCaminho_rec(int **pi, int i, int j) {
  if (pi[i][j] == -1) {
    cout << j;
    return;
  }
  MenorCaminho_rec(pi, i, pi[i][j]);
  cout << " ";
  MenorCaminho_rec(pi, pi[i][j], j);
}

void MenorCaminho(int **pi, int i, int j) {
  cout << i << " ";
  MenorCaminho_rec(pi, i, j);
}

void floyd(wdigraph &G, double **dist, int **pi) {
  list<aresta>::iterator it;
  int i, j, k;
  int N = G.N;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      dist[i][j] = DBL_MAX;
      pi[i][j] = -1;
    }
    dist[i][i] = 0;
  }
  for (i = 0; i < N; i++) {
    for (it = G.V[i].AdjL.begin(); it != G.V[i].AdjL.end(); ++it) {
      j = (*it).viz;
      dist[i][j] = (*it).peso;
    }
  }
  for (k = 0; k < N; k++) {
    imprime_matriz(dist, N, N);
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        if (dist[i][j] > dist[i][k] + dist[k][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          pi[i][j] = k;
        }
      }
    }
  }
}

int main() {
  int i, j, k;

  wdigraph G;
  if (!wdigraph_create(G)) {
    cout << "Arquivo inexistente\n";
    return -1;
  }

  int N = G.N;
  double **dist = new double *[N];
  int **pi = new int *[N];
  for (i = 0; i < N; i++) {
    dist[i] = new double[N];
    pi[i] = new int[N];
  }

  // ALGORITMO DE FLOYD
  unsigned int time_start = getTick();
  floyd(G, dist, pi);
  unsigned int time_finish = getTick();

  cout << "\n-----------------------------------------\n";
  cout << "----- Matriz Final de Distancias --------\n";
  cout << "-----------------------------------------\n";
  imprime_matriz(dist, N, N);
  cout << "\n\n";

  cout << "\n------------------------------------------------\n";
  cout << " Todos os Menores Caminhos entre dois vertices \n";
  cout << "------------------------------------------------\n";
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (i == j)
        continue;
      cout << "\n";
      MenorCaminho(pi, i, j);
    }
  }
  cout << "\n\n";

  cout << "\nFloyd-Warshall - Tempo: " << (time_finish - time_start) << "miliseg" << endl;

  for (i = 0; i < N; i++) {
    delete[] dist[i];
    delete[] pi[i];
  }
  delete[] dist;
  delete[] pi;

  wdigraph_delete(G);

  return 0;
}
