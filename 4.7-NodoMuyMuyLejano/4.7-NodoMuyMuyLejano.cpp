/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
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
    vector<bool> visit;
    vector<int> dist; //dist[v] --> distancia entre el origen y v
    int _nodosAcanzables; //Numero de vertices visitados partiendo de s y teniendo el cuenta ttl
    int s;

    //O(V + A)
    void bfs(Grafo const& g, int s, int ttl) {
        queue<int> q;
        _nodosAcanzables = 1; //Comienza en 1 porque el propio nodo de consulta cuenta como alcanzable
        dist[s] = 0;
        visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto w : g.ady(v)) {
                //Debe comprobarse que la distancia entre el origen y el nodo es menor que ttl
                // y es un menor estricto porque dentro del if se suma 1 la distancia de w
                if (!visit[w] && dist[v] < ttl) {
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    q.push(w);
                    _nodosAcanzables++;
                    
                }
            }
        }

        
    }

public:
    CaminoMasCorto(Grafo const& g, int s, int ttl) : visit(g.V(), false), dist(g.V(), 0), s(s), _nodosAcanzables(1) {
        bfs(g, s, ttl);
    }

    int nodosAlcanzables() const {
        return _nodosAcanzables;
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, C;
    cin >> N >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    Grafo red = Grafo(N);

    int v, w;
    for (int i = 0; i < C; ++i) {
        cin >> v >> w;
        red.ponArista(v - 1, w - 1);
    }

    // resolver el caso posiblemente llamando a otras funciones
    int K, origen, ttl;
    int noVisitados;
    cin >> K;
    //O(K*(N + C))
    for (int i = 0; i < K; ++i) {
        cin >> origen >> ttl;
        CaminoMasCorto cam = CaminoMasCorto(red, origen - 1, ttl);
        noVisitados = red.V() - cam.nodosAlcanzables();
        cout << noVisitados << '\n';
    }
    cout << "---\n";

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
