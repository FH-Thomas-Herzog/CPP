#ifndef OVAL_H
#define OVAL_H

#include <Shape.h>

class Oval : public Shape {
  public:
    Oval(Point p, int lineWidth = 1);
    virtual ~Oval();
    virtual void InvertInWindow(ML::Window *w);
#ifdef WITH_SELECTION
    virtual void SelectInWindow(ML::Window *w);
#endif // WITH_SELECTION
};

#endif // OVAL_H
