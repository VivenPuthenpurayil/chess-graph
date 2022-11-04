#include <list>

class Graph {
public:
    void insertVertex(int v);
    void insertEdge(int v1, int v2);
    void removeVertex(int v);
    std::list<int> incidentEdges(int v);
    bool areAdjacent(int v1, int v2);

};