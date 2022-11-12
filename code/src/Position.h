#include <string>
#include <list>
#include <vector>

#define LIGHT 1
#define DARK 0

class Position {

public:

    Position(); // Starting Position
    Position(std::string fen);

    class Move {
        public:
            Move(const std::string from, const std::string to) : from(from), to(to) {};
            const std::string from;
            const std::string to;
            
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

    int toIndex(char rank, char file) const;
    int toIndex(std::string square) const;

private:
    std::string fen_;
    void build_(std::string fen);
    
};