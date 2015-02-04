#ifndef LINE_H
#define LINE_H

#include "Shape.h"

class Line : public Shape {
  public:
    Line(Point p, int linewidth = 1);
    virtual ~Line();
  // overriden methods
    virtual void InvertInWindow(ML::Window *w);
#ifdef WITH_SELECTION
    virtual void SelectInWindow(ML::Window *w);
#endif // WITH_SELECTION
};

#endif // LINE_H
