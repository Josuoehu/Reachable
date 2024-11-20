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
  void _printVector(const vector<int> &v, bool isInd);
  vector<int> _createIndices(int size);

public:
  Reachable(bool pRecalcul, int pPosObj, int pNumGrid);
  Reachable(int pPosObj, int pNumGrid);
  Reachable(bool pRecalcul, int pPosObj, int pNumGrid,
            vector<int> &pReachableVec);

  void printResult();
  vector<int> bfs(const MyGraph &adjmatrix, int numnodes, int orgnode);
  MyGraph *readFiles(string nameFile);
};
