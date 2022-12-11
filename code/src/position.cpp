#include "position.h"


Position::Position() {
    // Create position with default fen (starting position)
    evaluation = 0;
    build_("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::vector<std::string> move_strings {"a1b1", "a1a2", "b1d2", "b1a3", "b1c3", "c1b2", "c1d2", "d1c1", "d1e1", "d1c2", "d1d2", "d1e2", "e1d1", "e1f1", "e1d2", "e1e2", "e1f2", "f1e2", "f1g2", "g1e2", "g1f3", "g1h3", "h1g1", "h1h2", "a2b3", "b2a3", "b2c3", "c2b3", "c2d3", "d2c3", "d2e3", "e2d3", "e2f3", "f2e3", "f2g3", "g2f3", "g2h3", "h2g3", "a7b6", "b7a6", "b7c6", "c7b6", "c7d6", "d7c6", "d7e6", "e7d6", "e7f6", "f7e6", "f7g6", "g7f6", "g7h6", "h7g6", "a8a7", "a8b8", "b8a6", "b8c6", "b8d7", "c8b7", "c8d7", "d8c7", "d8d7", "d8e7", "d8c8", "d8e8", "e8d7", "e8e7", "e8f7", "e8d8", "e8f8", "f8e7", "f8g7", "g8f6", "g8h6", "g8e7", "h8h7", "h8g8"};
    for (auto & s : move_strings) {
        legal_moves.push_back(Position::Move(s));
    }
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
    while (it != (csv_entry.rbegin() + 2).base())
    {
        legal_moves.push_back(Position::Move(*it++));
    }
    evaluation = std::stof(*it++);
    result = std::stof(*it);
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
            material = 100;
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
