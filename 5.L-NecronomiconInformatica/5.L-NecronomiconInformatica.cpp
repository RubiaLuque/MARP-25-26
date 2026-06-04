/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
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

struct instruccion {
    char tipo;
    int salto; //-1 para instrucciones de tipo A
};

class Necronomicon {
private:

public:
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int L; 
    cin >> L;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<instruccion> code(L + 1); //Se añade 1 porque se busca llegar despues de la ultima instruccion
    char t; 
    int salto;
    for (int i = 0; i < L; ++i) {
        cin >> t;

        code[i].tipo = t;

        if (t == 'A') {
            code[i].salto = -1;
        }
        else {
            cin >> salto;
            code[i].salto = salto;
        }
    }

    //Se rellena el nodo final diferente 
    code[L].tipo = 'D';
    code[L].salto = -1;

    // resolver el caso posiblemente llamando a otras funciones

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
