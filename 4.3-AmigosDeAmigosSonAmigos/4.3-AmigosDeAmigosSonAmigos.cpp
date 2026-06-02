/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
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
class MaxComponenteConexa {
private:
    vector<bool> visit;
    int max; //Tamaño maximo de componente conexa

    //O(N+M)
    int dfs(Grafo const& g, int v) {
        visit[v] = true;
        int tam = 1;
        for (int w : g.ady(v)) {
            if (!visit[w]) { //Si w no estaba visitado es que es un nuevo vertice
                tam += dfs(g, w);
            }
        }

        return tam;
    }

public:
    
    MaxComponenteConexa(Grafo const& g) : visit(g.V(), false), max(0) {
        //O(N+M)
        for (int v = 0; v < g.V(); ++v) { //Se recorren todos lo vertices 
            if (!visit[v]) { //Si un vertice no esta ya visitado se trata de una nueva componente conexa
                int tam = dfs(g, v);
                if (tam > max) max = tam;
            }
        }
    }

    int maxTam() const {
        return max;
    }
};

void resuelveCaso() {

    // leer los datos de la entrada
    int N, M;
    cin >> N >> M;

    Grafo g(N); 
    int v, w;

    //O(M)
    for (int i = 0; i < M; ++i) {
        cin >> v >> w;
        g.ponArista(v - 1, w - 1); //No se lee directamente con cin porque los vertices empiezan en 1 y no en 0
    }

    // resolver el caso posiblemente llamando a otras funciones
    MaxComponenteConexa grupoMax(g);

    // escribir la solución
    cout << grupoMax.maxTam() << '\n';
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

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
