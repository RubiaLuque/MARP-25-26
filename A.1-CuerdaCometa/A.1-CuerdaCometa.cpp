/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

/*
Se debe pasar por un cordel (i) para toda posible longitud j antes de pasar al siguiente.
Se rellena cada matriz de izquierda a derecha y de arriba a abajo. Esto se deduce de antes haber planteado la funcion recursiva

Para todos los problemas el coste en tiempo es de O(N*L) donde N es el numero de cordeles y L la longitud de la cuerda
*/

//PROBLEMA INICIAL: ¿Se puede llegar a conseguir L? ----------------------------------------------------------------------------------
/*
i: cordel que se esta considerando
j: longitud de la cuerda actual
li: longitud de i

Funcion: sePuede(i,j): 
    - li > j --> sePuede(i-1, j): 
        No se puede coger i por ser mas larga que lo que resta de cuerda (j) asi que se consideran el resto de cordeles.
    - li <= j --> sePuede(i-1, j) || sePuede(i-1, j-li)
        - Si ya se podía llegar a j usando el resto de cordeles hasta i-1 entonces se seguira pudiendo sin incluir a i. 
            Si no se podia llegar antes sin incluir a i, ahora tampoco se puede. Esto se aplica tambien a la opcion li > j
        - Si se podía llegar a j-li usando otros cordeles anteriormente entonces se puede llegar a j usando i. 

sol[i][j] nos dice si podemos alcanzar la longitud j usando solo cordeles del 1 al i
Es importante tener en cuenta que no se puede sumar el mismo cordel dos veces, por eso unicamente se consulta la fila i-1. 
Cada cordel suma una sola vez, es decir, solamente tenemos un cordel de cada tipo. 
*/
bool sePuede(vector<int> const& cordeles, int L) {
    int N = cordeles.size();

    Matriz<bool> sol(N + 1, L + 1, false);
    //CASOS BASE
    sol[0][0] = true; //Se puede rellenar 0 longitud con 0 numeros de cuerda

    for (int i = 1; i <= N; ++i) {
        sol[i][0] = true; //CASOS BASE --> si se puede rellenar 0 longitud siempre
        for (int j = 1; j <= L; ++j) {
            if (cordeles[i - 1] > j) //No se puede usar el cordel i (representado en cordeles por i-1 al comezar en 0)
                sol[i][j] = sol[i - 1][j];
            else {
                sol[i][j] = sol[i - 1][j] || sol[i-1][j - cordeles[i - 1]];
            }

        }
    }

    return sol[N][L];
}
//Version con espacio adicional O(L) y con mismo coste en tiempo
bool sePuedeV(vector<int> const& cordeles, int L) {
    int N = cordeles.size();

    vector<bool> sol(L + 1, false);

    sol[0] = true; //Siempre se puede rellenar 0 longitud

    //Se recorre de derecha a izquierda para no sobreescribir valores que nos hagan falta en un futuro de forma incorrecta
    //Al hacer que j se mantenga igual o mayor a cordeles[i-1] es para ignorar todos aquellos cordeles que no se pueden coger por 
    // ser mayores que j
    for (int i = 1; i <= N; ++i) {
        for (int j = L; j >= cordeles[i - 1]; --j) {
            sol[j] = sol[j] || sol[j - cordeles[i - 1]];
        }
    }

    return sol[L];
}

//PROBLEMA 2: num formas de conseguir una longitud L. -------------------------------------------------------------------------------
/*
Funcion: num(i,j) 
    - Caso li > j --> num(i-1, j)
        Si no se puede coger el cordel i entonces el numero de formas de llegar a j es el mismo que para i-1
    - li <= j --> num(i-1, j) + num(i-1, j-li)
        Si se coge el cordel el numero de formas de llegar a j es la cantidad de formas que tenia el cordel anterior de llegar a j
        y se le suma la cantidad de formas que habia de llegar a j-li usando el cordel anterior. Es decir, a las formas de llegar a j
        que habia de antes, se le suma la forma del cordel actual para llegar a j

Casos base:
num(i, 0) --> rellenar longitud 0 con i cordeles es 1
*/
long long int numFormas(vector<int> const& cordeles, int L) {
    int N = cordeles.size();
    Matriz<long long int> num(N + 1, L + 1, 0);

    num[0][0] = 1; //Caso base

    for (int i = 1; i <= N; ++i) {
        num[i][0] = 1; //Casos base
        for (int j = 1; j <= L; ++j) {
            if (cordeles[i - 1] > j) //No se coge la cuerda
                num[i][j] = num[i - 1][j];
            else { //Si se coge la cuerda
                num[i][j] = num[i - 1][j] + num[i - 1][j - cordeles[i - 1]];
            }
        }
    }

    return num[N][L];
}

//Version con espacio adicional en O(L)
long long int numFormasV(vector<int> const& cordeles, int L) {
    int N = cordeles.size();

    vector<long long int> num(L + 1, 0);
    num[0] = 1; //Rellenar una distancia 0 se puede hacer de una forma solamente
    for (int i = 1; i <= N; ++i) {
        for (int j = L; j >= cordeles[i - 1]; --j) {
            num[j] = num[j] + num[j - cordeles[i - 1]];
        }
    }

    return num[L];
}


//PROBLEMA 3: min cuerdas para alcanzar L ----------------------------------------------------------------------------------------
/*
Funcion: cuerdas(i, j)
    - li > j --> cuerdas(i-1, j) 
        No se coge i entonces la menor forma de alcanzar j depende de la cuerda anterior
    - li <= j --> min( cuerdas(i-1, j), cuerdas(i-1, j-li) + 1)
        Se elige el minimo entre no coger la cuerda i y coger la cuerda i teniendo en cuenta que para ello hay que mirar 
        el minimo que ya hay en la cuerda anterior para j-li
        - Si se descarta el cordel (cuerdas(i-1,j)) se mira si habia forma de conseguir esa longitud con el resto de cuerdas.
        - Si no se descarta, se suma al minimo anterior la cuerda i
*/
EntInf minCuerdas(vector<int> const& cordeles, int L) {
    int N = cordeles.size();

    Matriz<EntInf> cuerdas(N + 1, L + 1, EntInf::_intInf);
    cuerdas[0][0] = 0; //Caso base

    for (int i = 1; i <= N; ++i) {
        cuerdas[i][0] = 0; //Caso base. Para una longitud 0 no se puede poner ninguna cuerda
        for (int j = 1; j <= L; ++j) {
            if (cordeles[i - 1] > j)
                cuerdas[i][j] = cuerdas[i - 1][j];
            else
                cuerdas[i][j] = std::min(cuerdas[i - 1][j], cuerdas[i - 1][j - cordeles[i - 1]] + 1);
        }
    }

    return cuerdas[N][L];
}
//Version con espacio adicional reducido a O(L)
EntInf minCuerdasV(vector<int> const& cordeles, int L) {
    int N = cordeles.size();

    vector<EntInf> cuerdas(L + 1, EntInf::_intInf);
    cuerdas[0] = 0; //No se puede poner nunguna cuerda para una longitud 0

    for (int i = 1; i <= N; ++i) {
        for (int j = L; j >= cordeles[i - 1]; --j) {
            cuerdas[j] = std::min(cuerdas[j], cuerdas[j - cordeles[i - 1]] + 1);
        }
    }

    return cuerdas[L];
}

//PROBLEMA 4: min coste necesario -----------------------------------------------------------------------------------------------
/*
Funcion: cost(i,j)
    - li > j --> cost(i-1,j) 
        Si la cuerda no se coge el coste es el mismo que coger el coste de las demas que si se cogen
    - li <= j --> min( cost(i-1, j), cost(i-1, j-li) + costes[i])
        Si la cuerda se coge el coste es el minimo entre no coger la cuerda y si cogerla y añadirle el coste de esta
        - No se coge la cuerda: coste igual a coger el resto de cuerdas
        - Si se coge la cuerda: coste igual a la suma entre el resto de cuerdas que si se cogen y el coste de la cuerda i
Importante: cost habla del caso recursivo, costes habla del vector de costes para cada cuerda
*/
EntInf minCoste(vector<int> const& cordeles, vector<int> const& costes, int L) {
    int N = cordeles.size();

    Matriz<EntInf> cost(N + 1, L + 1, EntInf::_intInf);
    //Caso base cost(0,0)
    cost[0][0] = 0; //El coste de rellenar 0 longitud con 0 cuerdas es 0 al no gastar ninguna

    for (int i = 1; i <= N; ++i) {
        cost[i][0] = 0; //Caso base cost(i,0). No rellenar espacio significa que no se gasta nada
        for (int j = 1; j <= L; ++j) {
            if (cordeles[i - 1] > j) //No se puede coger la cuerda
                cost[i][j] = cost[i - 1][j];
            else
                cost[i][j] = std::min(cost[i - 1][j], cost[i - 1][j - cordeles[i - 1]] + costes[i-1]);
        }
    }

    return cost[N][L];
}
//Version con espacio adicional reducido a O(L)
EntInf minCosteV(vector<int> const& cordeles, vector<int> const& costes, int L) {
    int N = cordeles.size();

    vector<EntInf> cost(L + 1, EntInf::_intInf);
    cost[0] = 0;

    for (int i = 1; i <= N; ++i) {
        for (int j = L; j >= cordeles[i - 1]; --j) {
            cost[j] = std::min(cost[j], cost[j - cordeles[i - 1]] + costes[i - 1]);
        }
    }

    return cost[L];
}


bool resuelveCaso() {

    // leer los datos de la entrada
    int N, L; 
    cin >> N >> L;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> cordeles(N);
    vector<int> costes(N);


    for (int i = 0; i < N; ++i) {
        cin >> cordeles[i];
        cin >> costes[i];
    }

    
    //SOLUCION CON COSTE EN ESPACIO ADICIONAL O(N*L)
    //PROBLEMA BASICO: ¿Se puede formar L?
    //bool aux = sePuede(cordeles, L);
    //if (aux) {
    //    cout << "SI ";
    //    //PROBLEMA 2: num formas de conseguir L
    //    cout << numFormas(cordeles, L) << ' ';
    //    //PROBLEMA 3: min cuerdas para conseguir L
    //    cout << minCuerdas(cordeles, L) << ' ';
    //    //PROBLEMA 4: min coste necesario
    //    cout << minCoste(cordeles, costes, L);

    //    cout << '\n';
    //} 
    //else cout << "NO\n";
    
    //SOLUCION CON COSTE ES ESPACIO ADICIONAL O(L)
    bool aux = sePuedeV(cordeles, L);
    if (aux) {
        cout << "SI ";
        //PROBLEMA 2: num formas de conseguir L
        cout << numFormasV(cordeles, L) << ' ';
        //PROBLEMA 3: min cuerdas para conseguir L
        cout << minCuerdasV(cordeles, L) << ' ';
        //PROBLEMA 4: min coste necesario
        cout << minCosteV(cordeles, costes, L);

        cout << '\n';
    }
    else cout << "NO\n";
    
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
