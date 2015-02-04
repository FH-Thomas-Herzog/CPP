#include "Line.h"
using namespace ML;

Line::Line(Point p, int linewidth)
  : Shape(p, linewidth) {
  Register("Line", "Shape");
}

Line::~Line() { /* nothing to do */ }

void Line::InvertInWindow(Window* w) {
   w->DrawLine(p1, p2, lineWidth);
}

#ifdef WITH_SELECTION
void Line::SelectInWindow(Window *w) {
  DrawHandle(w, p1);
  DrawHandle(w, p2);
}
#endif // WITH_SELECTION
