// OSBridge2X11.cpp:                                     MiniLib V.4, 2004
// ----------------
// Bridge to platform specific GUI operating system (Unix X11).
//========================================================================

#include <cstring>
#include <cctype>
using namespace std;

#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <X11/IntrinsicP.h>
#include <X11/CoreP.h>

#include <Xm/Xm.h>
#include <Xm/MainW.h>
#include <Xm/Label.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/CascadeB.h>
#include <Xm/MessageB.h>
#include <Xm/Form.h>
#include <Xm/DrawingA.h>
#include <Xm/ToggleB.h>
#include <Xm/Text.h>

#include "MetaInfo.h"
#include "MLApplication.h"
#include "MLWindow.h"
using namespace ML;

#include "OSBridge.h"


#define MAXSTRING   256
#define MAXINFOLEN  630
#define MENUHEIGHT   30

  //--- fonts defined for Linux in directory /usr/X11R6/lib/X11/fonts ---

#define HELV8  "*-adobe-helvetica-bold-o-normal--8-*"
#define HELV12 "*-adobe-helvetica-bold-o-normal--12-*"
#define HELV24 "*-adobe-helvetica-bold-o-normal--24-*"


  const int cMaxMenuName   =   15;  // maximal length of the menu name
  const int cMaxMenus      =   20;  // maximal number of menus
  const int cMaxCmdName    =   15;  // maximal length of the command name
  const int cMaxCmds       =   30;  // maximal number of commands
  const int cMaxBarHSize   =   MENUHEIGHT;  // menubar size (height)

  enum DrawColor {black, white};
  enum DrawMode  {addMode, invertMode};

  static char *miniFonts[] = { HELV8,    // Helvetica size 8
                               HELV12,   // Helvetica size 12
                               HELV24 }; // Helvetica size 24

  struct WindowPeer {
    Widget       widget;
    Widget       graphicWidget;
    Widget       menuBar;
    Widget       formWidget;
    ::Window     drawArea;
    ::Window     window;
    Display     *display;
    GC           gc;
    int          width, height;
    int          innerWidth, innerHeight;
    XFontStruct *font;
    Atom         delAtom;
  }; // struct

  //--- one menubar structure (e.g., for File, Edit, etc.) ---

  struct MenuDescr {
    Widget  menuPullDown;                    // menubar widget
    char    title[cMaxMenuName];             // menubar title
    char    command[cMaxCmds][cMaxCmdName];  // list of commands
    char    shortCut[cMaxCmds];              // command shortCut
    int     cmdNumb[cMaxCmds];               // command nr. of each menubar
    int     maxCmdNr;                        // actual last command number
  }; // struct


  //--- menubar structure, memory for the array for all windows ---

  struct MenuBarStr {
    char menu[cMaxMenuName];
    char cmd[cMaxCmdName];
    char shortCut;
  }; // struct


  //--- module golbals ---

  static XtAppContext app;

  static Widget topLevel;     // top level widget (application)
  static Widget menuBar;      // bar of the menu
  static Widget mainWidget;

  static int lastMenuBar = 0;
  static int lastMenuCmd = 0;

  static MenuDescr  menuItems [cMaxMenus] = {0};           // menubar structures
  static MenuBarStr menuBarArr[cMaxMenus*cMaxCmds] = {0};  // menubars for all windows
  static ::Window   focusWindow = 0;
  static int        menuBarPos  = 0;


  //=== 1. application utilities ===

  void OSB_InitApplication(char *applName) {
    int   argc = 1;
    char *argv[1] = {applName};
    topLevel = XtAppInitialize(&app, "Application", NULL,
                               0, &argc, argv, NULL, NULL, 0);
    menuBar = XmCreateMenuBar(topLevel, "menuBar", NULL, 0);
  } // OSB_InitApplication

  void OSB_DestroyApplication() {
   XtDestroyApplicationContext(app);
  } // OSB_DestroyApplication


  static int ShortCutCmdNr(char key) {
    char  ch;
    if ( (key < 'a') || (key > 'z') )
      return 0;
    ch = toupper(key);
    for (int i = 0; i < lastMenuBar; i++) {
      for (int j = 0; j < menuItems[i].maxCmdNr; j++) {
        if (menuItems[i].shortCut[j] == ch)
          return menuItems[i].cmdNumb[j];
      } // for
    } // for
    return 0;
  } // ShortCutCmdNr

  void OSB_GetNextEvent(Event &e) {
    XEvent      xe;
    bool        found;
    ML::Window *w;
    WindowPeer  wp;
    XRectangle  clipRect;

    found = false;
    w = 0;
    while (!found) {
      if ( !XtAppPending(app) ) {
        e.kind = idleEvent;
        return;
      } else { // XtAppPending
        XtAppNextEvent(app, &xe);
        XtDispatchEvent(&xe);
        // find affected xe window
        wp.display  =  xe.xany.display;
        wp.window   =  xe.xany.window;
        wp.drawArea =  xe.xany.window;
        w = Application::instance->WindowOf(&wp);

        if (w != 0) {
          e.wp = w->GetWindowPeer();
          clipRect.x = 0;
          clipRect.y = 0;
          if (e.wp) {
            clipRect.width  = e.wp->width;
            clipRect.height = e.wp->height;
            XSetClipRectangles(e.wp->display, e.wp->gc,
                               0, 0, &clipRect, 1, YSorted);
          } // if
        } else {
          e.wp = 0;
        } // else

//### cout << "Event: " << xe.kind << ", window: " << xe.window <<
//###         ", found:" << ((w) ? w->GetWindowPeer()->window : 0) <<
//###         ", focus: " << focusWindow << endl;

        switch (xe.type) {

          case DestroyNotify: {
//### cout << "(DestroyNotify)" << endl;
             if (w != 0) {
               focusWindow = xe.xdestroywindow.window;
               e.kind = quitEvent;
              } // if
            break;
          } // case

          case ButtonPress: {
            if (w == 0)
              break;
//### cout << "(ButtonPress)" << (w->WinDescr())->drawArea <<
//###         "..." << xe.xany.window << endl;
            e.pos.x = xe.xbutton.x;
            e.pos.y = xe.xbutton.y; // -MENUHEIGHT;
            e.kind  = buttonDownEvent;
            found = true;
            break;
          } // case

          case ButtonRelease:  {
            if (w == 0)
              break;
//### cout << "(ButtonRelease)" << (w->WinDescr())->drawArea <<
//###         "..." << xe.xany.window << endl; // HDO
            e.pos.x = xe.xbutton.x;
            e.pos.y = xe.xbutton.y; // -MENUHEIGHT;
            e.kind  = buttonReleaseEvent;
            found = true;
            break;
          } // case

          case MotionNotify: {
//### cout << "(MouseMotion) " << endl;
            if (w == 0)
              break;
            e.pos.x = xe.xbutton.x;
            e.pos.y = xe.xbutton.y;
            e.kind  = mouseMoveEvent;
            found = true;
            break;
          } // case

          case FocusIn: {
//### cout << "(FocusIn: w=" << xe.xfocus.window << ")" << endl;
            if ( (w != 0) && (w->GetWindowPeer() !=0) )
              focusWindow = (w->GetWindowPeer())->window;
            break;
          } // case

          case FocusOut: {
//### cout << "(FocusOut: w=" << xe.xfocus.window << ")" << endl;
            // focusWindow = 0;
            break;
          }// case

          case ClientMessage: {
//### cout << "(ClientMessage)" << endl;
            if (xe.xclient.format == 32)
              Application::instance->OnCommand(xe.xclient.data.l[0]);
            found = true;
            break;
          } // case

          case KeyPress: {
//### cout << "(KeyPress)" << endl;
            KeySym  keySym;
            int     cmd;
            char   *key;
            keySym = XKeycodeToKeysym(xe.xkey.display, xe.xkey.keycode, 0);
            key = XKeysymToString(keySym);
            if (strlen(key) > 1)
              break;
            if (w == 0)
              break;
            if (xe.xkey.state == Mod1Mask) {
              cmd = ShortCutCmdNr(key[0]);
              e.kind = commandEvent;
              e.commandNr = cmd;
              found = (cmd > 0);
            } else if (xe.xkey.state == 0) {
              e.kind = keyEvent;
              e.key = key[0];
              found = true;
            } // else
            break;
          } // break

          case Expose: {
            if (w) {
//### cout << "(Expose: window=" << xe.xany.window <<
//###         ", send=" << xe.xany.send_event <<
//###         ", x=" << xe.xexpose.x << ", y=" << xe.xexpose.y <<
//###         ", w=" << xe.xexpose.width << ", h=" <<  xe.xexpose.height << ")" << endl;
              focusWindow = xe.xexpose.window;
              clipRect.x = xe.xexpose.x;
              clipRect.y = xe.xexpose.y;
              clipRect.width = xe.xexpose.width;
              clipRect.height = xe.xexpose.height;
              if (xe.xany.send_event) {
                XClearArea(e.wp->display, e.wp->window,
                           clipRect.x, clipRect.y, clipRect.width,
                           clipRect.height, false);
              } // if
              XSetClipRectangles(e.wp->display, e.wp->gc,
                                 0, 0, &clipRect, 1, YSorted);
              e.kind = redrawEvent;
              found = true;
            } else {
              Iterator *it = Application::instance->NewOpenWindowsIterator();
              ML::Object *o;
              ML::Window *w;
              while ((o = it->Next()) != 0) {
                w = (ML::Window*)o;
                w->Update();
              } // while
              delete it;
            } // else
            break;
          } // case

          case ConfigureNotify: {
//### cout << "(ConfigureNotify)" << endl;
            // get focused window
            wp.window   = focusWindow;
            wp.drawArea = focusWindow;
            w = Application::instance->WindowOf(&wp);
//### cout << "(Configure: wnd=" << xe.xconfigure.window <<
//###         ", x=" << xe.xconfigure.x << ", y=" << xe.xconfigure.y <<
//###         ", w=" << xe.xconfigure.width << ",h =" <<  xe.xconfigure.height << ")" << endl;
            if (w) {
               // get dimension of focus window and send eResize message
              XWindowAttributes attr;
              e.wp = w->GetWindowPeer();
              XGetWindowAttributes(e.wp->display, e.wp->window, &attr);
              e.wp->width  = attr.width;;
              e.wp->height = attr.height;
              XGetWindowAttributes(e.wp->display, e.wp->drawArea, &attr);
              e.wp->innerWidth  = attr.width;
              e.wp->innerHeight = attr.height; // - MENUHEIGHT;
              e.kind = resizeEvent;
              found = true;
            } // if
            break;
          } // case

          default : {
//### cout << "(?)" << endl;
            break;
          } // default

        } // switch
      } // else
    } // while

//### cout << "==> e.msg=" << (int)e.msg << endl;

  } // OSB_GetNextEvent


  //=== 2. menu management utilitiess ===

  void CommandCallBack(Widget widget, XtPointer client, XtPointer call) {
    static XEvent   xe;
    ::Window        window  = XtWindow(topLevel);
    Display        *display = XtDisplay(topLevel);
    xe.xclient.display = display;
    xe.xclient.window  = window;
    xe.xclient.type    = ClientMessage;
    xe.xclient.format  = 32;
    xe.xclient.message_type = XInternAtom(XtDisplay(topLevel), "MiniLib", false);
    xe.xclient.data.l[0] = (long) client;
    XSendEvent(display, XtWindow(topLevel), false, 0, &xe);
  } // CommandCallBack

  int InsertMenu(Widget widget, char *title, char *cmd, char shortCut) {
    Widget button;
    Widget subWidget;
    Arg    args[25];
    int    menuPos;
    int    cmdPos;
    int    n, i;
    // look for title
    i = 0;
    while ( (i < lastMenuBar) && (i < cMaxMenus) &&
            (strcmp(menuItems[i].title, title) != 0) ) {
      i++;
    } // while
    if (strcmp(menuItems[i].title, title) != 0) { // title not found
      i = ++lastMenuBar;  // number of menu will be increased
      menuItems[i].menuPullDown = XmCreatePulldownMenu(widget, title, NULL, 0);
      strcpy(menuItems[i].title, title);
      menuItems[i].maxCmdNr  = 0;  // actually no commands inserted
      n = 0;
      XtSetArg(args[n], XmNsubMenuId, menuItems[i].menuPullDown); // set subMenuID
      n++;
      subWidget = XtCreateManagedWidget(title, xmCascadeButtonWidgetClass,
                                        widget, args, n);
    } // if
    menuPos = i;  // remember menu position
    cmdPos = ++menuItems[menuPos].maxCmdNr; // increase position of new command

    n = 0;
    XtSetArg(args[n], XmNmnemonic, shortCut); // set short cut option
    n++;
    XtSetArg(args[n], XmNlabelString,
             XmStringCreateLtoR(cmd, XmSTRING_DEFAULT_CHARSET)); // set command label
    n++;
    // insert command values
    button = XtCreateManagedWidget(cmd, xmPushButtonWidgetClass,
                                   menuItems[menuPos].menuPullDown, args, n);
    // call callback function (key is lastMenuCmd)
    XtAddCallback(button, XmNactivateCallback, CommandCallBack,
                  (XtPointer)lastMenuCmd);
    //turn menu option on
    XtSetSensitive(button, True);
    // insert title/cmd info into stucture
    strcpy(menuItems[menuPos].command [cmdPos],   cmd);
           menuItems[menuPos].shortCut[cmdPos] = shortCut;
           menuItems[menuPos].cmdNumb [cmdPos] = lastMenuCmd;
    lastMenuCmd++;
    return lastMenuCmd - 1;
  } // InsertMenu

  int OSB_NewMenuCommand(const char *menu, const char *cmd, char shortCut) {
    int commandValue = InsertMenu(menuBar,
                                  const_cast<char*>(menu),
                                  const_cast<char*>(cmd), shortCut);
    // remember menuCommand insert values
    strcpy(menuBarArr[menuBarPos].menu,      menu);
    strcpy(menuBarArr[menuBarPos].cmd,       cmd);
           menuBarArr[menuBarPos].shortCut = shortCut;
    menuBarPos++;
    return commandValue;
  } // OSB_NewMenuCommand

  void OSB_InstallMenuBar() {
    XtRealizeWidget(topLevel);
  } // OSB_InstallMenuBar

  void OSB_RemoveMenuBar() {
     XtDestroyWidget(menuBar);
  } // OSB_RemoveMenuBar


  //=== 3. window management utilities ===

  void OSB_GetMouseState(const WindowPeer *wp,
                         bool &buttonPressed, Point &pos) {
    ::Window     root,   child;
    int          rootX,  rootY;    // root  window position
    int          childX, childY;   // child window position
    unsigned int buttonState;
    if (XQueryPointer(wp->display, wp->drawArea, &root, &child,
        &rootX, &rootY, &childX, &childY, &buttonState)) {
      // position is exact position of active window
      pos.x = childX;
      pos.y = childY; // - MENUHEIGHT;
    } else {
      pos.x = rootX;
      pos.y = rootY;
    } // else
    buttonPressed = (bool)(buttonState & Button1Mask);
  } // OSB_GetMouseState

  void OSB_ShowMessageWindow(const char *winTitle, const char *message) {
     Arg    args[25];
     Widget messageWidget;
     int    n = 0;
     XtSetArg(args[n], XtNx,      300);
     n++;
     XtSetArg(args[n], XtNy,      300);
     n++;
     XtSetArg(args[n], XtNwidth,  400);
     n++;
     XtSetArg(args[n], XtNheight, 100);
     n++;
     XtSetArg(args[n], XmNmessageString,
              XmStringCreateLtoR(const_cast<char*>(message),
              XmSTRING_DEFAULT_CHARSET));
     n++;
     messageWidget = XmCreateMessageDialog(topLevel, const_cast<char*>(winTitle),
                                           args, n);
     // help button will not be used
     XtUnmanageChild(XmMessageBoxGetChild(messageWidget, XmDIALOG_HELP_BUTTON));
     XtManageChild(messageWidget);
  } // OSB_ShowMessageWindow

  bool OSB_EqualWindowPeers(const WindowPeer *wp1, const WindowPeer *wp2) {
    return ( (wp1 == wp2) ||
           ( (wp1 != 0) && (wp2 != 0) && (wp1->window   == wp2->window)   ) ||
           ( (wp1 != 0) && (wp2 != 0) && (wp1->drawArea == wp2->drawArea) ));
  } // OSB_EqualWindowPeers

  void OSB_CreateNewWindow(char *title, WindowPeer *&wp) {
    Arg                 args[30];
    XWindowAttributes   attr;
    Font                fontID;
    Widget              shell;
    int                 n, i;
    wp = new WindowPeer;
    n = 0;
    XtSetArg(args[n], XtNwidth,  600); n++;
    XtSetArg(args[n], XtNheight, 400); n++;
    shell = XtCreatePopupShell(title, transientShellWidgetClass,
                               topLevel, args, n);
    // put the popup shell of popup out
    XtPopup(shell, XtGrabNone);
    mainWidget = XmCreateMainWindow(shell, title, NULL, 0);
    XtManageChild(mainWidget);
    wp->widget = shell;
    wp->widget->core.widget_class->core_class.visible_interest = true;
    // widget for graphical representation
    n = 0;
    XtSetArg(args[n], XtNx, 0);
    n++;
    XtSetArg(args[n], XtNy, MENUHEIGHT);
    n++;
    wp->graphicWidget =  XtCreateManagedWidget("Graphic", xmDrawingAreaWidgetClass,
                                                mainWidget, args, n);
    n = 0;
    XtSetArg(args[n], XtNwidth,  600);
    n++;
    XtSetArg(args[n], XtNheight, MENUHEIGHT);
    n++;

    // remember window and display
    wp->window   = XtWindow(mainWidget);
    wp->drawArea = XtWindow(wp->graphicWidget);
    wp->display  = XtDisplay(wp->graphicWidget);
    // create a graphic context
    wp->gc       = XCreateGC(wp->display, wp->window, 0, NULL);
    // set right font (it is fixed by cMenuBarFont)
    fontID       = XLoadFont(wp->display, miniFonts[0]);
    wp->font     = XQueryFont(wp->display, fontID);

    //insert main menu bar
    wp->menuBar = XmCreateMenuBar(mainWidget, "menuBar", args, n);
    lastMenuBar = 0;
    lastMenuCmd = 0L;
    for (i = 0; i < menuBarPos; i++) {
      InsertMenu(wp->menuBar, menuBarArr[i].menu,
                 menuBarArr[i].cmd,  menuBarArr[i].shortCut);
    } // for
    XtManageChild(wp->menuBar);
    XtManageChild(wp->graphicWidget);

    //XtRealizeWidget(wp->graphicWidget);
    XtRealizeWidget(mainWidget);

    //Remember dimension
    XGetWindowAttributes(wp->display, wp->window, &attr);
    wp->width       = attr.width;
    wp->height      = attr.height;
    XGetWindowAttributes(wp->display, wp->drawArea, &attr);
    wp->innerWidth  = attr.width;
    wp->innerHeight = attr.height;// - MENUHEIGHT;
  } // OSB_CreateNewWindow

  void OSB_DestroyOldWindow(WindowPeer *&wp) {
    if (wp) {
      // destroy popup => popdown
      XtPopdown(wp->widget);
      // free the resources
      XFreeGC(wp->display, wp->gc);
      // destroy the widget itself
      XtDestroyWidget(wp->widget);
      delete wp;
    } // if
    wp = 0;
  } // OSB_DestroyOldWindow

  WindowPeer *TempWindowPeer() {
    const int         wpArrMax = 50;
    static WindowPeer wpArr[wpArrMax];
    static int        wpArrNextFree = 0;
    wpArrNextFree = (wpArrNextFree + 1) % wpArrMax;
    return &(wpArr[wpArrNextFree]);
  } // TempWindowPeer

  WindowPeer *OSB_ActiveWindowPeer() {
    WindowPeer *tmpWindow = TempWindowPeer();
    tmpWindow->window   = focusWindow;
    tmpWindow->drawArea = focusWindow;
    return tmpWindow;
  } // OSB_ActiveWindowPeer

  bool OSB_IsVisible(const WindowPeer *wp) {
    return (wp->widget->core.visible);
  } // OSB_IsVisible

  void OSB_EraseContent(const WindowPeer *wp) {
   XClearArea(wp->display, wp->drawArea, 0, 0, wp->width, wp->height, false);
  } // OSB_EraseContent

  void OSB_GetContent(const WindowPeer *wp, Point &topLeft, int &w, int &h) {
    topLeft.x = 0;
    topLeft.y = 0;
    w = wp->innerWidth;
    h = wp->innerHeight;
  } // OSB_GetContent

  void OSB_InvalRect(const WindowPeer *wp, Point topLeft, int w, int h) {
    static XEvent xe;
    xe.xexpose.type       = Expose;
    xe.xexpose.send_event = false;
    xe.xexpose.display    = wp->display;
    xe.xexpose.window     = wp->window;
    xe.xexpose.x          = topLeft.x;
    xe.xexpose.y          = topLeft.y; // + MENUHEIGHT
    xe.xexpose.width      = w;
    xe.xexpose.height     = h;
    xe.xexpose.count      = 0;
    XSendEvent(wp->display, wp->window, false, 0, &xe);
  } // OSB_InvalRect


  //=== 4. drawing utilties ===

  static int XWindowsColorOf(DrawColor color) {
    switch (color) {
      case white:
        return 1;
      case black:
        return 0;
      default:
        return 0;
    } // switch
  } // XWindowsColorOf

  void OSB_DrawDot(const WindowPeer *wp, Point pos) {
    DrawMode        mode = invertMode;
    GC              gc;
    Display        *display;
    ::Window        root;
    Arg             args[30];
    Pixel           bg;
    XGCValues       values;
    unsigned long   mask;
    int             n;
    values.line_width = 1;
    if (mode == invertMode) {
      // get graphic widget values (background color)
      n = 0;
      XtSetArg(args[n], XmNbackground, &bg);
      n++;
      XtGetValues(wp->graphicWidget, args, n);
      values.foreground = XWindowsColorOf(black) ^ bg;
      values.function   = GXxor;
      mask = GCFunction | GCForeground | GCLineWidth;
    } else { // mode == addMode
      values.foreground = XWindowsColorOf(black);
      mask = GCForeground | GCLineWidth;
    } // if
    // create display and gc
    display = XtDisplay(wp->graphicWidget);
    root    = RootWindowOfScreen(XtScreen(wp->graphicWidget));
    gc      = XCreateGC(display, root, mask, &values);
    // draw oval
    XDrawPoint(display, XtWindow(wp->graphicWidget), gc,
               pos.x, pos.y /* + MENUHEIGHT */ );
    XFreeGC(display, gc);
  } // OSB_DrawDot

  void OSB_DrawLine(const WindowPeer *wp,
                    Point start, Point end, int t) {
    DrawMode        mode = invertMode;
    GC              gc;
    Display        *display;
    ::Window        root;
    Arg             args[30];
    Pixel           bg;
    XGCValues       values;
    unsigned long   mask;
    int             n;
    values.line_width = t;
    if (mode == invertMode) {
      // get graphic widget values (background color)
      n = 0;
      XtSetArg(args[n], XmNbackground, &bg);
      n++;
      XtGetValues(wp->graphicWidget, args, n);
      values.foreground = XWindowsColorOf(black) ^ bg;
      values.function   = GXxor;
      mask =   GCFunction | GCForeground | GCLineWidth;
    } else { // mode == addMode
     values.foreground = XWindowsColorOf(black);
     mask = GCForeground | GCLineWidth;
    } // if
    // create display and gc
    display = XtDisplay(wp->graphicWidget);
    root    = RootWindowOfScreen(XtScreen(wp->graphicWidget));
    gc      = XCreateGC(wp->display, root, mask, &values);
    // draw line
    XDrawLine(display, XtWindow(wp->graphicWidget), gc,
              start.x, start.y /* + MENUHEIGHT */ ,
              end.x,   end.y);
    XFreeGC(display, gc);
 } // OSB_DrawLine

  void OSB_DrawRectangle(const WindowPeer *wp,
                         Point topLeft, int w, int h, int t, bool fill) {
    DrawMode        mode = invertMode;
    GC              gc;
    Display        *display;
    ::Window        root;
    Arg             args[30];
    Pixel           bg;
    XGCValues       values;
    unsigned long   mask;
    int             n;
    values.line_width = t;
    if (mode == invertMode) {
      // get graphic widget values (background color)
      n = 0;
      XtSetArg(args[n], XmNbackground, &bg);
      n++;
      XtGetValues(wp->graphicWidget, args, n);
      values.foreground = XWindowsColorOf(black) ^ bg;
      values.function   = GXxor;
      mask =   GCFunction | GCForeground | GCLineWidth;
    } else { // mode == addMode
      values.foreground = XWindowsColorOf(black);
      mask = GCForeground | GCLineWidth;
    } // if
    // create display and gc
    display = XtDisplay(wp->graphicWidget);
    root    = RootWindowOfScreen(XtScreen(wp->graphicWidget));
    gc      = XCreateGC(display, root, mask, &values);
    // catch negative width and height
    if (w < 0) {
      w = -w;
      topLeft.x -= w;
    } // if
    if (h < 0) {
      h = -h;
      topLeft.y -= h;
    } // if
    if (fill)
      XFillRectangle(display, XtWindow(wp->graphicWidget), gc,
                     topLeft.x, topLeft.y /* + MENUHEIGHT */ ,
                     w, h);
    else
      XDrawRectangle(display, XtWindow(wp->graphicWidget), gc,
                     topLeft.x, topLeft.y /* + MENUHEIGHT */ ,
                     w, h);
    XFreeGC(display, gc);
  } // OSB_DrawRectangle

  void OSB_DrawOval(const WindowPeer *wp,
                    Point topLeft, int w, int h, int t, bool fill) {
    DrawMode        mode = invertMode;
    GC              gc;
    Display        *display;
    ::Window        root;
    Arg             args[30];
    Pixel           bg;
    XGCValues       values;
    unsigned long   mask;
    int             n;
    values.line_width = 1;
    if (mode == invertMode) {
      // get graphic widget values (background color)
      n = 0;
      XtSetArg(args[n], XmNbackground, &bg); n++;
      XtGetValues(wp->graphicWidget, args, n);
      values.foreground = XWindowsColorOf(black) ^ bg;
      values.function = GXxor;
      mask = GCFunction | GCForeground | GCLineWidth;
    } else { // mode == addMode
      values.foreground = XWindowsColorOf(black);
      mask = GCForeground | GCLineWidth;
    } // if
    // create display and gc
    display = XtDisplay(wp->graphicWidget);
    root = RootWindowOfScreen(XtScreen(wp->graphicWidget));
    gc =  XCreateGC(display, root, mask, &values);
    //catch negative width and height
    if (w < 0) {
      w = -w;
      topLeft.x -= w;
    } // if
    if (h < 0) {
      h = -h;
      topLeft.y -= h;
    } // if
    if (fill)
      XFillArc(display, XtWindow(wp->graphicWidget), gc,
               topLeft.x, topLeft.y /* + MENUHEIGHT */ ,
         w, h, 0, 23040);
    else
      XDrawArc(display, XtWindow(wp->graphicWidget), gc,
               topLeft.x, topLeft.y /* + MENUHEIGHT */ ,
         w, h, 0, 23040);
    XFreeGC(display, gc);
  } // OSB_DrawOval

  void OSB_DrawString(const WindowPeer *wp,
                      Point pos, const char *str, int size) {
    GC            gc;
    Display      *display;
    ::Window      root;
    XGCValues     values;
    Font          fontID;
    unsigned long mask;
    // create display and gc
    display = XtDisplay(wp->graphicWidget);
    root    = RootWindowOfScreen(XtScreen(wp->graphicWidget));
    gc      = XCreateGC(display, root, mask, &values);
    // set font (it is defined in cMenuBarFont)
    if (size == 1) {
      fontID = XLoadFont(display, miniFonts[0]);
    } else if (size == 2) {
      fontID = XLoadFont(display, miniFonts[1]);
    } else {
      fontID = XLoadFont(display, miniFonts[2]);
    } // if
    values.foreground = 0;  // black
    values.background = 1;  // white
    values.font       = fontID;
    mask = GCFont | GCForeground | GCBackground;
    // draw text
    XDrawString(display, XtWindow(wp->graphicWidget), gc,
                pos.x, pos.y /* + MENUHEIGHT */ ,
                str, strlen(str));
    XUnloadFont(display, fontID);
    XFreeGC(display, gc);
  } // OSB_DrawString


//========================================================================
// end of file OSBridge2X11.cpp
