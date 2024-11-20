#include "MyGraph.h"
#include <boost/circular_buffer.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace boost;

/**
 * @class MyGraph
 * @brief Implementation of a graph using a vector of vectors.
 */

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
