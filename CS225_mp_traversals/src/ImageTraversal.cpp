#include <cmath>
#include <iterator>
//#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt( (h*h) + (s*s) + (l*l) );
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_front(point);
  }

  /*bool bfs_visited(unsigned x, unsigned y) {

  }

  void bfs_setVisit(unsigned x, unsigned y) {

  }*/

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_front(point);
  }

  /*bool dfs_visited(unsigned x, unsigned y) {  

  }

  void dfs_setVisit(unsigned x, unsigned y) {

  }*/
  /**
  * Removes and returns the current Point in the bfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    if(work_list.empty()) return Point(-1, -1);
    Point ret = work_list.back();
    work_list.pop_back();
    return ret;
  }

  /**
  * Removes and returns the current Point in the dfs traversal
  * @param work_list the structure which stores the list of points which need to be visited by the traversal
  */
  Point dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    if(work_list.empty()) return Point(-1, -1);
    Point ret = work_list.front();
    work_list.pop_front();
    return ret;
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param traversal_add a function pointer to an implemented function which takes in a reference to the work list
  * and the point to be added
  * @param traversal_pop a function pointer to an implemented function which takes in a reference to the work list
  * and returns the next point to be processed in the traversal
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop) {  
    /** @todo [Part 1] */
    t_tol = tolerance;

    t_start_P = start;
    t_current_P = start;

    t_adds = traversal_add;
    t_pops = traversal_pop;

    t_image = PNG(png);
    for(unsigned i = 0; i < png.width(); i++) {
      for(unsigned j = 0; j < png.height(); j++) {
        //Point curr(i, j);
        t_visited.push_back(false);
      }
    }
    
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    ImageTraversal::Iterator start(this->t_tol, this->t_start_P, this->t_start_P, this->t_adds, this->t_pops, this->t_image);
    return start;
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    Point p(-1, -1);
    ImageTraversal::Iterator end(this->t_tol, this->t_start_P, p, this->t_adds, this->t_pops, this->t_image);
    return end;
    //return nullptr;
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
    return;
  }

  ImageTraversal::Iterator::Iterator(double tol, Point & start, Point & curr, add_function add, pop_function pop, PNG & image) {
    i_tol = tol;
    i_start_P = start;
    i_current_P = curr;

    i_adds = add;
    i_pops = pop;

    i_image = PNG(image);
    i_start_pix = image.getPixel(start.x, start.y);
    for(unsigned i = 0; i < image.width(); i++) {
      for(unsigned j = 0; j < image.height(); j++) {
        //Point curr(i, j);
        i_visited.push_back(false);
      }
    }
    
  }

  /**
  * Iterator increment opreator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */
    //std::cout << i_current_P.x << " x " << i_current_P.y << " y#1" << std::endl;
    if(((i_current_P.x + 1) < i_image.width()) && (i_current_P.y < i_image.height())) { // check in bound
      Point r(i_current_P.x + 1, i_current_P.y);
      //std::cout << (i_image.width() * r.x + r.y) << " vector index ";
      //std::cout << r.x << " width";
      if(i_visited[i_image.height()*r.x + r.y] != true) { // not visited
        if(calculateDelta(i_image.getPixel(r.x, r.y), i_image.getPixel(i_start_P.x, i_start_P.y)) < i_tol) {
          i_adds(work_list, r);
          //std::cout << "add r ";
        }
      }
    }

    if(i_current_P.y + 1 < i_image.height()) { // check in bound
      Point b(i_current_P.x, i_current_P.y + 1);
      if(i_visited[i_image.height()*b.x + b.y] != true) { // not visited
        if(calculateDelta(i_image.getPixel(b.x, b.y), i_image.getPixel(i_start_P.x, i_start_P.y)) < i_tol) {
          i_adds(work_list, b);
          //std::cout << "add b ";
        }
      }
    }

    if(i_current_P.x - 1 < i_image.width()) { // check in bound
      Point l(i_current_P.x - 1, i_current_P.y);
      if(i_visited[i_image.height()*l.x + l.y] != true) { // not visited
        if(calculateDelta(i_image.getPixel(l.x, l.y), i_image.getPixel(i_start_P.x, i_start_P.y)) < i_tol) {
          i_adds(work_list, l);
          //std::cout << "add l ";
        }
      }
    }

    if(i_current_P.y - 1 < i_image.height()) { // check in bound
      Point a(i_current_P.x, i_current_P.y - 1);
      if(i_visited[i_image.height()*a.x + a.y] != true) { // not visited
        if(calculateDelta(i_image.getPixel(a.x, a.y), i_image.getPixel(i_start_P.x, i_start_P.y)) < i_tol) {
          i_adds(work_list, a);
          //std::cout << "add a ";
        }
      }
    }

    i_visited[(i_image.height() * i_current_P.x) + i_current_P.y] = true;
    
    i_current_P = i_pops(work_list);
    if(i_current_P.x < i_image.width() && i_current_P.y < i_image.height()) {
      while(i_visited[(i_image.height() * i_current_P.x) + i_current_P.y] == true) {
        i_current_P = i_pops(work_list);
        if(i_current_P.x >= i_image.width() || i_current_P.y >= i_image.height()) break;
      }
    }
    //std::cout << i_current_P.x << " x " << i_current_P.y << " y #2" << std::endl;
    //i_current_P = work_list.front();
    return *this;
  }

  /**
  * Iterator accessor opreator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return i_current_P;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    if(this->i_current_P.x == other.i_current_P.x && this->i_current_P.y == other.i_current_P.y) return false;
    return true;
  }

}