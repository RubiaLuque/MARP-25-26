/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

//Debe detectarse si existen ciclos. En caso afirmativo no se pueden realizar las tareas.
// Si no hay ciclos, se debe dar una ordenacion topologica

class OrdenTopologico {
private:
    vector<bool> visit;
    deque<int> _orden; //ordenacion topologica
    vector<bool> apilado;
    bool _hayCiclo;

    //O(V + A)
    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;

        visit[v] = true;

        for (auto w : g.ady(v)) {

            if (!visit[w]) {
                visit[w] = true; apilado[w] = true;
                dfs(g, w);
            }
            else if (apilado[w]) { // hay un ciclo
                _hayCiclo = true;
                return;
            }
        }

         apilado[v] = false;
         _orden.push_front(v); 
        
    }

public:
    //O(V + A) porque cada vertice se visita una sola vez
    OrdenTopologico(Digrafo const& g) : visit(g.V(), false), apilado(g.V(), false), _hayCiclo(false) {

        for (int v = 0; v < g.V() && !_hayCiclo; ++v) {
            if (!visit[v]) {
                dfs(g, v);
            }
        }
    }

    bool hayCiclo() const {
        return _hayCiclo;
    }

    const deque<int>& orden() const {
        return _orden;
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int numTareas, A;
    cin >> numTareas >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo g(numTareas);

    int v, w;
    for (int i = 0; i < A; ++i) {
        cin >> v >> w;
        g.ponArista(v - 1, w - 1);
    }

    // resolver el caso posiblemente llamando a otras funciones
    OrdenTopologico o(g);
    
    // escribir la solución
    if (o.hayCiclo()) cout << "Imposible\n";
    else {
        deque<int> orden = o.orden();
        for (auto i : orden) {
            cout << i + 1 << ' '; //Se suma 1 porque las tareas empiezan en 1 y no en 0 como en el grafo
        }
        cout << '\n';
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
