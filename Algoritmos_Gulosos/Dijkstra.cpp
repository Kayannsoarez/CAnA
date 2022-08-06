#include <cfloat>
#include <climits>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>
#include <stack>
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

  double custo;
  int pai;
  bool ok;
} vertice;

typedef struct wdigraph {
  int N; // numero de vertices
  int M; // numero de arestas
  vertice *V;
} wdigraph;

int wdigraph_create(wdigraph &G, string arquivo) {
  aresta A;
  ifstream arq;
  arq.open(arquivo.c_str());
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

void dijkstra(wdigraph &G, int s) {
  list<aresta>::iterator it;
  if (G.N <= 0)
    return;
  for (int x = 0; x < G.N; x++) {
    G.V[x].custo = DBL_MAX;
    G.V[x].pai = s;
    G.V[x].ok = false;
  }
  G.V[s].custo = 0;

  for (int j = 1; j <= G.N; j++) {
    int u;
    double custo_min = DBL_MAX;
    for (int x = 0; x < G.N; x++) {
      if ((!G.V[x].ok) && (custo_min >= G.V[x].custo)) {
        custo_min = G.V[x].custo;
        u = x;
      }
    }
    G.V[u].ok = true;
    for (it = G.V[u].AdjL.begin(); it != G.V[u].AdjL.end(); ++it) {
      int v = (*it).viz;
      double peso = (*it).peso;
      if ((!G.V[v].ok) && (G.V[v].custo > peso + G.V[u].custo)) {
        G.V[v].custo = peso + G.V[u].custo;
        G.V[v].pai = u;
      }
    }
  }

  for (int x = 0; x < G.N; x++) {
    cout << "dist[" << s << "][" << x << "]=" << G.V[x].custo
         << " / Pai=" << G.V[x].pai << endl;
  }
}

int main() {
  wdigraph G;

  cout << "\n---------------------------------------------";
  cout << "\n---------------- DIJKSTRA -------------------";
  cout << "\n---------------------------------------------\n";
  if (!wdigraph_create(G, "entrada_dijkstra_adjL.txt")) {
    cout << "Arquivo inexistente\n";
    return -1;
  }

  unsigned int time_start = getTick();
  dijkstra(G, 0);
  unsigned int time_finish = getTick();

  cout << "\nDijkstra - Tempo: " << (time_finish - time_start) << "miliseg"
       << endl;

  wdigraph_delete(G);

  return 0;
}
