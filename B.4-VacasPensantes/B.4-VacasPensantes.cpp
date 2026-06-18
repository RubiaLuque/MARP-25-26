
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

/*@ <answer>

Los cubos no estan ordenados segun la cantidad de comida que contengan y se garantiza que son numeros distintos

Tenemos que cubos es el vector que almacena las cantidades de comida de cada cubo de forma que cubos[i] es la cantidad de comida del 
cubo i.

Funcion recursiva:
    comida(i,j) = max comida entre los indices i..j suponiendo que se come primero

Caso recursivo: (para i < j)
    comida(i,j) = max(comer izq, comer drcha)
        - COMER IZQ:
            - cubos[i+1] > cubos[j] --> comer(i+2, j) + cubos[i]
                En este caso ocurre que el cubo posterior a i es mayor a j por lo que Devoradora lo cogera si cogemos
                nosotros el cubo i. Entonces debemos mirar a partir de i+1, es decir, i+2. Como hemos cogido el cubo de la izquierda, 
                sumamos su cantidad a lo que hemos comido
            - cubos[i+1] <= cubos[j] --> comer(i+1, j-1) + cubos[i]
                El cubo i+1 es menor a j por lo que Devoradora cogera j si nosotros cogemos i.

        - COMER DRCHA:
            - cubos[i] > cubos[j-1] --> comer(i+1, j-1) + cubos[j]
                Si el cubo j-1 es menor al de la derecha y nosotros cogemos el j, Devoradora cogera el cubo i
            - cubos[i] <= cubos[j-1] --> comer(i, j-2) + cubos[j]
                Si el cubo j-1 tiene menos comida que el cubo i y nosotros cogemos el j, Devoradora cogera el j-1. Por lo que
                hay que mirar entonces entre el cubo i y el j-2 al estar ya cogidos el j y j-1
    

Casos base:
comida(i,i) = cubos[i] --> Solo hay un cubo entonces se come de el al ser nosotros los que comemos primero
comida(i,j) = 0 --> donde i > j. Los indices se han cruzado
comida(i, i+1) = max(i, i+1) --> Si solo quedan dos cubos comemos del mayor

Coste en tiempo de O(n*n) y en espacio adicional de O(n*n) donde n es el numero de cubos
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int maxComida(vector<int> const& cubos) {
    
    int n = cubos.size(); //numero total de cubos

    Matriz<int> comida(n, n, 0); //Como se trata de maximizar, se rellena todo a 0

    //Casos base: solo hay un cubo --> rellenar la diagonal ppal
    for (int i = 0; i < n; ++i) {
        comida[i][i] = cubos[i];
    }


    //Se recorre la matriz por diagonales desde la diagonal ppal hacia arriba en la implementacion ascendente
    //Todos los casos por debajo de la diagonal principal son casos base que corresponden a i > j rellenos a 0
    // d comienza en 1 porque la diagonal ppal que equivaldria a d=0 ya esta rellena con los casos base
    for (int d = 1; d < n; ++d) { //por diagonales
        for (int i = 0; i < n - d; ++i) { //por filas. Cada fila comienza a recorrerse a partir de la diagonal ppal de ahi i < n - d
            int j = i + d; //Columna perteneciente a la fila i y la diagonal d

            //Caso base: solo quedan dos cubos
            if (i + 1 == j) {
                comida[i][j] = max(cubos[i], cubos[j]);
            }
            //Comemos por alguno de los extremos
            else {
                int iz, drcha;

                //Debemos mirar por qué lado es mejor comer asi que comprobamos ambos
                //CASO COMER POR LA IZQUIERDA
                //Caso ambos comemos por la izquierda
                if (cubos[i + 1] > cubos[j]) {
                    iz = comida[i + 2][j] + cubos[i];
                }
                //Caso nosotros comemos por la izquierda y Devoradora por la derecha
                else {
                    iz = comida[i + 1][j - 1] + cubos[i];
                }

                //CASO COMER POR LA DERECHA
                //Caso nosotros comemos por la derecha y Devoradora por la izquierda
                if (cubos[i] > cubos[j - 1]) {
                    drcha = comida[i + 1][j - 1] + cubos[j];
                }
                //Caso ambos comemos por la derecha
                else {
                    drcha = comida[i][j - 2] + cubos[j];
                }

                //comida(i,j) es el mayor de lo que podemos comer por la derecha y por la izquierda
                comida[i][j] = max(iz, drcha);
                
            }

        }
    }

    return comida[0][n - 1];
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N; 
    cin >> N;
    if (N==0)
        return false;

    //Vector con las cantidades de comida en cada cubo de iz a dcha
    vector<int> cubos(N);
    for (int i = 0; i < N; ++i) {
        cin >> cubos[i];
    }

    int sol = maxComida(cubos);

    cout << sol << '\n';

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
