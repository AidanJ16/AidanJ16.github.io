/**
 * @file ImageTraversal.h
 */
#pragma once

#include <iterator>
#include <deque>
#include <vector>
#include <map>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

using namespace cs225;

/**
 * @brief Namespace containing everything required for an image traversal
 * 
 */
namespace Traversals {
  /**
  * This defines the expected types for an add function for a traversal
  * The first parameter is the deque which stores the list of points to be processed
  * The second parameter is the new point which needs to be added to the deque
  */
  typedef void (*add_function) (std::deque<Point> &, const Point &);
  
  /**
  * This defines the expected types for an add function for a traversal
  * The first parameter is the deque which stores the list of points to be processed
  * The function then returns the next point to be processed (and removes it from the deque)
  */
  typedef Point (*pop_function) (std::deque<Point> &);

  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);

  void bfs_add(std::deque<Point> & work_list, const Point & point);
  void dfs_add(std::deque<Point> & work_list, const Point & point);
  Point bfs_pop(std::deque<Point> & work_list);
  Point dfs_pop(std::deque<Point> & work_list);

  /**
  * A base class for traversal algorithms on images.
  * This class provides a traversal of the image by returning instances of ImageTraversal::Iterator.
  */
  class ImageTraversal {
  public:
    /**
    * A forward iterator through an ImageTraversal.
    */
    class Iterator : std::iterator<std::forward_iterator_tag, Point> {
    public:
      Iterator();

      Iterator & operator++();
      Point operator*();
      bool operator!=(const Iterator &other);
      Iterator(double tol, Point & start, Point & curr, add_function add, pop_function pop, PNG & image);

      /** @todo [Part 1] */
      /** add member functions if neccesary*/

    private:
      /** @todo [Part 1] */
      /** add private members here if neccesary*/
      std::deque<Point> work_list;
      std::vector<bool> i_visited;
      PNG i_image;
      HSLAPixel i_start_pix;
      Point i_start_P;
      Point i_current_P;
      add_function i_adds;
      pop_function i_pops;
      double i_tol;
    };

    /**
    * Constructor for the given traversal
    */
    ImageTraversal(const PNG & png, const Point & start, double tolerance, add_function traversal_add, pop_function traversal_pop);

    /**
    * Returns an iterator for the traversal starting at the first point (specified in the constructor).
    */
    Iterator begin();

    /**
    * Returns an iterator for the traversal one past the end of the traversal.
    */
    Iterator end();

  private:
    /** @todo [Part 1] */
    /** add private members here if neccesary*/
    std::vector<bool> t_visited;
    PNG t_image;
    HSLAPixel t_start_pix;
    Point t_start_P;
    Point t_current_P;
    add_function t_adds;
    pop_function t_pops;
    double t_tol;
  };
}