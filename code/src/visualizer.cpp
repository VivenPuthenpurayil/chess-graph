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
            std::cout << "|";
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
        std::cout << p.board[i].identifier;
        std::cout << Color::Modifier(Color::FG_DEFAULT);
        
    }
    std::cout << "\n";
    std::cout << Color::Modifier(Color::FG_DEFAULT);
    std::cout << Color::Modifier(Color::BG_DEFAULT);
    
    
    


}