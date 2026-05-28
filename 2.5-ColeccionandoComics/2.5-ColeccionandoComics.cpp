/*@ <authors>
 *
 * MARP57
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <cstdint>
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

struct elemento {
    int64_t id;
    int pila;
};

bool operator>(elemento const& a, elemento const& b) {
    return a.id > b.id;
}

bool resuelveCaso() {

    // leer los datos de la entrada

    int N;
    cin >> N; //numero de pilas

    if (!std::cin)  // fin de la entrada
        return false;

    vector<vector<int64_t>> pilas(N);

    //O(K*N)
    for (int i = 0; i < N; ++i) { //O(N)
        int K; cin >> K;
        for (int j = 0; j < K; ++j) { //O(K)
            int64_t id; cin >> id;
            pilas[i].push_back(id); //O(1)
        }
    }

    priority_queue<elemento, vector<elemento>, greater<elemento>> pq;

    //Se guarda la cima de cada pila en una cola de prioridad de minimos
    //O(N logN)
    for (int i = 0; i < N; ++i) {
        pq.push({ pilas[i].back(), i }); //O(logN)
    }

    int64_t min_global = INT64_MAX;
    int pos_min_global = 0;
    int turno = 0;

    //O(K * log N)
    while (!pq.empty()) {
        turno++;
        auto min = pq.top(); //Menor elemento de entre las cimas de los montones
        pq.pop(); //O(logN)

        pilas[min.pila].pop_back(); //Se elimina de su pila

        //Si esa pila no esta vacia, se coloca su nueva cima en la cola de prioridad
        if (!pilas[min.pila].empty()) {
            pq.push({ pilas[min.pila].back(), min.pila }); //O(logN)
        }

        //Se comprueba si es el minimo global
        if (min.id < min_global) {
            min_global = min.id;
            pos_min_global = turno;
        }
    }
    
    // escribir la solución
    cout << pos_min_global << '\n';

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
