/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

/*

Hay que en cuenta que solamente se puede avanzar de arriba a abajo y de iz. a derecha segun las condiciones del problema para no dar 
pasos de mas. En este caso, la funcion sol(i,j) nos dice cuantas formas hay de llegar a la casilla i,j. 
Para ello hay que tener en cuenta las casillas superior e izquierda, es decir: sol(i-1, j) y sol(i, j-1)

Funcion: sol(i,j)
    - sol(i,j) != X --> sol(i,j) = sol(i-1, j) + sol(i, j-1)
    - sol(i,j) == X --> sol(i,j) = 0 porque no hay forma de llegar hasta aqui

Casos especiales:
    - sol(0,j) --> Borde izquierdo --> sol(0,j) = sol(0, j-1)
    - sol(i,0) --> Borde superior --> sol(i,0) = sol(i-1, 0)

Caso base:
sol(0,0) = 1 porque solo hay un camino al origen, que es ya estar ahi

Coste total en tiempo y en espacio de O(N*M) donde N es el numero de filas y M de columnas.

*/

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M; //num calles este-oeste, num calles norte-sur
    cin >> N >> M;
    if (!std::cin)  // fin de la entrada
        return false;
    
    //Se rellena una matriz que representa la cuidad y cada casilla es una interseccion
    //Como se busca llegar al extremo inferior derecho (N-1, M-1) el tamaño de la matriz es de N*M
    vector<string> ciudad(N);
    for (string& l : ciudad) {
        cin >> l;
    }

    Matriz<int64_t> sol(N, M, 0);
    
    //Caso base
    sol[0][0] = 1;

    //Borde izquierdo
    for (int i = 1; i < N; ++i) {
        if (ciudad[i][0] != 'X') sol[i][0] = sol[i - 1][0];
    }

    //Borde superior
    for (int j = 1; j < M; ++j) {
        if (ciudad[0][j] != 'X') sol[0][j] = sol[0][j - 1];
    }

    //Recursion
    for (int i = 1; i < N; ++i) {
        for (int j = 1; j < M; ++j) {
            if (ciudad[i][j] != 'X') sol[i][j] = sol[i - 1][j] + sol[i][j - 1];
        }
    }

    cout << sol[N - 1][M - 1] << '\n';

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
