#include "MyGraph.h"
#include <boost/circular_buffer.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace boost;

MyGraph::MyGraph(int pNumNodes) : _numNodes{pNumNodes}, _adjmatrix(pNumNodes) {}

MyGraph::MyGraph(const vector<vector<int>> &pAdjmatrix)
    : _numNodes(pAdjmatrix.size()), _adjmatrix{pAdjmatrix} {}

MyGraph::MyGraph() : _numNodes(0), _adjmatrix() {}

vector<int> MyGraph::bfs(int pOrgnode) {
  circular_buffer<int> cola(_numNodes);
  cola.push_back(pOrgnode);
  vector<int> reachable(_numNodes, 0);

  reachable.at(pOrgnode) = 1;
  while (!cola.empty()) {
    int actual = cola.front();
    cola.pop_front();
    for (int i{0}; i < _numNodes; i++) {
      if ((_adjmatrix.at(actual).at(i) == 1 || _adjmatrix.at(i).at(actual)) &&
          reachable.at(i) == 0) {
        reachable[i] = 1;
        cola.push_back(i);
      }
    }
  }
  return reachable;
}

void MyGraph::addEdge(int pOrgnode, int pDestnode) {
  if (pOrgnode == pDestnode) {
    throw runtime_error("You've entered the same node twice.");
  } else if (pOrgnode < pDestnode) {
    _adjmatrix.at(pOrgnode).at(pDestnode) = 1;
  } else {
    _adjmatrix.at(pDestnode).at(pOrgnode) = 1;
  }
}

void MyGraph::setNumNodes(int pNumNodes) {
  _numNodes = pNumNodes;
  _adjmatrix.resize(pNumNodes, vector<int>(pNumNodes, 0));
}

int MyGraph::getNumNodes() const {
  int tamGraph = _adjmatrix.size();
  if (tamGraph != _numNodes) {
    return tamGraph;
  } else {
    return _adjmatrix.size();
  }
}

bool MyGraph::isConnected(int pOrgnode, int pDestnode) const {
  return _adjmatrix.at(pOrgnode).at(pDestnode);
}

// No se si tiene mucho sentido esto.
void MyGraph::addNode(int pOrgnode) {
  for (int i{0}; i < _numNodes; i++) {
    _adjmatrix.at(pOrgnode).push_back(0);
  }
  _adjmatrix.push_back(vector<int>(_numNodes + 1, 0));
}
