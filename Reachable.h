#include <string>
#include <vector>

#include "MyGraph.h"

using namespace std;

typedef vector<vector<int>> matrixint;

class Reachable {
private:
  bool _needRecalcul;
  int _posObjetivo, _numGrid;
  vector<int> _objReachableVector;
  void _printVector(bool isInd);
  vector<int> _createIndices(int size);

public:
  void printResult();
  vector<int> bfs(const MyGraph &adjmatrix, int numnodes, int orgnode);
  MyGraph *readFiles(string nameFile);
};
