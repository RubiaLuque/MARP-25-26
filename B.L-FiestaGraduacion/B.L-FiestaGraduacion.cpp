/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Maximizar el numero de canciones dadas dos listas. Debe cumplirse que:
 - Una cancion solo puede aparecer en la lista final si esta en ambas listas originales
 - Las canciones presentes en la lista final deben seguir el mismo orden entre sí en las listas originales (no hace falta que 
   sea una inmediatamente despues de la otra)

Funcion recursiva:
lista(i, j) = max tam de la lista final teniendo en cuenta desde i a ni de la primera lista y j a nj de la segunda
i = cancion perteneciente a la primera lista
j = cancion perteneciente a la segunda lista
ni = tamaño lista i
nj = tamaño lista j

Casos recursivos:
    - lista1[i] == lista2[j] --> lista(i+1, j+1) + 1
        La cancion en ambas listas coincide por lo que se suma 1 al incluir la cancion en la lista final y se avanza en ambas listas

    - lista[i] != lista[j] --> max( lista(i+1, j), lista(i, j+1))
        Las canciones no coinciden asi que se mira el tamaño maximo que tendria la lista si se avanza en una o en otra lista una posicion

Casos base:
lista(i, nj + 1) = 0 --> caso vacio al haber llegado al final de la lista 2 (j > nj)
lista(ni + 1, j) = 0 --> caso vacio al haber llegado al final de la lista 1 (i > ni)
lista(ni + 1, nj + 1) = 0 --> ambas listas estan vacias (i > ni && i > nj)

Llamada inicial:
lista(0,0) --> Se comienza a ver desde el principio de ambas listas 

Coste total en tiempo de O(ni*nj) donde ni es el tamaño de la primera lista y nj el tamaño de la segunda.
Coste en espacio adicional de O(ni*nj)
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

vector<string> leerLista() {
    vector<string> lista; //Variable a devolver (lista de canciones)

    string linea;
    getline(cin, linea); //lee y guarda toda la linea de una lista en la variable linea
    
    //Si no hay entrada (lista vacia) se devuelve un vector vacio de strings
    if (!cin)
        return {};
    
    //Con esto podemos leer palabra a palabra de toda la lista
    stringstream ss(linea);
    string cancion;

    //Mientras queden palabras por leer de la linea 
    while (ss >> cancion) {
        lista.push_back(cancion);
    }

    return lista;
}


vector<string> canciones(vector<string> const& l1, vector<string> const& l2) {
    int ni = l1.size();
    int nj = l2.size();

    Matriz<int> lista(ni + 1, nj + 1, 0); 

    //No hace falta rellenar los casos base de forma especial porque al inicializar la matriz a 0 ya se esta haciendo
    //Como en este caso estamos haciendo que se necesite tener los datos de (i+1, j+1), (i,j+1) y (i+1, j) para construir la solucion, 
    // la matriz esta al reves de lo habitual. Los casos base son la ultima fila y columna y la matriz se recorre desde la esquina 
    // inferior derecha hasta la superior izquierda. 
    //Al inicializar la matriz con tamaño (ni + 1)*(nj+1) tiene indices de 0..ni y 0..nj
    //Las posiciones ni y nj de la matriz son los casos base, por eso se comienza a recorrer desde ni-1 y nj-1
    for (int i = ni - 1; i >= 0; --i) {
        for (int j = nj - 1; j >= 0; --j) {
            //Las canciones son la misma asi que se añade y se continua mirando el resto
            if (l1[i] == l2[j]) {
                lista[i][j] = lista[i + 1][j + 1] + 1;
            }
            //Canciones no iguales. Hay que mirar si es mejor avanzar en una lista o en otra
            else {
                lista[i][j] = max(lista[i + 1][j], lista[i][j + 1]);
            }
        }
    }

    //Reconstruccion de la solucion
    //Tal y como se ha planteado la funcion recursiva, la solucion se encuentra en lista(0,0) asi que se empieza a reconstruir por ahi
    int i = 0, j = 0;
    vector<string> sol;
    while (i < ni && j < nj) {
        //Si la cancion es la misma entonces es que se ha añadido
        if (l1[i] == l2[j]) {
            sol.push_back(l1[i]);
            ++i; ++j;
        }
        //La solucion optima indica que se ha avanzado en la primera lista
        else if(lista[i][j] == lista[i+1][j]) {
            ++i;
        }
        //La solucion optima indica que se ha avanzado en la segunda lista 
        //(lista[i][j] == lista[i][j + 1])
        else {
            ++j;
        }
    }

    return sol;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    vector<string> lista1 = leerLista();

    if (!std::cin)  // fin de la entrada
        return false;

    vector<string> lista2 = leerLista();

    vector<string> sol = canciones(lista1, lista2);

    for (int i = 0; i < sol.size(); ++i) {
        cout << sol[i] << " ";
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
