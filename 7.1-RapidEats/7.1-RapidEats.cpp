/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
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
    int origen;
    vector<int> dist;
    vector<AristaDirigida<int>> ulti;
    IndexPQ<int> pq; //cola de prioridad variable de vertices con prioridad distancia a origen

    void relajar(AristaDirigida<int> a) {
        int v = a.desde();
        int w = a.hasta();

        //La distancia que ya habia a w es mayor a la distancia del nuevo camino atravesando v, se cambia el camino minimo de w para que corresponda
        // con el que pasa por v al ser menor
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
            ulti[w] = a;
        }
    }

public:
    //O(AlogV)
    Djkstra(DigrafoValorado<int> const& g, int orig) : origen(orig), dist(g.V(), INF), ulti(g.V()), pq(g.V()) {

        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop(); //O(logV)

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

    deque<AristaDirigida<int>> camino(int v) const {
        deque<AristaDirigida<int>> cam;

        //Se retrocede para recuperar el camino
        AristaDirigida<int> a;

        for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()]) {
            cam.push_front(a);
        }
        cam.push_front(a);

        return cam;
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, C; //num vertices, num calles
    std::cin >> N >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> g(N);
    int v, w, valor;

    for (int i = 0; i < C; ++i) {
        std::cin >> v >> w >> valor;
        //todas las calles son de doble sentido
        g.ponArista({ v - 1, w - 1, valor });
        g.ponArista({ w - 1, v - 1, valor });
    }

    int K, orig, dest;
    std::cin >> K;
    //O(K*AlogV) siendo K el numero de pedidos, A numero de aristas y V numero de vertices que tiene el grafo g
    for (int i = 0; i < K; ++i) {
        std::cin >> orig >> dest;
        Djkstra dj(g, orig - 1);
        if (!dj.hayCamino(dest - 1)) cout << "NO LLEGA\n";
        else {
            cout << dj.distancia(dest - 1) << ": ";
            deque<AristaDirigida<int>> d = dj.camino(dest - 1);

            while (!d.empty()) {
                cout << d.front().desde() + 1 << " -> ";
                d.pop_front();
            }

            cout << dest << '\n';
        }
    }

    cout << "---\n";
    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución

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
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
