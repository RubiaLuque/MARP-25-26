
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

struct caja {
    int id; //Numero de la caja
    int tiempo; //Tiempo de espera
};

bool operator<(caja const& a, caja const& b) {
    return b.tiempo < a.tiempo || (b.tiempo == a.tiempo && b.id < a.id);
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, C;
    cin >> N >> C;
    if (N==0 && C == 0)
        return false;

    priority_queue<caja> cajas;
    
    for (int i = 1; i <= N; ++i) { //O(N*logN)
        //Todas las cajas comienzan con tiempo de espera 0
        cajas.push({ i, 0 }); //O(log(N))
    }

    for (int i = 0; i < C; ++i) { //O(C*logN)
        int t_C;
        cin >> t_C;

        auto caja = cajas.top(); 
        cajas.pop(); //O(logN)
        caja.tiempo += t_C;
        cajas.push(caja); //O(logN)
    }

    auto cajaIsmael = cajas.top();
    cout << cajaIsmael.id << '\n';

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
