#include <string>
#include <utility>
#include <vector>

#include "MyGraph.h"

using namespace std;

typedef vector<vector<pair<int, bool>>> Grid;

class Reachable {
private:
  bool _needRecalcul;
  int _posObjetivo, _numGridFil, _numGridCol;
  vector<int> _objReachableVector;
  vector<bool> _walls;
  Grid _grid;
  void _printVector(const vector<int> &v, bool isInd);
  vector<int> _createIndices(int size);
  void _removeOrAddWall(int pNode, bool pIsRemoving);

public:
  Reachable();
  Reachable(bool pRecalcul);
  Reachable(bool pRecalcul, int pPosObj, int pNumGridFil, int pNumGridCol);
  Reachable(int pPosObj, int pNumGridFil, int pNumGridCol);
  Reachable(bool pRecalcul, int pPosObj, int pNumGridFil, int pNumGridCol,
            vector<int> pReachableVec, Grid pGrid);

  static pair<int, int> calculateFilCol(int pNode, int pFil, int pCol);
  void printResult();
  void bfs();
  vector<int> bfs(int pOrgnode);
  void setNeedRecalcul(bool pNeedRecalcul);
  void setPosObjetivo(int pPosObj);
  void setNumGridFil(int pNumGridFil);
  void setNumGridCol(int pNumGridCol);
  int getPosObjetivo() const;
  int getNumGridCol() const;
  int getNumGridFil() const;
  bool getNeedRecalcul() const;
  void addWall(int pNode);
  void removeWall(int pNode);
  bool isAWall(int pNode);
  void setWalls(const vector<bool> &pWalls);
  bool needRecalcul(int pNode, int pFilaNode, int pColNode);
  static vector<int> createIndices(int size);
};
