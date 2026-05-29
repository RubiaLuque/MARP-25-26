/*@ <authors>
 *
 * MARP57
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

//Para que haya una reparticion mejor, se debe tener en cuenta el grupo original de cada instrumento
//En mayor subgrupo es aquel que resulte de hacer musicos/partituras para un instrumento. Como el num de partituras
// puede ser mayor que 2, hay que tener en cuenta el resto, que NO se suma
// Importante: se busca conseguir la parte entera de la division por arriba, por eso se suma 1 si hay resto
struct instrumento {
    int n_musicos;
    int n_partituras;
};

// cuando b es mas prioritario
/* Se considera prioridad en base a :
* --> Subgrupo mas grande
*/
bool operator<(instrumento a, instrumento b) {
    // se suma 1 si hay resto. En una suma, true suma 1, tal y como esta escrito en la segunda parte de la operacion

    //Se calcula el tamaño del grupo mas grande posible para cada instrumento, pero no importa cómo se gestionen los otros
    // grupos mientras sean mas pequeños
    //Los instrumentos se ordenan en la cola basandose unicamente en el tamaño de su subgrupo mas grande
    int max_grupo_a = a.n_musicos / a.n_partituras;
    if (a.n_musicos % a.n_partituras > 0) max_grupo_a++;
    int max_grupo_b = b.n_musicos / b.n_partituras;
    if (b.n_musicos % b.n_partituras > 0) max_grupo_b++;
    return max_grupo_b > max_grupo_a;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int partituras, n_instrumentos;
    cin >> partituras >> n_instrumentos;

    if (!std::cin)  // fin de la entrada
        return false;

    priority_queue<instrumento> cola; //Cola de maximos

    int n_musicos;
    //O(n_instrumentos * log n_instrumentos)
    for (int i = 0; i < n_instrumentos; ++i) {
        cin >> n_musicos;
        cola.push({ n_musicos, 1 }); //Una partitura por cada instrumento
    }

    partituras -= n_instrumentos; //Partituras restantes disponibles

    //O(partituras * log n_instrumentos)
    while (partituras--) {
        auto inst = cola.top();
        cola.pop();
        inst.n_partituras++;
        cola.push(inst);
    }

    auto inst = cola.top();

    int max_grupo = inst.n_musicos / inst.n_partituras;
    if (inst.n_musicos % inst.n_partituras > 0) max_grupo++;
    cout << max_grupo << '\n';

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
