
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

struct paciente {
    string nombre;
    int gravedad;
    int tiempoEspera;
};

bool operator<(paciente const& a, paciente const& b) {
    return a.gravedad < b.gravedad || (a.gravedad == b.gravedad && a.tiempoEspera > b.tiempoEspera);
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int n; //num eventos
    cin >> n;
    if (n==0)
        return false;

    priority_queue<paciente> cola;
    char tipoEvento;
    int turno = 0;

    for (int i = 0; i < n; ++i) {
        cin >> tipoEvento;
        if (tipoEvento == 'I') {
            string nombre; 
            int gravedad;
            cin >> nombre >> gravedad;
            cola.push({ nombre, gravedad, turno }); //logN
            turno++;
        }
        else if (tipoEvento == 'A') {
            auto pacienteAcc = cola.top();
            cola.pop(); //logN
            cout << pacienteAcc.nombre << '\n';
        }
        
    }

    cout << "---\n";

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
