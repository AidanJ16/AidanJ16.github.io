#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;

// INTRO PARAGRAPH
// In this mp we had to implement the following:
// First was the Shape class where we had to implement the constructor and the getName() function
// Next was the Rectangle class, where we had implement the constructor, getArea(), getVolume(), operator+, and operator-
// Next was the Circle class, where we had to implement the constructor, getArea(), getvolume(), operator+, and operator-
// Next was the Sphere class, where we had to implement the constructor, getArea(), getVolume(), operator+, and operator-
// Next was the RectPrism class, where we had to implement the constructor, getArea(), getVolume(), operator+, and operator-
// Next was CreateShapes function which reads an input file and initializes the corresponding objects
// The function returns a list of pointers to the objects initialized according to the data in the file
// We then had to implement MaxVolume and MaxArea which given a list of object pointers would compute each objects area and volume
// It would then return the maximum volume and maximum area respectively
//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
	  name_ = name;  // set shape name to private name_
	}
	
  	string getName() {
	  return name_;  // return name_
	}
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {
	  // set rectangle width and height to private width_ and height_
	  width_ = width;
	  length_ = length;
	}
	
  	double getArea() const {
	  // area of rectangle = w*h
	  return width_ * length_;
	}
	
  	double getVolume() const {
	  // volume of rectangle = 0
	  return 0;
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {
	  // create new rectangle with new width and height
	  Rectangle r;
	  r.width_ = rec.width_ + getWidth();
	  r.length_ = rec.length_ + getLength();
	  return r;
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {
	  // create new rectangle with new width and height based on operation
	  // new width and height but be greater than or equal to 0
	  Rectangle r;
	  r.width_ = getWidth() - rec.width_;
	  if(r.width_ < 0) r.width_ = 0;
	  r.length_ = getLength() - rec.length_;
	  if(r.length_ < 0) r.length_ = 0;
	  return r;
	} 
	
	T getWidth() const { 
	  return width_;
	}
	
	T getLength() const { 
	  return length_;
	}
private:
	T width_;
        T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {
	  // set circle radius to radius_
	  radius_ = radius;
	}
	
  	double getArea() const{
	  // area of circle = r^2 * PI
	  return radius_*radius_*M_PI;
	}
	
 	double getVolume() const{
	  // volume of circle = 0
	  return 0;
	}
	
  	Circle operator + (const Circle& cir){
	  // create new circle with new radius based on operation
	  Circle c(0);
	  c.radius_ = cir.radius_ + getRadius();
	  return c;
	}
	
	Circle operator - (const Circle& cir){
	  // create new circle with new radius
	  // ensure radius is greater than or equal to 0
	  Circle c(0);
	  c.radius_ = getRadius() - cir.radius_;
	  if(c.radius_ < 0) c.radius_ = 0;
	  return c;
	} 

	double getRadius() const { 
	  return radius_;
	}
	
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {
	  // set sphere's radius to radius_
	  radius_ = radius;
	}

  	double getVolume() const {
	  // volume of sphere = (4/3)*radius^3 * PI
	  return (4.0/3.0)*radius_*radius_*radius_*M_PI;
	}	
	
  	double getArea() const {
	  // area of sphere = 4*PI*radius^2
	  return (4.0)*M_PI*radius_*radius_;
	}

	Sphere operator + (const Sphere& sph) {
	  // create new sphere with new radius based on operation
	  Sphere s(0);
	  s.radius_ = sph.radius_ + getRadius();
	  return s;
	}

	Sphere operator - (const Sphere& sph) {
	  // create new sphere with new radius based on operation
	  // ensure radius is greater than or equal to 0
	  Sphere s(0);
	  s.radius_ = getRadius() - sph.radius_;
	  if(s.radius_ < 0) s.radius_ = 0;
	  return s;
	} 
	
	double getRadius() const {
	  return radius_;
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {
	  // set rectprism's length, width, and height to length_, width_, and height_
	  length_ = length;
	  width_ = width;
	  height_ = height;
	}
	
  	double getVolume() const {
	  // volume of rectprism = l*w*h
	  return length_*width_*height_;
	}
  	
	double getArea() const {
	  // area of rectprism = 2*(l*w + l*h + w*h)
	  return 2* ((length_*width_) + (length_*height_) + (width_*height_));
	}
	
	RectPrism operator + (const RectPrism& rectp){
	  // create new rectprism with updated length, width, and height
	  RectPrism p(0,0,0);
	  p.length_ = rectp.length_ + getLength();
	  p.width_ = rectp.width_ + getWidth();
	  p.height_ = rectp.height_ + getHeight();
	  return p;
	}
	
	RectPrism operator - (const RectPrism& rectp){
	  // create new rectprism with updated length, width, and height
	  // ensure length, width, and height are all greater than or equal to 0
	  RectPrism p(0,0,0);
	  p.length_ = getLength() - rectp.length_;
	  if(p.length_ < 0) p.length_ = 0;
	  p.width_ = getWidth() - rectp.width_;
	  if(p.width_ < 0) p.width_ = 0;
	  p.height_ = getHeight() - rectp.height_;
	  if(p.height_ < 0) p.height_ = 0;
	  return p;
	}	
	
	double getWidth() const { 
	  return width_;
	}
	
	double getLength() const { 
	  return length_;
	}
	
	double getHeight() const { 
	  return height_;
	}
  
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here
  // create list of pointers to shapes
  list<Shape*> list;
  int length;
  string name;
  // read input file
  ifstream ifs (file_name, std::ifstream::in);
  // set number of objects to length
  ifs>>length;
  // iterate through the number of objects in the file
  for(int i = 0; i <length; i++) {
    // for each object set its name
    // find which object it is based on the name
    ifs>>name;
    Shape* curr = NULL;
    // if object is rectangle set the width and height and create new rectangle
    // set pointer curr to the new rectangle
    if(name == "Rectangle") {
      double w;
      double h;
      ifs>>w>>h;
      curr = new Rectangle<double>(w, h);
    }
    // if object is circle set the radius and create new circle
    // set pointer curr to the new circle
    if(name == "Circle") {
      double r;
      ifs>>r;
      curr = new Circle(r);
    }
    // if object is rectprism set the width, length, and height and create new rectprism
    // set pointer curr to the new rectprism
    if(name == "RectPrism") {
      double w;
      double l;
      double h;
      ifs>>w>>l>>h;
      curr = new RectPrism(w, l, h);
    }
    // if object is sphere set the radius and create new sphere
    // set pointer curr to the new sphere
    if(name == "Sphere") {
      double r;
      ifs>>r;
      curr = new Sphere(r);
    }
    // add the pointer to the object from the file to back of our list
    list.push_back(curr);
  }
  // once iterated through all objects in file close and return our list
  ifs.close();
  
  return list;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	// iterate through all objects in list
	// calculate the area for each, if area is larger than max then update max
	int length = shapes.size();
	double temp;
        for(std::list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++) {
	  temp = (*it)->getArea();
	  if(temp > max_area) {
	    max_area = temp;
	  }
	}
	//return max area of all objects in list
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	// iterate through all objects in list
	// calculate volume for each, if volume is larger than max then update max
	int length = shapes.size();
	double temp;
	for(std::list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++) {
	  temp = (*it)->getVolume();
	  if(temp > max_volume) {
	    max_volume = temp;
	  }
	}
	// return max volume of all objects in list
	return max_volume;
}
#endif

