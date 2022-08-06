#include <climits>
#include <cmath>
#include <ctime>
#include <string>
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

int mochila(int* peso, int* valor, int N, int W, bool repet) {
    int i, w;
    if (repet)
    {
        int* V = new int[W+1];
        V[0] = 0;
        for (w=1; w<=W; w++) {
            V[w] = 0;
            for (i=0; i<N; i++) {
                if ((peso[i]<=w)&&(V[w]<V[w-peso[i]]+valor[i]))
                    V[w] = V[w-peso[i]] + valor[i];
            }
        }
        int r = V[W];
        delete[] V;
        return r;
    }
    else
    {
        int** V = new int*[N+1];
        for (i=0; i<=N; i++) V[i] = new int[W+1];
        for (w=0; w<=W; w++) V[0][w] = 0;

        for (i=1; i<=N; i++) {
            for (w=0; w<=W; w++) {
                V[i][w] = V[i-1][w];
                if ((peso[i-1]<=w) && (V[i][w] < V[i-1][w-peso[i-1]] + valor[i-1])) {
                    V[i][w] = V[i-1][w-peso[i-1]] + valor[i-1];
                }
            }
        }
        int r = V[N][W];
        for (i=0; i<=N; i++) delete[] V[i];
        delete[] V;
        return r;
    }
}

int main() {
  const int N = 5;
  int peso[N] = {1,1,2,4,12};
  int valor[N] = {1,2,2,10,4};
  // capacidade da mochila
  int W = 15; 

  int time_start = getTick();
  cout << "Valor Maximo com Repeticao: " << mochila(peso,valor,N,W,true) << endl;
  int time_finish = getTick();

  cout << "Mochila - com loop:  " << (time_finish - time_start) << "miliseg" << endl  <<  endl;
  
  cout << "Valor Maximo sem Repeticao: " << mochila(peso,valor,N,W,false) << endl;

  cout << "Mochila - sem loop:  " << (time_finish - time_start) << "miliseg" << endl;
  
  return 0;
}
