// takes a position, generates a graph.
#include "graph.h"
#include "position.h"



Graph generateSupport(Position pos) {
    Graph output(64);

    for (auto & move : pos.legal_moves) {
        int f = pos.toIndex(move.from);
        int t = pos.toIndex(move.to);

        if (pos.board[t].type != Position::Piece::NONE && (pos.board[t].color == pos.board[f].color)) {
            output.insertEdge(f, t); // Directed Edge
        }
        
    }
    
    return output;

}

Graph generateSupport(Position pos, bool color) {

    // We might want to store a mapping 
    // Support Graph

    // All graphs size of whole board for now, we can change it later
    Graph output(64);

    for (auto & move : pos.legal_moves) {
        int f = pos.toIndex(move.from);
        int t = pos.toIndex(move.to);

        if (pos.board[t].type != Position::Piece::NONE && (pos.board[t].color == color && pos.board[f].color == color)) {
            output.insertEdge(f, t); // Directed Edge
        }
        
    }
    
    return output;
}

Graph generateAttack(Position pos) {
    Graph output(64);

    for (auto & move : pos.legal_moves) {
        int f = pos.toIndex(move.from);
        int t = pos.toIndex(move.to);

        if (pos.board[t].type != Position::Piece::NONE && (pos.board[t].color != pos.board[f].color)) {
            output.insertEdge(f, t); // Directed Edge
        }
        
    }
    
    return output;
}
Graph generateAttack(Position pos, bool color) {

    Graph output(64);

    for (auto & move : pos.legal_moves) {
        int f = pos.toIndex(move.from);
        int t = pos.toIndex(move.to);

        if (pos.board[t].type != Position::Piece::NONE && (pos.board[t].color != pos.board[f].color) && (pos.board[t].color == color)) {
            output.insertEdge(f, t); // Directed Edge
        }
        
    }
    
    return output;
}
