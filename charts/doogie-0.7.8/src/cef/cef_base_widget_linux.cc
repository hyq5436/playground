#include "cef/cef_base_widget.h"
#include "cef/cef_embed_window_linux.h"

#include <X11/Xlib.h>
#include "gtk_utils.h"

namespace doogie {

void CefBaseWidget::InitWindowInfo() {
#if 0
    void *pWin = create_browser_window();
    XID t = getWindowsHandle(pWin);
    WId wid = (WId) t;
    QWindow* win = QWindow::fromWinId(wid);

    window_info_.SetAsChild((CefWindowHandle) wid,
                            CefRect(0, 0, width(), height()));

#else
    auto win = new CefEmbedWindow(this);
    window_info_.SetAsChild((CefWindowHandle) win->winId(),
                            CefRect(0, 0, width(), height()));
#endif

    override_widget_ = QWidget::createWindowContainer(win, this);
    // We need to remove ourselves if we're still around when this is
    //  destroyed
    connect(override_widget_, &QWidget::destroyed, this, [=](QObject*) {
       deleteLater();
    });
}

void CefBaseWidget::ForwardKeyboardEventsFrom(CefRefPtr<CefHandler> handler) {
  // See cef_base_widget_win's version of this for a more in-depth discussion,
  //  but basically this sends the same key event the browser gets but has no
  //  way right now of cancelling the browsre version when it's handled.
  Window win_id = override_widget_->winId();
  handler->SetPreKeyCallback([=](const CefKeyEvent& event,
                                 CefEventHandle os_event,
                                 bool*) {
    if (os_event && IsForwardableKeyEvent(event)) {
      os_event->xkey.window = win_id;
      XSendEvent(cef_get_xdisplay(), win_id, true, NoEventMask, os_event);
    }
    return false;
  });
}

Window GetChild(Window parent) {
    auto xdisplay = cef_get_xdisplay();
    Window root_ret;
    Window parent_ret;
    Window* children_ret;
    unsigned int child_count_ret;
    auto status = XQueryTree(xdisplay, parent, &root_ret,
                             &parent_ret, &children_ret, &child_count_ret);
    Window ret = 0;
    if (status != 0 && child_count_ret > 0) {
      ret = children_ret[0];
      XFree(children_ret);
    }
    return ret;
}

void CefBaseWidget::UpdateSize() {
    auto child = GetChild(window_info_.parent_window);
    if (child > 0) {
        override_widget_->resize(width(), height());
        auto xdisplay = cef_get_xdisplay();
        XWindowChanges changes = {};
        changes.x = 0;
        changes.y = 0;
        changes.width = width();
        changes.height = height();

        qDebug() << "CefBaseWidget UpdateSize" << changes.width;

        XConfigureWindow(xdisplay,
                         child,
                         CWX | CWY | CWHeight | CWWidth,
                         &changes);
    }
}

}  // namespace doogie
