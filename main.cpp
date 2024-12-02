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
  Grid walls; // Vector de booleanos
  int fil;           // Primer entero
  int col;          // Segundo entero

  ReadData() : fil(-1), col(-1) {}
  // Constructor opcional
  ReadData(const Grid &pWalls, int pFil, int pCol)
      :  walls(pWalls), fil(pFil), col(pCol) {}
};

ReadData readFiles(string nameFile) {
  // matrixint *grafo = new matrixint();
  ReadData data;
  string aux;
  ifstream fichero(nameFile, ifstream::in);
  if (not fichero.fail()) {
    // cout << "Entra dentro del fichero." << endl;
    int nnodes, nfil, ncol, wall;
    // Leer el número de nodos
    fichero >> nfil >> ncol;
    nnodes = nfil * ncol;
    Grid grid(nfil, vector<pair<int, bool>>(ncol));

    int value = 0; // Valor inicial para los pares

    // Rellenar la matriz con valores consecutivos
    for (int i = 0; i < nfil; ++i) {
      for (int j = 0; j < ncol; ++j) {
        grid[i][j] = make_pair(value++, false); // Número e indicación si es par
      }
    }

    //vector<bool> walls(nnodes, true);
    // cout << "Nodos: " << nnodes << endl;
    // Leer y descartar la línea con la almohadilla (#)
    fichero >> aux; // Debería ser "#"
    // cout << "Se ignora: " << aux << endl;
    //  Inicializamos el grafo como una matriz de nxn llena de ceros
    //  grafo->resize(nnodes, vector<int>(nnodes, 0));
    while (!fichero.eof()) {
      fichero >> wall;
      pair<int, int> filcol = Reachable::calculateFilCol(wall, nfil, ncol);
      // Se puede mejorar mucho
      grid.at(filcol.first).at(filcol.second).second = true;
    }
    data.walls = grid;
    data.fil = nfil;
    data.col = ncol;
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
