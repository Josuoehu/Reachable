#include <vector>

using namespace std;

/**
 * @class MyGraph
 * @brief Implementation of a graph using a vector of vectors.
 */
class MyGraph {

private:
  vector<vector<int>> _adjmatrix;
  int _numNodes;

public:
  MyGraph(int pNumNodes);
  MyGraph(const vector<vector<int>> &pAdjmatrix);
  MyGraph();

  vector<int> bfs(int pOrgnode);
  void setNumNodes(int pNumNodes);
  int getNumNodes() const;
  bool isConnected(int pOrgnode, int pDestnode) const;
  void addEdge(int pOrgnode, int pDestnode);
  void addNode(int pOrgnode);
};
