#pragma once

#include <string>
#include <list>
#include <vector>
#include "utils.h"

#define LIGHT 1
#define DARK 0

class Position {

public:
    /**
      * Creates a position object using the standard starting chess position.
      */
    Position(); // Starting Position
    /**
      * Creates a position object using the user specified FEN string.
      * @param fen The FEN string of the position.
      */
    Position(std::string fen);
    /**
      * Creates a position object using a vector of std::strings read in the format specified in our csv input.
      * @param data The std::vector of std::strings in the expected order.
      */
    Position(std::vector<std::string> data);

    
    /**
      * Represents a move from one square to another.
      */
    class Move {
        public:
            /**
             * Creates a move from a string in the format "a4c3" meaning, a4 to c3.
             */
            Move(const std::string move) : from(move.substr(0, 2)), to(move.substr(2, 2)) {};
            /**
             * Creates a move from two substrings, from and to.
            */
            Move(const std::string from, const std::string to) : from(from), to(to) {};

            std::string from;
            std::string to;
            
        private:
    };

    /**
      * Creates a position object using a fen string, a vector of moves, and an evaluation.
      */
    Position(std::string fen, std::list<Move> moves, float evaluation);

    /**
      * Represents a piece with a color but not position.
      */
    class Piece {
        public:
            Piece();
            Piece(char type);
            enum PieceType {NONE, PAWN, BISHOP, KNIGHT, ROOK, KING, QUEEN};
            PieceType type;
            bool color;
            
    };

    /**
      * The evaluation of the position from white's pov calculated by stockfish.
      */
    float evaluation;

    /**
      *
      */
    std::list<Move> legal_moves;
    std::vector<Piece> board; 
    int num_pieces;
    int num_pieces_white;
    int num_pieces_black;

    int toIndex(char rank, char file) const;
    int toIndex(std::string square) const;

private:
    std::string fen_;
    void build_(std::string fen);
    
};
