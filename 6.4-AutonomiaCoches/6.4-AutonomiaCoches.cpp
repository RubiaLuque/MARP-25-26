/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

/*@ <answer>

- Caso 1: grafo conexo con V > 1 --> arista mayor de ARM
- Caso 2: grafo conexo con V == 1 --> 0
- Caso 3: grafo no conexo --> Imposible

Coste en tiempo en caso peor de O(AlogA) siendo A el numero de aristas y O(A) en espacio adicional

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class AutonomiaCoches {
private:
    vector<Arista<int>> _ARM;
    ConjuntosDisjuntos cjtos;

public:

    AutonomiaCoches(GrafoValorado<int> const& g) : _ARM(g.V()), cjtos(g.V()) {
        PriorityQueue<Arista<int>> pq(g.aristas());

        while (!pq.empty()) {
            auto a = pq.top(); 
            pq.pop(); 
            int v = a.uno(); 
            int w = a.otro(v);

            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a);

                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }

    bool esConexo() const {
        return cjtos.num_cjtos() == 1;
    }

    int maxAristaARM() const {
        return _ARM.back().valor();
    }

};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M; //num cuidades (vertices), num carreteras (aristas)
    cin >> N >> M;
    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> g(N);
    int v, w, valor;
    for (int i = 0; i < M; ++i) {
        cin >> v >> w >> valor;
        g.ponArista({ v - 1, w - 1, valor });
    }

    if (g.V() == 1) cout << 0 << '\n'; //Caso especial
    else {
        AutonomiaCoches autonomia(g);
        if (!autonomia.esConexo()) cout << "Imposible\n";
        else {
            cout << autonomia.maxAristaARM() << '\n';
        }
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
