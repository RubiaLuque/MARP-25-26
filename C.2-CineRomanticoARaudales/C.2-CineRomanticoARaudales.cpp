
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

/*@ <answer>
Podria resolverse de forma que i signifique que se miran las peliculas desde la primera hasta la i, pero en ese caso habria que 
ordenar por hora de finalizacion y el resto del problema se plantearia teniendo en cuenta esto.

cine(i) = maxima cantidad de tiempo viendo peliculas considerando desde la pelicula i hasta la N siendo que estas estan ordenadas
            por hora de inicio


Caso recursivo: 
cine(i) = max( cine(i+1), d_i + cine( sig(i))

Esto significa que se elige entre el maximo valor que consigamos de comparar dos casos:
    - No elegir la pelicula i y continuar mirando desde la pelicula i+1
    - Sí elegir la pelicula i, hay dos opciones:
        - No se puede ver ninguna despues: tan solo se tiene en cuenta la duracion d_i 
        - Sí se puede ver una despues: se añade la duracion d_i al maximo calculado anteriormente para la siguiente posible 
        pelicula que ver sig(i)

sig(i) hace referencia a la siguiente pelicula que se puede ver teniendo en cuenta d_i y los 10 mins de margen del ejercicio por lo que
seria el indice j mas pequeño que cumpla que j > i (es una pelicula posterior) y que inicio de j sea igual o mayor a la hora de finalizacion
de i + 10 minutos extra

Caso base:
cine(N) = d_n porque solo queda una pelicula asi que solo se puede ver esa

Llamada inicial:
cine(0) --> Se empieza desde la pelicula 0, la primera

Recorrido del espacio adicional usando programacion ascendente de derecha a izquierda.

Coste total en O(NlogN) siendo N el numero de peliculas. No es O(N*N) porque al tener las peliculas ordenadas por hora de inicio
se puede encontrar la siguiente haciendo una busqueda binaria que tiene coste logN para cada pelicula que estemos viendo
por lo que en caso peor se hace una busqueda binaria logN para N peliculas lo que resulta en un coste O(NlogN) y con un espacio adicional
en O(N)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Peli {
    int ini, duracion;
};

//Encontrar la siguiente pelicula posible mediante busqueda binaria para que el coste total no sea O(N*N) sino O(NlogN)
int siguiente(vector<Peli> const& p, int j, int minInicioPelicula) {
    int max_j = p.size() - 1;
    int res = p.size(); 

    //Mientras que no se haya llegado al maximo valor que puede tener j como indice
    while (j <= max_j) {
        int mid = (max_j + j) / 2;

        //Si la pelicula que se esta comprobando tiene una hora de inicio igual o posterior a la finalizacion de i + 10 mins 
        // entonces se puede ver
        if (p[mid].ini >= minInicioPelicula) {
            res = mid;
            max_j = mid - 1;
        }
        //Si no se puede ver, se mira la siguiente pelicula descartando la mitad izquierda al estar ordenadas por hora de inicio
        // y se comienza a comprobar a partir de la mitad
        else {
            j = mid + 1;
        }
    }

    return res;
}

int maxTiempo(vector<Peli> const& p) {
    int n = p.size(); //n es el numero de peliculas

    vector<int> cine(n);

    //Casos base
    cine[n - 1] = p[n - 1].duracion; //Si solo hay una pelicula el tiempo de visualizacion es lo que dura

    for (int i = n - 2; i >= 0; --i) {

        //Buscar la siguiente pelicula que se puede ver tras la actual
        int minIniPeli = p[i].ini + p[i].duracion + 10;
        int j = siguiente(p, i + 1, minIniPeli);
        //Si j es igual a n entonces eso significa que no se ha encontrado una pelicula compatible
        bool enc = (j == n) ? false : true;

        int nuevaPeli; 
        //Si se ha encontrado una nueva pelicula entonces el tiempo de visualizacion es el que ya teniamos 
        if (enc) {
            //caso d_i + cine( sig(i) ) donde sig(i) es una peli valida
            nuevaPeli = p[i].duracion + cine[j]; //Se añade el tiempo de ver i al tiempo de visualizacion si vemos j
        }
        //No se ha encontrado otra peli que se pueda ver despues de i 
        else {
            //Caso d_i donde sig(i) no es una peli valida
            nuevaPeli = p[i].duracion;
        }

        //Es entonces cuando se tiene en cuenta si descartar la peli i o no
        cine[i] = max(cine[i + 1], nuevaPeli);
    }

    return cine[0]; //lo que seria la llamada inicial
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N; //num pelis
    cin >> N;
    if (N==0)
        return false;

    vector<Peli> p(N);
    int dia, hora, mins;
    char aux;
    for (int i = 0; i < N; ++i) {
        cin >> dia >> hora >> aux >> mins;
        //Se empieza en el dia 0 para que las horas de inicio absolutas sean a partir de 0
        p[i].ini = (dia-1) * 60 * 24 + hora*60 + mins; 
        cin >> p[i].duracion;

    }

    //O(N*logN) por la ordenacion de las peliculas basada en su hora de inicio
    std::sort(p.begin(), p.end(), [](Peli const& a, Peli const& b) {
        return a.ini < b.ini;
        });

    // resolver el caso posiblemente llamando a otras funciones
    int tmax = maxTiempo(p);

    // escribir la solución
    cout << tmax << '\n';

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
