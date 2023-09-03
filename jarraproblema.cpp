#include <iostream>
#include <set>
#include <vector>
#include <queue>

using namespace std;
/*
////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////SI FUNCIONA///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
*/
struct EstadoJarra {
    int jarraA;
    int jarraB;
    vector<string> acciones;

    EstadoJarra(int a, int b) : jarraA(a), jarraB(b) {}

    bool operator==(const EstadoJarra& otro) const {
        return jarraA == otro.jarraA && jarraB == otro.jarraB;
    }

    bool operator<(const EstadoJarra& otro) const {
        if (jarraA != otro.jarraA) return jarraA < otro.jarraA;
        return jarraB < otro.jarraB;
    }
};

// Función para resolver el problema de las jarras
bool resolverProblemaJarras(int capacidadJarraA, int capacidadJarraB, int objetivo, EstadoJarra& estadoActual, set<EstadoJarra>& visitados) {
    if (estadoActual.jarraA == objetivo || estadoActual.jarraB == objetivo) {
        return true;
    }

    visitados.insert(estadoActual);

    // Llenar la jarra A
    if (estadoActual.jarraA < capacidadJarraA) {
        EstadoJarra nuevoEstado(capacidadJarraA, estadoActual.jarraB);
        if (visitados.find(nuevoEstado) == visitados.end()) {
            nuevoEstado.acciones = estadoActual.acciones;
            nuevoEstado.acciones.push_back("Llenar A");
            if (resolverProblemaJarras(capacidadJarraA, capacidadJarraB, objetivo, nuevoEstado, visitados)) {
                estadoActual = nuevoEstado;
                return true;
            }
        }
    }

    // Llenar la jarra B
    if (estadoActual.jarraB < capacidadJarraB) {
        EstadoJarra nuevoEstado(estadoActual.jarraA, capacidadJarraB);
        if (visitados.find(nuevoEstado) == visitados.end()) {
            nuevoEstado.acciones = estadoActual.acciones;
            nuevoEstado.acciones.push_back("Llenar B");
            if (resolverProblemaJarras(capacidadJarraA, capacidadJarraB, objetivo, nuevoEstado, visitados)) {
                estadoActual = nuevoEstado;
                return true;
            }
        }
    }

    // Vaciar la jarra A
    if (estadoActual.jarraA > 0) {
        EstadoJarra nuevoEstado(0, estadoActual.jarraB);
        if (visitados.find(nuevoEstado) == visitados.end()) {
            nuevoEstado.acciones = estadoActual.acciones;
            nuevoEstado.acciones.push_back("Vaciar A");
            if (resolverProblemaJarras(capacidadJarraA, capacidadJarraB, objetivo, nuevoEstado, visitados)) {
                estadoActual = nuevoEstado;
                return true;
            }
        }
    }

    // Vaciar la jarra B
    if (estadoActual.jarraB > 0) {
        EstadoJarra nuevoEstado(estadoActual.jarraA, 0);
        if (visitados.find(nuevoEstado) == visitados.end()) {
            nuevoEstado.acciones = estadoActual.acciones;
            nuevoEstado.acciones.push_back("Vaciar B");
            if (resolverProblemaJarras(capacidadJarraA, capacidadJarraB, objetivo, nuevoEstado, visitados)) {
                estadoActual = nuevoEstado;
                return true;
            }
        }
    }

    // Verter agua de A a B
    if (estadoActual.jarraA > 0 && estadoActual.jarraB < capacidadJarraB) {
        int aguaVertida = min(estadoActual.jarraA, capacidadJarraB - estadoActual.jarraB);
        EstadoJarra nuevoEstado(estadoActual.jarraA - aguaVertida, estadoActual.jarraB + aguaVertida);
        if (visitados.find(nuevoEstado) == visitados.end()) {
            nuevoEstado.acciones = estadoActual.acciones;
            nuevoEstado.acciones.push_back("Verter A a B");
            if (resolverProblemaJarras(capacidadJarraA, capacidadJarraB, objetivo, nuevoEstado, visitados)) {
                estadoActual = nuevoEstado;
                return true;
            }
        }
    }

    // Verter agua de B a A
    if (estadoActual.jarraB > 0 && estadoActual.jarraA < capacidadJarraA) {
        int aguaVertida = min(estadoActual.jarraB, capacidadJarraA - estadoActual.jarraA);
        EstadoJarra nuevoEstado(estadoActual.jarraA + aguaVertida, estadoActual.jarraB - aguaVertida);
        if (visitados.find(nuevoEstado) == visitados.end()) {
            nuevoEstado.acciones = estadoActual.acciones;
            nuevoEstado.acciones.push_back("Verter B a A");
            if (resolverProblemaJarras(capacidadJarraA, capacidadJarraB, objetivo, nuevoEstado, visitados)) {
                estadoActual = nuevoEstado;
                return true;
            }
        }
    }

    return false;
}

int main() {
    int capacidadJarraA, capacidadJarraB, objetivo;

    cout << "Capacidad de la jarra A: ";
    cin >> capacidadJarraA;

    cout << "Capacidad de la jarra B: ";
    cin >> capacidadJarraB;

    cout << "Objetivo deseado: ";
    cin >> objetivo;

    EstadoJarra estadoInicial(0, 0);
    set<EstadoJarra> visitados;

    if (resolverProblemaJarras(capacidadJarraA, capacidadJarraB, objetivo, estadoInicial, visitados)) {
        cout << "Solución encontrada:" << endl;
        for (const string& accion : estadoInicial.acciones) {
            cout << accion << endl;
        }
    } else {
        cout << "No se ha encontrado solucion" << endl;
    }

    return 0;
}
