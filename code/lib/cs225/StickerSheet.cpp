#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {

    this->stickers.reserve(max);
    this->locations.reserve(max);
    this->base = new Image(picture); // Deep copy?

}

StickerSheet::StickerSheet(const StickerSheet &other) {
    unsigned max = other.stickers.capacity();
    this->stickers.reserve(max);
    this->locations.reserve(max);
    this->base = new Image(*other.base);

    for (Image* ip : other.stickers)
            this->stickers.push_back(new Image(*ip));
    this->locations = other.locations;
}

StickerSheet::~StickerSheet() {
    for (Image* ip : this->stickers)
            delete ip;
    this->locations.clear();
    delete this->base;
    return;
}

const StickerSheet & StickerSheet::operator=(const StickerSheet &other) {
    if (this != &other) {

        for (Image* ip : this->stickers)
            delete ip;

        this->stickers.clear();
        
        delete this->base;
        this->base = new Image(*other.base);

        for (Image* ip : other.stickers)
            this->stickers.push_back(new Image(*ip));
        
        this->locations.clear();
        this->locations = other.locations;
        

    }
    return *this;
}
void StickerSheet::changeMaxStickers(unsigned max) {
    // Does STL Vector handle relocation? Is this fine?
    if (max < this->stickers.capacity()) {
        for (int i = max ; i < (int) this->stickers.size(); i++) {
            this->removeSticker(i);
            //this->stickers.pop_back();
            
        }
        this->stickers.shrink_to_fit();
        this->locations.shrink_to_fit();
        
    }

    this->stickers.reserve(max);
    this->locations.reserve(max);
}

Image* StickerSheet::getSticker(unsigned index){
    if (index >= this->stickers.size()) {
        return NULL;
    }
    return this->stickers[index];
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {

    if (this->stickers.capacity() <= this->stickers.size()) {
        return -1;
    } 
    this->stickers.push_back(new Image(sticker));
    this->locations.push_back(std::make_pair(x, y));
    return this->stickers.size();

}

void StickerSheet::removeSticker(unsigned index) {
    delete this->stickers[index];
    this->stickers[index] = NULL;
    this->locations[index] = std::make_pair(0, 0);

}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    
    if (x < 0 or (x > this->base->width())) {
        return false;
    }
    if (y < 0 or (y > this->base->height())) {
        return false;
    }
    if (index > this->locations.size()) {
        return false;
    }
    if (this->stickers[index] == NULL) {
        return false;
    }
    
    this->locations.at(index) = std::make_pair(x, y);
    return true;

}

Image StickerSheet::render() const {

    Image result = Image(*this->base);

    for (int i = 0; i < (int) this->stickers.size(); i++) {

        if (this->stickers[i] == NULL) {
            continue;
        }
        Image* ip = this->stickers[i];

        unsigned y_loc = this->locations[i].second;
        unsigned x_loc = this->locations[i].first;

        if (y_loc + ip->height() > result.height()) {
            result.resize(result.width(), y_loc + ip->height());
        }

        if (x_loc + ip->width() > result.width()) {
            result.resize(x_loc + ip->width(), result.height());
        }

        for (unsigned y = 0; y < ip->height(); y++) {
            for (unsigned x = 0; x < ip->width(); x++) {
                cs225::HSLAPixel& base_pixel = result.getPixel(x+x_loc, y+y_loc);
                cs225::HSLAPixel& sticker_pixel = ip->getPixel(x, y);
                if (sticker_pixel.a > 0) {
                    base_pixel = sticker_pixel;
                }  
            }
        }
       
    }

    return result;
}