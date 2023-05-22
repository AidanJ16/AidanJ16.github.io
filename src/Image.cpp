#include "Image.h"

Image::Image() {
    cs225::PNG();
    x_ = 0;
    y_ = 0;
}
Image::Image(unsigned int width, unsigned int height) {
    cs225::PNG(width, height);
    x_ = 0;
    y_ = 0;
}
void Image::lighten() {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel & pix = this->getPixel(i, j);
            pix.l = pix.l + 0.1;
            if(pix.l >= 1) {
                pix.l = 1;
            }
        }
    }
}
void Image::lighten(double amount) {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel & pix = this->getPixel(i, j);
            pix.l = pix.l + amount;
            if(pix.l >= 1) {
                pix.l = 1;
            }
        }
    }
}
void Image::darken() {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel & pix = this->getPixel(i, j);
            pix.l = pix.l - 0.1;
            if(pix.l <= 0) {
                pix.l = 0;
            }
        }
    }
}
void Image::darken(double amount) {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel & pix = this->getPixel(i, j);
            pix.l = pix.l - amount;
            if(pix.l <= 0) {
                pix.l = 0;
            }
        }
    }
}
void Image::rotateColor(double degrees) {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel & pix = this->getPixel(i, j);
            pix.h = pix.h + degrees;
            if(pix.h > 360) {
                pix.h = pix.h - 360;
            } else if(pix.h < 0) {
                pix.h = pix.h + 360;
            }
        }
    }
}
void Image::saturate() {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel & pix = this->getPixel(i, j);
            pix.s = pix.s + 0.1;
            if(pix.s >= 1) {
                pix.s = 1;
            }
        }
    }
}
void Image::saturate(double amount) {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel & pix = this->getPixel(i, j);
            pix.s = pix.s + amount;
            if(pix.s >= 1) {
                pix.s = 1;
            }
        }
    }
}
void Image::scale(double factor) {
    double w = this->width();
    double h = this->height();
    unsigned int new_w_ = w*factor;
    unsigned int new_h_ = h*factor;
    PNG temp = PNG(new_w_, new_h_);

    for(unsigned int i = 0; i < new_w_; i++) {
        for(unsigned int j = 0; j < new_h_; j++) {
            temp.getPixel(i, j).h = this->getPixel(i / factor, j / factor).h;
            temp.getPixel(i, j).s = this->getPixel(i / factor, j / factor).s;
            temp.getPixel(i, j).l = this->getPixel(i / factor, j / factor).l;
            temp.getPixel(i, j).a = this->getPixel(i / factor, j / factor).a;
        }
    }
    this->resize(new_w_, new_h_);
    for(unsigned int i = 0; i < new_w_; i++) {
        for(unsigned int j = 0; j < new_h_; j++) {
            this->getPixel(i, j).h = temp.getPixel(i, j).h;
            this->getPixel(i, j).s = temp.getPixel(i, j).s;
            this->getPixel(i, j).l = temp.getPixel(i, j).l;
            this->getPixel(i, j).a = temp.getPixel(i, j).a;
        }
    }
}
void Image::scale(unsigned w, unsigned h) {
    double orig_w = this->width();
    double orig_h = this->height();

    double fact_w = static_cast<double>(w) / static_cast<double>(orig_w);
    double fact_h = static_cast<double>(h) / static_cast<double>(orig_h);

    double factor = std::min(fact_w, fact_h);

    unsigned int new_w = factor * orig_w;
    unsigned int new_h = factor * orig_h;

    PNG temp = PNG(new_w, new_h);
    for(unsigned int i = 0; i < new_w; i++) {
        for(unsigned int j = 0; j < new_h; j++) {
            temp.getPixel(i, j).h = this->getPixel(i / factor, j / factor).h;
            temp.getPixel(i, j).s = this->getPixel(i / factor, j / factor).s;
            temp.getPixel(i, j).l = this->getPixel(i / factor, j / factor).l;
            temp.getPixel(i, j).a = this->getPixel(i / factor, j / factor).a;
        }
    }
    this->resize(new_w, new_h);
    for(unsigned int i = 0; i < new_w; i++) {
        for(unsigned int j = 0; j < new_h; j++) {
            this->getPixel(i, j).h = temp.getPixel(i, j).h;
            this->getPixel(i, j).s = temp.getPixel(i, j).s;
            this->getPixel(i, j).l = temp.getPixel(i, j).l;
            this->getPixel(i, j).a = temp.getPixel(i, j).a;
        }
    }
    /*for(unsigned i = 0; i < w; i++) {
        for(unsigned j = 0; j < h; j++) {
            unsigned new_w_ = orig_w / w;
            unsigned new_h_ = orig_h / h;
            temp.getPixel(i, j).h = this->getPixel(i / new_w_, j / new_h_).h;
            temp.getPixel(i, j).s = this->getPixel(i / new_w_, j / new_h_).s;
            temp.getPixel(i, j).l = this->getPixel(i / new_w_, j / new_h_).l;
            temp.getPixel(i, j).a = this->getPixel(i / new_w_, j / new_h_).a;
        }
    }
    this->resize(w, h);
    for(unsigned i = 0; i < w; i++) {
        for(unsigned j = 0; j < h; j++) {
            this->getPixel(i, j).h = temp.getPixel(i, j).h;
            this->getPixel(i, j).s = temp.getPixel(i, j).s;
            this->getPixel(i, j).l = temp.getPixel(i, j).l;
            this->getPixel(i, j).a = temp.getPixel(i, j).a;
        }
    }*/
}
void Image::desaturate() {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel & pix = this->getPixel(i, j);
            pix.s = pix.s - 0.1;
            if(pix.s <= 0) {
                pix.s = 0;
            }
        }
    }
}
void Image::desaturate(double amount) {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel & pix = this->getPixel(i, j);
            pix.s = pix.s - amount;
            if(pix.s <= 0) {
                pix.s = 0;
            }
        }
    }
}
void Image::grayscale() {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel & pix = this->getPixel(i, j);
            pix.s = 0;
        }
    }
}
void Image::illinify() {
    for(unsigned int i = 0; i < this->width(); i++) {
        for(unsigned int j = 0; j < this->height(); j++) {
            cs225::HSLAPixel & pix = this->getPixel(i, j);
            if(pix.h > 113.5 || pix.h < 293.5) {
                pix.h = 216;
            } else {
                pix.h = 11;
            }
        }
    }
}