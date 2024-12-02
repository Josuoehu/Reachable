#include "Reachable.h"
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

using namespace std;

Reachable::Reachable(bool pRecalcul) : _needRecalcul(pRecalcul) {}
Reachable::Reachable(bool pRecalcul, int pPosObj, int pNumGridCol,
                     int pNumGridFil)
    : _needRecalcul{pRecalcul}, _posObjetivo{pPosObj}, _numGridFil{pNumGridFil},
      _numGridCol{pNumGridCol} {}
Reachable::Reachable(int pPosObj, int pNumGridFil, int pNumGridCol)
    : Reachable{false, pPosObj, pNumGridFil, pNumGridCol} {}
Reachable::Reachable(bool pRecalcul, int pPosObj, int pNumGridFil,
                     int pNumGridCol, vector<int> pReachableVec, MyGraph pGrafo)
    : _needRecalcul{pRecalcul}, _posObjetivo{pPosObj}, _numGridFil{pNumGridFil},
      _numGridCol{pNumGridCol}, _objReachableVector(move(pReachableVec)),
      _grafo(move(pGrafo)) {}

vector<int> Reachable::_createIndices(int size) {
  vector<int> indices(size);
  for (int i = 0; i < size; i++) {
    indices.at(i) = i;
  }
  return indices;
}

void Reachable::_printVector(const vector<int> &v, bool isInd) {
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

bool Reachable::isAWall(int pNode) { return _walls.at(pNode); }

void Reachable::bfs() { _objReachableVector = _grafo.bfs(_posObjetivo); }

void Reachable::printResult() {
  _printVector(_createIndices(_grafo.getNumNodes()), true);
  _printVector(_objReachableVector, false);
}

int Reachable::getPosObjetivo() const { return _posObjetivo; }

int Reachable::getNumGridCol() const { return _numGridCol; }

int Reachable::getNumGridFil() const { return _numGridFil; }

bool Reachable::getNeedRecalcul() const { return _needRecalcul; }

void Reachable::setGraph(const MyGraph &pGrafo) { _grafo = pGrafo; }

void Reachable::setNeedRecalcul(bool pRecalcul) { _needRecalcul = pRecalcul; }

void Reachable::setPosObjetivo(int pPosObj) { _posObjetivo = pPosObj; }

void Reachable::setNumGridCol(int pNumGridCol) { _numGridCol = pNumGridCol; }

void Reachable::setNumGridFil(int pNumGridFil) { _numGridFil = pNumGridFil; }

void Reachable::addWall(int pNode) { _removeOrAddWall(pNode, false); }

void Reachable::removeWall(int pNode) { _removeOrAddWall(pNode, true); }

bool Reachable::needRecalcul(int pNode, int pFilaNode, int pColNode) {}

void Reachable::_removeOrAddWall(int pNode, bool pIsRemoving) {
  if (_walls.at(pNode)) {
    pair<int, int> posicion = _calculateFilCol(pNode);
    // Arriba
    if (posicion.first != 0) {
      int nodeUp = pNode - _numGridCol;
      if (pIsRemoving) {
        _grafo.addEdge(pNode, nodeUp);
      } else {
        _grafo.deleteEdge(pNode, nodeUp);
      }
    }
    if (posicion.first != _numGridFil - 1) {
      int nodeDown = pNode + _numGridCol;
      if (pIsRemoving) {
        _grafo.addEdge(pNode, nodeDown);
      } else {
        _grafo.deleteEdge(pNode, nodeDown);
      }
    }
    if (posicion.second != 0) {
      int nodeLeft = pNode - _numGridFil;
      if (pIsRemoving) {
        _grafo.addEdge(pNode, nodeLeft);
      } else {
        _grafo.deleteEdge(pNode, nodeLeft);
      }
    }
    if (posicion.second != _numGridCol - 1) {
      int nodeRight = pNode + _numGridFil;
      if (pIsRemoving) {
        _grafo.addEdge(pNode, nodeRight);
      } else {
        _grafo.deleteEdge(pNode, nodeRight);
      }
    }
    _walls.at(pNode) = false;
  } else {
    if (pIsRemoving) {
      cerr << "The wall did not exist." << endl;
    } else {
      cerr << "The wall already exists." << endl;
    }
  }
}

pair<int, int> Reachable::_calculateFilCol(int pNode) {
  int fil{-1}, col{-1}, vertMov{-1}, horzMov{-1};
  fil = pNode / _numGridCol;
  col = pNode % _numGridFil;
  return make_pair(fil, col);
}
