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

 Menor numero de letras extra para conseguir que una palabra sea un palindromo

 Funcion recursiva:
 aibofobia(i,j) = min letras a añadir entre las letras i..j de la palabra 
    - i==j --> aibofobia(i+1, j-1)
    si las letras i, j coinciden (i==j) entonces el menor numero de letras para formar un palindromo sera el mismo que para 
    los siguientes extremos porque no se añade ninguna nueva letra
    - i != j --> min(aibofobia(i+1, j) +1, aibofobia(i, j-1) +1)
    si las letras no coinciden entonces debe añadirse una nueva letra en cualquiera de los extremos pero solo en uno: bien 
    la letra i en la posicion j+1 o la letra j en la posicion i-1. Se le suma 1 en ambos casos porque se añade una letra en cualquiera 
    de ambos casos. 
        - En caso de añadir la letra i, esta se coloca detras de la j en j+1 -> se avanza solo el indice i a drcha
        - En caso de añadir la letra j, esta se coloca detras de la i en i-1 -> se avanza solo el indice j a izq

Casos base:
aibofobia(i, i) = 0 --> No hay que poner una nueva letra
aibofobia(i, j) = 0 donde i > j --> Se cruzan los indices o palabra vacia, no hay que poner letra

Coste total en tiempo de O(n*n) donde n es la longitud de la palabra incial
Coste de O(n*n) en espacio adicional

Coste O(n) en tiempo de la reconstruccion de la solucion ya que se recorre i..j una sola vez donde i es el comienzo de la palabra y j
el final
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int pal(string const& palabra, Matriz<int>& aibofobia) {
    int n = palabra.size();

    //Se recorre la matriz por diagonales desde la principal hacia arriba
    // ya que la mitad inferior de la matriz esta compuesta de ceros por ser casos base
    for (int d = 1; d < n; ++d) { //Recorrido en diagonales
        for (int i = 0; i < n - d; ++i) { //recorrido por filas dentro de cada diagonal
            
            int j = d + i; //Columna correspondiente a la diagonal d y la fila i
            
            if (palabra[i] == palabra[j]) { //Misma letra
                aibofobia[i][j] = aibofobia[i + 1][j - 1];
            }
            else { //distintas letras
                aibofobia[i][j] = min(aibofobia[i + 1][j] + 1, aibofobia[i][j - 1] + 1);
            }
        }
    }

    //La solucion se encuentra en la fila 0, ultima columna
    return aibofobia[0][n - 1];
}

string reconstruir(string const& palabra, Matriz<int> const& aibofobia) {
    
    int i = 0, j = palabra.size() - 1;

    //Se crean tantos huecos " " para la palabra solucion como letras tiene
    // la palabra original más las letras añadidas
    string sol(palabra.size() + aibofobia[i][j], ' ');

    int pos = 0; //indice para saber en que posicion dentro de la palabra reconstruida estamos
    char c; //char correspondiente al caso que estamos mirando

    while (i <= j) {
        if (palabra[i] == palabra[j]) { //Ambas letras son iguales asi que el char es una de ellas seguro 
            c = palabra[i];
            ++i; --j; //Se avanzan ambos indices en sus respectivas direcciones
        }
        else { //Las letras son disntintas asi que debemos mirar cual de ellas se ha añadido

            //Si se cumple esto, significa que se ha añadido la letra del extremo izquierdo, por lo que es ese extremo el que avanza
            // a la derecha
            //(aibofobia[i][j] == aibofobia[i][j - 1] + 1)
            if (aibofobia[i][j] == aibofobia[i][j - 1] + 1) {
                c = palabra[j];
                --j; //avanza a la drcha
            }
            //Si se cumple esto es que se ha añadido la letra del extremo derecho (correpondiente a i), asi que es ese indice 
            // el unico que avanza a la izq
            else if (aibofobia[i][j] == aibofobia[i + 1][j] + 1) {
                c = palabra[i];
                ++i;
            }

        }

        //Se empieza a poner por el comienzo y por el final
        //Como cada letra puede estar dos veces al tener la mecanica de añadir letras, 
        // esta debe ponerse tambien en su lugar correspondiente con respecto del final de la palabra tambien
        //pos nos da la posicion adecuada con respecto al inicio y el final de la palabra
        sol[pos] = sol[sol.size() - pos - 1] = c;
        
        pos++;
    }

    return sol;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    string palabra;
    cin >> palabra;
    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<int> sol(palabra.size(), palabra.size(), 0);

    int minLetras = pal(palabra, sol);
    string solucion = reconstruir(palabra, sol);

    cout << minLetras << " " << solucion << '\n';

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
