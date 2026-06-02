/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <queue>
#include <cstdint>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminoMasCorto {
private:
    vector<bool> visit; //visit[v] --> ¿hay camino de s a v?
    //vector<int> ant; //ant[v] --> ultimo vertice antes de v
    vector<int> dist; //dist[v] --> num aristas entre s y v en camino mas corto
    int s; //origen

    //O(V + A)
    //Se modifica el bfs para añadirle un argumento mas que indica el origen desde el que queremos partir
    // de esta forma no es 0 por defecto
    void bfs(Grafo const& g, int s) {
        queue<int> q;
        dist[s] = 0; 
        visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto w : g.ady(v)) {
                if (!visit[w]) {
                    //ant[w] = v;
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    q.push(w);

                }
            }
        }
    }

public:
    CaminoMasCorto(Grafo const& g, int s) : visit(g.V(), false), dist(g.V(), 0), s(s) {
        bfs(g, s);
    }

    //Distancia desde el origen a v
    int distancia(int v) const {
        return dist[v];
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, C, alex, lucas, trabajo;
    //N --> num intersecciones = num vertices
    //C --> num calles = num aristas
    cin >> N >> C >> alex >> lucas >> trabajo;
    if (!std::cin)  // fin de la entrada
        return false;

    Grafo ciudad = Grafo(N);
    int v, w;
    //O(C)
    for (int i = 0; i < C; ++i) {
        cin >> v >> w;
        ciudad.ponArista(v - 1, w - 1);
    }

    //Se les resta 1 a sus interseccioens para que concuerden con los numeros de 0 a N-1 
    // ya que la entrada es de 1 a N
    alex-=1; lucas-=1; trabajo-=1;

    // resolver el caso posiblemente llamando a otras funciones
    //Dos posibles situaciones:
    // 1. Pueden partir por separado y juntarse por el camino
    // 2. Pueden ir por separado hasta el trabajo

    //O(N + C) siendo N el numero de vertices y C de aristas
    CaminoMasCorto camAlex = CaminoMasCorto(ciudad, alex);
    CaminoMasCorto camLucas = CaminoMasCorto(ciudad, lucas);
    CaminoMasCorto camTrabajo = CaminoMasCorto(ciudad, trabajo);

    int distAlex, distLucas, distTrabajo;

    int menosCostoso = INT32_MAX;

    //O(N) siendo N el numero de vertices
    //Se comprueba que interseccion es la menos costosa para juntarse
    // Se triangula la interseccion mas cercana (menos costosa) entre alex, lucas y el trabajo
    for (int i = 0; i < ciudad.V(); ++i) {
        distAlex = camAlex.distancia(i);
        distLucas = camLucas.distancia(i);
        distTrabajo = camTrabajo.distancia(i);

        int distTotal = distAlex + distLucas + distTrabajo;
        menosCostoso = std::min(menosCostoso, distTotal);
    }

    // escribir la solución
    cout << menosCostoso << '\n';

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
