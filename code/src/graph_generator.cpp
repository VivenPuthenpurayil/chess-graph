// takes a position, generates a graph.
#include "graph.h"
#include "position.h"


Graph generateGraph(Position pos) {
    // Support Graph
    Graph output(3);

    /**
    for (auto & move : pos.legal_moves) {
        // if 
        output.insertVertex(1);
        if (pos.board[pos.toIndex(move.to)].type != Position::Piece::NONE) {
            output.insertVertex(1);
            output.insertEdge(move.from, move.to); // Directed Edge
        }
        
        
    }
    */

    return output;

}