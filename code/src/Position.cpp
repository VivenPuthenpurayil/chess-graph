#include <position.h>


Position::Position() {
    // Create position with default fen (starting position)
    Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Position::Piece::Piece(char c) {
    if (islower(c)) {
        color = DARK;
    }
    else {
        color = LIGHT;
    }

    c = tolower(c);

    switch (c) {
        case 'r':
            type = ROOK;
        case 'n':
            type = KNIGHT;
        case 'b':
            type = BISHOP;
        case 'q':
            type = QUEEN;
        case 'k':
            type = KING;
        case 'p':
            type = PAWN;
        default:
            type = NONE;
    }
    
}

Position::Piece::Piece() {
    type = NONE;
    color = -1;

}

Position::Position(std::string fen) {
    board = std::vector<Piece>(64, Piece());
    int pos = 0;
    for(auto c : fen) {
        board[pos] = Piece(c);
    }

}

int Position::toIndex(std::string square) {
    return toIndex(square[0], square[1]);
}

int Position::toIndex(char rank, char file) {
    // 0, 0 is a1
    return ((int) (rank - 'a') * 8 + (int) file);

}