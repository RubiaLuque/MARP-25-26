
/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "IndexPQ.h"

using namespace std;


/*@ <answer>

 Coste de O(NlogN) por la ordenacion del vector de conferencias y el bucle for donde se usa una cola de prioridad
 con insercion y delecion en coste O(logN) que se hace N veces. 

 Coste total en tiempo de O(NlogN) y O(N) en espacio adicional por la cola de prioridad y el vector cNumSala.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Conferencia {
    int64_t ini, fin, numSala;
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N; //num conferencias
    cin >> N;
    if (N==0)
        return false;

    vector<Conferencia> c(N); //vector conferencias
    vector<int64_t> cNumSala(N); //vector con el numero de sala que corresponde a cada conferencia

    int64_t ini, fin; //[ini, fin)
    for (int i = 0; i < N; ++i) {
        cin >> ini >> fin;
        c[i] = { ini, fin, i }; //Se guardan los indices de las conferencias segun el orden de entrada en su numero de sala
        // ya que este solo se procesara una sola vez. De esta forma no hay que crear una variable extra dentro del struct
        // Este indice sirve para posicionar la sala dentro del vector cNumSala segun el orden de entrada
    }

    //O(NlogN)
    std::sort(c.begin(), c.end(), [](Conferencia a, Conferencia b) {
        return a.ini < b.ini || (a.ini == b.ini && a.fin<b.fin);
        });


    //pair = {fin, nº sala} --> se ordena de menor a mayor hora de finalizacion de una sala
    // asi la primera es siempre la que acaba antes y sabemos que si no se puede cuadrar una conferencia en esa sala entonces 
    // tampoco puede hacerse en las sucesivas
    priority_queue<pair<int64_t, int64_t>, vector<pair<int64_t, int64_t>>, greater<pair<int64_t, int64_t>>> salas;

    int64_t numSalas = 0; 
    //O(NlogN)
    for (const auto& conf : c) {

        //Se comprueba que la cola de prioridad no este vacia y que la sala que acaba mas tarde pueda cuadrar la conferencia actual
        if (!salas.empty() && salas.top().first <= conf.ini) {
            auto s = salas.top();
            salas.pop(); //O(logN)
            cNumSala[conf.numSala] = s.second;
            salas.push({ conf.fin, s.second }); //O(logN) --> Se vuelve a añadir a la cola con una nueva hora de finalizacion
        }
        //La cola esta vacia o no se puede posicionar la conferencia actual en la primera sala, que es la que antes tiene hueco
        else {
            numSalas++;
            salas.push({ conf.fin, numSalas }); //Comienza numerando las salas desde 1
            cNumSala[conf.numSala] = numSalas;
        }
    }

    cout << numSalas << '\n';

    for (int i = 0; i < N; ++i) {
        cout << cNumSala[i] << ' ';
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
