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
    material_black = 0;
    material_white = 0;
    num_pieces = 0;
    num_pieces_white = 0;
    num_pieces_black = 0;
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
        if (p.color == DARK) {
            num_pieces_black++;
            material_black += p.material;
        }
        else {
            num_pieces_white++;
            material_white += p.material;
        }
        num_pieces++;
        board[pos] = p;
        pos++;
    }
}

Position::Piece::Piece(char c) {
    identifier = c;
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
            material = 5;
            break;
        case 'n':
            type = KNIGHT;
            material = 3;
            break;
        case 'b':
            type = BISHOP;
            material = 3;
            break;
        case 'q':
            type = QUEEN;
            material = 9;
            break;
        case 'k':
            type = KING;
            material = 0;
            break;
        case 'p':
            type = PAWN;
            material = 1;
            break;
        default:
            type = NONE;
            material = 0;
            break;
    }
    
}

Position::Piece::Piece() {
    identifier = '.';
    type = NONE;
    color = -1;
    material = 0;
}

int Position::toIndex(std::string square) const {
    return toIndex(square[0], square[1]);
}

int Position::toIndex(char rank, char file) const {
    // 0, 0 is a8
    return ((rank - 'a') + ((8 - (file - '0')) * 8));

}
