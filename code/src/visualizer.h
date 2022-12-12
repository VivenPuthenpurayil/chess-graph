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

/**
  * Provide an image of a chess position based on a given colorscheme.
  * Colorscheme is used to declare groups (inteded for use with tarjans algorithm).
  */
Image get_groups_image(Position & p, std::vector<int> colorscheme);

/**
 * Get an image of the position without any coloring or anything.
 */
Image get_position_image(Position & p);

/**
  * Draw edges of a graph on a base image
  */
void draw_edges(Graph & g, Image & base, int color);

/**
 * Draw the position into a base image
 */
void draw_position(Position & p, Image & base);

/**
 * Change the color of a piece image.
*/
void color_piece(Image & i, int color);

/*
 * Helper function to retrieve the image of a piece via our images folder.
 */
Image get_piece_image(Position::Piece & p);

Image get_brandes_image(Position & p, std::vector<int> colorscheme);
