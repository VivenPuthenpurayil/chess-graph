#include "Image.h"
#include <unistd.h>
void Image::darken() {
    this->darken(0.1);
}

void Image::darken(double amount) {

    unsigned width = this->width();
    unsigned height = this->height();

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = this->getPixel(x, y);
            if (pixel.l <= amount) {
                pixel.l = 0;
            }
            else {
                pixel.l -= amount;
            }
        }
    }
}

void Image::lighten() {
    this->lighten(0.1);
}

void Image::lighten(double amount) {

    unsigned width = this->width();
    unsigned height = this->height();

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = this->getPixel(x, y);
            if (1 - pixel.l <= amount) {
                pixel.l = 1;
            }
            else {
                pixel.l += amount;
            }
        }
    }
}

void Image::saturate() {
    this->saturate(0.1);
}

void Image::saturate(double amount) {
    unsigned width = this->width();
    unsigned height = this->height();

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = this->getPixel(x, y);
            if (1 - pixel.s <= amount) {
                pixel.s = 1;
            }
            else {
                pixel.s += amount;
            }
        }
    }
}

void Image::desaturate() {
    this->desaturate(0.1);
}

void Image::desaturate(double amount) {

    unsigned width = this->width();
    unsigned height = this->height();

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = this->getPixel(x, y);
            if (pixel.s <= amount) {
                pixel.s = 0;
            }
            else {
                pixel.s -= amount;
            }
        }
    }
}

void Image::grayscale() {
    this->desaturate(1.0);
}

void Image::rotateColor(double degrees){
    unsigned width = this->width();
    unsigned height = this->height();

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = this->getPixel(x, y);
            double h = pixel.h;
            h += degrees;
            h = fmod(fmod(h, 360) + 360, 360); // Bind to be inbetween 0 and 360
            pixel.h = h;
        }
    }
}

void Image::illinify() {
    double orange = 11;
    double blue = 216;

    unsigned width = this->width();
    unsigned height = this->height();

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x++) {
            cs225::HSLAPixel& pixel = this->getPixel(x, y);
            double h = pixel.h;

            double d_orange = 180 - fabs(fmod(fabs(h - orange), 360) - 180);
            double d_blue = 180 - fabs(fmod(fabs(h - blue), 360) - 180); 

            if (d_orange < d_blue) {
                pixel.h = orange;
            }
            else {
                pixel.h = blue;
            }
        }
    }
    return;
}

void Image::scale(double factor) {

    
    unsigned newWidth = this->width() * factor;
    unsigned newHeight = this->height() * factor;
    
    if (factor < 1) {
        for (unsigned y = 0; y < newHeight; y++) {
            for (unsigned x = 0; x < newWidth; x++) {
                cs225::HSLAPixel& pixel = this->getPixel(x, y);
                pixel = this->getPixel(x / factor, y / factor);
            }
        }
        this->resize(newWidth, newHeight);
    }
    else if (factor > 1) {
        this->resize(newWidth, newHeight);
        Image copy = Image(*this);
        
        for (unsigned y = 0; y < newHeight; y++) {
            for (unsigned x = 0; x < newWidth; x++) {
                cs225::HSLAPixel& pixel = this->getPixel(x, y);
                pixel = cs225::HSLAPixel(copy.getPixel(x / factor, y / factor));
            }
        }
        

    }
    else if (factor == 1){
        this->resize(newWidth, newHeight);
    }
    
}

void Image::scale(unsigned w, unsigned h) {
    double factor = 1;

    factor = std::min((double) w / this->width(), (double) h / this->height());

    this->scale(factor);
    return;

}

void Image::drawline(int x0, int y0, int x1, int y1, int color) {
    // Draws a line between the two points on the image

    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;

    while (true) {
        auto & p = this->getPixel(x0, y0);
        p = cs225::HSLAPixel(color, 1, .5, 1);

        if (x0 == x1 && y0 == y1) break;
        if (error * 2 >= dy) {
            if (x0 == x1) break;
            error += dy;
            x0 = x0 + sx;
        }
        if (error * 2 <= dx) {
            if (y0 == y1) break;
            error += dx;
            y0 = y0 + sy;
        }
    }

}

void Image::drawthickline(int x0, int y0, int x1, int y1, int color, int thickness) {
    // Draws a line between the two points on the image

    for (int dx = -thickness; dx < thickness; dx++) {
        for (int dy = -thickness; dy < thickness; dy++) {
            drawline(x0 + dx, y0 + dy, x1 + dx, y1 + dy, color);
        }
    }

}