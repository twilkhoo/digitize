#include "xwindow.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

Xwindow::Xwindow(int width, int height) {
  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), BlackPixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix =
      XCreatePixmap(d, w, width, height, DefaultDepth(d, DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0, (XGCValues*)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[7][15] = {"white",     "black",         "firebrick",
                            "darkgreen", "rebeccapurple", "dimgrey", "darkorange"};

  cmap = DefaultColormap(d, DefaultScreen(d));
  for (int i = 0; i < 6; ++i) {
    XParseColor(d, cmap, color_vals[i], &xcolour);
    XAllocColor(d, cmap, &xcolour);
    colours[i] = xcolour.pixel;
  }

  XSetForeground(d, gc, colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
  hints.height = hints.base_height = hints.min_height = hints.max_height =
      height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d, True);

  usleep(1000);

  // Make sure we don't race against the Window being shown
  XEvent ev;
  while (1) {
    XNextEvent(d, &ev);
    if (ev.type == Expose) break;
  }
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg, int colour) {
  int length = msg.length();
  char str[100] = {0};

  for (int i = 0; i < length; i++) {
    str[i] = msg.c_str()[i];
  }

  XSetForeground(d, gc, colours[colour]);
  XTextItem ti = {str, length, 0, None};
  XDrawText(d, w, gc, x, y, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::showAvailableFonts() {
  int count;
  char** fnts = XListFonts(d, "*", 10000, &count);

  for (int i = 0; i < count; ++i) cout << fnts[i] << endl;
}
