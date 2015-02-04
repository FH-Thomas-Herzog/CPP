#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <Shape.h>


class Rectangle : public Shape {
  public:
    Rectangle(Point p, int lineWidth = 1);
    virtual ~Rectangle();
    virtual void InvertInWindow(ML::Window *w);
#ifdef WITH_SELECTION
    virtual void SelectInWindow(ML::Window *w);
#endif // WITH_SELECTION
};

#endif // RECTANGLE_H
