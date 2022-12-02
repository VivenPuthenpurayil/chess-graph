#include "position.h"


Position::Position() {
    // Create position with default fen (starting position)
    evaluation = 0;
    build_("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

Position::Position(std::string fen) {
    evaluation = 0;
    build_(fen);
}

Position::Position(std::string fen, std::list<Position::Move> moves, float eval) {
    build_(fen);
    legal_moves = moves;
    evaluation = eval;
}
Position::Position(std::vector<std::string> csv_entry) {

    build_(csv_entry[0]);
    
    auto it = csv_entry.begin() + 1;
    // Second to last ele
    while (it != (csv_entry.rbegin() + 1).base())
    {
        legal_moves.push_back(Position::Move(*it++));
    }
    evaluation = std::stof(*it);
}

void Position::build_(std::string fen) {
    num_pieces = 0;
    board = std::vector<Piece>(64, Piece());
    int pos = 0;
    fen_ = fen;
    for(auto c : fen) {
        if (c == ' ') { // End of FEN string
            break;
        }
        else if (c == '/') {
            continue;
        }
        else if (isdigit(c)) {
            pos += (c - '0');
            continue;
        }
        Piece p(c);
        num_pieces++;
        board[pos] = p;
        pos++;
    }
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
            break;
        case 'n':
            type = KNIGHT;
            break;
        case 'b':
            type = BISHOP;
            break;
        case 'q':
            type = QUEEN;
            break;
        case 'k':
            type = KING;
            break;
        case 'p':
            type = PAWN;
            break;
        default:
            type = NONE;
            break;
    }
    
}

Position::Piece::Piece() {
    type = NONE;
    color = -1;
}

int Position::toIndex(std::string square) const {
    return toIndex(square[0], square[1]);
}

int Position::toIndex(char rank, char file) const {
    // 0, 0 is a8
    return ((rank - 'a') + ((8 - (file - '0')) * 8));

}
