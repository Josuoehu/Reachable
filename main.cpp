#include <iostream>
#include <vector>
#include <boost/circular_buffer.hpp>

using namespace std;
using namespace boost;

typedef vector<vector<int>> matrixint;

vector<int> bfs(const matrixint &adjmatrix, int numnodes, int orgnode);

vector<int> bfs(const matrixint &adjmatrix, int numnodes, int orgnode) {
    circular_buffer<int> cola;
    cola.push_back(orgnode);
    vector<int> reachable(numnodes);

    reachable.at(orgnode) = 1;
    while(!cola.empty()) {
       for(int i {0}; i < numnodes; i++) {
           if (adjmatrix.at(orgnode).at(i) == 1 && reachable.at(i) == 0) {
               reachable[i] = 1;
           }
       }
    }
    return reachable;
}

int main()
{

    return 0;
}
