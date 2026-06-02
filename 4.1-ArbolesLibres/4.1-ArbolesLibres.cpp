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

class ArbolLibre {
    //Para que sea arbol libre debe ser aciclico y conexo
    // Conexo: que todos los vertices esten visitados
    // Aciclico: que haya camino entre todos los vertices --> si es conexo, debe haber V-1 aristas
private:
    vector<bool> visit; //Hay camino entre s y v?
    Grafo grafo;

    //O(A+V)
    void dfs(Grafo const& g, int v) {
        visit[v] = true;
        for (int w : g.ady(v)) {
            if(!visit[w])
                dfs(g, w);
        }
    }

    //O(V)
    bool esConexo() {
        for (int i = 0; i < visit.size(); ++i) {
            if (!visit[i]) return false;
        }

        return true;
    }

public:
    ArbolLibre(Grafo const& g): visit(g.V(), false), grafo(g) {
        dfs(g, 0);
    }

    bool esArbolLibre() {
        //Si es conexo y cumple que num aristas es num vertices - 1, es un arbol libre
        return esConexo() && (grafo.A() == grafo.V()-1);
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    Grafo g = Grafo(std::cin);

    if (!std::cin)  // fin de la entrada
        return false;


    // resolver el caso posiblemente llamando a otras funciones
    ArbolLibre l = ArbolLibre(g);
    // escribir la solución
    if (l.esArbolLibre()) cout << "SI\n";
    else cout << "NO\n";

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
