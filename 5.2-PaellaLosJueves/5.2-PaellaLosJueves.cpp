/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
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

class DFSDirigido {
private:
    int orig, dest;
    vector<bool> visit;
    Digrafo gInv;
    vector<bool> visitInv;

    void dfs(Digrafo const& g, int v) {
        visit[v] = true;
        for (auto w : g.ady(v)) {
            
            if (!visit[w]) {
                dfs(g, w);
            }
        }
    }

    void dfsInv(Digrafo const& g, int v) {
        visitInv[v] = true;
        for (auto w : g.ady(v)) {
            if (!visitInv[w])
                dfsInv(g, w);
        }
    }

public:
    DFSDirigido(Digrafo const& g, int orig, int dest) : visit(g.V(), false), orig(orig), dest(dest), gInv(g.inverso()), visitInv(gInv.V(), false) {
        //gInv = g.inverso(); //O(A+V)
        //Se hace DFS desde el origen para saber si el destino es alcanzable
        dfs(g, orig);
        dfsInv(gInv, dest);
    }

    //O(V) 
    //Si un vertice ha sido visitado tanto en el recorrido en el grafo original desde orig y en el recorrido en el grafo invertido
    // desde dest, entonces se cumple que:
    // - si hay camino dest -> v en grafo inverso ---> hay camino v -> dest en el grafo original
    int solucion() const {
        int total = 0;
        for (int i = 0; i < gInv.V(); ++i) {
            if (visit[i] && visitInv[i]) total++;
        }

        return total - 2; //inicio y destino no cuentan para la solucion
    }

    bool alcanzable(int v) const {
        return visit[v];
    }

    
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A;
    cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo dg(V);

    int v, w;
    for (int i = 0; i < A; ++i) {
        cin >> v >> w;
        dg.ponArista(v - 1, w - 1);
    }

    // resolver el caso posiblemente llamando a otras funciones
    int Q; 
    cin >> Q;
    int orig, dest;
    //O((V+A)*Q)
    for (int i = 0; i < Q; ++i) {
        cin >> orig >> dest;
        DFSDirigido dfs(dg, orig-1, dest-1); //O(V + A)
        //Si el vertice de destino no es alcanzable desde origen, entonces la respuesta es imposible
        if (!dfs.alcanzable(dest-1)) cout << "IMPOSIBLE\n";
        else {
            cout << dfs.solucion() << '\n';
        }
    }

    cout << "---\n";


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
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
