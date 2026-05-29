/*@ <authors>
 *
 * MARP86 Nombre Apellidos
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

struct tarea {
    int64_t t_ini;
    int64_t t_fin;
    int64_t intervalo; //Si es 0 es que se trata de una tarea unica
    bool periodica;
};

//Las tareas se ordenan segun su tiempo de inicio de menor a mayor
//Se resuelve para b mas prioritario que a 
bool operator<(tarea const& a, tarea const& b) {
    return b.t_ini < a.t_ini;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M;
    int64_t T;
    cin >> N >> M >> T;
    if (!std::cin)  // fin de la entrada
        return false;

    priority_queue<tarea> cola;
    int ini, fin, intervalo;

    //Tareas unicas
    for (int i = 0; i < N; ++i) {
        cin >> ini >> fin;
        cola.push({ ini, fin, 0, false });
    }

    //Tareas periodicas
    for (int i = 0; i < M; ++i) {
        cin >> ini >> fin >> intervalo;
        cola.push({ ini, fin, intervalo, true });
    }

    bool conflicto = false; 
    int ocupado = 0; //Nos dice en cada momento si hay una tarea activa y hasta cuando lo esta

    while (!conflicto && !cola.empty() && cola.top().t_ini < T) {
        auto t = cola.top();
        cola.pop();
        //Se hace antes de definir ocupado para que no de conflicto una tarea consigo misma
        if (t.t_ini < ocupado)
            conflicto = true;
        ocupado = t.t_fin; //Esta ocupado hasta el final de la tarea
        if (t.periodica) {
            cola.push({ t.t_ini + t.intervalo, t.t_fin + t.intervalo, t.intervalo, true });
        }
    }

    if (conflicto)
        cout << "SI\n";
    else
        cout << "NO\n";


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
