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

Cada conjunto disjunto tiene como minimo un aeropuerto. Se maximiza el nivel de aeropuertos de forma que si construir una
carretera es igual o mas costoso que un aeropuerto se elige el segundo. 

Al final, el coste total es el coste de las carreteras mas el coste de aeropuerto por numero de aeropuertos. Dentro del 
coste de las carreteras se incluye el coste de un aeropuerto si se cumple lo mencionado anteriormente. Este coste no se 
corresponde con el valor del ARM. 

Usando ARM se minimiza el coste total de la construccion de carreteras, a lo que se le añade la posibilidad de no construir
una carretera si es igual o mas costosa que un aeropuerto. 

 Coste total en tiempo de O(AlogA) y en espacio adicional de O(A) siendo A el num aristas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


class Aeropuertos {
private:
    vector<Arista<int>> _ARM;
    ConjuntosDisjuntos cjtos;
    int costeMin;
    int numAeros;
    int costeAero;

public:
    Aeropuertos(GrafoValorado<int> const& g, int costeAero) : cjtos(g.V()), costeMin(0), numAeros(0), costeAero(costeAero) {
        PriorityQueue<Arista<int>> pq(g.aristas());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno();
            int w = a.otro(v);

            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a);

                if (a.valor() >= costeAero) { //Se maximiza el numero de aeropuertos
                    numAeros++;
                    //costeMin += costeAero;
                }
                else {
                    costeMin += a.valor();
                }

                if (_ARM.size() == g.V() - 1) break;
            }
        }

    }

    int numAeropuertos() const {
        //Cada conjunto disjunto tiene como minimo un aeropuerto
        return numAeros + cjtos.num_cjtos();
    }

    int costeMinTotal() const {
        return costeMin + numAeropuertos() * costeAero;
    }
};


bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M, A; //num localidades, num carreteras, coste aeropuerto
    cin >> N >> M >> A;
    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> g(N);

    int v, w, valor;
    for (int i = 0; i < M; ++i) {
        cin >> v >> w >> valor;
        g.ponArista({ v - 1, w - 1, valor });
    }


    if (N == 1) { //Caso especial donde solo hay una localidad sin carreteras
        cout << A << ' ' << 1 << '\n';
    }
    else {
        // resolver el caso posiblemente llamando a otras funciones
        Aeropuertos aero(g, A);
        // escribir la solución
        cout << aero.costeMinTotal() << ' ' << aero.numAeropuertos() << '\n';
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
