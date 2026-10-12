#include <iostream>
using namespace std;

const int CAPACIDAD = 10;  //Tamaño fijo de los arreglos (memoria simulada)
const int NULO = -1;  // Representa "Puntero nulo" usando -1

class Lista_Cursores {
    private:
    int data[CAPACIDAD];  // Arreglo paralelo: valores
    int next [CAPACIDAD]; // Arreglo paralelo: curso al siguiente
    int head; // Cursor al primer nodo de la lista
    int free_; // Cursor al primer espacio libre

public:
    // Constructor: Inicializa todos los espacios como libres,
    // enlazados entre si (0 -> 1 -> 2 -> ... -> CAPACIDAD-1 -> NULO)
    Lista_Cursores(){
        for (int i = 0; i < CAPACIDAD - 1; i++){
            next[i] = i + 1;
        }
        next[CAPACIDAD - 1] = NULO;
        free_ = 0;   // El primer librre es la posicion 0
        head = NULO; // La lista empieza vacia
    }

    // Toma un espacio  libre del arreglo (equivale a "new" / "malloc")
    int asignarNodo(){
        if (free_ == NULO){
            cout << " ¡Sin espacio disponible (arreglo lleno)\n";
            return NULO;
        }
        int nodo = free_;
        free_ = next[free_];
        return nodo;
    }
    // Devuelve un espacio al "monton" de libres (Equivalente a "Delete" / "free")
    void liberarNodo(int idx){
        next[idx] = free_;  // El nodo liberado apunta al antiguo libre
        free_ = idx; // ahora el primer libre es este nodo
    }

    // Insectar un valor al INICIO de la lista
    void InsectarInicio(int valor){
        int nuevo = asignarNodo();
        if (nuevo == NULO) return;

        data [nuevo] = valor;
        data [nuevo] = head;  // El nuevo nodo apunta al antiguo head
        head = nuevo;  // El head ahora es el nuevo nodo
    }

    // Elimina la PRIMERA ocurrencia del valor en la lista
    void eliminarValor(int valor){
        int actual = head;
        int anterior = NULO;

        while (actual != NULO && data [actual] != valor){
            anterior = actual;
            actual = next[actual];

        }
         if (actual == NULO){
            cout << "Valor" << valor << "No encontrado.\n";
            return;
        }
        // Desconectar el nodo "actual" de la lista
        if ( anterior == NULO){
            head = next[actual];  // era el primer nodo
        } else {
            next[anterior] =  next[actual];   // saltar el nodo eliminado
        }

        liberarNodo(actual); // regresar el espacio a la lista de libres
    }

    // Recorre e imprime la lista siguiendo los cursores desde head
    void imprimir(){
        int actual = head;
        cout << "Lista:";
        if (actual == NULO) cout << "(Vacia)";
        while (actual != NULO){
            cout << data[actual];
            if (next[actual] != NULO) cout << "->";
            actual = next[actual];

        }
        cout << "\n";
    }
    // Muestra el estado interno de los arreglos paralelos (para depurar)
    // y comparar con la traza hecha a mano / con la AI)
    void mostrarEstadoInterno(){
        cout << "\n idx : " ;
        for (int i = 0; i < CAPACIDAD; i++) cout << i << "  ";
        cout << "\n data : " ;
        for (int i = 0; i < CAPACIDAD; i++) cout << data[i] << "  ";
        cout << "\n next : " ;
        for (int i = 0; i < CAPACIDAD; i++) cout << next[i] << "  ";
        cout << "\n head =  " << head << " | free = " << free_ << "\n\n";

    }
};

int main(){
    Lista_Cursores lista;

    cout << "== Insertando 30, 20, 10 al inicio ==\n";
    lista.InsectarInicio(30);
    lista.InsectarInicio(20);
    lista.InsectarInicio(10);
    lista.imprimir();
    lista.mostrarEstadoInterno();

    cout << "== Eliminando el valor 20 ==\n";
    lista.eliminarValor(20);
    lista.imprimir();
    lista.mostrarEstadoInterno();

    cout << "== Insertando 40 al inicio (reutiliza el espacio liberado) ==\n";
    lista.InsectarInicio(40);
    lista.imprimir();
    lista.mostrarEstadoInterno();

    return 0;
}