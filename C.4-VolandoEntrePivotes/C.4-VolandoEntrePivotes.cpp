
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

 N= numero total de pivotes
 S = numero de pivotes que puede saltarse el padre
    S = 0 --> No puede saltarse ninguno y Ana debe ir de uno en otro
    S = 1 --> Puede tanto saltar de uno al siguiente como saltarse uno 

Obtener cuantas formas distintas tiene el padre de Ana de hacerla volar entre N pivotes dado un S

Funcion recursiva:
pivotes(i) = num formas de hacer saltar desde el pivote i hasta el N

Caso recursivo:
pivotes(i) = 

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, S;
    cin >> N >> S;
    if (N==0 && L ==0)
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
