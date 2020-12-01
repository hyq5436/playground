#ifndef GTKUTILS_H
#define GTKUTILS_H
#include <X11/Xlib.h>


class GtkUtils
{
public:
    GtkUtils();
};
void* create_browser_window();
XID getWindowsHandle(void* pWindow);

#endif // GTKUTILS_H
