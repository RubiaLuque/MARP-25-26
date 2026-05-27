
/*@ <authors>
 *
 * MARP57 Muxu Rubia
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue> //Para usar las colas de prioridad
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

int64_t esfuerzoSumar(priority_queue<int64_t, vector<int64_t>, greater<int64_t>>& cola_min, int n) {
    if (n == 1) return 0; //Si solo hay un numero el coste es 0 porque no tiene que sumar nada

    int64_t esfuerzo = 0;

    //Coste total O(NlogN)
    while (cola_min.size() > 1) { // Lo que queda en el ultimo elemento de la cola es el resultado final de la suma
        int64_t a = cola_min.top(); //O(1)
        cola_min.pop(); //O(1)
        int64_t b = cola_min.top();
        cola_min.pop();

        esfuerzo += a + b;
        cola_min.push(a+b); //O(logN)
    }

    return esfuerzo;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N; 
    cin >> N;
    if (N==0)
        return false;
    priority_queue<int64_t, vector<int64_t>, greater<int64_t>> cola_min;

    //Coste total de este bucle O(N logN)
    for (int i = 0; i < N; ++i) { //O(N)
        int64_t num;
        cin >> num;
        cola_min.push(num); //O(log N)
    }
    // resolver el caso posiblemente llamando a otras funciones
    int64_t esfuerzoTotal = esfuerzoSumar(cola_min, N);
    // escribir la solución
    cout << esfuerzoTotal << endl;

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
