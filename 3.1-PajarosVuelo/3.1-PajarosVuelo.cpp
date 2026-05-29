
/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
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

bool resuelveCaso() {

    // leer los datos de la entrada
    int64_t edadPrimero; 
    int numParejas;
    cin >> edadPrimero >> numParejas;
    if (edadPrimero == 0 && numParejas == 0)
        return false;

    //Dos colas de prioridad, una para cada lado de la bandada
    //El primero no esta en ninguna de las dos colas
    priority_queue<int64_t> jovenes; //Cola maximos
    priority_queue < int64_t, vector<int64_t>, greater<int64_t>> viejos; //Cola minimos

    //O(numParejas * log numParejas)
    for (int i = 0; i < numParejas; ++i) {
        int64_t paj1, paj2;
        cin >> paj1 >> paj2;

        if (paj1 > edadPrimero) {
            viejos.push(paj1);
        }
        else if (paj1 < edadPrimero) {
            jovenes.push(paj1);
        }

        if (paj2 > edadPrimero) {
            viejos.push(paj2);
        }
        else if (paj2 < edadPrimero) {
            jovenes.push(paj2);
        }

        //Los dos de la pareja son mas jovenes que el primero
        if (jovenes.size() > viejos.size()) {
            viejos.push(edadPrimero);
            edadPrimero = jovenes.top();
            jovenes.pop();
        }
        //Los dos de la pareja son mas viejos que el primero
        else if (jovenes.size() < viejos.size()) {
            jovenes.push(edadPrimero);
            edadPrimero = viejos.top();
            viejos.pop();
        }

        //Si la pareja son uno mas joven y otro mas viejo que el primero, no se hace nada

        cout << edadPrimero << " ";
    }
    
    cout << '\n';

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
