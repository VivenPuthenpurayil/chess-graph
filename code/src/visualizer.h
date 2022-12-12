#pragma once

#include "../lib/cs225/Image.h"
#include "../lib/cs225/StickerSheet.h"

#include "position.h"
#include "graph.h"
#include "utils.h"

#include <map>
#include <iostream>

/**
 * Display position in the terminal
*/
void display_position(Position & p);

/**
 * Display color groups in the terminal according to a colorscheme.
*/
void display_groups(Position & p, std::vector<int> colorscheme);

Image get_groups_image(Position & p, std::vector<int> colorscheme);

Image get_position_image(Position & p);

/**
 * Draw edges of a graph on a base image
*/
void draw_edges(Graph & g, Image & base, int color);

void draw_position(Position & p, Image & base);

void color_piece(Image & i, int color);

Image get_piece_image(Position::Piece & p);

Image get_brandes_image(Position & p, std::vector<int> colorscheme);
