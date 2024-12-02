#include <string>
#include <utility>
#include <vector>

#include "MyGraph.h"

using namespace std;

typedef vector<vector<int>> matrixint;

class Reachable {
private:
  bool _needRecalcul;
  int _posObjetivo, _numGridFil, _numGridCol;
  vector<int> _objReachableVector;
  vector<bool> _walls;
  MyGraph _grafo;
  void _printVector(const vector<int> &v, bool isInd);
  vector<int> _createIndices(int size);
  pair<int, int> _calculateFilCol(int pNode);
  void _removeOrAddWall(int pNode, bool pIsRemoving);

public:
  Reachable();
  Reachable(bool pRecalcul);
  Reachable(bool pRecalcul, int pPosObj, int pNumGridFil, int pNumGridCol);
  Reachable(int pPosObj, int pNumGridFil, int pNumGridCol);
  Reachable(bool pRecalcul, int pPosObj, int pNumGridFil, int pNumGridCol,
            vector<int> pReachableVec, MyGraph pGrafo);

  void setGraph(const MyGraph &pGrafo);
  MyGraph getGraph();
  void printResult();
  void bfs();
  MyGraph *readFiles(string nameFile);
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
};
