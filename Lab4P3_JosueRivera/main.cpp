#include <iostream>
#include<cstring>
#include <vector>
using namespace std;
vector<int> posicionesRepetidas;
void agregarPalabra(vector<char*> &palabras, char *nuevaPalabra) {
    palabras.push_back(nuevaPalabra);
}

bool noEsRepetida(int num) {
    for (int posNum = 0; posNum < posicionesRepetidas.size(); posNum++) {
        if(num == posicionesRepetidas.at(posNum)) {
            return false;
        }
    }
    return true;
}

void contarFrecuencias(const vector<char*> &palabras, vector<int> &frecuencias) {
    int contadorFrecuencia = 1;
    cout << "Conteo de palabras: " << endl;
    for (int posicion = 0; posicion < palabras.size(); posicion++) {
        for (int posicionAuxiliar = 0; posicionAuxiliar < palabras.size(); posicionAuxiliar++) {
            if(noEsRepetida(posicion) && strstr(palabras[posicion], palabras[posicionAuxiliar]) && posicion != posicionAuxiliar && strlen(palabras[posicion]) == strlen(palabras[posicionAuxiliar])) { //identifica si una palabra se repite, utilizando el mismo vector, despues, se añade la cantidad de repeticion a las frecuencias, y guardo las posiciones de las palabras repetidas.
                contadorFrecuencia++;
                posicionesRepetidas.push_back(posicionAuxiliar);
            }
        }
        frecuencias.push_back(contadorFrecuencia);
        contadorFrecuencia = 1;
    }
}
void frecuenciaAscendente(vector<char*> &palabras, vector<int> &frecuencias) {
    int ordenamiento = 0;
    int posiAlto = 0;
    for (int posiTemp = 0; posiTemp < frecuencias.size(); posiTemp++) {
        for (int posicionFrecuency = 0; posicionFrecuency < frecuencias.size(); posicionFrecuency++) {
            if(ordenamiento < frecuencias.at(posicionFrecuency)) {
                ordenamiento = frecuencias.at(posicionFrecuency);
                posiAlto = posicionFrecuency;
            }
        }
        if(noEsRepetida(posiAlto)) {
            cout << palabras[posiAlto] << ": " << frecuencias[posiAlto] << endl;
        }
        frecuencias.at(posiAlto) = -1;
        ordenamiento = 0;
    }
}

void frecuenciaDescendente(vector<char*> &palabras, vector<int> &frecuencias) {
    int ordenamiento = 1000000000;
    int posiBajo = 0;
    for (int posiTemp = 0; posiTemp < frecuencias.size(); posiTemp++) {
        for (int posicionFrecuency = 0; posicionFrecuency < frecuencias.size(); posicionFrecuency++) {
            if(ordenamiento > frecuencias.at(posicionFrecuency)) {
                ordenamiento = frecuencias.at(posicionFrecuency);
                posiBajo = posicionFrecuency;
            }
        }
        if(noEsRepetida(posiBajo)) {
            cout << palabras[posiBajo] << ": " << frecuencias[posiBajo] << endl;
        }
        frecuencias.at(posiBajo) = 1000000000;
        ordenamiento = 1000000000;
    }
}

void alfabeticoAscendente(vector<char*> &palabras, vector<int> &frecuencias) {
    char abecedario[] = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"; //RECORRE EL ABECEDARIO SI LA LETRA DEL ABECEDARIO COINCIDE CON LA PRIMERA LETRA DE UNA PALABRA EN EL VECTOR SE IMPRIME (noEsRepetida es un metodo que permite no imprimir palabras que ya estan repetidas)
    for (int posLetra = 0; posLetra < strlen(abecedario); posLetra++) {
        for (int posWord = 0; posWord < palabras.size(); posWord++) {
            if(abecedario[posLetra] == palabras[posWord][0] && noEsRepetida(posWord)) {
                cout << palabras[posWord] << ": " << frecuencias[posWord] << endl;
            }
        }
    }
}

void alfabeticoDescendente(vector<char*> &palabras, vector<int> &frecuencias) {
    char abecedario[] = "aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ";
    for (int posLetra = strlen(abecedario)-1; posLetra >= 0; posLetra--) {
        for (int posWord = 0; posWord < palabras.size(); posWord++) {
            if(abecedario[posLetra] == palabras[posWord][0] && noEsRepetida(posWord)) {
                cout << palabras[posWord] << ": " << frecuencias[posWord] << endl;
            }
        }
    }
}

void ordenarResultados(vector<char*> &palabras, vector<int> &frecuencias, int opcionOrden) {
    if(opcionOrden) {
        contarFrecuencias(palabras, frecuencias);
    }
    switch(opcionOrden) {
        case 0:
            cout << "Saliendo del programa..." << endl;
            break;
        case 1:
            frecuenciaAscendente(palabras, frecuencias);
            break;
        case 2:
            frecuenciaDescendente(palabras, frecuencias);
            break;
        case 3:
            alfabeticoAscendente(palabras, frecuencias);
            break;
        case 4:
            alfabeticoDescendente(palabras, frecuencias);
            break;
        default:
            cout << "Esa no es una opción válida..." << endl;
    }
}

void liberarMemoria(vector<char*> &palabras) {
    palabras.clear();
}

void menu() {
    char *oracion = new char[80];
    int inicioPalabra = 0;
    int numeroLetras = 0;
    vector<char*> palabras;
    vector<int> frecuencias;
    int opcion;
    cout << "Ingrese una línea de texto: ";
    cin.getline(oracion, 80, '\n');
    for (int posLetraOracion = 0; posLetraOracion < strlen(oracion) ; posLetraOracion++) {
        char c = oracion[posLetraOracion];
        if(c != ' ' && posLetraOracion < strlen(oracion)-1) {
            numeroLetras++;
        } else {
            if(posLetraOracion == strlen(oracion)-1) {
                posLetraOracion++;
            }
            char *palabra = new char[numeroLetras];
            int posicionLetra = 0;
            for (int letra = inicioPalabra; letra < posLetraOracion; letra++) {
                palabra[posicionLetra] = oracion[letra];
                posicionLetra++;
            }
            agregarPalabra(palabras, palabra);
            numeroLetras = 0;
            inicioPalabra = posLetraOracion+1;
        }
    }
    do {
        cout << "0. Salir" << endl;
        cout << "1. Frecuencia Ascendente" << endl;
        cout << "2. Frecuencia Descendente" << endl;
        cout << "3. Orden Alfabetico Ascendente" << endl;
        cout << "4. Orden Alfabetico Descendente" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        ordenarResultados(palabras, frecuencias, opcion);
        //liberarMemoria(palabras);
        frecuencias.clear();
    } while(opcion != 0);
    liberarMemoria(palabras);
    delete[] oracion;
}

int main() {
    menu();
}
