#include "Shape.h"

using namespace std;
using namespace ML;

Shape::Shape(Point p, int lineWidth)
  : p1(p), p2(p), lineWidth(lineWidth) {
  Register("Shape", "Object");
}

Shape::~Shape() { /* nothing to do */ }

void Shape::MoveEnd(ML::Window* w, Point p) {
  if (p.x != p2.x || p.y != p2.y) {
    InvertInWindow(w); // delete
    p2 = p;
    InvertInWindow(w); // redraw
  }
}

static bool Between(int q, int a, int b) {
  return (a <= q && q <= b) || (b <= q && q <= a);
}

#ifdef WITH_SELECTION
bool Shape::HitBy(Point p) {
  bool hit = Between(p.x, p1.x, p2.x) && Between(p.y, p1.y, p2.y);
  cout << "shape hit == " << boolalpha << hit << endl;
  return hit;
}

void Shape::DeselectInWindow(Window *w) {
  SelectInWindow(w);
}

void Shape::DrawHandle(ML::Window *w, Point center, int width) {
  w->DrawRectangle(Point(center.x-width, center.y-width), width*2+1, width*2+1);
}
#endif // WITH_SELECTION
