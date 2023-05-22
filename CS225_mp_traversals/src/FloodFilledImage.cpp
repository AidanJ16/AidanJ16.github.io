#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  image = new PNG(png);
}

FloodFilledImage::~FloodFilledImage() {
  delete image;
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(Traversals::ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  trav.push_back(&traversal);
  color.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 * @param frameInterval how often to save frames of the animation
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  PNG im(*image);
  animation.addFrame(im);
  for(unsigned i = 0; i < trav.size(); ++i) {

    unsigned count = 0;
    //std::cout << image->width() << " width " << image->height();
    //for(const Point & p : (*(trav[0])))
    Traversals::ImageTraversal::Iterator it = trav[0]->begin();
    Traversals::ImageTraversal::Iterator end = trav[0]->end();
    while(it != end) { 
      count++;
      //std::cout << *it << " point " << std::endl;
      cs225::HSLAPixel & my_pix = im.getPixel((*it).x, (*it).y);
      cs225::HSLAPixel given_pix = color[0]->getColor((*it).x, (*it).y);
      my_pix.h = given_pix.h;
      my_pix.s = given_pix.s;
      my_pix.l = given_pix.l;
      my_pix.a = given_pix.a;

      if(count % frameInterval == 0) {
        animation.addFrame(im);
        count = 0;
        //std::cout << "adding frames";
      }
      ++it;
    }
    animation.addFrame(im);
    //std::cout << animation.frameCount() << std::endl;
  }
  return animation;
}
