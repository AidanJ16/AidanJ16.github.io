#include "StickerSheet.h"
#include <vector>
#include <iostream>
StickerSheet::StickerSheet(const Image & picture, unsigned max) {
    base_ = picture;
    index_ = 0;
    max_layers = max;
    x_coords = std::vector<int>(max);
    y_coords = std::vector<int>(max);
    stickers_ = std::vector<Image*>(max);
    for(unsigned i = 0; i < max_layers; i++) {
        stickers_.at(i) = NULL;
        //stickers_->at(i)->x_ = 0;
        //stickers_->at(i)->y_ = 0;
    }
}
StickerSheet::StickerSheet(const StickerSheet & other) {
    base_ = other.base_;
    index_ = other.index_;
    max_layers = other.max_layers;
    x_coords = other.x_coords;
    y_coords = other.y_coords;
    stickers_ = other.stickers_;
    /*for(unsigned a = 0; a < max_layers; a++) {
        if(other.stickers_->at(a) != NULL) {
            stickers_->at(a) = new Image(*(other.stickers_->at(a)));
            x_coords->at(a) = other.x_coords->at(a);
            y_coords->at(a) = other.y_coords->at(a);
            //stickers_->at(a)->x_ = (other.stickers_->at(a)->x_);
            //stickers_->at(a)->y_ = (other.stickers_->at(a)->y_);
            for(int i = 0; i < (stickers_->at(a)->x_); i++) {
                for(int j = 0; j < (stickers_->at(a)->y_); j++) {
                    cs225::HSLAPixel & pix_other = (*(other.stickers_->at(a))).getPixel(i, j);
                    cs225::HSLAPixel & pix_base = (*(stickers_->at(a))).getPixel(i, j);
                    pix_base.h = pix_other.h;
                    pix_base.s = pix_other.s;
                    pix_base.l = pix_other.l;
                    pix_base.a = pix_other.a;
                }
            }
        } else {
            stickers_->at(a) = NULL;
        }
    }
    for(int i = 0; i < max_layers; i++) {
        stickers_->at(i) = (other.stickers_->at(i));
    }*/
}
int StickerSheet::addSticker(Image & sticker, int x, int y) {
    if(index_ < max_layers) {
        x_coords.at(index_) = x;
        y_coords.at(index_) = y;
        stickers_.at(index_) = &sticker;
        index_++;
        return (index_ - 1);
    } else {
        stickers_.push_back(&sticker);
        x_coords.push_back(x);
        y_coords.push_back(y);
        index_++;
        max_layers++;
        return (index_ - 1);
    }
}
void StickerSheet::changeMaxStickers(unsigned max) {
    /*if(max < layers) {
        for(int i = max; i < max_layers; i++) {
            delete stickers_->at(i);
            stickers_->at(i) = NULL;
        }
    }*/
    stickers_.resize(max);
    x_coords.resize(max);
    y_coords.resize(max);
    if(max > max_layers) {
        for(unsigned i = max_layers; i < max; i++) {
            stickers_.at(i) = NULL;
        }
    }
    max_layers = max;
}
Image * StickerSheet::getSticker(unsigned index) {
    if(index_ < max_layers) {
        return stickers_.at(index);
    }
    return NULL;
}
int StickerSheet::layers() const {
    return max_layers;
}
const StickerSheet & StickerSheet::operator=(const StickerSheet & other) {
    /*for(int a = 0; a < max_layers; a++) {
        delete stickers_->at(a);
        stickers_->at(a) = NULL;
    }*/
    stickers_.clear();
    x_coords.clear();
    y_coords.clear();
    base_ = other.base_;
    index_ = other.index_;
    max_layers = other.max_layers;
    stickers_ = other.stickers_;
    x_coords = other.x_coords;
    y_coords = other.y_coords;
    /*for(unsigned a = 0; a < max_layers; a++) {
        if(other.stickers_->at(a) != NULL) {
            stickers_->at(a) = new Image(*(other.stickers_->at(a)));
            for(unsigned i = 0; i < (other.stickers_->at(a)->width()); i++) {
                for(unsigned j = 0; j < (other.stickers_->at(a)->height()); j++) {
                    cs225::HSLAPixel & pix_other = (*(other.stickers_->at(a))).getPixel(i, j);
                    cs225::HSLAPixel & pix_base = (*(stickers_->at(a))).getPixel(i, j);
                    pix_base.h = pix_other.h;
                    pix_base.s = pix_other.s;
                    pix_base.l = pix_other.l;
                    pix_base.a = pix_other.a;
                }
            }
            stickers_->at(a)->x_ = (other.stickers_->at(a)->x_);
            stickers_->at(a)->y_ = (other.stickers_->at(a)->y_);
        }
    }*/
    return *this;
}
void StickerSheet::removeSticker(unsigned index) {
    unsigned max = max_layers;
    if(index < max) {
        //delete stickers_->at(index);
        //stickers_->at(index) = NULL;
        //stickers_->at(index)->x_ = 0;
        //stickers_->at(index)->y_ = 0;
        stickers_.at(index) = NULL;
        stickers_.at(index) = 0;
        stickers_.at(index) = 0;
        --index_;
    }
}
Image StickerSheet::render() const {
    int max_x_ = base_.width();
    int max_y_ = base_.height();
    int min_x_ = 0;
    int min_y_ = 0;
    for(unsigned i = 0; i < max_layers; i++) {
        if(stickers_.at(i) != NULL) {
            int temp_x_max = x_coords.at(i) + stickers_.at(i)->width();
            int temp_y_max = y_coords.at(i) + stickers_.at(i)->height();
            int temp_x_min = x_coords.at(i);
            int temp_y_min = y_coords.at(i);
            if(temp_x_max > max_x_) {
                max_x_ = temp_x_max;
            }
            if(temp_y_max > max_y_) {
                max_y_ = temp_y_max;
            }
            if(temp_x_min < min_x_) {
                min_x_ = temp_x_min;
            }
            if(temp_y_min < min_y_) {
                min_y_ = temp_y_min;
            }
        } else {
            continue;
        }
    }
    max_x_ = max_x_ + abs(min_x_);
    max_y_ = max_y_ + abs(min_y_);
    
    Image ret2 = base_;
    ret2.resize(max_x_, max_y_);
    
    for(unsigned int i = 0; i < ret2.width(); i++) {
        for(unsigned int j = 0; j < ret2.height(); j++) {
            cs225::HSLAPixel & pix_base = ret2.getPixel(i, j);
            pix_base.h = 0.0;
            pix_base.s = 0.0;
            pix_base.l = 1.0;
            pix_base.a = 1.0;
        }
    }
    
    for(int i = 0; i < static_cast<int>(base_.width()); i++) {
        for(int j = 0; j < static_cast<int>(base_.height()); j++) {
            cs225::HSLAPixel pix_other = base_.getPixel(i,j);
            cs225::HSLAPixel & pix_base = ret2.getPixel(i - min_x_, j - min_y_);
            if(pix_other.a != 0) {
                //pix_base = pix_other;
                pix_base.h = pix_other.h;
                pix_base.s = pix_other.s;
                pix_base.l = pix_other.l;
                pix_base.a = pix_other.a;
            }
        }
    }

    int count = 0;
    for(unsigned a = 0; a < max_layers; a++) {
        if(stickers_.at(a) != NULL) {
            //std::cout << (*(stickers_.at(a))) << "sticker being added" << std::endl;
            //std::cout << x_coords.at(a) << " " << min_x_ << " " << y_coords.at(a) << " " << min_y_ << std::endl; 
            //std::cout << stickers_.at(a)->width() << " " << stickers_.at(a)->height() << std::endl;
            for(unsigned i = 0; i < stickers_.at(a)->width(); i++) {
                for(unsigned j = 0; j < stickers_.at(a)->height(); j++) {
                    //std::cout << (*(stickers_.at(a))).getPixel(i, j) << "sticker pixels" << std::endl;
                    cs225::HSLAPixel & pix_other = (*(stickers_.at(a))).getPixel(i, j);
                    cs225::HSLAPixel & pix_base = ret2.getPixel(i + x_coords.at(a) - min_x_, j + y_coords.at(a)- min_y_);
                    if(pix_other.a != 0) {
                        //pix_base = pix_other;
                        //std::cout << count++ << " ";
                        pix_base.h = pix_other.h;
                        pix_base.s = pix_other.s;
                        pix_base.l = pix_other.l;
                        pix_base.a = pix_other.a;
                    }
                    //std::cout << ret2.getPixel(i + x_coords.at(a) - min_x_, j + y_coords.at(a)- min_y_) << "ret2 pixels" << std::endl;
                }
            }
        }
    }
    
    return ret2;
}
int StickerSheet::setStickerAtLayer(Image & sticker, unsigned layer, int x, int y) {
    unsigned layers = max_layers;
    if(layer >= layers) {
        return -1;
    }
    int ret = 0;
    for(unsigned i = 0; i < layer; i++) {
        ret++;
    }
    //*(stickers_->at(index_)) = Image(sticker);
    stickers_.at(layer) = &sticker;
    x_coords.at(layer) = x;
    y_coords.at(layer) = y;
    /*for(unsigned i = 0; i < (sticker.width()); i++) {
        for(unsigned j = 0; j < (sticker.height()); j++) {
            cs225::HSLAPixel & pix_other = sticker.getPixel(i, j);
            cs225::HSLAPixel & pix_base = (*(stickers_->at(layer))).getPixel(i, j);
            pix_base.h = pix_other.h;
            pix_base.s = pix_other.s;
            pix_base.l = pix_other.l;
            pix_base.a = pix_other.a;
        }
    }*/
    return layer;
}
bool StickerSheet::translate(unsigned index, int x, int y) {
    unsigned layers = max_layers;
    if(index >= layers || stickers_.at(index) == NULL) {
        return false;
    }
    x_coords.at(index) = x;
    y_coords.at(index)= y;
    return true;
}
StickerSheet::~StickerSheet() {
    /*for(unsigned a = 0; a < max_layers; a++) {
        if(stickers_->at(a) != NULL) {
            delete stickers_->at(a)->x_;
            delete stickers_->at(a)->y_;
        }
    }*/
    /*x_coords.clear();
    y_coords.clear();
    x_coords = NULL;
    y_coords = NULL;
    stickers_.clear();
    stickers_ = NULL;
    base_ = NULL;*/
}