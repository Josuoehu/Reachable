#include <algorithm>
#include <boost/circular_buffer.hpp>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "Reachable.h"

using namespace std;
using namespace boost;

MyGraph readFiles(string nameFile) {
  // matrixint *grafo = new matrixint();
  MyGraph grafo{};
  string aux;
  ifstream fichero(nameFile, ifstream::in);
  if (not fichero.fail()) {
    // cout << "Entra dentro del fichero." << endl;
    int nnodes, col, fil;
    // Leer el número de nodos
    fichero >> nnodes;
    // cout << "Nodos: " << nnodes << endl;
    grafo.setNumNodes(nnodes);
    // Leer y descartar la línea con la almohadilla (#)
    fichero >> aux; // Debería ser "#"
    // cout << "Se ignora: " << aux << endl;
    //  Inicializamos el grafo como una matriz de nxn llena de ceros
    //  grafo->resize(nnodes, vector<int>(nnodes, 0));
    while (!fichero.eof()) {
      fichero >> col >> fil;
      // grafo->at(col).at(fil) = 1;
      grafo.addEdge(col, fil);
    }
  }
  return grafo;
}

int main(int argc, char *argv[]) {
  Reachable reachable(true);
  // cerr << "Introduzca el nombre del fichero" << endl;
  string nomFichero, aux;
  if (argc <= 2) {
    if (argc == 1) {
      cerr << "Introduce the name of the file:" << endl;
      cin >> nomFichero;
    } else {
      nomFichero = argv[1];
    }
    MyGraph grafo = readFiles(nomFichero);
    int tamGrafo = grafo.getNumNodes();
    // Creo que esto no tiene mucho sentido aquí.
    reachable.setNumGrid(tamGrafo);
    if (tamGrafo != 0) {
      reachable.setGraph(grafo);
      int nodoInici = -1;
      cerr << "Introduce the number of the node between 0 and " << tamGrafo
           << endl;
      cin >> nodoInici;
      reachable.setPosObjetivo(nodoInici);
      // vector<int> reachability = grafo.bfs(nodoInici);
      reachable.bfs();
      reachable.printResult();
      // printVector(createIndices(tamGrafo), true);
      // printVector(reachability, false);
      // delete grafo;
    } else {
      cerr << "Graph could not be loaded." << endl;
    }
    return 0;
  } else {
    cerr << "The number of arguments are not correct, try again.";
    return 1;
  }
}
