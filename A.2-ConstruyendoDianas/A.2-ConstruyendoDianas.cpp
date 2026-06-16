/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h" 

/*@ <answer>

 V: valor total que se quiere conseguir sumar
 S: numero de secciones de la diana

 i: seccion que se esta comprobando en ese momento
 j: valor parcial

 s_i: valor de la seccion i

 Funcion recursiva: dardos(i,j)
    - s_i > j --> dardos(i-1, j): no se coge la seccion i al tener un valor mayor que el parcial
    - s_i <= j --> min(dardos(i-1, j), dardos(i, j-s_i) + 1):
        Se elige la mejor opcion entre no elegir esa seccion y sí elegirla. En cuyo caso alcanzar j sera sumarle al numero minimo de dardos
        que hacen falta para j-s_i uno más. En este caso, al poder elegir una seccion mas de una vez se coge mira en la fila i.

Casos base:
 - dardos(i,0) = 0 No hacen falta mas secciones ni dardos para sumar un valor 0.
 - dardos(0,j) = Inf No quedan secciones por mirar pero aun queda distancia asi que no hay solucion

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

//Coste total en tiempo O(V*S) y en espacio adicional O(V*S)
//Se podria reducir el espacio adicional a O(V) ya que para construir i no necesitamos mas que i-1, pero 
// no es lo habitual si queremos reconstruir la solucion. Aunque también podría hacerse
vector<int> minDardos(vector<int> const& secciones, int V) {
    int N = secciones.size();
    Matriz<EntInf> dardos(N + 1, V + 1, EntInf::_intInf);

    dardos[0][0] = 0; //Caso base
    //Se recorre de izquierda a derecha y de arriba a abajo
    for (int i = 1; i <= N; ++i) {
        dardos[i][0] = 0;
        for (int j = 1; j <= V; ++j) {
            if (secciones[i - 1] > j) //No se coge la seccion
                dardos[i][j] = dardos[i - 1][j];

            else
                dardos[i][j] = std::min(dardos[i - 1][j], dardos[i][j - secciones[i - 1]] + 1);
        }
    }

    vector<int> sol;
    if (dardos[N][V] != EntInf::_intInf) { //Hay solucion
        cout << dardos[N][V] << ": ";
        int i = N; 
        int j = V;
        while (j > 0) { //Mientras no se haya llegado al valor que se quiere
            //Se ha cogido la seccion i si se cumple que:
            // - s_i es menor o igual a j
            // - el numero minimo es diferente al de i-1 para el mismo j porque si el valor fuera el mismo, esto indica que ya
            //      se podia obtener ese minimo sin necesidad de pasar por i. Esta misma comprobacion se puede hacer de forma que 
            //      se mire si dardos(i,j) > dardos(i, j-s_i) ya que se cumple si se ha sumado 1 a la segunda parte de la expresion
            //      y eso indica que sí se ha cogido i al venir de un valor previo de i para un j-s_i
            if (secciones[i - 1] <= j && dardos[i][j] != dardos[i - 1][j]) {
                sol.push_back(secciones[i - 1]); //Se añade al vector de solucion el valor de la seccion i
                j -= secciones[i - 1]; //Al haber cogido la seccion i, debe ahora comprobarse el valor de j al que se le ha restado s_i
            }
            else
                --i; //Si no se coge la seccion i se comprueba la seccion anterior para el mismo j ya que este no cambia al no elegir seccion
        }
        
    }
    else {
        cout << "Imposible";
    }

    return sol;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int V, S;
    cin >> V >> S;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> secciones(S);
    for (int i = 0; i < S; ++i) {
        cin >> secciones[i];
    }



    vector<int> sol = minDardos(secciones, V); 
    
    for (int i = 0; i < sol.size(); ++i) {
        cout << sol[i] << ' ';
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
