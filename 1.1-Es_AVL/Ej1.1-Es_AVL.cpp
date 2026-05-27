/*@ <authors>
 *
 * MARP57 Muxu Rubia
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "bintree.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename T>
struct sol {
    bool isAVL;
    int altura;
    T min, max;
};

template <typename T>
sol<T> esAVL(BinTree<T> const& tree) {
    //Caso base
    if (tree.empty()) {
        return { true, 0, T(), T() }; //T() es un constructor de template por defecto
    }

    //Casos recursion
    // izda
    sol<T> iz = esAVL(tree.left());
    // dcha
    sol<T> dr = esAVL(tree.right());

    int altura = max(iz.altura, dr.altura) + 1; //+1 porque se cuenta el nodo actual

    T menor;
    if (tree.left().empty()) menor = tree.root();
    else menor = iz.min;

    T mayor;
    if (tree.right().empty()) mayor = tree.root();
    else mayor = dr.max;

    bool ordenado = (tree.left().empty() || iz.max < tree.root()) &&
        (tree.right().empty() || dr.min > tree.root());

    bool es_avl = ordenado && (std::abs(iz.altura - dr.altura) < 2) && iz.isAVL && dr.isAVL;

    return { es_avl, altura, menor, mayor };

}

bool resuelveCaso() {

    // leer los datos de la entrada
    string dataType;
	cin >> dataType;

    if (!std::cin)  // fin de la entrada
        return false;

    if (dataType == "N") {
        BinTree<int> tree = read_tree<int>(std::cin);
        sol<int> sol = esAVL<int>(tree);

        if (sol.isAVL) cout << "SI\n";
        else cout << "NO\n";
    }
    else if (dataType == "P") {
        BinTree<string> tree = read_tree<string>(std::cin);
        sol<string> sol = esAVL<string>(tree);

        if (sol.isAVL) cout << "SI\n";
        else cout << "NO\n";
    }

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
