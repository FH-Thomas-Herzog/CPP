#ifndef SHAPE_H
#define SHAPE_H

#include <OSBridge.h>
#include <MLWindow.h>
#include <MLObject.h>


class Shape : public ML::Object {
  protected:
    Shape(Point p, int lineWidth = 1);

  public:
    Point p1, p2;
    int lineWidth;

    virtual ~Shape();
  // new methods
    virtual void InvertInWindow(ML::Window *w) = 0;
    virtual void MoveEnd(ML::Window *w, Point p);
#ifdef WITH_SELECTION
    virtual bool HitBy(Point p);
    virtual void SelectInWindow(ML::Window *w) = 0;
    virtual void DeselectInWindow(ML::Window *w);
    virtual void DrawHandle(ML::Window *w, Point center, int width=2);
#endif // WITH_SELECTION
};

#endif // SHAPE_H
