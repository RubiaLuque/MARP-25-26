
/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

Objetivo: minimizar el coste de unir N documentos de 2 en 2. El coste de unir dos documentos es la suma de sus longitudes


Definicion de la funcion recursiva:
coste(i,j) = {coste minimo de unir los documentos desde el i hasta el j,
              longitud del documento generado}
La funcion recursiva tiene dos valores porque hay que llevar la cuenta de los tamaños de los documentos generados en pasos
intermedios para no añadir complejidad al problema teniendo que hacer un recorrido sumando sus longitudes cada vez

Casos recursivos: (i<j)
coste(i,j) = { a, b }
            a = min {coste(i,k).first + coste(k+1, j).first} + b
                i<=k<j 
            b = li + coste(i+1, j).second
a: minimo coste en todas las formas posibles de unir 2 documentos entre i y j incluidos. En a, b se suma fuera del minimo
porque en el intervalo i..j las longitudes de cada documento son las mismas sin importar por donde se empiecen a juntar
b: tamaño del documento generado que se obtiene sumando los tamaños desde li a lj. Eso se hace guardando los valores 
ya calculados desde i+1 a j y sumandole el valor de i.

 Entonces es como llevar dos tablas superpuestas a la vez en la que se guarda el coste minimo de unir i..j y la longitud del 
 documento resultante.

 Casos base:
 coste(i,i) = {0, li} --> No hay coste de unir un solo documento y la longitud es la de si mismo

 Llamada inicial:
 coste(1, N) --> la llamada inicial hace que se recorra desde el primer documento hasta el ultimo

 Se usa una matriz de N*N que se rellena por diagonales desde la principal hacia arriba. 

 Coste total en tiempo de O(N^3) porque para cada intervalo i..j se recorren todos los posibles k tal que i<=k<j.
 Coste O(N*N) en espacio adicional.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const int INF = INT32_MAX;

int minCoste(vector<vector<pair<int, int>>>& coste, int N) {

    //Recorrido por diagonales desde la que esta por encima de la ppal
    for (int d = 1; d < N; ++d) {
        for (int i = 0; i < N - d; ++i) {
            int j = i + d;
            
            int val = INF;
            for (int k = i; k < j; ++k) { //i<=k<j
                val = min(val, coste[i][k].first + coste[k + 1][j].first);
            }
            coste[i][j].second = coste[i][i].second + coste[i + 1][j].second;
            coste[i][j].first = val + coste[i][j].second;
        }
    }

    return coste[0][N - 1].first;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N; //num documentos
    cin >> N;
    if (N==0)
        return false;

    vector<vector<pair<int, int>>> coste(N, vector<pair<int,int>>(N));
    //Caso base: diagonal principal
    for (int i = 0; i < N; ++i) {
        coste[i][i].first = 0;
        cin >> coste[i][i].second; 
    }

    cout << minCoste(coste, N) << '\n';
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

