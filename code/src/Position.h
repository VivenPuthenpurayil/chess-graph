#include <string>
#include <list>
#include <vector>

#define LIGHT 1;
#define DARK 0;

class Position {

public:

    Position(); // Starting Position
    Position(std::string fen);

    class Move {
        public:
            Move(std::string from, std::string to) : from(from), to(to) {};
            std::string from;
            std::string to;
            
        private:
    };

    class Piece {
        public:
            Piece();
            Piece(char type);
            enum PieceType {NONE, PAWN, BISHOP, KNIGHT, ROOK, KING, QUEEN};
            PieceType type;
            bool color;
            
    };

    std::list<Move> legal_moves;
    std::vector<Piece> board; 

    int toIndex(char rank, char file);
    int toIndex(std::string square);

    
private:
    std::string fen_;
    
    

};