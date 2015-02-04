#ifndef DRAWAPP_H
#define DRAWAPP_H

#include <MLApplication.h>


class DrawApp : public ML::Application {
  public:

    static const int NR_OF_LINE_WIDTHS = 5;
    int lineCmd, rectCmd, ovalCmd, *lineWidthCmds;

    DrawApp();
    virtual ~DrawApp();

    // override methods
    virtual void OpenNewWindow();
    virtual void BuildMenus();
};

#endif // DRAWAPP_H
