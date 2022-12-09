#include "visualizer.h"

void display_position(Position & p) {
    std::cout << Color::Modifier(Color::FG_GREEN);
    std::cout << "----------\n";
    for (size_t i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            if (i > 0) {
                std::cout << "|";
                std::cout << Color::Modifier(Color::BG_DEFAULT);
                std::cout << "\n";
            }
            std::cout << "|";
        }
        std::cout << p.board[i].identifier;
        
    }
    std::cout << "|\n----------\n";
    std::cout << Color::Modifier(Color::FG_DEFAULT);
    std::cout << Color::Modifier(Color::BG_DEFAULT);

}

void draw_position(Position & p, Image & base) {
    StickerSheet sheet(base, 64);

    for(size_t i = 0; i < 64; i++) {
        
        if (p.board[i].type == Position::Piece::NONE) {
            continue;
        }
        Image piece = get_piece_image(p.board[i]);


        int x = (i % 8);
        int y = ((i - x) / 8);

        sheet.addSticker(piece, x * 60 + 8, y * 60 + 8);
    }

    base = sheet.render();
}

Image get_position_image(Position & p) {
    Image board; board.readFromFile("../../images/chessboard.png");
    board.resize(480, 480);
    StickerSheet sheet(board, 64);

    for(size_t i = 0; i < 64; i++) {
        
        if (p.board[i].type == Position::Piece::NONE) {
            continue;
        }
        Image piece = get_piece_image(p.board[i]);


        int x = (i % 8);
        int y = ((i - x) / 8);

        sheet.addSticker(piece, x * 60 + 8, y * 60 + 8);
    }

    return sheet.render();
}

Image get_groups_image(Position & p, std::vector<int> colorscheme) {
    Image board; board.readFromFile("../../images/chessboard.png");
    board.resize(480, 480);
    StickerSheet sheet(board, 64);

    std::vector<int> colors = {0, 100, 60, 230, 305, 170};
    std::map<int, int> colormap;
    int j = 0;
    int group = 0;

    int color = 0;

    for(size_t i = 0; i < 64; i++) {
        
        // Assign color
        group = colorscheme[i];
        if (colormap.find(group) == colormap.end() && group != -1) {
            // No color found, assign one
            colormap[group] = colors[j++];
        }
        if (group == -1) {
            color = -1;
        }
        else {
            color = colormap[group];
        }

        if (p.board[i].type == Position::Piece::NONE) {
            continue;
        }
        Image piece = get_piece_image(p.board[i]);

        if (color != -1) {
            color_piece(piece, color);
        }

        int x = (i % 8);
        int y = ((i - x) / 8);

        sheet.addSticker(piece, x * 60 + 8, y * 60 + 8);
    }

    return sheet.render();
}

Image get_piece_image(Position::Piece & p) {
    Image out; 

    switch (p.identifier) {
        case 'R':
            out.readFromFile("../../images/whiterook.png");
            break;
        case 'N':
            out.readFromFile("../../images/whiteknight.png");
            break;
        case 'B':
            out.readFromFile("../../images/whitebishop.png");
            break;
        case 'Q':
            out.readFromFile("../../images/whitequeen.png");
            break;
        case 'K':
            out.readFromFile("../../images/whiteking.png");
            break;
        case 'P':
            out.readFromFile("../../images/whitepawn.png");
            break;
        case 'r':
            out.readFromFile("../../images/blackrook.png");
            break;
        case 'n':
            out.readFromFile("../../images/blackknight.png");
            break;
        case 'b':
            out.readFromFile("../../images/blackbishop.png");
            break;
        case 'q':
            out.readFromFile("../../images/blackqueen.png");
            break;
        case 'k':
            out.readFromFile("../../images/blackking.png");
            break;
        case 'p':
            out.readFromFile("../../images/blackpawn.png");
            break;
        default:
            out.readFromFile("../../images/whitepawn.png");
            break;
    }
    return out;
}

void color_piece(Image & i, int color) {
    i.saturate(1);
    i.darken(.4);
    i.rotateColor(color);
}

void display_groups(Position & p, std::vector<int> colorscheme) {
    // -1 for default, colored otherwise
    std::vector<Color::Code> colors = {Color::FG_RED, Color::FG_GREEN, Color::FG_YELLOW, Color::FG_BLUE, Color::FG_MAGENTA, Color::FG_CYAN};
    std::map<int, Color::Code> colormap; // Map a number in our colorscheme to a color
    int j = 0;
    int group = 0;
    Color::Code cmod;

    for (size_t i = 0; i < 64; i++) {
        
        if (i % 8 == 0) {
            if (i > 0) {
                std::cout << "|";
                std::cout << Color::Modifier(Color::BG_DEFAULT);
                std::cout << "\n";
            }
            std::cout << "| ";
        }

        group = colorscheme[i];
        if (colormap.find(group) == colormap.end() && group != -1) {
            // No color found, assign one
            colormap[group] = colors[j++];
        }
        if (group == -1) {
            cmod = Color::FG_DEFAULT;
        }
        else {
            cmod = colormap[group];
        }
        
        std::cout << Color::Modifier(cmod);
        std::cout << p.board[i].identifier << " ";
        std::cout << Color::Modifier(Color::FG_DEFAULT);
        
    }
    std::cout << "|\n";
    std::cout << Color::Modifier(Color::FG_DEFAULT);
    std::cout << Color::Modifier(Color::BG_DEFAULT);
    
}

void draw_edges(Graph & g, Image & base, int color) {
    for (size_t i = 0; i < 64; i++) {
        for(int n : g.out_neighbors(i)) {
            int x0 = (i % 8);
            int y0 = ((i - x0) / 8);
            int x1 = (n % 8);
            int y1 = ((n - x1) / 8);
            base.drawthickline(x0  * 60 + 30, y0 * 60 + 30, x1 * 60 + 30, y1 * 60 + 30, color, 3);
        }
    }
}

