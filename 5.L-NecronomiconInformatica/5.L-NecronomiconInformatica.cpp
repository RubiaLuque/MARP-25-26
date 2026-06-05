/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Digrafo.h"

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
struct instruccion {
    char tipo;
    int salto; //-1 para instrucciones de tipo A
};

class Necronomicon {
private:
    vector<bool> visit;
    vector<bool> apilado;
    bool _hayCiclo;
    int N; //numero instrucciones

    void dfs(vector<instruccion> const& code, int v) {
        apilado[v] = true;
        visit[v] = true;

        //Recorrido adyacentes segun instruccion
        int nextInst; 
        if (code[v].tipo == 'A') {
            nextInst = v + 1; //Avanza una instruccion
            if (!visit[nextInst]) {
                dfs(code, nextInst);
            }
            else if (apilado[nextInst]) {
                _hayCiclo = true;
                return;
            }
        }
        else if (code[v].tipo == 'J') {
            nextInst = code[v].salto; //Va a la instruccion del salto
            if (!visit[nextInst]) {
                dfs(code, nextInst);
            }
            else if (apilado[nextInst]) {
                _hayCiclo = true;
                return;
            }
        }
        else if (code[v].tipo == 'C') { //Tiene dos adyacentes
            for (int i = 0; i < 2; ++i) {
                //Adyacente 1 se corresponde con la siguiente instruccion: no realiza el salto
                if (i == 0) {
                    nextInst = v + 1; //Avanza una instruccion
                    if (!visit[nextInst]) {
                        dfs(code, nextInst);
                    }
                    else if (apilado[nextInst]) {
                        _hayCiclo = true;
                        return;
                    }
                }

                if (i == 1) {
                    nextInst = code[v].salto; //Va a la instruccion del salto
                    if (!visit[nextInst]) {
                        dfs(code, nextInst);
                    }
                    else if (apilado[nextInst]) {
                        _hayCiclo = true;
                        return;
                    }
                }
            }
        }
        

        apilado[v] = false;

    }


public:
    Necronomicon(vector<instruccion> const& code) : visit(code.size(), false), apilado(code.size(), false), N(code.size()) {
        dfs(code, 0); //Comienza siempre en la instruccion 0
    }

    void solucion() const {
        //Nunca acabara el ciclo si el ultimo nodo no ha sido visitado
        if (!visit[N-1]) cout << "NUNCA\n";

        //Acabara a veces si hay bucle pero si se llega al ultimo nodo
        else if (visit[N - 1] && _hayCiclo) cout << "A VECES\n";

        //Acabara siempre si no hay bucle
        else if (visit[N - 1] && !_hayCiclo) cout << "SIEMPRE\n";
    }
};
*/

class Necronomicon {
private:
    vector<bool> visit;
    vector<bool> apilado;
    bool _hayCiclo;

    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (!visit[w]) { // encontrado un nuevo vértice, seguimos
                dfs(g, w);
            }
            else if (apilado[w]) { // hemos detectado un ciclo
                // se recupera retrocediendo
                _hayCiclo = true;
                
            }
        }
        apilado[v] = false;
    }


public:
    Necronomicon(Digrafo const& g) : visit(g.V(), false), apilado(g.V(), false), _hayCiclo(false) {
        dfs(g, 0);
    }

    bool hayCiclo() const { return _hayCiclo; }

    bool visited(int v) const {
        return visit[v];
    }
    
};
bool resuelveCaso() {

    // leer los datos de la entrada
    int L; 
    cin >> L;
    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo g(L + 1); //Se añade un nodo extra al que se quiere llegar para saber si el codigo acaba o no
    char tipo;
    int salto;
    for (int i = 0; i < L; ++i) {
        cin >> tipo;

        if (tipo == 'A') {
            g.ponArista(i, i + 1);
        }
        else if (tipo == 'J') {
            cin >> salto;
            g.ponArista(i, salto - 1);
        }
        else if (tipo == 'C') {
            cin >> salto;
            g.ponArista(i, i + 1);
            g.ponArista(i, salto - 1);
        }
    }

    Necronomicon necro(g); //O(V + A)

    if (!necro.visited(L)) cout << "NUNCA\n";
    else {
        if (necro.hayCiclo()) cout << "A VECES\n";
        else if (!necro.hayCiclo()) cout << "SIEMPRE\n";
    }

    return true;
    /*
    vector<instruccion> code(L + 1); //Se añade 1 porque se busca llegar despues de la ultima instruccion
    char t; 
    int salto;
    for (int i = 0; i < L; ++i) {
        cin >> t;

        code[i].tipo = t;

        if (t == 'A') {
            code[i].salto = -1;
        }
        else {
            cin >> salto;
            code[i].salto = salto - 1; //Se resta 1 puesto que el vector comienza en 0 y las instrucciones en 1
        }
    }

    //Se rellena el nodo final diferente 
    code[L].tipo = 'D';
    code[L].salto = -1;

    // resolver el caso posiblemente llamando a otras funciones
    Necronomicon necronomicon(code);

    // escribir la solución
    necronomicon.solucion();
    return true;
    */
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
