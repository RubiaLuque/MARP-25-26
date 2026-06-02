/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
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

class Manchas {
private:
    int F, C; //Filas y columnas de la matriz
    vector<vector<bool>> visit; //Matriz de visitados
    int maxTam; //Tamaño mayor componente conexa
    int numComps; //numero componentes conexas

    vector<pair<int, int>> dirs = { {1,0}, {0,1}, {-1,0}, {0,-1} }; //Direcciones

    int dfs(vector<string> const& m, int i, int j) {
        visit[i][j] = true; //Se marca la casilla como visitada
        int tam = 1;
        for (auto d : dirs) {
            int dir_i = i + d.first;
            int dir_j = j + d.second;
            //Debe cumplir que:
            // - Este contenida dentro de la matriz
            // - Sea una mancha (#)
            // - No haya sido visitada antes
            if (dirCorrecta(dir_i, dir_j) && m[dir_i][dir_j] == '#' && !visit[dir_i][dir_j]) {
                tam += dfs(m, dir_i, dir_j);
            }
        }

        return tam;
    }

    //Comprueba si la direccion [i][j] esta contenida dentro de la matriz
    bool dirCorrecta(int i, int j) const {
        return (i >= 0 && i < F) && (j >= 0 && j < C);
    }

public:
    Manchas(vector<string> const& m) : F(m.size()), C(m[0].size()), visit(F, vector<bool>(C, false)), maxTam(0), numComps(0) {

        for (int i = 0; i < F; ++i) {
            for (int j = 0; j < C; ++j) {
                if (!visit[i][j] && m[i][j] == '#') { //Nueva componente conexa
                    numComps++;
                    int tam = dfs(m, i, j);
                    if (tam > maxTam) maxTam = tam;
                }
            }
        }
    }

    int maximo() const {
        return maxTam;
    }

    int numComponentes() const {
        return numComps;
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int F, C;
    cin >> F >> C;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<string> bitmap(F);

    for (string& linea : bitmap)
        cin >> linea;

    // resolver el caso posiblemente llamando a otras funciones
    Manchas manchas(bitmap);

    // escribir la solución
    cout << manchas.numComponentes() << ' ' << manchas.maximo() << '\n';
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
