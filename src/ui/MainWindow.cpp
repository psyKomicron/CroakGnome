#include "MainWindow.hpp"

namespace Croak::UI
{
    MainWindow::MainWindow(BaseObjectType *base, const Glib::RefPtr<Gtk::Builder>& builder) :
        Gtk::ApplicationWindow(base),
        builder{ builder }
    {
    }
}
