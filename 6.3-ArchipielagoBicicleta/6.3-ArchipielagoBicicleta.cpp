/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue> //Priority queue
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

/*@ <answer>

 1. Hacer ARM
 2. Comprobar num cjtos disjuntos: 
    - Si > 1 --> No hay suficientes puentes
    - ==1 --> Si hay suficientes, dar valor de ARM

Al hacer ARM se pasa de una particion unitaria a un unico conjunto si el grafo es conexo. Esto se deduce de que se van
uniendo todos los vertices a medida que se recorre el grafo al mismo conjunto que uno de los extremos de la arista que se 
esté procesando porque es necesario que dos extremos esten en conjuntos diferentes para evitar que existan bucles.
Así, se van reduciendo el numero de conjuntos hasta solo quedar 1 si es conexo.

Si no es conexo, hay tantos conjuntos disjuntos como componentes no conexas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class ARM_Kruskal {
private:
    vector<Arista<int>> _ARM;
    ConjuntosDisjuntos cjtos;
    int coste;


public:

    //O(AlogA)
    ARM_Kruskal(GrafoValorado<int> const& g) : cjtos(g.V()), coste(0) {
        PriorityQueue<Arista<int>> pq(g.aristas()); //Usar la del profesor porque la de std da error 

        while (!pq.empty()) {
            auto a = pq.top(); pq.pop(); //O(logA)
            int v = a.uno();
            int w = a.otro(v);

            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a);
                coste += a.valor();

                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }

    //O(1)
    bool grafoConexo() const {
        return cjtos.num_cjtos() == 1;
    }

    //O(1)
    int costeARM() const {
        return coste;
    }
    
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int I, P; //num islas, num puentes

    cin >> I >> P;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> g(I);

    int v, w, valor;
    for (int i = 0; i < P; ++i) {
        cin >> v >> w >> valor;
        g.ponArista({ v - 1, w - 1, valor });
    }

    // resolver el caso posiblemente llamando a otras funciones
    ARM_Kruskal arm(g); //O(PlogP) siendo P el numero de puentes (aristas) que tiene el grafo

    // escribir la solución
    if (!arm.grafoConexo()) cout << "No hay puentes suficientes\n";
    else cout << arm.costeARM() << '\n';

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
