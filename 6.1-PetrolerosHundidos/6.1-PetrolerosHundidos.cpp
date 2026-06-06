/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
using namespace std;

#include "ConjuntosDisjuntos.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Complejidad de O(F*C*lgN) donde F son las filas y C las columnas. 
 F*C es el numero total de elementos que tiene la particion y N el numero de adiciones de casillas con petroleo.

 O(F*C*lgN) ~= O(F*C) para valores de N pequeños

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const vector<pair<int, int>> dirs = { {1,0}, {0,1}, {-1,0}, {0,-1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1} };

bool dirCorrecta(int F, int C, int i, int j) {
    return (i >= 0 && i < F) && (j >= 0 && j < C);
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int F, C;
    cin >> F >> C;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<string> bitmap(F);

    for (string& linea : bitmap) {
        cin >> linea;
    }

    //Crear un objeto ConjuntoDisjunto al que se le añaden nuevos elementos cada vez y se comprueba el tamaño del mayor
    ConjuntosDisjuntos conj(F * C);
    int maxTam = 0;

    //Para la imagen inicial --> se crean los conjuntos disjuntos
    //O(F*C*dirs*lg(F*C)) --> O(F*C*lg(F*C)) ya que dirs es siempre 8
    for (int i = 0; i < F; ++i) {
        for (int j = 0; j < C; ++j) {

            if (bitmap[i][j] == '#') { //Es parte de una mancha
                for (auto d : dirs) { //Se comprueba en todas las direcciones
                    pair<int,int> dir = { i + d.first, j + d.second }; //Casilla a comprobar
                    //Evita que se salga del bitmap y comprueba que es una casilla mancha
                    if (dirCorrecta(F, C, dir.first, dir.second) && bitmap[dir.first][dir.second] == '#') {
                        conj.unir(i*C + j, dir.first * C + dir.second); //O(lg*N) ~= O(1)
                    }
                }

                //Por cada casilla de mancha que se encuentre se comprueba si su conjunto es el mayor
                if (conj.cardinal(i * C + j) > maxTam) //O(1)
                    maxTam = conj.cardinal(i * C + j);
                  
            }
        }
    }

    cout << maxTam << ' '; //Se escribe el tamaño de la mancha mas grande de la primera imagen
    int N, i, j; 
    cin >> N;

    //O(N*dirs*lgN) --> O(N*lgN) ya que dirs es siempre 8
    for (int n = 0; n < N; ++n) {
        cin >> i >> j;
        pair<int, int> m = { i - 1, j - 1 }; //Se resta 1 porque en el enunciado comienza desde 1 y no 0
        bitmap[m.first][m.second] = '#'; //Nueva casilla de petroleo

        //Se comprueban las casillas adyacentes para ver si puede formar parte de una mancha ya existente o no
        for (auto d : dirs) {
            pair<int, int> dir = { m.first + d.first, m.second + d.second }; //Posible otra casilla de petroleo ya existente
            if (dirCorrecta(F, C, dir.first, dir.second) && bitmap[dir.first][dir.second] == '#') {
                conj.unir(m.first * C + m.second, dir.first * C + dir.second); //O(lg*N) ~= O(1)
            }
        }

        //Se actualiza en maximo tamaño si procede
        if (conj.cardinal(m.first * C + m.second) > maxTam)
            maxTam = conj.cardinal(m.first * C + m.second);

        cout << maxTam << ' ';
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
