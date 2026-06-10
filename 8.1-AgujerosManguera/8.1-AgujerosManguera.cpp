/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


/*@ <answer>

 Minimizar numero de parches de L longitud teniendo N agujeros en una manguera.

 Vector de 0 a N-1 donde cada casilla guarde la posicion del agujero i

 Estrategia voraz: no poner parche si no es necesario

 Tiene un coste lineal O(N) donde se recorre el vector de agujeros ordenados de menor a mayor basado en su posicion

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int numParches(vector<int64_t> const& posAgujero, int L) {
    //Se comienza poniendo un parche
    int parches = 1;
    int distParche = posAgujero[0] + L; //El primero agujero esta a distancia 0 del primer parche porque lo pone sobre él

    for (int i = 1; i < posAgujero.size(); ++i) {
        //No sigue dentro de la distancia que cubre el parche
        if(posAgujero[i] > distParche) {
            parches++; //Se pone un nuevo parche
            distParche = posAgujero[i] + L; //Se actualiza lo que cubre ahora el parche desde la posicion de i 
        }
    }

    return parches;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, L; //num agujeros, longitud parches
    cin >> N >> L;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<int64_t> posAgujeros(N);

    int pos;
    for (int i = 0; i < N; ++i) {
        cin >> pos;
        posAgujeros[i] = pos;
    }

    // resolver el caso posiblemente llamando a otras funciones
    int sol = numParches(posAgujeros, L);

    // escribir la solución
    cout << sol << '\n';
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
