// takes a position, generates a graph.
#include "graph.h"
#include "position.h"


Graph generateGraph(Position pos) {
    Graph output;

    for (auto & move : pos.legal_moves) {
        // output.insertVertex(move.from);
        // output.insertVertex(move.to);
        // output.insertEdge(move.from, move.to); // Directed Edge
    }

    return output;

}