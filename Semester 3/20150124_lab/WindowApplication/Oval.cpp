#include "Oval.h"

using namespace ML;

Oval::Oval(Point p, int lineWidth)
  : Shape(p, lineWidth) {
  Register("Oval", "Shape");
}

Oval::~Oval() { /* nothing to do */ }


void Oval::InvertInWindow(ML::Window* w) {
  w->DrawOval(p1, p2.x - p1.x, p2.y - p1.y, lineWidth);
}

#ifdef WITH_SELECTION
void Oval::SelectInWindow(Window *w) {
  DrawHandle(w, p1);
  DrawHandle(w, p2);
  DrawHandle(w, Point(p1.x, p2.y));
  DrawHandle(w, Point(p2.x, p1.y));
}
#endif // WITH_SELECTION
