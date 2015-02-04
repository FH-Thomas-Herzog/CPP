#include <cassert>
#include "DrawWin.h"
#include "DrawApp.h"
#include "Shape.h"
#include "Line.h"
#include "Rectangle.h"
#include "Oval.h"
using namespace ML;
#ifdef V2
#include <iostream>
using namespace std;
#endif

DrawWin::DrawWin()
    : Window("Draw Window"),
      curLineWidth(1),
      shapes(new Vector()),
      app(dynamic_cast<DrawApp*>(Application::instance))
#ifdef V2
      ,newShape(nullptr)
#endif // V2
#ifdef WITH_SELECTION
      , selectedShape(nullptr)
#endif // WITH_SELECTION
      {

}

DrawWin::~DrawWin() {
 }

void DrawWin::Redraw() {
  }

void DrawWin::OnMousePressed(Point pos) {
}

#ifdef V2
void DrawWin::OnMouseMove(Point pos) {
 
}

void DrawWin::OnMouseReleased(Point pos) {
 
}

#endif // V2

void DrawWin::OnCommand(int commandNr) {

}
