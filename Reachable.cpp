#include "Reachable.h"
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

Reachable::Reachable(bool pRecalcul) : _needRecalcul(pRecalcul) {}
Reachable::Reachable(bool pRecalcul, int pPosObj, int pNumGrid)
    : _needRecalcul{pRecalcul}, _posObjetivo{pPosObj}, _numGrid{pNumGrid} {}
Reachable::Reachable(int pPosObj, int pNumGrid)
    : Reachable{false, pPosObj, pNumGrid} {}
Reachable::Reachable(bool pRecalcul, int pPosObj, int pNumGrid,
                     vector<int> pReachableVec, MyGraph pGrafo)
    : _needRecalcul{pRecalcul}, _posObjetivo{pPosObj}, _numGrid{pNumGrid},
      _objReachableVector(move(pReachableVec)), _grafo(move(pGrafo)) {}

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

void Reachable::bfs(){
  _objReachableVector = _grafo.bfs(_posObjetivo);
}

void Reachable::printResult() {
  _printVector(_createIndices(_numGrid), true);
  _printVector(_objReachableVector, false);
}

int Reachable::getPosObjetivo() const{
  return _posObjetivo;
}

int Reachable::getNumGrid() const{
  return _numGrid;
}

bool Reachable::getNeedRecalcul() const{
  return _needRecalcul;
}

void Reachable::setGraph(const MyGraph &pGrafo){
  _grafo = pGrafo;
}

void Reachable::setNeedRecalcul(bool pRecalcul) {
  _needRecalcul = pRecalcul;
}

void Reachable::setPosObjetivo(int pPosObj) {
  _posObjetivo = pPosObj;
}

void Reachable::setNumGrid(int pNumGrid) {
  _numGrid = pNumGrid;
}