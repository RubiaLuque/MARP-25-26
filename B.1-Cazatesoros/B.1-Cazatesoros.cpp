/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 T: capacidad total 
 N: num cofres

 Tiempo descenso a una profundidad p = p
 Tiempo ascenso desde profundidad p = 2*p

 Para cada cofre, necesita 3*p del total del tanque (T) si esta a profundidad p

 Problemas: 
 - max valor
 - num cofres para conseguir max valor
 - profundidad y valor para cada uno de esos cofres

 Hay que reconstruir la solucion 

 Caso recursivo:
 tanque(i,j) = 

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Cofre {
    int profundidad; 
    int oro;
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int T, N; //capacidad tanque oxigeno, num cofres totales 
    cin >> T; 
    if (!std::cin)  // fin de la entrada
        return false;

    // resolver el caso posiblemente llamando a otras funciones

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
