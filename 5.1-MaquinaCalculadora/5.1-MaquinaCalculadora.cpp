/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
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

const int MAX = 10000; //maximo dado por el problema 
const int INF = INT32_MAX;

//Devuelve los 3 adyacentes posibles
int adyacente(int v, int i) {
    switch (i) {
    case 0: return (v + 1) % MAX;
    case 1: return (v * 2) % MAX;
    case 2: return (v / 3); //No se hace %MAX en este caso porque nunca va a ser mayor que MAX al tratarse de una division
    }
}

//Devuelve la distancia entre origen y destino
int bfs(int orig, int dest) {
    if (orig == dest) return 0; 

    vector<int> dist(MAX, INF); //dist[v] --> distancia entre orig y v
    dist[orig] = 0; //origen tiene una distancia a si mismo de 0

    queue<int> q; 
    q.push(orig);

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = 0; i < 3; ++i) { //Sabemos que para cada nodo hay 3 adyacentes 
            int ady = adyacente(v, i);
            if (dist[ady] == INF) { //Si se cumple es que no ha sido visitado antes
                dist[ady] = dist[v] + 1;
                if (ady == dest) {
                    return dist[ady];
                }
                else {
                    q.push(ady);
                }

            }
        }

    }
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int orig, dest;
    cin >> orig >> dest;
    if (!std::cin)  // fin de la entrada
        return false;

    //Grafo implicito que se crea mientras se recorre.
    // En este caso no es necesario siquiera crear una estructura usando la clase Digrafo
    
    //O(V + A)
    int d = bfs(orig, dest);
    cout << d << '\n';



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
