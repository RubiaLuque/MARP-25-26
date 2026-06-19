
/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Se busca minimizar el esfuerzo en cortar una tabla de longitud L con N cortes.

 Funcion recursiva:
 esfuerzo(i,j) = minimo esfuerzo a realizar en dar un corte entre i+1 y j-1 ya que los extremos no hay que cortarlos
 i, j, k son posiciones fisicas en el espacio, no indices que hacen referencia a cortes

 Casos recursivos: (i<j)
    - min i<k<j {esfuerzo(i,k) + esfuerzo(k,j) + 2*(cortes[j]-cortes[i]) }
        Como no se corta por los extremos, k no es nunca i o j.
        Se corta la tabla en dos mitades delimitadas por k donde k esta en la mitad izquierda y en la derecha
        k actua como punto fisico que es una frontera compartida por las dos mitades resultantes

Caso base:
esfuerzo(i, i+1) = 0 --> ya que no hay que realizar ningun corte

Llamada inicial:
esfuerzo(0, N) --> donde N es el numero de cortes + los dos extremos 0 y L


Coste en tiempo y espacio adicional de O(N*N)
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const int INF = INT32_MAX;

int esfuerzoMin(vector<int> const& cortes) {

    int n = cortes.size(); //numero de cortes contando el 0 y el L

    Matriz<int> esfuerzo(n, n, 0);
    //Se empieza a recorrer la matriz desde la diagonal 2 porque:
    //  Diagonal 0 --> diagonal ppal, donde los indices i, j son iguales y no hay corte posible
    //  Diagona 1 --> una por encima de la ppal, son los casos base donde los puntos (i,j) de la tabla son consecutivos y al tratarse de 
    //                  numeros enteros no puede haber un corte entre ellos. p.ej: (0,1), (1,2)...
    //                  Entonces eso nos dice que no hay un k posible entre ellos
    for (int d = 2; d <= n - 1; ++d) {
        for (int i = 0; i < n - d; ++i) {
            int j = i + d;
            esfuerzo[i][j] = INF;
            for (int k = i + 1; k <= j - 1; ++k) {
                int temp = esfuerzo[i][k] + esfuerzo[k][j] + (cortes[j] - cortes[i]) * 2;
                if (temp < esfuerzo[i][j]) {
                    esfuerzo[i][j] = temp;
                }
            }
        }
    }

    //Se devuelve el valor en la ultima casilla arriba a la derecha de la matriz
    return esfuerzo[0][n-1];
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int L, N; //L = longitud original del tablon, N=num cortes sobre el tablon
    cin >> L >> N;
    if (L==0 && N == 0)
        return false;

    vector<int> cortes(N+2);
    cortes[0] = 0; //Inicio de la tabla
    //los valores de los cortes varian desde 0 a L-1 en orden creciente
    for (int i = 1; i <= N; ++i) {
        cin >> cortes[i];
    }
    cortes[cortes.size() - 1] = L; //longitud L de la tabla

    // resolver el caso posiblemente llamando a otras funciones
    int e = esfuerzoMin(cortes);

    // escribir la solución
    cout << e << '\n';
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
