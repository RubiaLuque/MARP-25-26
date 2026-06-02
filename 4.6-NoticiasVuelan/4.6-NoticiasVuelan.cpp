/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Grafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class RedSocial {
private:
    vector<int> visit;
    vector<int> componente; //componente[v] --> nº componente a la que pertenece v
    vector<int> tamComp; //tamComp[i] --> tamaño de la componente conexa i

    //O(V + A)
    int dfs(Grafo const& g, int v) {
        visit[v] = true;
        int tam = 1; //Devuelve el tamaño de toda la componente conexa al final
        //v pertece a la componente de tamComp.size() ya que este valor se actualiza con cada nueva componete que se recorre
        componente[v] = tamComp.size(); 
        
        for (auto w : g.ady(v)) {
            if (!visit[w]) {
                tam += dfs(g, w);
            }
        }

        return tam;
    }

public:
    RedSocial(Grafo const& g): visit(g.V(), false), componente(g.V()) {
        //O(V + A) --> porque aunque se haga una llamada a dfs dentro de un for, cada vertice se recorre una sola vez
        for (int i = 0; i < g.V(); ++i) {
            if (!visit[i]) { //Nueva componente conexa
                int tam = dfs(g, i); //Recorre la nueva componente conexa completa
                tamComp.push_back(tam); //Nueva componete conexa con tamaño tam
            }
        }
    }

    //Dado un vertice devuelve el tamaño de la componente conexa a la que pertenece
    int tamCompV(int v) const {
        return tamComp[componente[v]];
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M; //num usuarios, num grupos
    cin >> N >> M;
    if (!std::cin)  // fin de la entrada
        return false;

    Grafo red = Grafo(N); //Grafo con numero de nodos igual a numero de usuarios

    //El grafo se crea de esta manera porque queremos tener el menor numero de aristas posibles ya que el coste es (V + A) 
    // asi, se crea de forma que cada persona de un grupo se conecta con la siguiente y no todas las del grupo entre sí.
    // Lo unico que interesa es que haya un camino entre las personas de un grup, pero si se crea una arista entre cada persona
    // de cada grupo el algoritmo se haria muy ineficiente para grafos con grupos conexos muy grandes
    int nIntegrantes;
    for (int i = 0; i < M; ++i) {
        cin >> nIntegrantes;
        if (nIntegrantes > 0) {
            int primero;
            cin >> primero; //Si el grupo es de un solo integrante es igual a que si dicho grupo no existiera para este ejercicio
            if (nIntegrantes > 1) {
                int segundo;
                for (int j = 0; j < nIntegrantes -1; ++j) {
                    //Se van poniendo aristas entre cada par de integrantes 
                    cin >> segundo;
                    red.ponArista(primero - 1, segundo - 1); //se resta uno porque los id usuarios empiezan en 1
                    primero = segundo;
                }
            }
        }
    }

    // resolver el caso posiblemente llamando a otras funciones
    RedSocial rs = RedSocial(red); //O(N + sum(T_i)) --> A es proporcional a sum(T_i)

    //Para cada usuario existente saber cuantas personas conocerían la noticia
    // escribir la solución
    for (int i = 0; i < red.V(); ++i) {
        cout << rs.tamCompV(i) << ' ';
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
