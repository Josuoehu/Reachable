#include <vector>

using namespace std;

class MyGraph {

private:
  vector<vector<int>> _adjmatrix;
  int _numNodes;

public:
  MyGraph(int pNumNodes);
  MyGraph(const vector<vector<int>> &pAdjmatrix);
  MyGraph();

  vector<int> bfs(int pOrgnode);
};