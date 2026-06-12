
/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Intervalo {
    int64_t ini, fin; //[ini, fin)
};

int64_t minTrabajos(vector<Intervalo> const& trabajos, int64_t C, int64_t F) {
    if (trabajos.size() == 0) return -1; //Devolver -1 significa que es imposible
    Intervalo zonaCubierta = { C, C }; //La zona que tenemos cubierta inicialmente es un intervalo vacio

    int64_t finMejorIntervalo = C; //dentro de la zona cubierta, hasta donde se buscan intervalos mejores

    int64_t numTrabajos = 1;

    for (int i = 0; i < trabajos.size(); ++i) {
        Intervalo nuevo = trabajos[i];

        if (nuevo.ini > finMejorIntervalo) {
            if (nuevo.ini <= zonaCubierta.fin && nuevo.fin > zonaCubierta.fin) {
                numTrabajos++;
                finMejorIntervalo = zonaCubierta.fin;
            }
            else if (nuevo.ini > zonaCubierta.fin) {
                return -1;
            }
        }

        if (nuevo.ini <= finMejorIntervalo) {
            if (nuevo.fin > zonaCubierta.fin) {
                zonaCubierta.fin = nuevo.fin;

                if (zonaCubierta.fin >= F) {
                    break; //Ya esta todo cubierto
                }
            }
        }
    }

    return numTrabajos;


}

bool resuelveCaso() {

    // leer los datos de la entrada
    int64_t C, F, N; //[C, F) y num trabajos
    cin >> C >> F >> N;
    if (C==0 && F==0 && N==0)
        return false;

    //El objetivo es cubrir todo el intervalo [C, F) con trabajos encadenados y que estos sean los minimos posibles
    vector<Intervalo> trabajos(N);

    int64_t c, f;
    for (int i = 0; i < N; ++i) {
        cin >> c >> f;
        trabajos[i] = { c, f };
    }

    std::sort(trabajos.begin(), trabajos.end(), [](Intervalo a, Intervalo b) {
        return a.ini < b.ini;
        });


    int64_t numTrabajos = minTrabajos(trabajos, C, F);

    if (numTrabajos == -1) cout << "Imposible\n";
    else cout << numTrabajos << '\n';

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
