#include <boost/circular_buffer.hpp>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;
using namespace boost;

typedef vector<vector<int>> matrixint;

void printVector(const vector<int> &v, bool isInd);
vector<int> bfs(const matrixint &adjmatrix, int numnodes, int orgnode);
matrixint *readFiles(string nameFile);
vector<int> createIndices(int size);

vector<int> createIndices(int size) {
  vector<int> indices(size);
  for (int i = 0; i < size; i++) {
    indices.at(i) = i;
  }
  return indices;
}

// Comment
vector<int> bfs(const matrixint &adjmatrix, int numnodes, int orgnode) {
  circular_buffer<int> cola(numnodes);
  cola.push_back(orgnode);
  vector<int> reachable(numnodes, 0);

  reachable.at(orgnode) = 1;
  while (!cola.empty()) {
    int actual = cola.front();
    cola.pop_front();
    for (int i{0}; i < numnodes; i++) {
      if ((adjmatrix.at(actual).at(i) == 1 || adjmatrix.at(i).at(actual)) &&
          reachable.at(i) == 0) {
        reachable[i] = 1;
        cola.push_back(i);
      }
    }
  }
  return reachable;
}

matrixint *readFiles(string nameFile) {
  matrixint *grafo = new matrixint();
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

void printVector(const vector<int> &v, bool isInd) {
  cout << "[";
  for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    // if (distance(it, v.end()) == 1) {
    cout << *it;
    if (it + 1 != v.end()) {
      if (!isInd) {
        if ((it - v.begin()) >= 99)
          cout << ",   ";
        else if ((it - v.begin()) >= 9) {
          cout << ",  ";
        } else {
          cout << ", ";
        }
      } else {
        cout << ", ";
      }
    }
  }
  cout << "]" << endl;
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
