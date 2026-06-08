
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

class Djkstra {
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
    Djkstra(DigrafoValorado<int> const& g, int orig) : dist(g.V(), INF), origen(orig), ulti(g.V()), pq(g.V()) {
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

    bool hayCamino(int v) const {
        return dist[v] != INF;
    }

    int distancia(int v) const {
        return dist[v];
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N; //num paginas web (vertices)
    cin >> N;
    if (N==0)
        return false;

    vector<int> tCarga(N);
    int t; 
    for (int i = 0; i < N; ++i) {
        cin >> t; 
        tCarga[i] = t;
    }

    DigrafoValorado<int> g(N);

    int M; //num enlaces (aristas)
    cin >> M;
    int v, w, valor;
    for (int i = 0; i < M; ++i) {
        cin >> v >> w >> valor;
        //Al valor de la arista (t enlace) se le suma el tCarga propio de la web de destino
        g.ponArista({ v - 1, w - 1, valor + tCarga[w-1]});
    }

    //Importante siempre añadir el tiempo del vertice de origen al tiempo total dado por djkstra para los casos 
    // en los que N es alcanzable

    Djkstra dj(g, 0); //O(MlogN)

    // escribir la solución
    if (!dj.hayCamino(N - 1)) cout << "IMPOSIBLE\n";
    else {
        cout << tCarga[0] + dj.distancia(N - 1) << '\n';
    }


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
