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

class MultiCamMinimo {
private:
    const int INF = INT32_MAX;
    int origen;
    vector<int> dist;
    vector<AristaDirigida<int>> ulti;
    IndexPQ<int> pq;

    //Se inicializa a 1 en la constructora porque se garanzita que hay, al menos, un camino minimo al ser 
    // el destino siempre un nodo alcanzable
    vector<int> numCams; //numero de caminos minimos

    void relajar(AristaDirigida<int> a) {
        int v = a.desde();
        int w = a.hasta();

        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            ulti[w] = a;
            pq.update(w, dist[w]);
            //Si el camino s-w es mas corto pasando por s-v-w entonces el numero de caminos minimos de w es igual al de v
            numCams[w] = numCams[v];
        }
        //Se llega por otro lado con el mismo coste? En caso afirmativo, se encuentra otro camino
        else if (dist[w] == dist[v] + a.valor()) {
            numCams[w] += numCams[v];
        }
    }

public:
    MultiCamMinimo(DigrafoValorado<int> const& g, int orig) : origen(orig), dist(g.V(), INF), ulti(g.V()), pq(g.V()), numCams(g.V()) {
        dist[origen] = 0; 
        pq.push(origen, 0);
        numCams[origen] = 1;
        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();

            for (auto a : g.ady(v)) {
                relajar(a);
            }
        }
    }

    int numCaminosTotal(int v) const {
        return numCams[v];
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, C; //num intersecciones (vertices), num calles (aristas)
    cin >> N >> C;

    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> g(N);
    int v, w, valor;
    for (int i = 0; i < C; ++i) {
        cin >> v >> w >> valor;
        g.ponArista({ v - 1, w - 1, valor });
        g.ponArista({ w - 1, v - 1, valor });
    }

    //Origen = 1
    //Destino = N
    
    MultiCamMinimo m(g, 0); //O(ClogN) donde C es el numero de aristas y N de vertices

    cout << m.numCaminosTotal(N-1) << '\n';


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
