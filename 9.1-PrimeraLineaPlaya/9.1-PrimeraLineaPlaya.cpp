/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <deque>
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

struct Edificio {
    int64_t ini, fin;

    bool dentroLimitesEdificio(int n) {
        return n >= ini && n < fin;
    }
};

int tuneles(deque<Edificio>& edificios) {
    int numTuneles = 1;

    Edificio actual = edificios.front();
    edificios.pop_front();

    while (!edificios.empty()) {
        Edificio nuevo = edificios.front();
        edificios.pop_front();

        //Mantener un pasadizo en todos aquellos que de algun modo solapen con el edificio actual
        //Cuando un edificio deje de solapar, se crea un nuevo pasadizo y se actualiza el edificio actual
        if (nuevo.ini >= actual.fin) {
            actual = nuevo;
            numTuneles++;
        }

    }
    return numTuneles;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N; 
    cin >> N;
    if (N==0)  // fin de la entrada
        return false;

    deque<Edificio> edificios(N);

    int w, e;
    for (int i = 0; i < N; ++i) {
        cin >> w >> e;
        edificios[i] = { w, e };
    }

    //O(NlogN)
    sort(edificios.begin(), edificios.end(), [](Edificio a, Edificio b) {
        return a.fin < b.fin || (a.fin == b.fin && a.ini < b.ini); 
        });

    //O(N)
    int nTuneles = tuneles(edificios);
    // escribir la solución
    cout << nTuneles << '\n';
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
