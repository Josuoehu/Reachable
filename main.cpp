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


struct ReadData {
  MyGraph myGraph;        // Instancia de tu clase MyGraph
  std::vector<bool> walls; // Vector de booleanos
  int fil;           // Primer entero
  int col;          // Segundo entero

  ReadData() : fil(-1), col(-1) {}
  // Constructor opcional
  ReadData(const MyGraph& graph, const std::vector<bool>& flagsVec, int int1, int int2)
      : myGraph(graph), walls(flagsVec), fil(int1), col(int2) {}
};

ReadData readFiles(string nameFile) {
  // matrixint *grafo = new matrixint();
  ReadData data;
  MyGraph grafo{};
  string aux;
  ifstream fichero(nameFile, ifstream::in);
  if (not fichero.fail()) {
    // cout << "Entra dentro del fichero." << endl;
    int nnodes, col, fil, nfil, ncol;
    // Leer el número de nodos
    fichero >> nfil >> ncol;
    nnodes = nfil * ncol;
    vector<bool> walls(nnodes, true);
    // cout << "Nodos: " << nnodes << endl;
    grafo.setNumNodes(nnodes);
    // Leer y descartar la línea con la almohadilla (#)
    fichero >> aux; // Debería ser "#"
    // cout << "Se ignora: " << aux << endl;
    //  Inicializamos el grafo como una matriz de nxn llena de ceros
    //  grafo->resize(nnodes, vector<int>(nnodes, 0));
    while (!fichero.eof()) {
      fichero >> col >> fil;
      // Se puede mejorar mucho
      walls.at(col) = false;
      walls.at(fil) = false;
      // grafo->at(col).at(fil) = 1;
      grafo.addEdge(col, fil);
    }
    data.myGraph = grafo;
    data.walls = walls;
    data.fil = fil;
    data.col = col;
  }
  return data;
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
    ReadData fileData = readFiles(nomFichero);
    MyGraph grafo = fileData.myGraph;
    vector<bool> walls = fileData.walls;
    int tamGrafo = grafo.getNumNodes();
    // Creo que esto no tiene mucho sentido aquí.
    reachable.setNumGridFil(fileData.fil);
    reachable.setNumGridCol(fileData.col);
    reachable.setWalls(walls);
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
