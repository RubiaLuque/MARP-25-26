/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class DFSValorado {
private:
    vector<bool> visit;

    void dfs(GrafoValorado<int> const& g, int v, int umbral) {
        visit[v] = true;
        for (auto a : g.ady(v)) {
            if (a.valor() >= umbral) { //La calle debe ser igual o mas grande que el camion
                int w = a.otro(v);
                if (!visit[w]) {
                    dfs(g, w, umbral);
                }
            }
        }
    }

public:
    DFSValorado(GrafoValorado<int> const& g, int v, int umbral) : visit(g.V(), false) {
        dfs(g, v, umbral);
    }

    bool visited(int v) const {
        return visit[v];
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int V, E;
    cin >> V >> E;
    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> g(V);

    int v, w, ancho;
    for (int i = 0; i < E; ++i) {
        cin >> v >> w >> ancho;
        g.ponArista({ v - 1, w - 1, ancho });
    }

    int K;
    int orig, dest, anchura;
    cin >> K;
    //O(K * (V + E))
    for (int i = 0; i < K; ++i) {
        cin >> orig >> dest >> anchura;
        DFSValorado d (g, orig - 1, anchura);
        if (d.visited(dest - 1)) cout << "SI\n";
        else cout << "NO\n";
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
