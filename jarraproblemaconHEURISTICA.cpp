#include <iostream>
#include <set>
#include <vector>
#include <queue>

using namespace std;

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

    int calcularHeuristica(int objetivo) const {
        int diferenciaA = abs(jarraA - objetivo);
        int diferenciaB = abs(jarraB - objetivo);
        return diferenciaA + diferenciaB;
    }
};

struct ComparadorCosto {
    int objetivo;

    ComparadorCosto(int objetivo) : objetivo(objetivo) {}

    bool operator()(const EstadoJarra& a, const EstadoJarra& b) const {
        return a.acciones.size() + a.calcularHeuristica(objetivo) > b.acciones.size() + b.calcularHeuristica(objetivo);
    }
};

bool resolverProblemaJarras(int capacidadJarraA, int capacidadJarraB, int objetivo, EstadoJarra& estadoActual) {
    ComparadorCosto comparador(objetivo);
    priority_queue<EstadoJarra, vector<EstadoJarra>, ComparadorCosto> colaPrioridad(comparador);
    set<EstadoJarra> visitados;

    colaPrioridad.push(estadoActual);

    while (!colaPrioridad.empty()) {
        EstadoJarra actual = colaPrioridad.top();
        colaPrioridad.pop();

        if (actual.jarraA == objetivo || actual.jarraB == objetivo) {
            estadoActual = actual;
            return true;
        }

        visitados.insert(actual);

        if (actual.jarraA < capacidadJarraA) {
            EstadoJarra nuevoEstado(capacidadJarraA, actual.jarraB);
            if (visitados.find(nuevoEstado) == visitados.end()) {
                nuevoEstado.acciones = actual.acciones;
                nuevoEstado.acciones.push_back("Llenar A");
                colaPrioridad.push(nuevoEstado);
            }
        }

        if (actual.jarraB < capacidadJarraB) {
            EstadoJarra nuevoEstado(actual.jarraA, capacidadJarraB);
            if (visitados.find(nuevoEstado) == visitados.end()) {
                nuevoEstado.acciones = actual.acciones;
                nuevoEstado.acciones.push_back("Llenar B");
                colaPrioridad.push(nuevoEstado);
            }
        }

        if (actual.jarraA > 0) {
            EstadoJarra nuevoEstado(0, actual.jarraB);
            if (visitados.find(nuevoEstado) == visitados.end()) {
                nuevoEstado.acciones = actual.acciones;
                nuevoEstado.acciones.push_back("Vaciar A");
                colaPrioridad.push(nuevoEstado);
            }
        }

        if (actual.jarraB > 0) {
            EstadoJarra nuevoEstado(actual.jarraA, 0);
            if (visitados.find(nuevoEstado) == visitados.end()) {
                nuevoEstado.acciones = actual.acciones;
                nuevoEstado.acciones.push_back("Vaciar B");
                colaPrioridad.push(nuevoEstado);
            }
        }

        if (actual.jarraA > 0 && actual.jarraB < capacidadJarraB) {
            int aguaVertida = min(actual.jarraA, capacidadJarraB - actual.jarraB);
            EstadoJarra nuevoEstado(actual.jarraA - aguaVertida, actual.jarraB + aguaVertida);
            if (visitados.find(nuevoEstado) == visitados.end()) {
                nuevoEstado.acciones = actual.acciones;
                nuevoEstado.acciones.push_back("Verter A a B");
                colaPrioridad.push(nuevoEstado);
            }
        }

        if (actual.jarraB > 0 && actual.jarraA < capacidadJarraA) {
            int aguaVertida = min(actual.jarraB, capacidadJarraA - actual.jarraA);
            EstadoJarra nuevoEstado(actual.jarraA + aguaVertida, actual.jarraB - aguaVertida);
            if (visitados.find(nuevoEstado) == visitados.end()) {
                nuevoEstado.acciones = actual.acciones;
                nuevoEstado.acciones.push_back("Verter B a A");
                colaPrioridad.push(nuevoEstado);
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

    if (resolverProblemaJarras(capacidadJarraA, capacidadJarraB, objetivo, estadoInicial)) {
        cout << "Solución encontrada:" << endl;
        for (const string& accion : estadoInicial.acciones) {
            cout << accion << endl;
        }
    } else {
        cout << "No se ha encontrado solucion" << endl;
    }

    return 0;
}

