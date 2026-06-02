/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

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
    int P; 
    cin >> P;
    if (!std::cin)  // fin de la entrada
        return false;

    //Traduce de str a int para que los nodos del grafo sean numericos
    map<string, int> idActores;
    map<string, vector<int>> peliculas; //Actores que participan en cada pelicula

    map<int, set<int>> grafo; // lista de adyancentes usando los id de los actores
    int id = 0;

    for (int i = 0; i < P; ++i) {
        string pelicula; int numActoresPelicula;
        cin >> pelicula >> numActoresPelicula;
        peliculas.insert({ pelicula, {} }); //Cada pelicula se inserta con un vector vacio
        for (int j = 0; j < numActoresPelicula; ++j) {
            string nombreActor;
            cin >> nombreActor;
            idActores.insert({ nombreActor, id });
            peliculas[pelicula].push_back(id);

            id++;
        }
    }


    //Se crea un grafo del tamaño del numero de actores totales



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
