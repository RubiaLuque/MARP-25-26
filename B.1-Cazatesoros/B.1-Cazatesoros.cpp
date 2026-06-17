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

 T: capacidad total 
 N: num cofres

 Tiempo descenso a una profundidad p = p
 Tiempo ascenso desde profundidad p = 2*p

 Para cada cofre, necesita 3*p del total del tanque (T) si esta a profundidad p
 p_i hace referencia a la profundidad p del objeto i
 v_i hace referencia al valor del cofre i

 Problemas: 
 - max valor
 - num cofres para conseguir max valor
 - profundidad y valor para cada uno de esos cofres

 Hay que reconstruir la solucion, por lo que se no se reduce el espacio adicional al tener que usaar sí o sí i-1 para reconstruir i

 Caso recursivo:
 tanque(i,j) = maximo de oro que podemos obtener teniendo un espacio max j en el tanque considerando los cofres del 1 al i
    - tanque(i-1, j) si p_i*3 > j --> No se coge el cofre
    - max( tanque(i-1, j), tanque(i-1, j-3*p_i) + v_i) )
        - mayor valor entre no considerar el cofre i o sí considerarlo, restando a la capacidad j del tanque 3*p_i que es lo que 
        se necesita para obtener dicho cofre y sumando el valor v_i del cofre

Casos base:
tanque(i,0) = 0 --> No se pueden coger mas cofres estando el tanque vacio
tanque(0,j) = 0 --> No se añade valor al no poder coger mas objetos

Coste en tiempo de O(N*T) donde N es el numero de cofres y T la capacidad total del tanque. 
Coste en espacio adicional de O(N*T) y coste en tiempo de la reconstruccion de la solucion de O(N).
Estos costes se cumplen para los casos de implementacion ascendente y descendente

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Cofre {
    int profundidad; 
    int oro;
};

//Version del problema con implementacion descendente ----------------------------------------------------------------
int tanque_rec(vector<Cofre> const& c, int i, int j, Matriz<int> & tanque) {
    
    //Subproblema ya resuelto
    if (tanque[i][j] != -1)
        return tanque[i][j];

    //Casos base
    if (i == 0 || j == 0)
        tanque[i][j] = 0;
    //No se puede acceder al cofre por lo que se descarta
    else if (3 * c[i - 1].profundidad > j) {
        tanque[i][j] = tanque_rec(c, i - 1, j, tanque);
    }
    //Si se puede acceder al cofre y se valora si es optimo cogerlo o no en funcion de si maximiza el valor del oro total
    else {
        tanque[i][j] = std::max(tanque_rec(c, i - 1, j, tanque), 
            tanque_rec(c, i - 1, j - 3 * c[i - 1].profundidad, tanque) + c[i - 1].oro);
    }

    return tanque[i][j];
}
int tanque(vector<Cofre> const& c, int T, vector<bool>& sol, int& numCofres) {
    int n = c.size();
    Matriz<int> tanque(n + 1, T + 1, -1);

    int valorOro = tanque_rec(c, n, T, tanque); //O(nT)

    //Reconstruccion de la solucion
    int i = n, j = T; //se recorre hacia atras
    sol = vector<bool>(n, false); //nos permitira saber a que objeto nos referimos si esta a true
    numCofres = 0; //numero de cofres que forman parte de la solucion

    //O(n) ya que como mucho recorre el numero de objetos
    while (i > 0 && j > 0) {
        //Si el valor maximo de tanque(i,j) es distinto que para el del objeto i-1, eso significa que no se tenia ya el valor optimo
        // y que por tanto el objeto i forma parte de la solucion
        if (tanque[i][j] != tanque[i - 1][j]) {
            sol[i - 1] = true;
            j -= c[i - 1].profundidad * 3;
            numCofres++;
        }
        --i;
    }

    return valorOro;
}

//Version del problema con implementacion ascendente --------------------------------------------------------------------------------
int tanqueAsc(vector<Cofre> const& c, int T, vector<bool>& sol, int& numCofres) {
    int n = c.size();

    //En caso de recursion ascendente no necesitamos saber si un subproblema ha sido resuelto o no puesto que la matriz se recorre
    // entera de arriba a abajo y de izquierda a derecha una sola vez. Es por eso que se inicializa a 0
    Matriz<int> tanque(n + 1, T + 1, 0);

    //Casos base (no seria necesario ya que toda la matriz se inicializa a 0)
    tanque[0][0] = 0; 

    for (int i = 1; i <= n; ++i) {
        tanque[i][0] = 0; //Caso base
        for (int j = 1; j <= T; ++j) {
            //No se puede coger el cofre
            if (c[i - 1].profundidad * 3 > j)
                tanque[i][j] = tanque[i - 1][j];

            //Si se puede coger el cofre
            else {
                tanque[i][j] = max(tanque[i - 1][j], 
                    tanque[i - 1][j - 3 * c[i - 1].profundidad] + c[i - 1].oro);
            }
        }
    }

    //Reconstruccion de la solucion (igual que el metodo descendente)
    int i = n, j = T;
    sol = vector<bool>(n, false);
    numCofres = 0;
    while (i > 0 && j > 0) {
        if (tanque[i][j] != tanque[i - 1][j]) {
            sol[i - 1] = true;
            j -= c[i - 1].profundidad * 3;
            numCofres++;
        }
        --i;
    }

    return tanque[n][T];
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int T, N; //capacidad tanque oxigeno, num cofres totales 
    cin >> T >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<Cofre> c(N);
    for (int i = 0; i < N; ++i) {
        cin >> c[i].profundidad >> c[i].oro;
    }

    vector<bool> sol;
    int numCofres;

    int oro = tanque(c, T, sol, numCofres);
    //int oro = tanqueAsc(c, T, sol, numCofres); --> Descomentar para version ascendente

    cout << oro << '\n'; //cantidad de oro
    cout << numCofres << '\n'; //Num cofres parte de la solucion

    for (int i = 0; i < N; ++i) {
        //Si el objeto i forma parte de la solucion se escriben sus caracteristicas
        if (sol[i])
            cout << c[i].profundidad << " " << c[i].oro << '\n';
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
