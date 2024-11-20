#include <boost/circular_buffer.hpp>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "MyGraph.h"
#include "Reachable.h"

using namespace std;
using namespace boost;

Reachable *readFiles(string nameFile) {
  // matrixint *grafo = new matrixint();
  MyGraph *grafo = new MyGraph();
  string aux;
  ifstream fichero(nameFile, ifstream::in);
  if (not fichero.fail()) {
    cout << "Entra dentro del fichero." << endl;
    int nnodes, col, fil;
    // Leer el número de nodos
    fichero >> nnodes;
    cout << "Nodos: " << nnodes << endl;

    // Leer y descartar la línea con la almohadilla (#)
    fichero >> aux; // Debería ser "#"
    cout << "Se ignora: " << aux << endl;

    // Inicializamos el grafo como una matriz de nxn llena de ceros
    grafo->resize(nnodes, vector<int>(nnodes, 0));
    while (!fichero.eof()) {
      fichero >> col >> fil;
      grafo->at(col).at(fil) = 1;
    }
  }
  return grafo;
}

int main(int argc, char *argv[]) {
  // cerr << "Introduzca el nombre del fichero" << endl;
  string nomFichero, aux;
  if (argc <= 2) {
    if (argc == 1) {
      cerr << "Introduce the name of the file:" << endl;
      cin >> nomFichero;
    } else {
      nomFichero = argv[1];
    }
    matrixint *grafo = readFiles(nomFichero);
    if (grafo) {
      int nodoInici = -1;
      cerr << "Introduce el numero del nodo entre 0 y " << grafo->size() - 1
           << endl;
      cin >> nodoInici;
      int tamGrafo = grafo->size();
      vector<int> reachability = bfs(*grafo, tamGrafo, nodoInici);
      printVector(createIndices(tamGrafo), true);
      printVector(reachability, false);
      delete grafo;
    }
    return 0;
  } else {
    cerr << "The number of arguments are not correct, try again.";
    return 1;
  }
}
