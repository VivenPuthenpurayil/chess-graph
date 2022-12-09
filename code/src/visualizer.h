#pragma once

#include "../lib/cs225/Image.h"
#include "../lib/cs225/StickerSheet.h"

#include "position.h"
#include "graph.h"
#include "utils.h"

#include <map>
#include <iostream>

void display_position(Position & p);

void display_groups(Position & p, std::vector<int> colorscheme);

Image display_groups_png(Position & p, std::vector<int> colorscheme);

void color_piece(Image & i, int color);

Image get_piece_image(Position::Piece & p);
