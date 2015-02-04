#include "Rectangle.h"

using namespace ML;

Rectangle::Rectangle(Point p, int lineWidth)
  : Shape(p, lineWidth) {
  Register("Rectangle", "Shape");
}

Rectangle::~Rectangle() { /* nothing to do */ }

void Rectangle::InvertInWindow(Window* w) {
  w->DrawRectangle(p1, p2.x-p1.x, p2.y-p1.y, lineWidth);
}

#ifdef WITH_SELECTION
void Rectangle::SelectInWindow(Window *w) {
  DrawHandle(w, p1);
  DrawHandle(w, p2);
  DrawHandle(w, Point(p1.x, p2.y));
  DrawHandle(w, Point(p2.x, p1.y));
}
#endif
