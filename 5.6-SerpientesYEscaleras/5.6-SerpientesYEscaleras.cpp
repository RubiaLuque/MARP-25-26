
/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
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

class Juego {
private:
    const int INF = INT32_MAX;
    vector<int> dist;
    int destino; //Ultima casilla del tablero
    int minMovs;

    int bfs(vector<int> tablero, int dado) {
        queue<int> q;

        //Siempre se empieza desde la primera casilla
        dist[0] = 0;
        q.push(0);

        while (!q.empty()) {
            int actual = q.front(); 
            q.pop();

            //Caso base: llegamos a destino
            if (actual == destino) {
                return dist[destino]; //El menor numero de movs es la distancia (saltos) recorrida
            }

            //los adyacentes son ahora las posibles casillas donde caiga el dado
            for (int i = 1; i <= dado; ++i) { 
                int next = actual + i; //Casilla siguiente o adyacente
                
                //Se rompe el bucle si para un valor i de dado la casilla siguiente se sale del bucle ya que se cumplira 
                // tambien para todos los valores de i mayores del valor de i actual
                if (next > destino) break;

                //Se comprueba si estamos en una serpiente o escalera
                if (tablero[next] != -1) {
                    next = tablero[next]; //Se sube/baja por la serpiente/escalera cambiando el valor de next
                }

                //Casilla no visitada
                if (dist[next] == INF) {
                    dist[next] = dist[actual] + 1;
                    q.push(next);
                }
                    
                
            }
        }

        return dist[destino];
    }

public:
    Juego(vector<int> const& tablero, int dado) : dist(tablero.size(), INF), destino(tablero.size()-1) {
        minMovs = bfs(tablero, dado);
    }

    int getMinMovs() const {
        return minMovs;
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, K, S, E;
    cin >> N >> K >> S >> E;
    if (N == 0 && K == 0 && S == 0 && E == 0)
        return false;

    int casillasTotales = N * N;

    //Se rellena con -1 todo el vector
    vector<int> tablero(casillasTotales, -1);

    int orig, dest;
    //Los destinos distintos a -1 son una serpiente o una escalera
    for (int i = 0; i < (S + E); ++i) {
        cin >> orig >> dest;
        tablero[orig - 1] = dest - 1; //Se resta 1 para que respete que el vector empieza en 0 y el tablero en 1
    }

    // resolver el caso posiblemente llamando a otras funciones
    Juego j(tablero, K); //O(casillasTotales + S + E)
    // escribir la solución
    cout << j.getMinMovs() << '\n';

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
