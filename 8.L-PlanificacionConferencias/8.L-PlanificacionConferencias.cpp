
/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <algorithm>
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

struct Conferencia {
    int id; //se corresponde con su posicion en el vector cID
    int64_t ini, fin, numSala;
};
//O(N) 
int organizar(deque<Conferencia>& c, vector<Conferencia>& cId, unordered_map<int64_t, vector<Conferencia>>& salas, int N) {
    int numSalas = 1; //Si hay al menos una conferencia debe haber una sala
    //Guardar la sala con menor hora de finalizacion. Asi sabremos que si una nueva conferencia no entra en esta sala, hay que crear una nueva
    int64_t salaMenorFin = 0; //Al comienzo la sala que antes tiene la finalizacion es la 0

    //Primera conferencia se añade a la primera sala
    Conferencia actual = c.front();
    c.pop_front();
    actual.numSala = 0;
    salas[0].push_back(actual);

    //Se añade en que sala esta en el vector de IDs
    cId[actual.id].numSala = 0;

    for (int i = 1; i < N; ++i) {
        Conferencia nueva = c.front();
        c.pop_front();

        //Si la nueva conferencia se puede insertar tras la actual, se hace
        if (nueva.ini >= actual.fin) {
            nueva.numSala = actual.numSala;
            salas[actual.numSala].push_back(nueva);
            if (salas[salaMenorFin].back().fin > salas[actual.numSala].back().fin) {
                salaMenorFin = actual.numSala;
            }
            actual = nueva;
        }
        //Si no se puede hacer lo anterior, se comprueba si se puede insertar en la sala de menor hora de finalizacion
        else {

            if (salas[salaMenorFin].back().fin <= nueva.ini) {
                nueva.numSala = salaMenorFin;
                salas[salaMenorFin].push_back(nueva);
                if (salas[actual.numSala].back().fin < salas[salaMenorFin].back().fin) {
                    salaMenorFin = actual.numSala; //Al haber insertado una conferencia en la sala con menor hora de finalizacion
                    // esta deja de serlo asi que la nueva sala con menor hora de finalizacion pasa a ser la de la actual

                }
                actual = nueva; //Se actualiza la actual con la nueva
            }
            //Si no se ha podido colocar en la sala con menor hora de finalizacion, se crea una nueva sala 
            //En este caso la sala con menor hora de finalizacion no cambia
            else {
                nueva.numSala = salas.size();
                salas[salas.size()].push_back(nueva);
                actual = nueva;
                numSalas++;
            }
        }

        //Se añade en que sala esta en el vector de IDs
        cId[actual.id].numSala = actual.numSala;
    }

    return numSalas;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N; //num conferencias
    cin >> N;
    if (N==0)
        return false;

    deque<Conferencia> c(N);
    vector<Conferencia> cId(N); //vector con el orden de entrada

    int64_t ini, fin; //[ini, fin)
    for (int i = 0; i < N; ++i) {
        cin >> ini >> fin;
        c[i] = { i,ini, fin, -1 }; //Sala -1 indica que no esta aun organizada
        cId[i] = { i,ini, fin, -1 };
    }

    //O(NlogN) se ordena solamente la cola doble
    std::sort(c.begin(), c.end(), [](Conferencia a, Conferencia b) {
        return a.fin < b.fin || (a.fin == b.fin && a.ini<b.ini);
        });

    unordered_map<int64_t, vector<Conferencia>> salas;

    int numSalas = organizar(c, cId, salas, N);
    cout << numSalas << '\n';

    for (int i = 0; i < N; ++i) {
        cout << cId[i].numSala + 1 << ' ';
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
