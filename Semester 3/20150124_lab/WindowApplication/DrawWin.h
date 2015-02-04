#ifndef DRAWWIN_H
#define DRAWWIN_H

#include <MLWindow.h>
#include <MLVector.h>
#include "DrawApp.h"
#ifdef V2
#include "Shape.h"
#endif // V2


class DrawWin : public ML::Window {
  private:
    int curLineWidth, curShapeCommand;
    ML::Vector *shapes;
    DrawApp *app;
#ifdef V2
    Shape *newShape;
#endif
#ifdef WITH_SELECTION
    Shape *selectedShape;
#endif // WITH_SELECTION


  public:
    DrawWin();
    virtual ~DrawWin();

    // overridden methods
    virtual void Redraw();
    virtual void OnMousePressed(Point pos);
    virtual void OnCommand(int commandNr);
#ifdef V2
    virtual void OnMouseMove(Point pos);
    virtual void OnMouseReleased(Point pos);
#endif // V2
};

#endif // DRAWWIN_H
