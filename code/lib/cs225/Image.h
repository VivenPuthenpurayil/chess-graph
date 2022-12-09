/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 * A subclass of PNG with more member functions for modifying the image.
 */

#pragma once
#include <math.h>
#include "PNG.h" 
#include "HSLAPixel.h"


class Image: public cs225::PNG {
    public:

        /**
         * Lighten an Image by increasing the luminance of every pixel by 0.1
         */
        void lighten();

        /**
         * Lighten an Image by increasing the luminance of every pixel by an amount.
         * @param amount Amount to increase luminace by.
         */
        void lighten(double amount);

        /**
         * Darken an Image by increasing the luminance of every pixel by 0.1
         */
        void darken();

        /**
         * Darken an Image by decreasing the luminance of every pixel by an amount.
         * @param amount Amount to decrease luminace by.
         */
        void darken(double amount);

        /**
         * Saturates an Image by increasing the saturation of every pixel by 0.1.
         */
        void saturate();

        /**
         * Saturates an Image by increasing the saturation of every pixel by an amount.
         * @param amount Amount to increase saturation by.
         */
        void saturate(double amount);

        /**
         * Desaturates an Image by decreasing the saturation of every pixel by 0.1.
         */
        void desaturate();

        /**
         * Desaturates an Image by decreasing the saturation of every pixel by an amount.
         * @param amount Amount to decrease saturation by.
         */
        void desaturate(double amount);

        /**
         * Turns the Image grayscale
         */
        void grayscale();

        /**
         * Rotates the color wheel by an amount.
         * @param degrees Amount to rotate color wheel by.
         */
        void rotateColor(double degrees);
        

        /**
         * Illinifies the image
         */
        void illinify();

        /**
         * Scales the image by an amount.
         * @param factor The factor to scale the image by
         */
        void scale(double factor);

        /**
         * Scales the image to fit within a size.
         * @param w The width of the result.
         * @param h The height of the result.
         */  
        void scale(unsigned w, unsigned h);

        /**
         * Draws a line between the two points
        */
        void drawline(int x0, int y0, int x1, int y1, int color);

        void drawthickline(int x0, int y0, int x1, int y1, int color, int thickness);
        

};

