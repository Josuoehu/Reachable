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
  MyGraph _grafo;
  void _printVector(const vector<int> &v, bool isInd);
  vector<int> _createIndices(int size);

public:
  Reachable();
  Reachable(bool pRecalcul);
  Reachable(bool pRecalcul, int pPosObj, int pNumGrid);
  Reachable(int pPosObj, int pNumGrid);
  Reachable(bool pRecalcul, int pPosObj, int pNumGrid,
            vector<int> pReachableVec, MyGraph pGrafo);

  void setGraph(const MyGraph &pGrafo);
  MyGraph getGraph();
  void printResult();
  void bfs();
  MyGraph *readFiles(string nameFile);
  void setNeedRecalcul(bool pNeedRecalcul);
  void setPosObjetivo(int pPosObj);
  void setNumGrid(int pNumGrid);
  int getPosObjetivo() const;
  int getNumGrid() const;
  bool getNeedRecalcul() const;
  void addWall(int pNode1, int pNode2);
};
