/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> //para usar sort
using namespace std;

/*@ <answer>

 Estrategia voraz: maximizar numero de exitos 


 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int numVictorias(vector<int> const& aliados, vector<int> const& enemigos, int N) {
    int victorias = 0; //Se empieza por 0 victorias
    int i = 0; //contador enemigos
    int j = 0; //contador aliados
    
    while (i < N && j < N) {
        //En cada momento vamos a tener el grupo mayor para cada bando

        if (enemigos[i] > aliados[j]) {
            ++i; //no se puede defender una ciudad con ese numero de enemigos asi que se comprueba el siguiente numero de enemigos
        }
        else if (enemigos[i] <= aliados[j]) {
            ++i; ++j;
            victorias++;
        }
    }

    return victorias;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N; //num ciudades invadidas
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    vector<int> enemigos(N);
    vector<int> aliados(N);

    int num;
    //Se rellena el vector de los enemigos
    for (int i = 0; i < N; ++i) {
        cin >> num;
        enemigos[i] = num;
    }

    //Se rellena el vector de los aliados
    for (int i = 0; i < N; ++i) {
        cin >> num;
        aliados[i] = num;
    }

    //Se ordenan ambos vectores de mayor a menor --> O(NlogN)
    sort(enemigos.begin(), enemigos.end(), greater<int>());
    sort(aliados.begin(), aliados.end(), greater<int>());

    //O(N)
    int victorias = numVictorias(aliados, enemigos, N);

    cout << victorias << '\n';
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
