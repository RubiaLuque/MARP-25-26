
/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <deque>
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

struct Pelicula {
    int64_t ini, fin;
};

int64_t numPeliculas(deque<Pelicula>& cartelera) {
    int peliculas = 1; //Siempre vera al menos 1 que es la primera
    Pelicula actual = cartelera.front(); //O(1)
    cartelera.pop_front(); //O(1)

    while (!cartelera.empty()) {
        Pelicula nueva = cartelera.front();
        cartelera.pop_front();
        
        //Si la nueva pelicula comienza despues que la ultima se considera que se puede ver
        if (nueva.ini >= actual.fin) {
            peliculas++;
            actual = nueva; //Se actualiza la pelicula actual
        }
    }
    return peliculas; 
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int64_t N; 
    cin >> N;
    if (N==0)
        return false;

    deque<Pelicula> cartelera(N);

    int64_t dia, duracion;
    int64_t hora, min;
    char aux;
    for (int i = 0; i < N; ++i) {
        cin >> dia >> hora >> aux >> min >> duracion;
        //Se empieza a contar el minuto 0 en el dia 1, por eso se resta 1 al dia
        int64_t ini = 1440 * (dia - 1) + 60 * hora + min; //hora inicio en minutos teniendo el cuenta el dia
        int64_t fin = ini + duracion + 10;  //hora fin en minutos (se añade +10 por tiempo que necesita entre peliculas)
        cartelera[i] = { ini, fin };
    }

    //Se ordenan en base a dia y finalizacion ascendente --> O(NlogN)
    //Se busca ordenar en base a la finalizacion porque ya incluye la duracion en su valor
    //Si se ordena por hora de comienzo podemos encontrarnos con una pelicula muy larga al principio
    std::sort(cartelera.begin(), cartelera.end(), [](Pelicula a, Pelicula b) {
        return  a.fin < b.fin;
        });

    //O(N)
    int64_t maxPeliculas = numPeliculas(cartelera);
    cout << maxPeliculas << '\n';

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
