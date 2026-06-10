/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <cstdint>
using namespace std;

#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Laberinto {
private:
    const int INF = INT32_MAX;
    vector<int> dist;
    int origen;
    vector<AristaDirigida<int>> ulti;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde();
        int w = a.hasta();

        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }

public:
    Laberinto(DigrafoValorado<int> const& g, int orig) : dist(g.V(), INF), ulti(g.V()), origen(orig), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);

        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();

            for (auto a : g.ady(v)) {
                relajar(a);
            }
        }
    }

    int distancia(int v) const {
        return dist[v];
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    /*
    N --> num celdas (vertices)
    S --> celda de salida 
    T --> tiempo limite
    P --> num pasadizos (aristas)
    */

    int N, S, T, P; 
    cin >> N >> S >> T >> P;
    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> g(N);

    int v, w, valor;
    for (int i = 0; i < P; ++i) {
        cin >> v >> w >> valor;
        g.ponArista({ v - 1, w - 1, valor });
    }

    //Creamos un grafo inverso de g para establecer la salida como el punto de partida y que se transforme en un problema
    // de origen unico

    DigrafoValorado<int> gi = g.inverso(); //O(N + P)

    Laberinto lab(gi, S-1); //O(PlogN)

    int numRatones = 0;
    //O(P)
    for (int i = 0; i < N; ++i) {
        if (lab.distancia(i) <= T) numRatones++;
    }

    cout << numRatones - 1 << '\n';
    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
